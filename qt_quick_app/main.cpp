#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QObject>
#include <QThread>
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
#include "command_node.h"
#include "mainwindow.h"
#include "web_file_dialog.h"
#include <QWebView>
#include <QDir>
#include <QApplication>
#include <QDesktopWidget>
#include "safe_application.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("nGauge");
    QCoreApplication::setOrganizationName("ICSPI");
    SafeApplication app(argc, argv); // init app
    QQmlApplicationEngine engine;

    // Thread declarations
    QThread* serial_thread = new QThread();
    QThread* sender_thread = new QThread();
    QThread* receiver_thread = new QThread();

    // Object creation
    Builder* builder = new Builder();
    SerialPort* serial_port = new SerialPort();
    SendWorker* send_worker = new SendWorker();
    ReceiveWorker* receive_worker = new ReceiveWorker();
    AFM* afm = builder->build_afm();
    builder->wire(afm, serial_port, send_worker, receive_worker);
    builder->generate_command_nodes();

    // Thread connections
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
    QObject::connect(serial_thread, SIGNAL(finished()), serial_port, SLOT(close()));

    // Set up view
    MainWindow m(afm, new WebFileDialog());
    m.show();

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
    int closed_event = app.exec();
    serial_thread->quit();
    receiver_thread->quit();
    sender_thread->quit();
    return closed_event;
}
