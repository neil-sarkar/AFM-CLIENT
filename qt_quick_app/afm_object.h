#ifndef AFMOBJECT_H
#define AFMOBJECT_H

#include <QObject>
#include "command_node.h"

class AFMObject : public QObject
{
    Q_OBJECT
public:
    explicit AFMObject();
    virtual void init();
    typedef std::function<void(QByteArray paylaod)> callback_return_type;

signals:
    void command_generated(CommandNode* command);

private:

public slots:
};

#endif // AFMOBJECT_H
