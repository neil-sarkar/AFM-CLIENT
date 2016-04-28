#ifndef SENDWORKER_H
#define SENDWORKER_H

#include <QObject>
#include <QQueue>
#include "command_node.h"
#include "thread_safe_queue.h"

class SendWorker : public QObject
{
    Q_OBJECT
public:
    explicit SendWorker(QObject *parent = 0);
    ThreadSafeQueue<CommandNode*> send_command_queue;

signals:
    void send_command_immediately();
    void command_dequeued(CommandNode*);
    void immediately_dequeue();

private slots:
    void dequeue_command();

public slots:
    void enqueue_command(CommandNode* command_node);
    void flush();
    void handle_receive_return();

private:
    int tag;
    void populate_send_bytes(CommandNode*);
    int iterate_tag();
    void validate_send_length(CommandNode* command_node);
    void mask_special_characters(CommandNode* command_node);
};

#endif // SENDWORKER_H
