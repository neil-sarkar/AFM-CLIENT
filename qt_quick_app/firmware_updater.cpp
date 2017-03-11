//based off of samba.  Should technically make this compatible with other MCUs for futureproofing.
//merge/morph with serial_port sometime

#include "firmware_updater.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QElapsedTimer>

FirmwareUpdater::FirmwareUpdater(QObject *parent) : QObject(parent) {
	m_portname = "";
	m_baudrate = 0;
}

void FirmwareUpdater::update_firmware () {
    open();
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
		info = portList.at(0);
		if (info.isValid()){
			port = info.portName();
		}
		//else throw error
		else {
            emit to_console(QString("The Portname is boned."));
		}
	}// else throw error
	else {
        emit to_console(QString("There ain't no ports."));
	}
	return port;
}

void FirmwareUpdater::open(){
	m_portname = get_serial_port_name();

	if (m_portname.isEmpty()){
		return;
	}

	QSerialPortInfo info(m_portname);

	m_serial.setBaudRate(115200);
	m_serial.setDataBits(QSerialPort::Data8);
	m_serial.setParity(QSerialPort::NoParity);
	m_serial.setStopBits(QSerialPort::OneStop);
	m_serial.setFlowControl(QSerialPort::NoFlowControl);

	if (m_serial.open(QIODevice::ReadWrite))
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
		}
		else
		{
			//couldnot switch binary
			emit to_console(QString("Swap to binary mode failed."));
		}
	}
	else
	{
		//couldn't open port
		emit to_console(QString("Opening port failed."));
	}
}

void FirmwareUpdater::serial_write(const QString &str)
{

	QByteArray data = str.toLocal8Bit();
	m_serial.write(data.constData(), data.length());
	m_serial.waitForBytesWritten(10);
}

QByteArray FirmwareUpdater::serial_read(int minBytes, int timeout /*defualt 10*/)
{
	QByteArray resp;
    QElapsedTimer timer;

	timer.start();
	do {
		if (timeout > 0 && (timer.elapsed() >= timeout))
			break;
		m_serial.waitForReadyRead(10);
		if (m_serial.bytesAvailable())
			resp.append(m_serial.readAll());
	} while (resp.length() < minBytes);

	return resp;
}

void FirmwareUpdater::close()
{
	if (m_serial.isOpen())
	{
		m_serial.close();
	}
}

