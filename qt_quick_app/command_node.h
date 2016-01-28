#ifndef COMMANDNODE_H
#define COMMANDNODE_H

#include <QObject>
#include <functional>
#include <QDebug>

class CommandNode : public QObject {
    Q_OBJECT
public:
    unsigned char message_id;
    std::function<QByteArray()> execute_command;
    std::function<void()> execute_postamble;
    std::function<void()> update_UI;
    QByteArray afm_return_value;
    int tag_number;

    CommandNode(std::function<QByteArray()> x, std::function<void()> y, std::function<void()> z) {
        execute_command = x;
        execute_postamble = y;
        update_UI = z;
        qDebug() << execute_command();
    }
};

#endif // COMMANDNODE_H

