#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QObject>
#include <QThread>
#include "receiver.h"
#include "serial_port.h"
#include "adc.h"
#include "motor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

//    Motor motor;
//    QQmlContext *context1 = new QQmlContext(engine.rootContext());
//    context1->setContextObject(motor);


//    QQmlComponent motor_component(&engine);
//    component.setData(QUrl(QStringLiteral("qrc:///Motor.qml")));
//    component.create(context1);


    QQuickView view;
    Motor* motor = new Motor();
    view.rootContext()->setContextProperty("motor", motor);
    view.setSource(QUrl(QStringLiteral("qrc:///Motor.qml")));
    view.show();

//    QThread* motor_thread = new QThread();
//    motor->moveToThread(motor_thread);
//    motor_thread->start();

//    Motor motor;
//    engine.rootContext()->setContextProperty("motor", &motor);
//    QQmlComponent component(&engine, QUrl::fromLocalFile("Motor.qml"));
//    component.create();

    QThread* serial_thread = new QThread();
    SerialPort* serial_port = new SerialPort();
    serial_port->moveToThread(serial_thread);
    serial_thread->start();

//    QQuickView *view = new QQuickView;
//    view->setSource(QUrl("qrc:/Motor.qml"));
//    Motor motor;
//    motor.setRootObject(view->rootObject());

//    engine.rootContext()->setContextProperty("motor", &motor);
//    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:///Motor.qml")));
//    component.create();


//    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
//    QObject::connect(&receiver, SIGNAL(send_byte(char)), serial_port, SLOT(write_byte(char)));

    return app.exec();
}
