#include "send_worker.h"
#include <QDebug>

SendWorker::SendWorker(QObject *parent) : QObject(parent)
{
    tag = 0;
}

void SendWorker::enqueue_command(CommandNode* command_node) {
    tag++;
    command_node->tag_number = tag;
    qDebug() << "Enqueueing " << command_node->tag_number;
    command_queue.enqueue(command_node);
    dequeue_command();
}

CommandNode* SendWorker::dequeue_command() {
    CommandNode* node = command_queue.dequeue();
    qDebug() << "Dequeued" << node->tag_number;
    return node;
}
