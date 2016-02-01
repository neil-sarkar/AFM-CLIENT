#ifndef AFMOBJECT_H
#define AFMOBJECT_H

#include <QObject>
#include "command_node.h"

class AFMObject : public QObject
{
    Q_OBJECT
public:
    explicit AFMObject();

signals:
    void command_generated(CommandNode* command);

public slots:
};

#endif // AFMOBJECT_H
