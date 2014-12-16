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
    queue<returnBuffer*>& graph_queue;
    icspiAFM& r_afm; //afm object to communicate with MCU
public:
    receiver(QObject *parent,
             queue<receivetype>& receivequeue,
             queue<returnBuffer*>& returnqueue,
             queue<returnBuffer*>& graphqueue,
             icspiAFM& afm):
        QObject(parent),
        m_queue(receivequeue),
        r_queue(returnqueue),
        graph_queue(graphqueue),
        r_afm(afm){}
    void abort();
    ~receiver();

private:
    //icspiAFM m_afm;
    bool _abort;
    bool isError;

signals:
    void finished();
    void serialError(); //emited to the mainwindow when there is an error

public slots:
    void mainLoop();
};

#endif // RECEIVER_H
