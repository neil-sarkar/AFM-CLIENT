#include "send_worker.h"
#include <QDebug>

SendWorker::SendWorker(QObject *parent) : QObject(parent)
{}

void SendWorker::enqueue_command(CommandNode* command_node) {
    command_queue.enqueue(command_node);
}

CommandNode* SendWorker::dequeue_command() {
    return command_queue.dequeue();
}
