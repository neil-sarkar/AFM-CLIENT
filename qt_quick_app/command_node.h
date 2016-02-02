#ifndef COMMANDNODE_H
#define COMMANDNODE_H

#include <QObject>
#include <functional>
#include <QDebug>

class CommandNode : public QObject {
    Q_OBJECT
public:
    unsigned char id;
    QObject* instance;
    QByteArray payload;
    std::function<void()> postamble;
    std::function<void()> update_UI;
    int tag;
    unsigned int num_failed_bytes;
    int num_receive_bytes;
    int num_send_bytes;

    CommandNode(unsigned char _id, QObject* _instance, QByteArray _payload = 0) {
        id = _id;
        instance = _instance;
        payload = _payload;
    }
    CommandNode() {}

     CommandNode(const CommandNode& other) {
//         instance = new QObject();
//         *instance = *other.instance;
        id = other.id;
        num_receive_bytes = other.num_receive_bytes;
        num_send_bytes = other.num_send_bytes;

     }

     CommandNode& operator=( const CommandNode& other) {
         id = other.id;
         num_receive_bytes = other.num_receive_bytes;
         num_send_bytes = other.num_send_bytes;
         return *this;
     }

private:
};

#endif // COMMANDNODE_H

