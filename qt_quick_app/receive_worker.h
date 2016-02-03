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
    void build_working_response();

private:
    ThreadSafeQueue<CommandNode*> command_queue;
    ThreadSafeQueue<char> response_byte_queue;
    QByteArray working_response;
    bool complete_message;
    void process_working_response();
    void assert_return_integrity(CommandNode* node, unsigned char tag, unsigned char id, int length);

};

#endif // RECEIVEWORKER_H
