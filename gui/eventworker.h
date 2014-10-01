#ifndef EVENTWORKER_H
#define EVENTWORKER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <afm.h>
#include <queue>
#include <commandNode.h>
#include <QTimer>

using std::queue;

class eventworker : public QObject
{
    Q_OBJECT
    queue<commandNode*>& m_queue;

public:
    eventworker();
    eventworker(QObject *parent, queue<commandNode*>& _queue) : m_queue(_queue),QObject(parent){}

private:
    nanoiAFM m_afm;
    QTimer *graphTimer;     // graph timer which can change intervals
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
signals:
    void finished();

public slots:
    void updateGraph();
    void generalTimerUpdate();
    void mainLoop();
};

#endif // EVENTWORKER_H
