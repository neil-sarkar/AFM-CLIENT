#ifndef GLOBALS_H
#define GLOBALS_H

// ALL THE GLOBAL DECLARATIONS

#include <QMutex>
#include <commandnode.h>
#include <afm.h>
#include <returnbuffer.h>
#include <afm_worker.h>

extern QMutex mutex; //to be used when two threads are trying to access the afm at the same time

//node struct for receiveQueue
struct receivetype{
    returnType name;
    char message_id;
    char message_tag;
    int writeByte_result;
};

#endif// GLOBALS_H
