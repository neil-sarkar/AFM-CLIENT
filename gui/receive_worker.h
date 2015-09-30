#ifndef receive_worker_H
#define receive_worker_H
#include <QObject>
#include <queue>
#include <globals.h>

using std::queue;



class receive_worker : public QObject
{
Q_OBJECT
queue<receivetype>& receive_queue;
queue<returnBuffer*>& return_queue;
queue<returnBuffer*>& graph_queue;
icspiAFM& r_afm;     //TODO remove me?
public:
receive_worker(QObject *parent,
               queue<receivetype>& receivequeue,
               queue<returnBuffer*>& returnqueue,
               queue<returnBuffer*>& graphqueue,
               icspiAFM& afm) :
    QObject(parent),
    receive_queue(receivequeue),
    return_queue(returnqueue),
    graph_queue(graphqueue),
    r_afm(afm) {
}
void abort();
~receive_worker();

private:
bool _abort;
bool isError;
QByteArray uart_resp;
bool next_command_clear_to_write = true;
returnType next_command_name;
char next_command_message_id;
char next_command_message_tag;
int next_command_writeByte_result;

signals:
void finished();
void serialError();     //emited to the mainwindow when there is an error
bool isOpen();
void getNextMsg();

public slots:
void mainLoop();
void process_uart_resp(QByteArray new_uart_resp);
//Q_SLOT void push_recv_queue(returnType name);
void push_recv_queue(char message_id, char message_tag, int writeByte_result);
};

#endif // receive_worker_H
