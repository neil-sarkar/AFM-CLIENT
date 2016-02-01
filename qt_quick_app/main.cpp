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
#include "pga.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Thread declarations
    QThread* serial_thread = new QThread();
    QThread* sender_thread = new QThread();
    QThread* receiver_thread = new QThread();

    // Object creation (to be moved into application builder class
    Motor* motor = new Motor();
    DAC* dac = new DAC(1);
    PGA* pga = new PGA(1);
    SerialPort* serial_port = new SerialPort();
    SendWorker* send_worker = new SendWorker();
    ReceiveWorker* receive_worker = new ReceiveWorker();

    // View config
    QQuickView motor_view, dac_view;
    motor_view.rootContext()->setContextProperty("motor", motor);
    motor_view.setSource(QUrl(QStringLiteral("qrc:///Motor.qml")));
    motor_view.show();
    dac->init();
    dac_view.rootContext()->setContextProperty("dac", dac);
    dac_view.setSource(QUrl(QStringLiteral("qrc:///DAC.qml")));
    dac_view.show();

    // Wire up signals and slots
    QObject::connect(motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(dac, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));


    // Assign objects to threads
    serial_port->moveToThread(serial_thread);
    send_worker->moveToThread(sender_thread);
    receive_worker->moveToThread(receiver_thread);

    // Thread start
    serial_thread->start();
    sender_thread->start();
    receiver_thread->start();

    // Cleanup
    engine.quit();
    int r = app.exec();
    serial_thread->quit();
    receiver_thread->quit();
    sender_thread->quit();
    return r;
}
