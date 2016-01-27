#ifndef COMMANDNODE_H
#define COMMANDNODE_H

#include <QObject>
#include <functional>


class CommandNode : public QObject
{
    Q_OBJECT
public:
    explicit CommandNode(QObject *parent = 0);
signals:
public slots:
private:
    // void functions that's are already bound to an instance of a class and has parameters set
    std::function<void()> execute_command;
    std::function<void()> execute_postamble; // the postamble action
    std::function<void()> update_UI; // the postamble action
    QByteArray afm_return_value;
    int tag_number;
};

#endif // COMMANDNODE_H
