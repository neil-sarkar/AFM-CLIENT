#ifndef COMMANDNODE_H
#define COMMANDNODE_H

#include <QObject>
#include <functional>
#include <QDebug>

struct AbstractCommandNode : public QObject {
    virtual ~AbstractCommandNode() = 0;
};

class CommandNode : public AbstractCommandNode {
    Q_OBJECT
public:
    unsigned char id;
    QByteArray payload;
    std::function<void(QByteArray)> process_callback;
    int tag;

    // these are not unsigned because we can set -1 for errors
    int num_receive_bytes;
    int num_send_bytes;

    CommandNode(const CommandNode& other, QByteArray _payload);
    CommandNode(const CommandNode& other, std::function<void(QByteArray)> _process_callback, QByteArray _payload = 0);
    CommandNode() {}
    CommandNode(const CommandNode& other); // copy constructor
    CommandNode& operator=( const CommandNode& other);
    ~CommandNode();

private:
};

#endif // COMMANDNODE_H

