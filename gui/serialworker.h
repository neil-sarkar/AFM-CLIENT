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
    queue<returnBuffer*>& return_queue;
    //nanoiAFM m_afm;
public:
    serialworker(QObject *parent, queue<commandNode*>& _queue,queue<returnBuffer*>& _returnqueue) :
        QObject(parent),
        m_queue(_queue),
        return_queue(_returnqueue)  {}
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
    returnBuffer* _buffer;
    int _index;

signals:
    void valueChanged(const QString &value);
    void valueChanged(double value);
    void finished();
    void updateStatusBar(QString _string);

public slots:
    void mainLoop();
};

#endif // SERIALWORKER_H
