#include "receive_worker.h"
#include "assert.h"
#include "constants.h"
#include "adc.h"
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
    assert (response_byte_queue.isFull() == false);
    response_byte_queue.enqueue(byte);
    emit response_byte_received();
}

void ReceiveWorker::build_working_response() {
    // Relevant test cases: escape, newline | escape escape | escape newline newline | escape (char when unmasked returns escape) (another char) |
    assert (!response_byte_queue.isEmpty());
    quint8 byte = response_byte_queue.dequeue();

    if (byte == Escape_Character && !escape) {
        escape = true;
        return;
    }
    if (escape) { // previous char was escape character
        byte &= ~Mask_Character; // unmask byte
        escape = false;
        working_response += byte;
        return;
    }
    if (byte == Message_Delimiter) { // if we're seeing a newline, it could mean the message is done or just be garbage at the beginning of a message
        if (working_response.length() >= Message_Size_Minimum) { // minimum message size on return would be 2, this implies we have a complete message
            if (static_cast<unsigned char>(working_response.at(0)) == Special_Message_Character)
                handle_asynchronous_message();
            else if (command_queue.count()) {
                process_working_response(); // could technically spin up a new thread for each response process
            }
            else
                qDebug() << "This async command is not accounted for" << static_cast<unsigned char>(working_response.at(0)) << working_response;
            working_response.clear();
            return;
        } else if (!working_response.length()) { // if we're starting a message with a newline, we ignore it because it doesn't tell us anything
            return;
        }
    }
    working_response += byte;
}

void ReceiveWorker::process_working_response() {
    unsigned char response_tag = working_response.at(0);
    unsigned char response_id = working_response.at(1);
    qDebug() << "Now processing" << response_tag << response_id << working_response;
    assert (command_queue.isEmpty() == false);
    CommandNode* node = command_queue.dequeue();
    assert_return_integrity(node, response_tag, response_id, working_response.length());
    if (node->process_callback) {
        node->process_callback(working_response.right(working_response.length() - 2)); // maybe run in separate thread to avoid blocking
    }
    delete node;
}

void ReceiveWorker::assert_return_integrity(CommandNode* node, unsigned char tag, unsigned char id, int length) {
    if (tag != node->tag) {
        qDebug() << "tag mismatch " << tag << node->tag;
        assert (tag == node->tag);
    }
    assert (id  == node->id);

    if (node->num_receive_bytes == Set_Receive_Bytes_Error) {
        qDebug() << "User must set number of receive bytes at time of dynamic command creation";
    }

    if (length != node->num_receive_bytes) {
        qDebug() << length << node->num_receive_bytes << node->id;
    }

    assert (length == node->num_receive_bytes);
}

void ReceiveWorker::handle_asynchronous_message() {
    qDebug() << "Received async message" << working_response;
    if (is_mcu_reset_message())
        emit mcu_reset_message_received();
    else if (is_auto_approach_info())
        emit auto_approach_info_received(working_response.right(working_response.length() - 2));
    else if (is_auto_approach_stopped_message())
        handle_auto_approach_stopped_message();
    else if (static_cast<unsigned char>(working_response.at(1)) == 0xaa) {
        qDebug() << "BUFFER FULL";
        assert(false);
    } else
        qDebug() << "unknown message" << working_response;
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

bool ReceiveWorker::is_auto_approach_info() {
    if (static_cast<unsigned char>(working_response.at(1)) == Auto_Approach_Info_Character)
        return true;
    return false;
}

bool ReceiveWorker::is_auto_approach_stopped_message() {
    qDebug() << static_cast<unsigned char>(working_response.at(1)) << Auto_Approach_Stopped_Character;
    return (static_cast<unsigned char>(working_response.at(1)) == Auto_Approach_Stopped_Character);
}

void ReceiveWorker::handle_auto_approach_stopped_message() {
    // I think the MCU auto approach routine is blocking - it would be better to trigger it on interrupt
    // Either way, to circumvent that for now, we have to flush all the commands that came
    // before the stop message, and just stop all execution
    bool stop_command_had_been_queued = false;
    while (command_queue.count()) {
        CommandNode* node = command_queue.dequeue();
        if (node->id == Auto_Approach_Stopped_Character)
            stop_command_had_been_queued = true;
        delete node;
    }

    // assert(stop_command_had_been_queued);
    qDebug() << "Command queue flushed - new count" << command_queue.count();
}

void ReceiveWorker::flush() {
    qDebug() << "here" << command_queue.count();
    while (command_queue.count())
        delete command_queue.dequeue();
    while (response_byte_queue.count())
        response_byte_queue.dequeue();
}

const unsigned char ReceiveWorker::MCU_Reset_Message[5] = {0xF2, 0x61, 0x66, 0x6d, 0x21};
