#include "serialworker.h"
#include "afm.h"
#include <QThread>
#include <QEventLoop>
#include <iostream>
#include <queue>
#include <returnBuffer.h>
#include <string>
#include <returnTypes.h>

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
    QVector<double>& _amplitude = QVector<double>();
    QVector<double>& _frequency = QVector<double>();
    int _bytesRead = 0;


    forever {
        if (!_abort) {
            //condition.wait(&mutex);
        }

        if (_abort) {
            emit finished();
            //mutex.unlock();
            return;
        }
        mutex.lock();
        if(!m_queue.empty()){

            commandNode* _node = m_queue.front();
            _command = _node->getcommandName();

            switch(_command) {
                case writeDAC:
                    _ID = _node->getqval();
                    _val = _node->getdval();
                    m_afm.writeDAC((qint8)_ID,(double)_val);
                    break;
                case readDAC:
                    _node->getqval() ? _ID = -1:_ID=_node->getqval();
                    _returnBytes = m_afm.readDAC((qint8)_node->getqval());
                    if(_ID == DAC_ZOFFSET_FINE)
                        return_queue.push(new returnBuffer<int>(DACZOFFSETFINE,(float)_returnBytes));
                    else if(_ID == DAC_ZOFFSET_COARSE)
                        return_queue.push(new returnBuffer<int>(DACZOFFSETCOARSE,(float)_returnBytes));
                    else if(_ID == DAC_BFRD1)
                        return_queue.push(new returnBuffer<int>(DACBFRD1,(float)_returnBytes));
                    else if(_ID == DAC_BFRD2)
                        return_queue.push(new returnBuffer<int>(DACBFRD2,(float)_returnBytes));
                    else if(_ID == DAC_BFRD3)
                        return_queue.push(new returnBuffer<int>(DACBFRD3,(float)_returnBytes));
                    else if(_ID == DAC_ZAMP)
                        return_queue.push(new returnBuffer<int>(DACZAMP,(float)_returnBytes));
                    else if(_ID == DAC_BR1)
                        return_queue.push(new returnBuffer<int>(DACBR1,(float)_returnBytes));
                    else if(_ID == DAC_BR2)
                        return_queue.push(new returnBuffer<int>(DACBR2,(float)_returnBytes));
                    else if(_ID == DAC_X1)
                        return_queue.push(new returnBuffer<int>(DACX1,(float)_returnBytes));
                    else if(_ID == DAC_X2)
                        return_queue.push(new returnBuffer<int>(DACX2,(float)_returnBytes));
                    else if(_ID == DAC_Y1)
                        return_queue.push(new returnBuffer<int>(DACY1,(float)_returnBytes));
                    else if(_ID == DAC_Y2)
                        return_queue.push(new returnBuffer<int>(DACY2,(float)_returnBytes));
                    else if(_ID == -1)
                        break;
                    else
                        return_queue.push(new returnBuffer<int>(DAC,(float)_returnBytes));
                    break;
                case readADC:
                    _ID = _node->getqval();
                    _returnBytes = m_afm.readADC((qint8)_node->getqval());
                    if(_ID == AFM_ADC_AMPLITUDE_ID)
                        return_queue.push(new returnBuffer<int>(AFMADCAMPLITUDEID,(float)_returnBytes));
                    else
                        return_queue.push(new returnBuffer<int>(ADC,(float)_returnBytes));
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
                case stageSetContinuous:
                    m_afm.stageSetContinuous();
                    break;
                case stageAbortContinuous:
                    m_afm.stageAbortContinuous();
                    break;
                case pidEnable:
                    _success = m_afm.pidEnable();
                    //return_queue.push(new returnBuffer<int>(PIDEnable,_success));
                    break;
                case pidDisable:
                    _success = m_afm.pidDisable();
                    //return_queue.push(new returnBuffer<int>(PIDDisable,_success));
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
                case stageSetDirForward:
                    m_afm.stageSetDirForward();
                    break;
                case stageSetPulseWidth:
                    m_afm.stageSetPulseWidth(_node->getqval());
                    break;
                case afmAutoApproach:
                    m_afm.autoApproach();
                    break;
                case setPort:
                    detectedSerialPorts = QSerialPortInfo::availablePorts();
                    _node->getdval() == 0 ? _index = 0 :_index = _node->getdval();
                    if(detectedSerialPorts.size()==0)
                    {
                        qDebug() << "Unable to find any serial ports." << endl;
                    }
                    else
                    {
                        m_afm.setPort(detectedSerialPorts.at(_index));
                        m_afm.open(QIODevice::ReadWrite);
                        m_afm.setBaudRate(76800);
                    }
                    break;
                case getPorts:
                    detectedSerialPorts = QSerialPortInfo::availablePorts();
                    _node->getdval() == 0 ? _index=0:_index=_node->getdval();
                    if(detectedSerialPorts.size()==0)
                    {
                        qDebug() << "Unable to find any serial ports." << endl;
                    }
                    else
                    {
                        m_afm.setPort(detectedSerialPorts.at(_index));
                        m_afm.open(QIODevice::ReadWrite);
                        m_afm.setBaudRate(76800);
                    }
                    _buffer = new returnBuffer<int>(GETPORTS,detectedSerialPorts);
                    return_queue.push(_buffer);
                    break;
                 case frequencySweep:
                    _amplitude = _node->getamplitude();
                    _frequency = _node->getfrequency();
                    _bytesRead = _node->getbytesRead();
                    _success = m_afm.frequencySweep(_node->getnumPoints(),_node->getstartFrequency(),_node->getstepSize(),_amplitude,_frequency,_bytesRead);
                    _buffer = new returnBuffer<int>(FREQSWEEP,_success,_amplitude,_frequency,_bytesRead);
                    return_queue.push(_buffer);
                    break;
                 case setDacValues:
                    m_afm.setDACValues(_node->getqval(),_node->getdval());
                    break;
            }
            m_queue.pop();

        }
        mutex.unlock();
    }
}

void serialworker::abort()
{
    //QMutexLocker locker(&mutex);
    //mutex.unlock();
    _abort = true;
    //condition.wakeOne();
}
serialworker::~serialworker()
{
    //emit finished();
}
