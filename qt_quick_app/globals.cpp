#include "globals.h"

QHash<QString, CommandNode> command_hash;
QVector<QColor> color_map;
bool port_writing_command = false;
bool is_approaching = false;
bool is_scanning = false;
QMutex mutex;
