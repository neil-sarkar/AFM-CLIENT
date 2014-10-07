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
    float _returnBytes;

    forever {
        //QThread::msleep(1000);
        //mutex.lock();
        if (!_abort) {
            //condition.wait(&mutex);
        }

        if (_abort) {
            emit finished();
            //mutex.unlock();
            return;
        }

        if(!m_queue.empty()){
            commandNode* _node = m_queue.front();
            _command = _node->getcommandName();
            //mutex.unlock();
            mutex.lock();

            qDebug() << "Received method : " << _command << endl;
            switch(_command) {
            case writeDAC:
                _dacID = _node->getdacID();
                _val = _node->getdval();
                //dowriteDAC(_dacID,_val);
                m_afm.writeDAC((qint8)_dacID,(double)_val);
                break;
            case readDAC:
                _dacID = _node->getqval();
                _returnBytes = m_afm.readDAC(_dacID);
                return_queue.push(new returnBuffer<int>('i', _returnBytes));
                break;
            case readADC:
                _dacID = _node->getqval();
                _returnBytes = m_afm.readADC(_dacID);
                return_queue.push(new returnBuffer<int>('i', _returnBytes));
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
                _val = _node->getdval();
                m_afm.memsSetAmplitude(_val);
                break;
            case memsSetBridgeVoltage:
                _val = _node->getdval();
                m_afm.memsSetBridgeVoltage(_val);
                break;
            case stageSetStep:
                m_afm.stageSetStep();
                break;
            case pidEnable:
                _success = m_afm.pidEnable();
                return_queue.push(new returnBuffer<int>('i',_success));
                break;
            case pidDisable:
                _success = m_afm.pidDisable();
                return_queue.push(new returnBuffer<int>('i',_success));
                break;
            case pidSetP:
                m_afm.pidSetP(_node->getP());
                break;
            case pidSetI:
                m_afm.pidSetI(_node->getI());
                break;
            case pidSetD:
                m_afm.pidSetD(_node->getD());
                break;
            case pidSetPoint:
                m_afm.pidSetPoint(_node->getval1());
                break;
            case stageSetDirBackward:
                m_afm.stageSetDirBackward();
                break;
            case stageSetPulseWidth:
                m_afm.stageSetPulseWidth(_node->getqval());
                break;
            case setPorts:
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
                    //qDebug() << detectedSerialPorts.at(0).portName() << endl;
                    m_afm.setPort(detectedSerialPorts.at(0));
                    m_afm.open(QIODevice::ReadWrite);
                    m_afm.setBaudRate(78600);
                }
               // QSerialPortInfo _test = detectedSerialPorts.at(0);
                returnBuffer<int>* _buffer = new returnBuffer<int>('Q',1,detectedSerialPorts);
                return_queue.push(_buffer);
                break;
            }

            m_queue.pop();
            mutex.unlock();
        }
        else
        {
            //mutex.unlock();
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
    //mutex.unlock();
    _abort = true;
    condition.wakeOne();
}
