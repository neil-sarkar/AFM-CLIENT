#include <serial_port.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QDebug>
#include <QTimer>
#include <QTextCodec>
#include <assert.h>
#include "globals.h"
#include "constants.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent) {
    port = new QSerialPort(this);
    port->setReadBufferSize(0);
    connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handle_error(QSerialPort::SerialPortError)));
}

SerialPort::~SerialPort() { // Destructor - handle all cleanup
    close();
    emit disconnected();
    delete port_scan_timer;
}

void SerialPort::handle_error(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError) {
        // crashes for some reason (QT sucks)
        //close();
    }
}

bool SerialPort::auto_connect() {
    // this method attempts to find all the ports connected and connect to (open) the one
    // that it thinks is the AFM
    QList<QSerialPortInfo> connected_ports = QSerialPortInfo::availablePorts();

    if (!connected_ports.size()) // if there are no ports available
        return false;
    for (int i = 0; i < connected_ports.size(); i++){ // iterate through the ports
        qDebug() << connected_ports[i].portName();
        qDebug() << connected_ports[i].manufacturer();
        if (open(connected_ports[i].portName(), AFM_Baud_Rate)) {
            return true;
        }
    }
    return false;
}

bool SerialPort::open(QString port_name, qint32 baud_rate) {
    close(); // close the current port, if any
    port->setPortName(port_name);
    port->setBaudRate(baud_rate);
    if (port->open(QIODevice::ReadWrite)) {
        if (detect_afm()) {
            port_scan_timer->stop();
            is_connected = true;
            initialize_reading();
            emit connected();
        } else {
            close();
        }
    }
    return is_connected;
}

void SerialPort::reset_mcu() {
    qDebug() << "Resetting MCU";
    emit resetting_mcu(); // this connects to the flushing of the buffers
    // super important, because the UI creation will try to call a bunch of setters
    QByteArray message;
    message += "MMM";
    write_bytes(message);
}

bool SerialPort::detect_afm() {
    if(port->waitForReadyRead(1000)) {
        // check for AFM heartbeat packet content
        QByteArray data = port->readAll();
        qDebug() << "data on port:" << data;
        return data.contains("\xF2""afm!");
    } else {
        qDebug() << "no data on port";
        return false;
    }
}

void SerialPort::initialize_reading() {
    qDebug() << "Data left on port from before" << port->readAll(); // Read any data left on the port
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(on_ready_read()));
}

void SerialPort::close() {
    if (is_connected) {
        reset_mcu();
    }
    port->close();
    qDebug() << "Closing port";
    is_connected = false;
    emit disconnected();
}

int SerialPort::write_byte(char byte) { // This method is the only one that actually writes anything to the serial port
    if (port->write(&byte, 1) == 1) { //        qDebug() << QString().sprintf("%2p",byte);
        return AFM_Success;
    }

    qDebug() << "Failed to write byte " << byte;
    return AFM_Fail;
}

int SerialPort::write_bytes(QByteArray bytes) { // This method is the only one that actually writes anything to the serial port
    qDebug() << "Sending " << bytes;
    if (port->write(bytes.data(), bytes.length()) == bytes.length()) { //        qDebug() << QString().sprintf("%2p",byte);
        return AFM_Success;
    }
    qDebug() << "Failed to write byte ";
    return AFM_Fail;
}

void SerialPort::on_ready_read() {
    QByteArray q = port->readAll();
    qDebug() << "On serial read all" << q << q.length();
    for (char byte : q) {
        emit byte_received(byte);
    }
}

void SerialPort::check_connected() { // In order to check if the AFM is connected, we will try to read some data from it
    qDebug() << "Checking connection";
    char temp_buffer[1]; // Create a buffer that will store the first char of data that the serial port has waiting for us
    if (!port->isOpen() || port->peek(temp_buffer, sizeof(temp_buffer)) == -1) // -1 is returned if there was an error in reading the port (aka the device has yet to be connected to)
        auto_connect(); // call auto_connect() since we're not connected
    else {
        on_ready_read(); // ensure that any bytes missed by the last read operation get processed
    }
}

void SerialPort::scan_for_ports() { // this method starts a timer that will call check_connected() every one second
    // every time one second goes by, the timeout() signal is called, and hence the check_connected() slot is invoked
    port_scan_timer = new QTimer(this);
    connect(port_scan_timer, SIGNAL(timeout()), this, SLOT(check_connected()));
    port_scan_timer->start(1000);
}

void SerialPort::execute_command(CommandNode* command_node) {
    int result = 0; // this variable stores a negative number indicating the number of bytes that failed to send.

    QByteArray message;

    // delimit with newlines
    message += '\n';
    for (int i = 0; i < command_node->payload.length(); i++) {
        message += command_node->payload[i];
    }
    message += '\n';

    write_bytes(message);
    // TODO:: throw graceful exception
    assert (result == AFM_Success);
    emit message_sent(command_node);
}

const int SerialPort::AFM_Baud_Rate = 115200;
const int SerialPort::AFM_Success = 0;
const int SerialPort::AFM_Fail = -1;
