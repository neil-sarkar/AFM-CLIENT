#include "receiver.h"
#include <QDebug>

Receiver::Receiver(QObject *parent) : QObject(parent)
{}

void Receiver::receiveFromQml(int value) {
    qDebug() << "Received in C++ from QML:" << value;
}

void Receiver::receiveFromQml(double value) {
    qDebug() << "Received in C++ from QML:" << value;
}

void Receiver::receiveFromQml(QString message) {
    qDebug() << "Received in C++ from QML:" << message;
}



