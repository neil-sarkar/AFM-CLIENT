#include "command_node.h"

CommandNode::CommandNode(const CommandNode& other, QObject* _instance, QByteArray _payload) {
    id = other.id;
    num_receive_bytes = other.num_receive_bytes;
    num_send_bytes = other.num_send_bytes;
    instance = _instance;
    payload = _payload;
}

CommandNode::CommandNode(const CommandNode& other, std::function<void(QByteArray)> _process_callback, QByteArray _payload) {
    id = other.id;
    num_receive_bytes = other.num_receive_bytes;
    num_send_bytes = other.num_send_bytes;
    process_callback = _process_callback;
    payload = _payload;
}

CommandNode::CommandNode(const CommandNode& other) {
    id = other.id;
    num_receive_bytes = other.num_receive_bytes;
    num_send_bytes = other.num_send_bytes;
}

CommandNode& CommandNode::operator=( const CommandNode& other) {
     id = other.id;
     num_receive_bytes = other.num_receive_bytes;
     num_send_bytes = other.num_send_bytes;
     return *this;
}

CommandNode::~CommandNode() {}
AbstractCommandNode::~AbstractCommandNode() {}
