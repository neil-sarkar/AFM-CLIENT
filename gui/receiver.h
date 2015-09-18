#ifndef RECEIVER_H
#define RECEIVER_H
#include <QObject>
#include <queue>
#include <globals.h>

using std::queue;



class receiver : public QObject
{
    Q_OBJECT
    queue<receivetype>& recv_queue;
    queue<returnBuffer*>& rtn_queue;
    queue<returnBuffer*>& graph_queue;
    icspiAFM& r_afm; //afm object to communicate with MCU
public:
    receiver(QObject *parent,
             queue<receivetype>& receivequeue,
             queue<returnBuffer*>& returnqueue,
             queue<returnBuffer*>& graphqueue,
             icspiAFM& afm):
        QObject(parent),
        recv_queue(receivequeue),
        rtn_queue(returnqueue),
        graph_queue(graphqueue),
        r_afm(afm) {}
    void abort();
    ~receiver();

private:
    //icspiAFM m_afm;
    bool _abort;
    bool isError;
    bool serial_is_ready = false;

signals:
    void finished();
    void serialError(); //emited to the mainwindow when there is an error

public slots:
    void mainLoop();
    void serial_ready(int);
    void start_wait_for_init();
};

#endif // RECEIVER_H
