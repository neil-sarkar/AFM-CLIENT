#include "send_worker.h"
#include "constants.h"
#include <assert.h>
#include <QDebug>

SendWorker::SendWorker(QObject *parent) : QObject(parent)
{
    tag = -1;
    QObject::connect(this, SIGNAL(command_received()), this, SLOT(dequeue_command()));
}

void SendWorker::enqueue_command(CommandNode* command_node) {
    qDebug() << "enqueueing";
    command_node->tag = iterate_tag(); // assign tag then increment
    assert (command_queue.isFull() == false);
    command_queue.enqueue(command_node);
    emit command_received(); // emit this signal so that we're processing dequeue's in the send_workers event loop, not in the caller thread's event loop which would be blocking
}

void SendWorker::dequeue_command() {
    qDebug() << "dequeue command";
    assert(command_queue.isEmpty() == false);
    CommandNode* command_node = command_queue.dequeue();
    qDebug() << "about to populate sned bytes";
    populate_send_bytes(command_node);
    qDebug() << "pre command dequeue";
    emit command_dequeued(command_node);
    qDebug() << "command dequeued emitted";
}

void SendWorker::populate_send_bytes(CommandNode* command_node) {
    validate_send_length(command_node); // Check if the payload given has the right number of bytes
    mask_special_characters(command_node);
    command_node->payload.insert(0, command_node->id);
    command_node->payload.insert(0, command_node->tag);
    // so now it looks like [tag, id, original payload)
}

int SendWorker::iterate_tag() {
    tag = (tag + 1) % 256;
    if (tag == Message_Delimiter || tag == Escape_Character || tag == Special_Message_Character) // we can't write these - they're deemed special characters
        return iterate_tag();
    return tag;
}

void SendWorker::validate_send_length(CommandNode* command_node) {
    if (command_node->payload.length() != command_node->num_send_bytes - Num_Meta_Data_Bytes)
        qDebug() << command_node->payload.length() << command_node->num_send_bytes - Num_Meta_Data_Bytes;
        assert (command_node->payload.length() == command_node->num_send_bytes - Num_Meta_Data_Bytes);
    // we haven't added the tag or id yet, hence subtract num_meta_data_bytes
}

void SendWorker::mask_special_characters(CommandNode* command_node) {
    for (int i = 0; i < command_node->payload.length(); i++) {
        char payload_byte = command_node->payload[i];
        if (payload_byte == Newline_Character || payload_byte == Escape_Character) {
            command_node->payload[i] = payload_byte | Mask_Character;
            command_node->payload.insert(i, Escape_Character);
        }
    }
}

void SendWorker::flush() {
    while (command_queue.count())
        delete command_queue.dequeue();
}
