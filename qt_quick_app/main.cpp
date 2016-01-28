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
#include "send_worker.h"
#include "dac.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;



    QQuickView view;
    Motor* motor = new Motor();
    view.rootContext()->setContextProperty("motor", motor);
    view.setSource(QUrl(QStringLiteral("qrc:///Motor.qml")));
//    view.show();

    QQuickView view2;
    DAC* dac = new DAC(1);
    view2.rootContext()->setContextProperty("dac", dac);
    view2.setSource(QUrl(QStringLiteral("qrc:///DAC.qml")));
    view2.show();

    QThread* serial_thread = new QThread();
    SerialPort* serial_port = new SerialPort();
    serial_port->moveToThread(serial_thread);
    serial_thread->start();

    QThread* sender_thread = new QThread();
    SendWorker* send_worker = new SendWorker();
    send_worker->moveToThread(sender_thread);
    sender_thread->start();

    QObject::connect(motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(dac, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));


    return app.exec();
}
