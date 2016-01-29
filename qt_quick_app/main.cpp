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
#include "receive_worker.h"
#include "dac.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QThread* serial_thread = new QThread();
    SerialPort* serial_port = new SerialPort();
    serial_port->moveToThread(serial_thread);
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
    serial_thread->start();

    QQuickView view;
    Motor* motor = new Motor();
    view.rootContext()->setContextProperty("motor", motor);
    view.setSource(QUrl(QStringLiteral("qrc:///Motor.qml")));
    view.show();

    QQuickView view2;
    DAC* dac = new DAC(1);
    dac->init();
    view2.rootContext()->setContextProperty("dac", dac);
    view2.rootContext()->setContextProperty("motor", motor);
    view2.setSource(QUrl(QStringLiteral("qrc:///DAC.qml")));


    view2.rootContext()->setContextProperty("serial_port", serial_port);
    view2.show();

    QThread* sender_thread = new QThread();
    SendWorker* send_worker = new SendWorker();
    send_worker->moveToThread(sender_thread);
    sender_thread->start();

    QThread* receiver_thread = new QThread();
    ReceiveWorker* receive_worker = new ReceiveWorker();
    receive_worker->moveToThread(receiver_thread);
    receiver_thread->start();

    QObject::connect(motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(dac, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);

    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));


    return app.exec();
}
