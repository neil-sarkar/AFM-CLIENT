#include "receive_worker.h"
#include "assert.h"
#include "constants.h"
#include "adc.h"
#include <QtConcurrent>
#include "globals.h"

ReceiveWorker::ReceiveWorker(QObject *parent) : QObject(parent){
    escape = false;

}

void ReceiveWorker::enqueue_command(CommandNode* command_node) {
    assert (receive_command_queue.isFull() == false);
    receive_command_queue.enqueue(command_node);
}

void ReceiveWorker::enqueue_response_byte(char byte) {
    assert (response_byte_queue.isFull() == false);
    response_byte_queue.enqueue(byte);
    emit response_byte_received();
}

void ReceiveWorker::build_working_response() {
    // Relevant test cases: escape, newline | escape escape | escape newline newline | escape (char when unmasked returns escape) (another char) |
    if (response_byte_queue.isEmpty()) // this could happen when we have a hard MCU reset where we have pending signals trying to call this slot after the queue is emptied in another operation
        return;
    quint8 byte = response_byte_queue.dequeue();
    if (byte == Escape_Character && !escape) {
//        qDebug() << "GOT ESCAPE";
        escape = true;
        return;
    }
    if (escape) { // previous char was escape character
//        qDebug() << byte;
        byte &= ~Mask_Character; // unmask byte
//        qDebug() << byte;
        escape = false;
        working_response += byte;
        return;
    }
    if (byte == Message_Delimiter) { // if we're seeing a newline, it could mean the message is done or just be garbage at the beginning of a message
//        qDebug() <<"Response length" << working_response.length();
        if (working_response.length() >= Message_Size_Minimum) { // minimum message size on return would be 2, this implies we have a complete message
            if (static_cast<unsigned char>(working_response.at(0)) == Special_Message_Character) {
                handle_asynchronous_message(); // should really be called "special message". The "auto approach stop command" (aka the pause confirmation) also has the special character
            } else if (receive_command_queue.count()) {
                process_working_response();
            } else {
                qDebug() << "This async command is not accounted for" << static_cast<unsigned char>(working_response.at(0)) << working_response;
            }

            working_response.clear();
            return;
        } else if (!working_response.length()) { // if we're starting a message with a newline, we ignore it because it doesn't tell us anything
            return;
        }
    }
    working_response += byte;
//    qDebug() << "Working response" << working_response;
}

void ReceiveWorker::process_working_response() {
    unsigned char response_tag = working_response.at(0);
    unsigned char response_id = working_response.at(1);
    qDebug() << "Now processing" << response_tag << response_id << working_response;
    assert (receive_command_queue.isEmpty() == false);
    CommandNode* node = receive_command_queue.dequeue();
    
    if (!is_response_valid(node, response_tag, response_id, working_response.length())) { // check temporal order is correct
        handle_invalid_response();
    } else if (node->process_callback) {
        node->process_callback(working_response.right(working_response.length() - Num_Meta_Data_Bytes)); // maybe run in separate thread to avoid blocking
    }

    emit receive_returned();
    delete node;
}

void ReceiveWorker::handle_invalid_response() {
    qDebug() << "Invalid response received";
    // one possible reason for an invalid response is that we had a hard reset button reset in the process
    // iterate through receive_command_queue to see if that was the case
    while (response_byte_queue.count()) {
        if (static_cast<unsigned char>(response_byte_queue.dequeue()) == Special_Message_Character) {
            qDebug() << "Special message character found; resetting";
            handle_hardware_reset();
        }
    }
}

bool ReceiveWorker::is_response_valid(CommandNode* node, unsigned char tag, unsigned char id, int length) {
    if (tag != node->tag) {
        qDebug() << "tag mismatch " << tag << node->tag;
        return false;
    }

    if (id != node->id) {
        qDebug() << "id mismatch " << id<< node->id;
        return false;
    }

    if (node->num_receive_bytes == Set_Receive_Bytes_Error) {
        qDebug() << "User must set number of receive bytes at time of dynamic command creation";
        return false;
    }

    if (length != node->num_receive_bytes) {
        qDebug() << "Length mismatch, got: " << length << "| expected:" << node->num_receive_bytes << "| for ID " << node->id;
        return false;
    }
    return true;
}

void ReceiveWorker::handle_hardware_reset() {
    mutex.lock();
    port_writing_command = false;
    mutex.unlock();
    flush();
}

void ReceiveWorker::handle_asynchronous_message() {
    qDebug() << "Received async message" << working_response;
    if (is_mcu_reset_message())
        handle_hardware_reset();
    else if (is_auto_approach_info())
        emit auto_approach_info_received(working_response.right(working_response.length() - 2));
    else if (is_auto_approach_stopped_message())
        handle_auto_approach_stopped_message();
    else if (static_cast<unsigned char>(working_response.at(1)) == 0xaa) {
        qDebug() << "BUFFER FULL";
        assert(false); // not sure what we should do here. this could happen if we spam the reset button infinitely.
    } else {
        qDebug() << "unknown message" << working_response;
    }
}

bool ReceiveWorker::is_mcu_reset_message() {
    if (MCU_Reset_Message_Length == working_response.length()) {
        for (int i = 0; i < MCU_Reset_Message_Length; i++) {
            if (MCU_Reset_Message[i] != static_cast<unsigned char>(working_response[i]))
                return false;
        }
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
    // I think the MCU auto approach routine is blocking - it would be better to use interrupts
    // Either way, to circumvent that for now, we have to flush all the commands that came
    // before the stop message, and just stop all execution
    while (receive_command_queue.count()) {
        CommandNode* node = receive_command_queue.dequeue();
        if (node->id == Auto_Approach_Stopped_Character)
            delete node;
    }

    qDebug() << "Command queue flushed - new count" << receive_command_queue.count();
    mutex.lock();  // TODO: look into atomic bools
    is_approaching = false;
    port_writing_command = false;
    mutex.unlock();
}

void ReceiveWorker::flush() {
    qDebug() << "Flushing receive queues" << receive_command_queue.count();
    while (receive_command_queue.count())
        delete receive_command_queue.dequeue();
    while (response_byte_queue.count())
        response_byte_queue.dequeue();
}

const unsigned char ReceiveWorker::MCU_Reset_Message[5] = {0xF2, 0x61, 0x66, 0x6d, 0x21};
const int ReceiveWorker::MCU_Reset_Message_Length = 5;
