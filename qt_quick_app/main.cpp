#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QObject>
#include <QThread>
#include "receiver.h"
#include "serial_port.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    Receiver receiver;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("receiver", &receiver); // creates a name receiver and ties it to the receiver we instantiated
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    QThread* serial_thread = new QThread();
    SerialPort* serial_port = new SerialPort();
    serial_port->moveToThread(serial_thread);
    serial_thread->start();
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
    QObject::connect(&receiver, SIGNAL(send_byte(char)), serial_port, SLOT(write_byte(char)));

    return app.exec();
}
