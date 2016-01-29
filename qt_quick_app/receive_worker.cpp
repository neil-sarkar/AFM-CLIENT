#include "receive_worker.h"

ReceiveWorker::ReceiveWorker(QObject *parent) : QObject(parent)
{
//    QObject::connect(this, SIGNAL(command_received()), this, SLOT(dequeue_command()));
    QObject::connect(this, SIGNAL(response_byte_received()), this, SLOT(build_working_response()));
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

void ReceiveWorker::build_working_response() {
    char byte = response_byte_queue.dequeue();

    if (byte == 0x0a) { // if we're seeing a newline, it could mean the message is done or just be garbage at the beginning of a message
        if (working_response.length() >= 2) { // minimum message size on return would be 2, this implies we have a complete message
            qDebug() << "Received complete message of size " << working_response.length() << ": " << working_response.toHex();
            process_working_response(); // could technically spin up a new thread for each response process
            working_response.clear();
            return;
        } else if (working_response.length() == 0) { // if we're starting a message with a newline, we ignore it because it doesn't tell us anything
            return;
        }
    }

    if (working_response.length() && working_response.at(working_response.length() - 1) == 0x10) { // previous char was escape character
        byte &= ~0x80; // unmask byte
    }

    working_response += byte;
}

void ReceiveWorker::process_working_response() {
    char response_tag = working_response.at(0);
    char response_id = working_response.at(1);
    CommandNode* node = command_queue.dequeue();

    if (response_tag == node->tag && response_id == node->id)
        node->update_UI();

    delete node;

}
