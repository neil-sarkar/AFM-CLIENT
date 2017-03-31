/*
	This file is based off of ATMEL's OPEN SOURCE software SAM-BA 3.1.4
*/
//Should technically make this compatible with other MCUs for futureproofing.
//merge/morph with serial_port sometime

#include "firmware_updater.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QElapsedTimer>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QList>

FirmwareUpdater::FirmwareUpdater(QObject *parent) : QObject(parent) {
	m_portname = "";
	m_baudrate = 0;
	m_serial = new QSerialPort(this);
	m_isboot = false;
}

void FirmwareUpdater::entered_bootloader() {
	m_isboot = true;
}

void FirmwareUpdater::update_firmware (QString mcu_bin) {
	m_mcu_bin = mcu_bin;

	if (QString::compare(m_mcu_bin , "") == 0){
		emit push_to_AFM(QString("No binary file provided. Please click \"Choose Firmware\" button first."));
		return;
	}

	if (!m_isboot){
		emit push_to_AFM(QString("Not in bootloader. Please click \"Enter Bootloader\" button first."));
		return;
	}

    stop_current_serial();

    emit push_to_AFM(QString("Starting FW Reprogram..."));

    if (!open()){
        qDebug() << "Could not OPEN connection.";
        if (m_serial->isOpen())
    		close();
    	emit push_to_AFM(QString("Connection could not be acquired.  Try again."));
    	return;
    }

    check_device_ID(CIRD_REG_ADDR);

    load_file(FLASH_PATH);
    if (!write_applet(APPLET_CODE_ADDR, &m_bin_buf)){
    	qDebug() << "Could not UPLOAD applet.";
    	if (m_serial->isOpen())
    		close();
    	emit push_to_AFM(QString("Could not UPLOAD utility applet"));
    	return;
    }

    quint32 args [] = {0x00000001, 5};

    if (run_applet(0, args, 2)){
    	check_mail();    	
    }
    else {
    	emit push_to_AFM(QString("Could not RUN utility applet"));
    	return;
    }

    if (!run_applet(1, args, 0)){
    	qDebug() << "Applet ERASE failed.";
    	if (m_serial->isOpen())
    		close();
    	emit push_to_AFM(QString("Utility applet ERASE Failed"));
    	return;
    }

    qDebug() << "Erased old firmware...";
    emit push_to_AFM(QString("Erased old firmware..."));

    if (!write_to_flash()){
		qDebug() << "Applet WRITE failed.";
    	if (m_serial->isOpen())
    		close();
    	emit push_to_AFM(QString("Writing firmware failed"));
    	return;
    }

    quint32 gpnvm [] = {1 , 1};

    if (!run_applet(6, gpnvm, 2)){
    	qDebug() << "Applet GPVM failed.";
    	if (m_serial->isOpen())
    		close();
    	emit push_to_AFM(QString("Could not set to boot from flash"));
    	return;
    }

    if (!serial_write_word(0x400E1800, 0xA5000001)){
    	qDebug() << "Soft Reset failed.";
    	if (m_serial->isOpen())
    		close();
    	emit push_to_AFM(QString("Could not software reset"));
    	return;
    }

    if (m_serial->isOpen()){
		close();
    }

    emit push_to_AFM(QString("Finished programming. Restart NGAUGE if necessary."));
    emit start_timer();
}

FirmwareUpdater::~FirmwareUpdater() {
	close();
}

QString FirmwareUpdater::get_serial_port_name() {
	QString port = "";
    QList <QSerialPortInfo> portList;
	QSerialPortInfo info;

    portList = QSerialPortInfo::availablePorts();

	if (!portList.isEmpty()){
        for (int i = 0; i < portList.size(); i++){
            info = portList.at(i);
            if (info.isValid()){
                port = info.portName();
                qDebug() << "Portname: "<< port;
                if (!port.contains("COM") && !port.contains("usbmodem")){
                    port = "";
                }
                else {
                  break;
                }
            }
            //else throw error
            else {
                emit to_console(QString("The Portname is invalid."));
            }
        }
	}// else throw error
	else {
        emit to_console(QString("There are no ports."));
	}
	return port;
}

void FirmwareUpdater::stop_current_serial(){
	emit stop_timer();
	emit close_conn();
}

