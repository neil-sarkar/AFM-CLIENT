#include "send_worker.h"
#include <QDebug>

SendWorker::SendWorker(QObject *parent) : QObject(parent)
{
    tag = 0;
    QObject::connect(this, SIGNAL(command_received()), this, SLOT(dequeue_command()));
}

void SendWorker::enqueue_command(CommandNode* command_node) {
    if (tag == 0x0A || tag == 0x10) // we can't write these - they're deemed special characters
        tag++;
    command_node->tag = tag; // assign tag then increment
    tag++;
    command_queue.enqueue(command_node);
    emit command_received(); // emit this signal so that we're processing dequeue's in the send_workers event loop, not in the caller thread's event loop which would be blocking
}

void SendWorker::dequeue_command() {
    // there should be a lookup table where it populates all the appropriate fields of the command node

    CommandNode* command_node = command_queue.dequeue();
    emit command_dequeued(command_node);
}
