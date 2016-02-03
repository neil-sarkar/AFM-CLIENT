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
    QObject* instance;
    QByteArray payload;
    std::function<void()> process_callback;
    std::function<void()> ui_callback;
    int tag;
    unsigned int num_failed_bytes;
    int num_receive_bytes;
    int num_send_bytes;
    static void null_ting () {}

    CommandNode(const CommandNode& other, QObject* _instance, QByteArray _payload = 0);
    CommandNode(const CommandNode& other, QObject* _instance, std::function<void()> _process_callback);
    CommandNode() {}
    CommandNode(const CommandNode& other); // copy constructor
    CommandNode& operator=( const CommandNode& other);
    ~CommandNode();

private:
};

#endif // COMMANDNODE_H

