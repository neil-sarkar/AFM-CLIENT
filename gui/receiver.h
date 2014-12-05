#ifndef RECEIVER_H
#define RECEIVER_H
#include <QObject>
#include <queue>
#include <globals.h>

using std::queue;



class receiver : public QObject
{
    Q_OBJECT
    queue<receivetype>& m_queue;
    queue<returnBuffer*>& r_queue;
    nanoiAFM& r_afm;
public:
    receiver(QObject *parent,
             queue<receivetype>& receivequeue,
             queue<returnBuffer*>& returnqueue,
             nanoiAFM& afm):
        QObject(parent),
        m_queue(receivequeue),
        r_queue(returnqueue),
        r_afm(afm){}
    void abort();
    ~receiver();

private:
    //nanoiAFM m_afm;
    bool _abort;
    bool isError;

signals:
    void finished();
    void serialError();

public slots:
    void openPort(QSerialPortInfo _port);
    void mainLoop();
};

#endif // RECEIVER_H
