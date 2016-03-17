#ifndef GLOBALS_H
#define GLOBALS_H

#include <QHash>
#include <QMutex>
#include "command_node.h"

extern QHash<QString, CommandNode> command_hash;
extern bool port_writing_command;
extern QMutex mutex;

#endif // GLOBALS_H
