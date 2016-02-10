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
#include "command_node.h"
#include "mainwindow.h"
#include <QWebView>
#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qDebug() << "App path" << app.applicationDirPath();

    MainWindow m;
    m.show();

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

    // Thread connections (to abstract later)
    QObject::connect(serial_thread, SIGNAL(started()), serial_port, SLOT(scan_for_ports()));
    QObject::connect(serial_thread, SIGNAL(finished()), serial_port, SLOT(close()));


    // Set up the view
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("motor", afm->motor);
    context->setContextProperty("afm", afm);
    context->setContextProperty("adc", afm->ADC_collection[ADC::Z_Piezoresistor_Amplitude]);
    context->setContextProperty("dac_z_coarse", afm->DAC_collection[DAC::Z_Offset_Coarse]);
    context->setContextProperty("dac_z_fine", afm->DAC_collection[DAC::Z_Offset_Fine]);
    context->setContextProperty("pga_x1", afm->PGA_collection[PGA::X_1]);
    context->setContextProperty("pga_x2", afm->PGA_collection[PGA::X_2]);
    context->setContextProperty("pga_y1", afm->PGA_collection[PGA::Y_1]);
    context->setContextProperty("pga_y2", afm->PGA_collection[PGA::Y_2]);
    context->setContextProperty("pga_z_fine", afm->PGA_collection[PGA::Z_Fine]);
    context->setContextProperty("pga_dds", afm->PGA_collection[PGA::DDS_Amplitude]);
    context->setContextProperty("pga_z_coarse", afm->PGA_collection[PGA::Z_Coarse]);
    context->setContextProperty("pga_leveling", afm->PGA_collection[PGA::Leveling]);
    context->setContextProperty("scanner", afm->scanner );
    context->setContextProperty("pid", afm->scanner->pid);
    context->setContextProperty("sweeper", afm->sweeper);
    context->setContextProperty("dds", afm->sweeper->dds);
    context->setContextProperty("approacher", afm->approacher);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

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
