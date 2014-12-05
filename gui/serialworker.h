#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <queue>
#include <commandNode.h>
#include <returnBuffer.h>
#include <globals.h>
#include <QThread>
#include <QEventLoop>
#include <iostream>
#include <returnBuffer.h>
#include <string>
#include <stdlib.h>
using std::queue;



class serialworker : public QObject
{
    Q_OBJECT
    queue<commandNode*>& m_queue;
    queue<receivetype>& receive_queue;
    nanoiAFM& s_afm;
public:
    serialworker(QObject *parent,
                 queue<commandNode*>& _queue,
                 queue<receivetype>& _receivequeue, nanoiAFM& afm) :
        QObject(parent),
        m_queue(_queue),
        receive_queue(_receivequeue), s_afm(afm)  {}
    ~serialworker();
    void abort();


private:
    //nanoiAFM m_afm;
    Command _command;
    double _val;
    qint8 _ID;
    bool _abort;
    float _returnBytes;
    QWaitCondition condition;
    int _success;
    returnBuffer* _buffer;
    int _index;

signals:
    void finished();
    void openPort(QSerialPortInfo _port);
    void updateStatusBar(QString _string);

public slots:
    void mainLoop();
};

#endif // SERIALWORKER_H
