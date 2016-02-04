#include "receive_worker.h"
#include "assert.h"
#include "constants.h"
#include <QtConcurrent>

ReceiveWorker::ReceiveWorker(QObject *parent) : QObject(parent)
{
    num_commands_received = 0;
    QObject::connect(this, SIGNAL(response_byte_received()), this, SLOT(build_working_response()));
}

void ReceiveWorker::enqueue_command(CommandNode* command_node) {
    assert (command_queue.isFull() == false);
    command_queue.enqueue(command_node);
}

void ReceiveWorker::enqueue_response_byte(char byte) {
    response_byte_queue.enqueue(byte);
    emit response_byte_received();
}

void ReceiveWorker::build_working_response() {
    char byte = response_byte_queue.dequeue();
    if (byte == Message_Delimiter) { // if we're seeing a newline, it could mean the message is done or just be garbage at the beginning of a message
        if (working_response.length() >= Message_Size_Minimum) { // minimum message size on return would be 2, this implies we have a complete message
            if (command_queue.count())
                process_working_response(); // could technically spin up a new thread for each response process
            else if (static_cast<unsigned char>(working_response.at(0)) == Special_Message_Character) {
                qDebug() << "got async message";
                handle_asynchronous_message();
            } else {
                qDebug() << "i dont know" << working_response.at(0);
            }
            working_response.clear();
            return;
        } else if (!working_response.length()) { // if we're starting a message with a newline, we ignore it because it doesn't tell us anything
            return;
        }
    }

    if (working_response.length() && working_response.at(working_response.length() - 1) == Escape_Character) { // previous char was escape character
        byte &= ~Mask_Character; // unmask byte
        working_response = working_response.remove(working_response.length() - 1, 1); // remove the escape char from the working_response
    }
    working_response += byte;

}

void ReceiveWorker::process_working_response() {
    unsigned char response_tag = working_response.at(0);
    unsigned char response_id = working_response.at(1);
    qDebug() << "Now processing" << response_tag << response_id << working_response.toHex();

    assert (command_queue.isFull() == false);
    CommandNode* node = command_queue.dequeue();
    num_commands_received += 1;
    assert_return_integrity(node, response_tag, response_id, working_response.length());
    if (node->process_callback) {
        QtConcurrent::run(node->process_callback, working_response.right(working_response.length() - 2)); // to avoid blocking this thread
    }
    delete node;
}

void ReceiveWorker::assert_return_integrity(CommandNode* node, unsigned char tag, unsigned char id, int length) {
    if (tag != node->tag) {
        qDebug() << "Command queue count" << command_queue.count();
        qDebug() << "Number of commands received" << num_commands_received;
        qDebug() << "tag mismatch " << tag << node->tag;
        assert (tag == node->tag);
    }
    assert (id  == node->id);

    if (node->num_receive_bytes == Set_Receive_Bytes_Error) {
        qDebug() << "User must set number of receive bytes at time of dynamic command creation";
    }

    if (length != node->num_receive_bytes) {
        qDebug() << length << node->num_receive_bytes;
    }

    assert (length == node->num_receive_bytes);
}

void ReceiveWorker::handle_asynchronous_message() {
    if (is_mcu_reset_message())
        emit mcu_reset_message_received();
}

bool ReceiveWorker::is_mcu_reset_message() {
    if (MCU_Reset_Message_Length == working_response.length()) {
        for (int i = 0; i < MCU_Reset_Message_Length; i++)
            if (MCU_Reset_Message[i] != static_cast<unsigned char>(working_response[i]))
                return false;
        return true;
    }
    return false;
}

const unsigned char ReceiveWorker::MCU_Reset_Message[5] = {0xF2, 0x61, 0x66, 0x6d, 0x21};
