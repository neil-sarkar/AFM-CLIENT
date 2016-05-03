#ifndef GLOBALS_H
#define GLOBALS_H
#include <QHash>
#include <QMutex>
#include <QRgb>
#include <QColor>
#include "command_node.h"

class AFMObject;
extern QHash<QString, CommandNode> command_hash;
extern QVector<QColor> color_map;
extern bool port_writing_command;
extern bool is_approaching;
extern bool is_scanning;
extern QMutex mutex;
typedef qint32 point;
typedef qint32 double_point; // it's the same as point, for now, since plus/minus 4095 * 2 still would fit in plus/minus 2^16
typedef quint16 coordinate;
typedef QHash<QString, AFMObject*> peripheral_collection;

#endif // GLOBALS_H
