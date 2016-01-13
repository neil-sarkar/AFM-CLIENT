#include <mainwindow.h>
#include <globals.h>
#include <QSignalMapper>
#include <receive_worker.h>
#include <eventworker.h>
#include <debugger.h>
#include <QDebug>

QMutex mutex;

void customDebugger(QtMsgType type, const QMessageLogContext& context, const QString& str) {
    // if there is a status code, then the message will look like this "[STATUS_CODE] [MESSAGE]" Note the space.
    char customMessageType = str[0].toLatin1(); // convert the Qchar that is str[0] to a char
    // so you can actually make a switch case out of it
    QString messageTypePrintValue = "--";
    QString message = str;
    if (str.length() > 1 && str[1] == ' ') { // Check for the space
        switch (customMessageType) {
            case 'I': // I for input (messages being receieved by the GUI from the microcontroller)
                messageTypePrintValue = "<-";
                message = str.mid(2);
                break;
            case 'O': // O for output (messages being sent to the microcontroller)
                messageTypePrintValue = "->";
                message = str.mid(2);
                break;
            case 'S': // S for status (messages that are neither I/O, but just status messages)
                messageTypePrintValue = "--";
                message = str.mid(2);
                break;
        }
    }
    // use qPrintable or else you'll get " " around every string sent to qDebug()
    qDebug() << qPrintable(QTime::currentTime().toString()) << qPrintable(messageTypePrintValue) << qPrintable(message);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customDebugger);

    queue<commandNode *> commandQueue = queue<commandNode *>();
    queue<receivetype> receiveQueue = queue<receivetype>();
    queue<returnBuffer *> returnQueue = queue<returnBuffer *>();
    queue<returnBuffer *> graphQueue = queue<returnBuffer *>();

    // Configure the afm abstraction layer and afm_worker thread
    QThread *afmThread = new QThread();
    afm_worker *afmWorker = new afm_worker();
    afmWorker->moveToThread(afmThread);
    QObject::connect(afmThread, SIGNAL(started()), afmWorker, SLOT(init_serial_port()));
    QObject::connect(afmWorker, SIGNAL(finished()), afmThread, SLOT(quit()), Qt::DirectConnection);
    afmThread->start(QThread::HighPriority);
    icspiAFM *afm = new icspiAFM();

    /**********************5 Threads***********************************
     *
     * afmThread:   See above
     * mainThread:      Handles GUI, pushed events to the serialThread
     * sendThread:    Handles serial communication between the Qt Application
     *                      and the MCU, sends arguments to the MCU
     * eventThread:     Creates events on a timer to gather continuous data
     *                      for plots
     * receiveThread:  Handles the receiving of data from the MCU. Sends data
     *                      to the mainThread to display to the user
     *
     *******************************************************************/


    // QT-specific operation threads
    QThread *sendThread = new QThread();
    QThread *eventThread = new QThread();
    QThread *mainThread = new QThread();
    QThread *receiveThread = new QThread();

    MainWindow *mainWorker = new MainWindow(0, commandQueue, returnQueue);
    send_worker *sendWorker = new send_worker(0, commandQueue, receiveQueue, *afm);
    eventworker *eventWorker = new eventworker(0, commandQueue, graphQueue);
    receive_worker *receiveWorker = new receive_worker(0, returnQueue, graphQueue);

    // Define the basic signals and slots and start the threads
    QObject::connect(mainThread, SIGNAL(started()), mainWorker, SLOT(MainWindowLoop()));
    QObject::connect(mainWorker, SIGNAL(finished()), mainThread, SLOT(quit()), Qt::DirectConnection);
    mainThread->start();

    sendWorker->moveToThread(sendThread);
    QObject::connect(sendThread, SIGNAL(started()), sendWorker, SLOT(mainLoop()));
    QObject::connect(sendWorker, SIGNAL(finished()), sendThread, SLOT(quit()), Qt::DirectConnection);
    sendThread->start();

    eventWorker->moveToThread(eventThread);
    QObject::connect(eventThread, SIGNAL(started()), eventWorker, SLOT(mainLoop()));
    QObject::connect(eventWorker, SIGNAL(finished()), eventThread, SLOT(quit()), Qt::DirectConnection);
    eventThread->start();

    receiveWorker->moveToThread(receiveThread);
    QObject::connect(receiveThread, SIGNAL(started()), receiveWorker, SLOT(mainLoop()));
    QObject::connect(receiveWorker, SIGNAL(finished()), receiveThread, SLOT(quit()), Qt::DirectConnection);
    receiveThread->start();

    // Define additional signals and slots.
    // UI Elements
    QObject::connect(sendWorker, SIGNAL(updateStatusBar(QString)), mainWorker, SLOT(updateStatusBar(QString)));
    QObject::connect(receiveWorker, SIGNAL(serialError()), mainWorker, SLOT(serialError()));
    QObject::connect(eventWorker, SIGNAL(updatePlot(double, int)), mainWorker, SLOT(updatePlot(double, int)));
    // Serial port operation details
    QObject::connect(sendWorker, SIGNAL(open_serial_port(QString, qint32)), afmWorker, SLOT(open_serial_port(QString, qint32)));
    QObject::connect(sendWorker, SIGNAL(close_serial_port()), afmWorker, SLOT(close_serial_port()));
    QObject::connect(receiveWorker, SIGNAL(serial_port_is_open()), afmWorker, SLOT(serial_port_is_open()));
    QObject::connect(sendWorker, SIGNAL(serial_port_is_open()), afmWorker, SLOT(serial_port_is_open()));
    // afm interfacing
    //QObject::connect(receiveWorker, SIGNAL(getNextMsg()), afmWorker, SLOT(getNextMsg()));
    QObject::connect(afm, SIGNAL(clearPayloadBuffer()), afmWorker, SLOT(clearPayloadBuffer()));
    QObject::connect(afm, SIGNAL(addPayloadByte(char)), afmWorker, SLOT(addPayloadByte(char)));
    QObject::connect(afm, SIGNAL(writeMsg(unsigned char)), afmWorker, SLOT(writeMsg(unsigned char)));
    QObject::connect(afmWorker, SIGNAL(process_uart_resp(QByteArray)), receiveWorker, SLOT(process_uart_resp(QByteArray)));
    QObject::connect(afmWorker, SIGNAL(finished()), mainWorker, SLOT(afmWorkerError()));
    //receive queue callbacks
    qRegisterMetaType<returnType>("returnType");
    //QObject::connect(sendWorker, SIGNAL(push_recv_queue(returnType)), receiveWorker, SLOT(push_recv_queue(returnType)));
    QObject::connect(afmWorker, SIGNAL(push_recv_queue(unsigned char, unsigned char, int)), receiveWorker, SLOT(push_recv_queue(unsigned char, unsigned char, int)));
    QObject::connect(receiveWorker, SIGNAL(afm_worker_onReadyRead()), afmWorker, SLOT(onReadyRead()));

    //MainWindow close - thread termination
    QObject::connect(mainWorker, SIGNAL(finished()), sendThread, SLOT(quit()), Qt::DirectConnection);
    QObject::connect(mainWorker, SIGNAL(finished()), eventThread, SLOT(quit()), Qt::DirectConnection);
    QObject::connect(mainWorker, SIGNAL(finished()), receiveThread, SLOT(quit()), Qt::DirectConnection);
    QObject::connect(mainWorker, SIGNAL(finished()), afmThread, SLOT(quit()), Qt::DirectConnection);

    int rt = a.exec();

    /*Terminate threads on close*/
    sendWorker->abort();
    sendThread->wait();
    receiveWorker->abort();
    receiveThread->wait();
    eventWorker->abort();
    eventThread->wait();
    mainWorker->abort();
    mainThread->wait();

    delete sendThread;
    delete mainThread;
    delete eventThread;
    delete receiveThread;

    delete receiveWorker;
    delete sendWorker;
    delete eventWorker;
    delete mainWorker;

    return rt;
}
