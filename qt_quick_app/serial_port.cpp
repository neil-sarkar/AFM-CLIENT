#include <serial_port.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <serial_port_constants.h>
#include <QDebug>
#include <QTimer>

SerialPort::SerialPort() {
    port = new QSerialPort(this);
}

SerialPort::~SerialPort() {
    close();
    emit disconnected();
}

bool SerialPort::auto_connect() {
    // this method attempts to find all the ports connected and connect to (open) the one
    // that it thinks is the AFM
    QList<QSerialPortInfo> connected_ports = QSerialPortInfo::availablePorts();
    if (!connected_ports.size()) // if there are no ports available
        return false;
    for (int i = 0; i < connected_ports.size(); i++)
        qDebug() << connected_ports[i].manufacturer();

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
    }
    return is_connected;
}

void SerialPort::close() {
    port->close();
    is_connected = false;
    emit disconnected();
}

int SerialPort::writeByte(char byte) {
    if (port->write(&byte, 1) == 1)
        return SerialPortConstants.AFM_SUCCESS;

    qDebug() << "Failed to write byte " << QString("%1").arg(byte, 0, 16);
    return SerialPortConstants.AFM_FAIL;
}

void SerialPort::onReadyRead() {
    qDebug() << port->readAll();
}