bool FirmwareUpdater::open(){
	m_portname = get_serial_port_name();

	if (m_portname.isEmpty()){
		qDebug() << "No Ports found.";
		return false;
	}

	m_serial->setPortName(m_portname);
	m_serial->setBaudRate(115200);
	m_serial->setDataBits(QSerialPort::Data8);
	m_serial->setParity(QSerialPort::NoParity);
	m_serial->setStopBits(QSerialPort::OneStop);
	m_serial->setFlowControl(QSerialPort::NoFlowControl);

	if (m_serial->open(QIODevice::ReadWrite))
	{
		// resync in case some data was already sent to monitor:
		// send a single '#' and ignore response
		serial_write(QString("#")); //import
		serial_read(); //import

		// switch to binary mode
		serial_write(QString("N#"));
		QString resp(QString::fromLatin1(serial_read(2)));
		if (resp == "\n\r")
		{
			//opened connection
			emit to_console(QString("Connection opened."));
			qDebug() << "Connection Opened.";
			return true;
		}
		else
		{
			//couldnot switch binary
			emit to_console(QString("Swap to binary mode failed."));
			qDebug() << "Swap to binary mode failed.";
			return false;
		}
	}
	else
	{
		//couldn't open port
		emit to_console(QString("Opening port failed. (Denied)"));
		qDebug() << "Could not acquire port.";
		//qDebug() << m_serial->error() ;
		//qDebug() << m_serial->errorString().toLocal8Bit().constData() ;
		return false;
	}
	//emit start_timer();
}

void FirmwareUpdater::serial_write(const QString &str)
{
	QByteArray data = str.toLocal8Bit();
	m_serial->write(data.constData(), data.length());
	m_serial->waitForBytesWritten(10);
}

void FirmwareUpdater::serial_write(const QByteArray &data)
{
	m_serial->write(data.constData(), data.length());
	m_serial->waitForBytesWritten(10);
}

QByteArray FirmwareUpdater::serial_read(int minBytes, int timeout /*defualt 10*/)
{
	QByteArray resp;
    QElapsedTimer timer;

	timer.start();
	do {
		if (timeout > 0 && (timer.elapsed() >= timeout))
			break;
		m_serial->waitForReadyRead(10);
		if (m_serial->bytesAvailable())
			resp.append(m_serial->readAll());
	} while (resp.length() < minBytes);

	return resp;
}

bool FirmwareUpdater::load_file (const QString &file_path) {
    QFile file(file_path);

	if (!file.open(QIODevice::ReadOnly))
	{
		m_bin_buf.clear();
		qDebug() << "Local BIN file could not be opened.";
		return false;
	}
	qDebug() << "The file has been put in the coconut." ;

	m_bin_buf = file.readAll();

	qDebug() << "Bytearray size: "<< m_bin_buf.length();

	file.close();

	return true;
}

bool FirmwareUpdater::write_applet (const quint32 &address, QByteArray *data) {
	if (!m_serial->isOpen())
		return false;

	int length = data->length();
	int offset = 0;

	//qDebug() << QString().sprintf("S%x#", address + offset);
	while (length > 0)
	{
		int chunkSize = length > MAX_BUF_SIZE ? MAX_BUF_SIZE : length;
		serial_write(QString().sprintf("S%x,%x#", address + offset, chunkSize));
		serial_write(data->mid(offset, chunkSize));
		offset += chunkSize;
		length -= chunkSize;
	}

	return true;
}

bool FirmwareUpdater::check_device_ID(const quint32 &address) {
	bool device_good = false;

	if (!m_serial->isOpen())
		return false;

	serial_write(QString().sprintf("w%x,#", address));

	QByteArray resp = serial_read(4);
	quint32 buf = (((quint8)resp[3]) << 24) + (((quint8)resp[2]) << 16) + (((quint8)resp[1]) << 8) + ((quint8)resp[0]);
	quint8 arch = (buf >> 20) & 0xff;

	if (!(arch < 0x10 || arch > 0x13)){
		device_good = true;
		qDebug() << "Device is of SAMV7 Architecture.";
	}
	else{
		qDebug() << "Device is not SAMV7 conformant.";
	}

	return device_good;
}

