#include "serialworker.h"
#include "afm.h"
#include <QThread>
#include <QEventLoop>

//serialworker::serialworker()
//{
    /*SERIAL WORKER
        -Objective: Separate serial Read/Write from the GUI thread
        -Methods: requestMethod(Method)
        -Info: mainLoop will wait for methods to be requested. */


//}
serialworker::serialworker(QObject *parent) :
QObject(parent)
{

_abort = false;
}

void serialworker::mainLoop()
{
    forever {

        mutex.lock();
        if (!_interrupt && !_abort) {
            condition.wait(&mutex);
        }
        _interrupt = false;

        if (_abort) {
            emit finished();
            mutex.unlock();
            return;
        }

        Method method = _method;
        mutex.unlock();

        switch(method) {
        case writeByte:
            dowriteByte(0);
            break;
        case readByte:
            doreadByte();
            break;
        }
    }
}

void serialworker::requestMethod(serialworker::Method method)
{
    /*Called from the GUI
        -Params: Method to be called
        -*/
    QMutexLocker locker(&mutex);
    _interrupt = true;
    _method = method;
    condition.wakeOne();
}

void serialworker::dowriteByte(char byte)
{
    /*CALL AFM CODE*/
    //afm.writeByte(byte);
    char newbyte;
    newbyte = byte;
    //return AFM_SUCCESS;
}

void serialworker::doreadByte()
{
    /*CALL AFM CODE*/
    //return AFM_SUCCESS;
}
