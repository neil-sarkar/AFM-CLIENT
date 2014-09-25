#include "serialworker.h"
#include "afm.h"
#include <QThread>
#include <QEventLoop>
#include <iostream>
#include <queue>
using std::queue;

/***********************************************************************
 * SERIAL WORKER
    -Objective: Separate serial Read/Write from the GUI thread
    -Methods: requestMethod(Method)
    -Info: mainLoop will wait for methods to be requested.

This main loop will constantly check for methods to call
if _method matches a case in the switch statement the
corresponding method will be called. if _abort is ever set to
true the thread will exit.
***********************************************************************/
void serialworker::mainLoop()
{
    _abort = false;

//    QList<QSerialPortInfo> detectedSerialPorts = QSerialPortInfo::availablePorts();
//    if(detectedSerialPorts.size()==0)
//    {
//        //QMessageBox msgBox;
//        //msgBox.setText("Unable to find any serial ports.");
//        //msgBox.exec();
//        qDebug() << "Unable to find any serial ports." << endl;
//    }
//    else
//    {
//        afm->setPort(detectedSerialPorts.at(0));
//        afm->open(QIODevice::ReadWrite);
//    }

    forever {
        //QThread::msleep(1000);
        mutex.lock();
        if (!_abort) {
            //condition.wait(&mutex);
        }

        if (_abort) {
            emit finished();
            mutex.unlock();
            return;
        }

        if(!m_queue.empty()){
            commandNode* _node = m_queue.front();
            _command = _node->getcommandName();
            mutex.unlock();

            qDebug() << "Received method : " << _command << endl;

            switch(_command) {
            case writeDAC:
                _dacID = _node->getval1();
                _val = _node->getval2();
                //dowriteDAC(_dacID,_val);
                m_afm.writeDAC((char)_node->getdacID(),(double)_node->getdval());
                break;
            case readDAC:
                _dacID = _node->getdacID();
                _returnBytes = _node->getreturnBytes();
                //_returnBytes = afm.readDAC(_dacID);
                _returnBytes = 4;
                break;
            case setRasterStep:
                m_afm.setRasterStep();
                break;
            case memsSetOffset:
                _val = _node->getval1();
                m_afm.memsSetOffset(_val);
                break;
            case memsSetFrequency:
                _val = _node->getval1();
                m_afm.memsSetFrequency(_val);
                break;
            case memsSetAmplitude:
                _val = _node->getval1();
                m_afm.memsSetAmplitude(_val);
                break;
            case memsSetBridgeVoltage:
                _val = _node->getval1();
                m_afm.memsSetBridgeVoltage(_val);
                break;
            }
            m_queue.pop();
        }
        else{mutex.unlock();}
    }
}

/* The requestMethod initializes a method to be called from mainLoop
 *
 * Params: a method to be called

   This function sets placeholders for the method and all arguments required
*/

void serialworker::requestCommand(Command command)
{
    QMutexLocker locker(&mutex);
    //_method = method;
    condition.wakeOne();
}

/* The requestMethod overloaded to support writing to DAC
 *
 * Params: a method to be called
          a dacID
          a value to set the DAC
*/
void serialworker::requestCommand(Command command, qint8 dacID, double val)
{
    QMutexLocker locker(&mutex);
    _command = command;
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
