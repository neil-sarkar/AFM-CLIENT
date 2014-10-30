#include "mainwindow.h"
#include <globals.h>
//gotta follow this to add QtSerial Port
//http://qt-project.org/wiki/QtSerialPort#fn1921400492531950a902bc4


QMutex mutex;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    queue<commandNode*> commandQueue = queue<commandNode*>();
    queue<returnBuffer*> returnQueue = queue<returnBuffer*>();

    /**********************3 Threads***********************************
     *
     * mainThread:      Handles GUI, pushed events to the serialThread
     * serialThread:    Handles serial communication between the Qt Application
     *                      and the MCU, return data is pushed to a queue
     * eventThread:     Creates events on a timer to gather continuous data
     *                      for plots
     *
     *******************************************************************/

    QThread* serialThread = new QThread();
    QThread* eventThread = new QThread();
    QThread* mainThread = new QThread();

    MainWindow* mainWorker = new MainWindow(0,commandQueue,returnQueue);
    serialworker* serialWorker = new serialworker(0, commandQueue, returnQueue);
    eventworker* eventWorker = new eventworker(0,commandQueue,returnQueue);

    mainWorker->moveToThread(mainThread);
    QObject::connect(mainThread, SIGNAL(started()), mainWorker, SLOT(MainWindowLoop()));
    QObject::connect(mainWorker, SIGNAL(finished()), mainThread, SLOT(quit()), Qt::DirectConnection);
    mainThread->start();

    serialWorker->moveToThread(serialThread);
    QObject::connect(serialThread, SIGNAL(started()), serialWorker, SLOT(mainLoop()));
    QObject::connect(serialWorker, SIGNAL(finished()), serialThread, SLOT(quit()), Qt::DirectConnection);
    serialThread->start();

    eventWorker->moveToThread(eventThread);
    QObject::connect(eventThread, SIGNAL(started()), eventWorker, SLOT(mainLoop()));
    QObject::connect(eventWorker, SIGNAL(finished()), eventThread, SLOT(quit()), Qt::DirectConnection);
    eventThread->start();

    //mainWorker->resize(1000,600);
    //mainWorker->showMaximized();



    int rt = a.exec();

    /*Terminate threads on close*/
    serialWorker->abort();
    serialThread->wait();
    eventWorker->abort();
    eventThread->wait();
    mainWorker->abort();
    mainThread->wait();

    delete serialThread;
    delete mainThread;
    delete eventThread;

    delete serialWorker;
    delete eventWorker;
    delete mainWorker;

    return rt;
    //    //On Startup, populate the COM Port Combobox
    //    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //        qDebug() << "Name        : " << info.portName();
    //        qDebug() << "Description : " << info.description();
    //        qDebug() << "Manufacturer: " << info.manufacturer();

    //        if(info.manufacturer()==AFM_MANUFACTURER){
    //            w.afm.setPort(info);
    //            if (w.afm.open(QIODevice::ReadWrite)){
    //                qDebug() << "Sin Value: " << sin(M_PI);
    //                w.afm.writeDAC(2,1);
    //                //1+sin and 1-sin
    //                //qDebug() << "DAC Value: " << w.afm.readDAC(2);
    //                //qDebug() << "ADC Value: " << w.afm.readADC(1);

    //                while(1){
    //                    for(int i=0; i< 360; i++){
    //                         //w.afm.writeDAC(0, 1+sin(i*M_PI/360));
    //                        // w.afm.writeDAC(0,1);
    //                        // w.afm.writeDAC(2,2);
    //                        //sleep(0.1);
    //                        //w.afm.writeDAC(2, 1-sin(i*M_PI/360));
    //                        w.afm.writeDAC(11, 2.5 - (i/10));
    //                    }
    //                }
    //                w.afm.close();
    //            }
    //        }

    //    calculateLineScan(3000,2000,1000);
}