bool FirmwareUpdater::run_applet(int cmd, quint32 *args, int length) {
	int mbxOffset = 0;
    int iterations = length;

    //qDebug () << iterations;

	serial_write_word(APPLET_MAIL_ADDR + mbxOffset, cmd);
	mbxOffset += 4;
	serial_write_word(APPLET_MAIL_ADDR + mbxOffset, 0xffffffff);
	mbxOffset += 4;

    for (int i = 0; i < iterations; i++) {
		serial_write_word(APPLET_MAIL_ADDR + mbxOffset, args[i]);
		mbxOffset += 4;
	}

	go(APPLET_CODE_ADDR);

    int elapsed = 12;

	while (elapsed >= 0) {
        quint32 ack = serial_read_word(APPLET_MAIL_ADDR, 1000);
		qDebug () << QString().sprintf("%08x", ack);
		if (ack == (0xffffffff - cmd)) {
			// return applet status
			quint32 status = serial_read_word(APPLET_MAIL_ADDR + 4);

			if (status == 0){
				qDebug() << "Applet Successful ran.";
				return true;
			}
			else {
				qDebug() << "Status of applet is not ready." ;
			}
		}

        QThread::msleep(10);
		elapsed -= 1;
	}

	qDebug() << "Applet refused to run.";
    return false;
}

bool FirmwareUpdater::serial_write_word(const quint32 &address, quint32 data) {
	if (!m_serial->isOpen())
		return false;

	serial_write(QString().sprintf("W%x,%08x#", address, data));
	return true;
}

quint32 FirmwareUpdater::serial_read_word(quint32 address, int timeout)
{
	if (!m_serial->isOpen()){
		return 0;	
	}

	serial_write(QString().sprintf("w%x,#", address));

	QByteArray resp = serial_read(4, timeout);
	quint32 value = (((quint8)resp[3]) << 24) + (((quint8)resp[2]) << 16) +
			(((quint8)resp[1]) << 8) + ((quint8)resp[0]);
	return value;
}

bool FirmwareUpdater::go(const quint32 &address)
{
	if (!m_serial->isOpen())
		return false;

	serial_write(QString().sprintf("G%x#", address));

	return true;
}

void FirmwareUpdater::check_mail(){
	m_mem_size = serial_read_word(APPLET_MAIL_ADDR + ((0 + 2) * 4));
	m_buff_addr = serial_read_word(APPLET_MAIL_ADDR + ((1 + 2) * 4));
	m_buff_size = serial_read_word(APPLET_MAIL_ADDR + ((2 + 2) * 4));

	if (m_buff_size > 128*1024){
		m_buff_size = 128*1024;
	}

	if (m_mem_size > 1){
		qDebug() << "Detected " << m_mem_size << " of memory"; 
		emit push_to_AFM(QString().sprintf("Detected %dB of memory", m_mem_size));
	}
	else {
		qDebug() << "Memory detection failed"; 		
	}
}

//not completely futureproof as our program is TINY (i.e. smaller than the buffer)
//need to future proof this function, as out mcu expands. look to SAMBA
bool FirmwareUpdater::write_to_flash(){ 
	load_file(m_mcu_bin);

    if ((m_bin_buf.length() & (PAGE_SIZE - 1)) != 0) {
		int pad = PAGE_SIZE - (m_bin_buf.length() & (PAGE_SIZE - 1));
		m_bin_buf.append(QByteArray(pad, 0xff));
		qDebug()<<"Padded " << pad << " bytes to payload";
	}

    quint32 size = m_bin_buf.length() / PAGE_SIZE;

    //Debug () << QString().sprintf("%x",m_buff_addr);

    if(!write_applet(m_buff_addr, &m_bin_buf)){
    	qDebug () << "Failed to load MEMS bin into buffer";
    	emit push_to_AFM(QString("Failed to load MEMS bin into buffer"));
    	return false;
    }

    quint32 args [] = {m_buff_addr, size * PAGE_SIZE, 0};

    //qDebug() << args[0] << " " << args[1] << " " << args[2] << " " << sizeof(args);

    bool status = run_applet(2, args, 3);

    return	status;

    return false;
}


void FirmwareUpdater::close()
{
	if (m_serial->isOpen())
	{
		if (!m_serial->clear()){
			qDebug () << "Failed to clear serial";
		}
		m_serial->close();
	}
}

const quint32 FirmwareUpdater::APPLET_CODE_ADDR = 0x20401000;
const quint32 FirmwareUpdater::APPLET_MAIL_ADDR = 0x20401040;
const int FirmwareUpdater::MAX_BUF_SIZE = 32*1024;
const quint32 FirmwareUpdater::PAGE_SIZE = 512;
const quint32 FirmwareUpdater::CIRD_REG_ADDR = 0x400e0940;
const QString FirmwareUpdater::LOWLEVEL_PATH = QString("lowlevelinit-samv7.bin");
const QString FirmwareUpdater::FLASH_PATH = QString(":/mcu_bin/flash-samv7.bin");
const QString FirmwareUpdater::MEMS_PATH = QString("mems_mcu_usb.bin");
