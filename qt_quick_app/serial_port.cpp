#include <serial_port.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <serial_port_constants.h>
#include <QDebug>
#include <QTimer>

SerialPort::SerialPort(QObject *parent) : QObject(parent) {
    port = new QSerialPort(this);
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(on_ready_read()));
}

SerialPort::~SerialPort() { // Destructor - handle all cleanup
    close();
    emit disconnected();
    delete port_scan_timer;
}

bool SerialPort::auto_connect() {
    // this method attempts to find all the ports connected and connect to (open) the one
    // that it thinks is the AFM
    QList<QSerialPortInfo> connected_ports = QSerialPortInfo::availablePorts();
    if (!connected_ports.size()) // if there are no ports available
        return false;
    for (int i = 0; i < connected_ports.size(); i++) // iterate through the ports
        if (connected_ports[i].manufacturer() == SerialPortConstants.AFM_PORT_NAME) // check if the port is the AFM
            return open(connected_ports[i].portName(), SerialPortConstants.AFM_BAUD_RATE);
    return false;
}

bool SerialPort::open(QString port_name, qint32 baud_rate) {
    close(); // close the current port, if any
    port->setPortName(port_name);
    port->setBaudRate(baud_rate);
    if (port->open(QIODevice::ReadWrite)) {
        emit connected();
        is_connected = true;
        port_scan_timer->stop();
    }
    return is_connected;
}

void SerialPort::close() {
    port->close();
    qDebug() << "Closing port";
    is_connected = false;
    emit disconnected();
}

int SerialPort::write_byte(char byte) { // This method is the only one that actually writes anything to the serial port
    if (port->write(&byte, 1) == 1) {
        qDebug() << byte;
        return SerialPortConstants.AFM_SUCCESS;
    }


    qDebug() << "Failed to write byte " << byte;
    return SerialPortConstants.AFM_FAIL;
}

void SerialPort::on_ready_read() {
    qDebug() << "Incoming" << port->readAll();
}

void SerialPort::check_connected() { // In order to check if the AFM is connected, we will try to read some data from it
    qDebug() << "Checking connection";
    char temp_buffer[1]; // Create a buffer that will store the first char of data that the serial port has waiting for us
    if (port->peek(temp_buffer, sizeof(temp_buffer)) == -1) // -1 is returned if there was an error in reading the port (aka the device has yet to be connected to)
        auto_connect(); // call auto_connect() since we're not connected
}

void SerialPort::scan_for_ports() { // this method starts a timer that will call check_connected() every one second
    // every time one second goes by, the timeout() signal is called, and hence the check_connected() slot is invoked
    port_scan_timer = new QTimer(this);
    connect(port_scan_timer, SIGNAL(timeout()), this, SLOT(check_connected()));
    port_scan_timer->start(1000);
}

void SerialPort::execute_command(CommandNode* command_node) {
    qDebug() << "Tag: " << command_node->tag << "Id: " << command_node->id << "Payload:" << command_node->payload;
    int result = 0; // this variable stores a negative number indicating the number of bytes that failed to send.
    result += write_byte(0x0A); // delimit the message
    result += write_byte(command_node->tag); // send the tag (the message number as dictated by chronology)
    result += write_byte(command_node->id); // send the message id (tells microcontroller what kind of command this is)

    for (char payload_byte : command_node->payload)
        qDebug() << "Writing " << QString().sprintf("%2p",payload_byte);
//        result += write_byte(payload_byte); // send all the associated data with the command
    result += write_byte(0x0A); // delimit the message
}
