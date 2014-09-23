#include "serialworker.h"
#include "afm.h"
#include <QThread>
#include <QEventLoop>
#include <iostream>

/*SERIAL WORKER
    -Objective: Separate serial Read/Write from the GUI thread
    -Methods: requestMethod(Method)
    -Info: mainLoop will wait for methods to be requested. */
serialworker::serialworker(QObject *parent) :
QObject(parent)
{
    _abort = false;
}

/*This main loop will constantly check for methods to call
if _method matches a case in the switch statement the
corresponding method will be called. if _abort is ever set to
true the thread will exit.*/
void serialworker::mainLoop()
{
    forever {

        mutex.lock();
        if (!_abort) {
            condition.wait(&mutex);
        }

        if (_abort) {
            emit finished();
            mutex.unlock();
            return;
        }

        Method method = _method;
        mutex.unlock();

        switch(method) {
        case writeDAC:
            dowriteDAC(_dacID,_val);
            break;
//        case readDAC:
//            doreadDAC();
//            break;
        }
    }
}

/* The requestMethod initializes a method to be called from mainLoop
 *
 * Params: a method to be called

   This function sets placeholders for the method and all arguments required
*/

void serialworker::requestMethod(serialworker::Method method)
{
    QMutexLocker locker(&mutex);
    _method = method;
    condition.wakeOne();
}

/* The requestMethod overloaded to support writing to DAC
 *
 * Params: a method to be called
          a dacID
          a value to set the DAC
*/
void serialworker::requestMethod(serialworker::Method method, qint8 dacID, double val)
{
    QMutexLocker locker(&mutex);
    _method = method;
    _dacID = dacID;
    _val = val;
    condition.wakeOne();
}

void serialworker::dowriteByte(char byte)
{
    //afm.writeByte(byte);
}

void serialworker::dowriteDAC(qint8 dacID, double val)
{
    /*CALL AFM CODE*/
    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

//    if (abort) {
//        break;
//    }
    //afm.writeByte(byte);
    double newval = val;
    qDebug() << "DAC ID: " << dacID << endl;
    qDebug() << "Value received from main thread: " << newval << endl;
    //afm.writeDAC(dacID,newval);
    //return AFM_SUCCESS;
}

double serialworker::doreadDAC()
{
    /*CALL AFM CODE*/
    //float dacval = afm.readDAC();
    double dacval = 2;
    return dacval;
    //return AFM_SUCCESS;
}

void serialworker::abort()
{
    QMutexLocker locker(&mutex);
    _abort = true;
    condition.wakeOne();
}
