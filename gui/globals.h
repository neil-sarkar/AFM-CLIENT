#ifndef GLOBALS_H
#define GLOBALS_H

// ALL THE GLOBAL DECLARATIONS

#include <QMutex>
#include <commandnode.h>
#include <afm.h>
#include <returnbuffer.h>

extern QMutex mutex; //to be used when two threads are trying to access the afm at the same time


struct receivetype{
    returnType name;
    int numBytes;
};

//nanoiAFM *m_afm;

#endif// GLOBALS_H
