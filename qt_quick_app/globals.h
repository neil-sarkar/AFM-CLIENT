#ifndef GLOBALS_H
#define GLOBALS_H

#include <QHash>
#include <QMutex>
#include <QRgb>
#include <QColor>
#include "command_node.h"

extern QHash<QString, CommandNode> command_hash;
extern QHash<double, QColor> color_map;
extern bool port_writing_command;
extern bool is_approaching;
extern QMutex mutex;

#endif // GLOBALS_H
