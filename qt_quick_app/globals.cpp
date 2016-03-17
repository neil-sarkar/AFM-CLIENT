#include "globals.h"

QHash<QString, CommandNode> command_hash;
bool port_writing_command = false;
QMutex mutex;
