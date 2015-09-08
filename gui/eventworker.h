#ifndef EVENTWORKER_H
#define EVENTWORKER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <queue>
#include <commandNode.h>
#include <QTimer>
#include <returnBuffer.h>
#include <QThread>
#include <Qtimer>
#include <globals.h>
#include <mainwindow.h>

using std::queue;

class eventworker : public QObject
{
    //objects to be set in constructor
    Q_OBJECT
    queue<commandNode*>& cmd_queue;
    queue<returnBuffer*>& graph_queue;

public:
    eventworker();
    eventworker(QObject *parent,
                queue<commandNode*>& _queue,
                queue<returnBuffer*>& _returnqueue):
        QObject(parent),
        cmd_queue(_queue),
        graph_queue(_returnqueue) {}
    void abort();
    ~eventworker();
private:

    //nanoiAFM m_afm;
    QTimer *graphTimer;     // graph timer which can change intervals
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
    int ioTimer;
    bool _abort;
    MainWindow* _mainwindow; //used to check current tab
    returnBuffer* _node;     //current node
signals:
    void finished();
    void updatePlot(double _signal, int _plot); //signal to the mainwindow to update the plot

public slots:
    void updateGraph(); //timer event to send a read request to the MCU and then sends a signal to the mainwindow to update graph
    void mainLoop(); //used to set the timer
};

#endif // EVENTWORKER_H
