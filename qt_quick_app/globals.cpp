#include "globals.h"

QHash<QString, CommandNode> command_hash;
bool port_writing_command = false;
bool is_approaching = false;
QMutex mutex;
