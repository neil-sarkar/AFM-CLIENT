#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>
#include "command_node.h"
#include "thread_safe_queue.h"

class ReceiveWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveWorker(QObject *parent = 0);

signals:
    void command_received();
    void response_byte_received();

public slots:
    void enqueue_command(CommandNode*);
    void enqueue_response_byte(char);

private slots:
    void dequeue_command();
    void dequeue_response_byte();

private:
    ThreadSafeQueue<CommandNode*> command_queue;
    ThreadSafeQueue<qint8> response_byte_queue;

};

#endif // RECEIVEWORKER_H
