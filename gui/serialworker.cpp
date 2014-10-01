#include "serialworker.h"
#include "afm.h"
#include <QThread>
#include <QEventLoop>
#include <iostream>
#include <queue>
#include <returnBuffer.h>

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
    QList<QSerialPortInfo>& detectedSerialPorts = QList<QSerialPortInfo>();
    int _success;

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
            //QMutexLocker locker(&mutex);
            switch(_command) {
            case writeDAC:
                mutex.lock();
                _dacID = _node->getval1();
                _val = _node->getval2();
                //dowriteDAC(_dacID,_val);
                m_afm.writeDAC((qint8)_node->getqval(),(double)_node->getdval());
                mutex.unlock();
                break;
            case readDAC:
                mutex.lock();
                 //QMutexLocker(&mutex);
                _dacID = _node->getqval();
                //_returnBuffer = _node->getreturnBuffer();
                //_returnBytes = m_afm.readDAC(_dacID);
                //_node->setreturnBuffer(4);

                return_queue.push(new returnBuffer<int>('i', (int)m_afm.readDAC(_dacID)));
                mutex.unlock();
                break;
            case readADC:
                mutex.lock();
                //QMutexLocker(&mutex);
                _dacID = _node->getqval();
                return_queue.push(new returnBuffer<int>('i', (int)m_afm.readADC(_dacID)));
                mutex.unlock();
                break;
            case setRasterStep:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.setRasterStep();
                mutex.unlock();
                break;
            case memsSetOffset:
                mutex.lock();
                //QMutexLocker(&mutex);
                _val = _node->getval1();
                m_afm.memsSetOffset(_val);
                mutex.unlock();
                break;
            case memsSetFrequency:
                mutex.lock();
                //QMutexLocker(&mutex);
                _val = _node->getval1();
                m_afm.memsSetFrequency(_val);
                break;
            case memsSetAmplitude:
                mutex.lock();
                //QMutexLocker(&mutex);
                _val = _node->getdval();
                m_afm.memsSetAmplitude(_val);
                mutex.unlock();
                break;
            case memsSetBridgeVoltage:
                mutex.lock();
                //QMutexLocker(&mutex);
                _val = _node->getdval();
                m_afm.memsSetBridgeVoltage(_val);
                mutex.unlock();
                break;
            case stageSetStep:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.stageSetStep();
                break;
            case pidEnable:
                mutex.lock();
               // QMutexLocker(&mutex);
                _success = m_afm.pidEnable();
                return_queue.push(new returnBuffer<int>('i',_success));
                break;
            case pidDisable:
                mutex.lock();
                //QMutexLocker(&mutex);
                _success = m_afm.pidDisable();
                return_queue.push(new returnBuffer<int>('i',_success));
                break;
            case pidSetP:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.pidSetP(_node->getP());
                break;
            case pidSetI:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.pidSetI(_node->getI());
                break;
            case pidSetD:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.pidSetD(_node->getD());
                break;
            case pidSetPoint:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.pidSetPoint(_node->getval1());
                break;
            case stageSetDirBackward:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.stageSetDirBackward();
                break;
            case stageSetPulseWidth:
                mutex.lock();
                //QMutexLocker(&mutex);
                m_afm.stageSetPulseWidth(_node->getqval());
                break;
            case setPorts:
                mutex.lock();
                //QMutexLocker(&mutex);
                detectedSerialPorts = QSerialPortInfo::availablePorts();
                if(detectedSerialPorts.size()==0)
                {
                    //QMessageBox msgBox;
                    //msgBox.setText("Unable to find any serial ports.");
                   // msgBox.exec();
                    qDebug() << "Unable to find any serial ports." << endl;
                }
                else
                {
                    m_afm.setPort(detectedSerialPorts.at(0));
                    m_afm.open(QIODevice::ReadWrite);
                }
               // QSerialPortInfo _test = detectedSerialPorts.at(0);
                returnBuffer<QList<QSerialPortInfo>> _buffer = returnBuffer<QList<QSerialPortInfo>>('Q',detectedSerialPorts);
                //return_queue->push(&_buffer);
                mutex.unlock();
                break;
            }

            m_queue.pop();
        }
        else
        {
            mutex.unlock();
        }
    }
}

/* The requestMethod initializes a method to be called from mainLoop
 *
 * Params: a method to be called

   This function sets placeholders for the method and all arguments required
*/

void serialworker::requestCommand(Command command)
{
    //QMutexLocker locker(&mutex);
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
    //QMutexLocker locker(&mutex);
    _command = command;
    _dacID = dacID;
    _val = val;
    condition.wakeOne();
}

float serialworker::doreadDAC(qint8 dacID)
{
    /*CALL AFM CODE*/
    float dacval = m_afm.readDAC(dacID);
    return dacval;
    //return AFM_SUCCESS;
}
float serialworker::doreadADC(qint8 adcID)
{
    /*CALL AFM CODE*/
    float adcval = m_afm.readADC(adcID);
    return adcval;
    //return AFM_SUCCESS;
}
void serialworker::abort()
{
    //QMutexLocker locker(&mutex);
    _abort = true;
    condition.wakeOne();
}
