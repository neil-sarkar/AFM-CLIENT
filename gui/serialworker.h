#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <afm.h>
#include <queue>
#include <commandNode.h>
#include <command.h>
#include <returnBuffer.h>
#include <globals.h>

using std::queue;



class serialworker : public QObject
{
    Q_OBJECT
    queue<commandNode*>& m_queue;
    queue<returnBuffer<int>*>& return_queue;
    //nanoiAFM m_afm;
public:
    serialworker(QObject *parent, queue<commandNode*>& _queue,queue<returnBuffer<int>*>& _returnqueue) : m_queue(_queue),return_queue(_returnqueue),QObject(parent){}
    void requestCommand(Command command);
    void requestCommand(Command command,qint8 dacID, double val);
    ~serialworker();
    void abort();


private:
    nanoiAFM m_afm;
    Command _command;
    double _val;
    qint8 _dacID;
    bool _abort;
    //QMutex mutex;
    QWaitCondition condition;

signals:
    void valueChanged(const QString &value);
    void valueChanged(double value);
    void finished();

public slots:
    float doreadDAC(qint8 dacID);
    float doreadADC(qint8 adcID);
    void mainLoop();
};

#endif // SERIALWORKER_H
