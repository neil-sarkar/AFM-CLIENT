#ifndef receive_worker_H
#define receive_worker_H
#include <QObject>
#include <queue>
#include <globals.h>
#include <deque>

#define ERR_MSG_TAG_MISMATCH 1
#define ERR_MSG_ID_MISMATCH 2
#define ERR_MSG_SIZE_MISMATCH 3
#define ERR_COMMAND_FAILED 4
#define ERR_MSG_MISSING 5
#define ERR_MSG_UNSOLICITED 6

using std::queue;
using std::deque;

class receive_worker : public QObject
{
Q_OBJECT
queue<receivetype>& receive_queue_old;
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
    receive_queue_old(receivequeue),
    return_queue(returnqueue),
    graph_queue(graphqueue),
    r_afm(afm) {
}
void abort();
~receive_worker();

private:
QTimer *cleaner_timer;
bool _abort;
bool isError;
QByteArray uart_resp;
bool next_command_clear_to_write = true;
returnType next_command_name;
char next_command_message_id;
char next_command_message_tag;
int next_command_writeByte_result;
deque<receivetype> receive_queue = deque<receivetype>();
void handle_error(short error_id);

signals:
void finished();
void serialError();     //emited to the mainwindow when there is an error
bool serial_port_is_open();
void getNextMsg();
void afm_worker_onReadyRead();
void afm_callback(int callback_operation);

public slots:
void mainLoop();
void process_uart_resp(QByteArray new_uart_resp);
//Q_SLOT void push_recv_queue(returnType name);
void push_recv_queue(char message_id, char message_tag, int writeByte_result);
void queue_cleaner();
};

#endif // receive_worker_H
