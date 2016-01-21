#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QObject>
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

    SerialPort serial_port;
    serial_port.auto_connect();
    return app.exec();
}
