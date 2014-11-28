#ifndef GLOBALS_H
#define GLOBALS_H

// ALL THE GLOBAL DECLARATIONS

#include <QMutex>
#include <commandnode.h>
#include <afm.h>
#include <returnbuffer.h>

extern QMutex mutex;

struct receivetype{
    returnType name;
    int numBytes;
};

//nanoiAFM *m_afm;

#endif// GLOBALS_H
