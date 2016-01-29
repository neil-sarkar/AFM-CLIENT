#include "receive_worker.h"

ReceiveWorker::ReceiveWorker(QObject *parent) : QObject(parent)
{
    QObject::connect(this, SIGNAL(command_received()), this, SLOT(dequeue_command()));
    QObject::connect(this, SIGNAL(response_byte_received()), this, SLOT(dequeue_response_byte()));
}

void ReceiveWorker::enqueue_command(CommandNode* command_node) {
    command_queue.enqueue(command_node);
    emit command_received();
}

void ReceiveWorker::dequeue_command() {
    qDebug() << "Receive Worker dequeueing " << command_queue.dequeue()->id;
}

void ReceiveWorker::enqueue_response_byte(char byte) {
    response_byte_queue.enqueue(byte);
    emit response_byte_received();
}

void ReceiveWorker::dequeue_response_byte() {
    qDebug() << "Receive Worker dequeuing " << response_byte_queue.dequeue();
}
