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
    ~serialworker();
    void abort();


private:
    nanoiAFM m_afm;
    Command _command;
    double _val;
    qint8 _ID;
    bool _abort;
    float _returnBytes;
    QWaitCondition condition;
    int _success;
    returnBuffer<int>* _buffer;
    int _index;

signals:
    void valueChanged(const QString &value);
    void valueChanged(double value);
    void finished();

public slots:
    void mainLoop();
};

#endif // SERIALWORKER_H
