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

public slots:
    void enqueue_command(CommandNode*);

private slots:
    void dequeue_command();

private:
    ThreadSafeQueue<CommandNode*> command_queue;

};

#endif // RECEIVEWORKER_H
