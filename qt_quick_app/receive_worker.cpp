#include "receive_worker.h"

ReceiveWorker::ReceiveWorker(QObject *parent) : QObject(parent)
{
    QObject::connect(this, SIGNAL(command_received()), this, SLOT(dequeue_command()));
}

void ReceiveWorker::enqueue_command(CommandNode* command_node) {
    command_queue.enqueue(command_node);
    emit command_received();
}

void ReceiveWorker::dequeue_command() {
    qDebug() << "Receive Worker dequeueing " << command_queue.dequeue()->id;
}

