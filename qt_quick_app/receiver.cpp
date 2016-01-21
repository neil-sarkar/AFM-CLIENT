#include "receiver.h"
#include "serial.h"
#include <QDebug>

Receiver::Receiver(QObject *parent) : QObject(parent) {}

void Receiver::receiveFromQml(char value) {
    qDebug() << "Received in C++ from QML:" << value;
    emit send_byte(value);
}

void Receiver::receiveFromQml(double value) {
    qDebug() << "Received in C++ from QML:" << value;
}

void Receiver::receiveFromQml(QString message) {
    qDebug() << "Received in C++ from QML:" << message;
    emit send_byte(message.at(0).toLatin1());
}



