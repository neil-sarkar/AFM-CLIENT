#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QObject>
#include <QThread>
#include "serial_port.h"
#include "firmware_updater.h"
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
#include <QImage>
#include <QBuffer>
#include <QFontDatabase>
#include "safe_application.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("nGauge");
    QCoreApplication::setOrganizationName("ICSPI");
    SafeApplication app(argc, argv); // init app
    QQmlApplicationEngine engine;
    QFontDatabase::addApplicationFont(":/fonts/roboto/Roboto-Thin.ttf");

    // Thread declarations
    QThread* serial_thread = new QThread();
    QThread* sender_thread = new QThread();
    QThread* receiver_thread = new QThread();
    QThread* fu_thread = new QThread();

    // Object creation
    Builder* builder = new Builder();
    SerialPort* serial_port = new SerialPort();
    FirmwareUpdater* firmware_updater = new FirmwareUpdater();
    SendWorker* send_worker = new SendWorker();
    ReceiveWorker* receive_worker = new ReceiveWorker();
    
    AFM* afm = builder->build_afm();
    builder->wire(afm, serial_port, send_worker, receive_worker, firmware_updater);
    builder->generate_command_nodes();
    builder->generate_color_map();
    builder->generate_color_bar();

    // Thread connections
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
    QObject::connect(serial_thread, SIGNAL(finished()), serial_port, SLOT(close()));
    
    QObject::connect(fu_thread, SIGNAL(finished()), firmware_updater, SLOT(close()));

    // Set up view
    QWidget* window = QApplication::desktop()->screen();
    const int horizontalDpi = window->logicalDpiX();
    qDebug() << "logical DPI x " << horizontalDpi;
    MainWindow m(afm, new WebFileDialog(), horizontalDpi/72.0);

    m.showMinimized();
    m.showMaximized();

    // Assign objects to threads
    serial_port->moveToThread(serial_thread);
    send_worker->moveToThread(sender_thread);
    receive_worker->moveToThread(receiver_thread);
    firmware_updater->moveToThread(fu_thread);

    // Thread start
    QObject::connect(&m, SIGNAL(loadFinished()), serial_thread, SLOT(start()));
    QObject::connect(&m, SIGNAL(loadFinished()), sender_thread, SLOT(start()));
    QObject::connect(&m, SIGNAL(loadFinished()), receiver_thread, SLOT(start()));
    QObject::connect(&m, SIGNAL(loadFinished()), fu_thread, SLOT(start()));

    // Cleanup
    engine.quit();
    int closed_event = app.exec();
    serial_thread->quit();
    receiver_thread->quit();
    sender_thread->quit();
    fu_thread->quit();
    return closed_event;
}
