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
#include <QTimer>
using std::queue;

class send_worker : public QObject
{
    Q_OBJECT
    queue<commandNode*>& cmd_queue;
    queue<receivetype>& receive_queue;
    icspiAFM& s_afm;
public:
    send_worker(QObject *parent,
                 queue<commandNode*>& _queue,
                 queue<receivetype>& _receivequeue, 
                 icspiAFM& afm) :
        QObject(parent),
        cmd_queue(_queue),
        receive_queue(_receivequeue), 
		s_afm(afm)  {}
    ~send_worker();
    void abort();


private:
    //icspiAFM m_afm;
    QTimer *queue_check_timer;
    bool serial_ready = false;
    Command _command;
    double _val;
    qint8 _ID;
    bool _abort;
    float _returnBytes;
    QWaitCondition condition;
    int _success;
    returnBuffer* _buffer;
    int _index; //used for serial ports
    int msg_tag = 0;

signals:
    bool open_serial_port(QString serialPortName, qint32 baud_rate);
    bool serial_port_is_open();
    void close_serial_port();
    void finished();
    void updateStatusBar(QString _string);
    Q_SIGNAL void push_recv_queue(returnType name);

public slots:
    void mainLoop();

private slots:
    void queue_check();
};

#endif // SERIALWORKER_H
