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

private slots:
    void dequeue_command();

public slots:
    void enqueue_command(CommandNode* command_node);

private:
    QMutex mutex;
    int tag;
    ThreadSafeQueue<CommandNode*> command_queue;
};

#endif // SENDWORKER_H
