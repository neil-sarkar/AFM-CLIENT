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
#include "pid.h"
#include "builder.h"
#include "afm.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // Thread declarations
    QThread* serial_thread = new QThread();
    QThread* sender_thread = new QThread();
    QThread* receiver_thread = new QThread();

    // Object creation
    SerialPort* serial_port = new SerialPort();
    SendWorker* send_worker = new SendWorker();
    ReceiveWorker* receive_worker = new ReceiveWorker();
    Builder* builder = new Builder();
    AFM* afm = builder->build_afm();

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("motor", afm->motor);
    context->setContextProperty("dac", afm->DAC_collection["board_1"]);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


//     View config

//    motor_view.show();
//    dac->init();
//    dac_view.rootContext()->setContextProperty("dac", afm->dac);
//    dac_view.setSource(QUrl(QStringLiteral("qrc:///DAC.qml")));
//    dac_view.show();
//    pga_view.rootContext()->setContextProperty("pga", pga);
//    pga_view.setSource(QUrl(QStringLiteral("qrc:///PGA.qml")));
//    pga_view.show();
//    pid_view.rootContext()->setContextProperty("pid", pid);
//    pid_view.setSource(QUrl(QStringLiteral("qrc:///PID.qml")));
//    pid_view.show();

    // Wire up signals and slots
    QObject::connect(afm->motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);


    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
    QObject::connect(serial_thread, SIGNAL(finished()), serial_port, SLOT(close()));


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
