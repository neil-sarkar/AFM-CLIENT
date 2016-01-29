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

    CommandNode(unsigned char _id, QObject* _instance, QByteArray _payload) {
        id = _id;
        instance = _instance;
        payload = _payload;
    }
};

#endif // COMMANDNODE_H

