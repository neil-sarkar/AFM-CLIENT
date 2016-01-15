#ifndef receive_worker_H
#define receive_worker_H
#include <QObject>
#include <QTime>
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
    queue<returnBuffer*>& return_queue;
    queue<returnBuffer*>& graph_queue;

public:
    receive_worker(QObject *parent,
               queue<returnBuffer*>& returnqueue,
               queue<returnBuffer*>& graphqueue) :
                QObject(parent),
                return_queue(returnqueue),
                graph_queue(graphqueue) {
}
    void abort();
    ~receive_worker();

private:
    bool _abort;
    QByteArray uart_resp;
    deque<receivetype> receive_queue = deque<receivetype>();
    void handle_error(short error_id);

signals:
    void finished();
    void serialError();     //emited to the mainwindow when there is an error
    bool serial_port_is_open(); // doesn't seem to be used anymore
    void getNextMsg();
    void afm_worker_onReadyRead();
    void afm_callback(int callback_operation);

public slots:
    void mainLoop();
    void process_uart_resp(QByteArray new_uart_resp);
    //Q_SLOT void push_recv_queue(returnType name);
    void push_recv_queue(unsigned char message_id, unsigned char message_tag, int writeByte_result);
};

#endif // receive_worker_H
