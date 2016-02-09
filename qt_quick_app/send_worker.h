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

signals:
    void command_received();
    void command_dequeued(CommandNode*);

private slots:
    void dequeue_command();

public slots:
    void enqueue_command(CommandNode* command_node);
    void flush();

private:
    QMutex mutex;
    int tag;
    void populate_send_bytes(CommandNode*);
    int iterate_tag();
    void validate_send_length(CommandNode* command_node);
    void mask_special_characters(CommandNode* command_node);
    ThreadSafeQueue<CommandNode*> command_queue;
};

#endif // SENDWORKER_H
