#include "send_worker.h"
#include <QDebug>

SendWorker::SendWorker(QObject *parent) : QObject(parent)
{
    tag = 0;
    QObject::connect(this, SIGNAL(command_received()), this, SLOT(dequeue_command()));
}

void SendWorker::enqueue_command(CommandNode* command_node) {
    command_node->tag_number = tag++; // assign tag then increment
    command_queue.enqueue(command_node);
    qDebug() << "Enqueued" << command_node->tag_number;
    emit command_received(); // could also just call dequeue_command right away
}

CommandNode* SendWorker::dequeue_command() {
    CommandNode* command_node = command_queue.dequeue();
    qDebug() << "Dequeued" << command_node->tag_number;
    return command_node;
}
