#ifndef EVENTWORKER_H
#define EVENTWORKER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <afm.h>
#include <queue>
#include <commandNode.h>
#include <QTimer>
#include <returnBuffer.h>
#include <mainwindow.h>

using std::queue;

class eventworker : public QObject
{
    Q_OBJECT
    queue<commandNode*>& m_queue;
    queue<returnBuffer<int>*>& return_queue;

public:
    eventworker();
    eventworker(QObject *parent, queue<commandNode*>& _queue,queue<returnBuffer<int>*>& _returnqueue)
        : m_queue(_queue),return_queue(_returnqueue),QObject(parent){}
    void abort();
    ~eventworker();
private:

    nanoiAFM m_afm;
    QTimer *graphTimer;     // graph timer which can change intervals
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
    int ioTimer;
    bool _abort;
signals:
    void finished();

public slots:
    void updateGraph();
    void generalTimerUpdate();
    void mainLoop();
};

#endif // EVENTWORKER_H
