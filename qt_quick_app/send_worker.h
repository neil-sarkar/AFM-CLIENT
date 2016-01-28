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

public slots:
    void enqueue_command(CommandNode* command_node);

private:
    QMutex mutex;
    int tag;
    ThreadSafeQueue<CommandNode*> command_queue;
    CommandNode* dequeue_command();

};

#endif // SENDWORKER_H
