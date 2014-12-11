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
    Q_OBJECT
    queue<commandNode*>& m_queue;
    queue<returnBuffer*>& return_queue;

public:
    eventworker();
    eventworker(QObject *parent,
                queue<commandNode*>& _queue,
                queue<returnBuffer*>& _returnqueue):
        QObject(parent),
        m_queue(_queue),
        return_queue(_returnqueue) {}
    void abort();
    ~eventworker();
private:

    //nanoiAFM m_afm;
    QTimer *graphTimer;     // graph timer which can change intervals
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
    int ioTimer;
    bool _abort;
    MainWindow* _mainwindow;
signals:
    void finished();

public slots:
    void updateGraph();
    void generalTimerUpdate();
    void mainLoop();
};

#endif // EVENTWORKER_H
