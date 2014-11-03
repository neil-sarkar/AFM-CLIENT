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
    QList<QSerialPortInfo>* detectedSerialPorts = new QList<QSerialPortInfo>();
    QVector<double>* _amplitude = new QVector<double>();
    QVector<double>* _frequency = new QVector<double>();
    int _bytesRead = 0;


    forever {

        if (_abort) {
            emit finished();
            return;
        }

        /* Prevent any other threads from writing or reading from the buffers
         * until this thread is finished the appropriate reads and writes*/
        mutex.lock();
        while(!m_queue.empty()){

            commandNode* _node = m_queue.front();
            _command = _node->getcommandName();

            switch(_command) {
                case writeDAC:
                    _ID = _node->getqval();
                    _val = _node->getdval();
                    m_afm.writeDAC((qint8)_ID,(double)_val);
                    break;
                case readDAC:
                    _ID=(qint8)_node->getqval();
                    _returnBytes = m_afm.readDAC(_ID);
                    switch(_ID){
                        case DAC_ZOFFSET_FINE:
                            return_queue.push(new returnBuffer(DACZOFFSETFINE,(float)_returnBytes));
                            break;
                        case DAC_ZOFFSET_COARSE:
                            return_queue.push(new returnBuffer(DACZOFFSETCOARSE,(float)_returnBytes));
                            break;
                        case DAC_BFRD1:
                            return_queue.push(new returnBuffer(DACBFRD1,(float)_returnBytes));
                            break;
                        case DAC_BFRD2:
                            return_queue.push(new returnBuffer(DACBFRD2,(float)_returnBytes));
                            break;
                        case DAC_BFRD3:
                            return_queue.push(new returnBuffer(DACBFRD3,(float)_returnBytes));
                            break;
                        case DAC_ZAMP:
                            return_queue.push(new returnBuffer(DACZAMP,(float)_returnBytes));
                            break;
                        case DAC_BR1:
                            return_queue.push(new returnBuffer(DACBR1,(float)_returnBytes));
                            break;
                        case DAC_BR2:
                            return_queue.push(new returnBuffer(DACBR2,(float)_returnBytes));
                            break;
                        case DAC_X1:
                            return_queue.push(new returnBuffer(DACX1,(float)_returnBytes));
                            break;
                        case DAC_X2:
                            return_queue.push(new returnBuffer(DACX2,(float)_returnBytes));
                            break;
                        case DAC_Y1:
                            return_queue.push(new returnBuffer(DACY1,(float)_returnBytes));
                            break;
                        case DAC_Y2:
                            return_queue.push(new returnBuffer(DACY2,(float)_returnBytes));
                            break;
                        case -1:
                            break;
                    }
                    break;
                case readADC:
                    _ID = _node->getqval();
                    _returnBytes = m_afm.readADC((qint8)_node->getqval());
                    if(_ID == AFM_ADC_AMPLITUDE_ID)
                        return_queue.push(new returnBuffer(AFMADCAMPLITUDEID,(float)_returnBytes));
                    else
                        return_queue.push(new returnBuffer(ADC,(float)_returnBytes));
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
                    *detectedSerialPorts = QSerialPortInfo::availablePorts();
                    _node->getdval() == 0 ? _index = 0 :_index = _node->getdval();

                    if(detectedSerialPorts->size()==0)
                        qDebug() << "Unable to find any serial ports." << endl;
                    else{
                        m_afm.setPort(detectedSerialPorts->at(_index));
                        m_afm.open(QIODevice::ReadWrite);
                        m_afm.setBaudRate(76800);
                    }
                    break;
                case getPorts:
                    *detectedSerialPorts = QSerialPortInfo::availablePorts();
                    _node->getdval() == 0 ? _index=0:_index=_node->getdval();

                    if(detectedSerialPorts->size()==0)
                        qDebug() << "Unable to find any serial ports." << endl;
                    else{
                        m_afm.setPort(detectedSerialPorts->at(_index));
                        m_afm.open(QIODevice::ReadWrite);
                        m_afm.setBaudRate(76800);
                    }

                    _buffer = new returnBuffer(GETPORTS,*detectedSerialPorts);

                    return_queue.push(_buffer);
                    break;
                 case frequencySweep:
                    *_amplitude = _node->getamplitude();
                    *_frequency = _node->getfrequency();
                    _bytesRead = _node->getbytesRead();

                    _success = m_afm.frequencySweep(_node->getnumPoints(),_node->getstartFrequency(),_node->getstepSize(),*_amplitude,*_frequency,_bytesRead);
                    _buffer = new returnBuffer(FREQSWEEP,_success,*_amplitude,*_frequency,_bytesRead);

                    return_queue.push(_buffer);
                    break;
                 case setDacValues:
                    m_afm.setDACValues(_node->getqval(),_node->getdval());
                    break;
                 case deviceCalibration:
                    _success = m_afm.deviceCalibration(_node->getdval(),'l');
                    if(_success == AFM_SUCCESS)
                        _success = m_afm.deviceCalibration(_node->getdval(),'r');
                    _buffer = new returnBuffer(DEVICECALIBRATION,_success);
                    return_queue.push(_buffer);
                    break;
                 case scanParameters:
                    _success = m_afm.scanParameters(_node->getvminLine(),_node->getvminScan(),_node->getvmax(),_node->getnumpts(),_node->getnumLines());
                    _buffer = new returnBuffer(SCANPARAMETERS,_success);
                    return_queue.push(_buffer);
                    break;
                 case startScan:
                    m_afm.startScan();
                    m_afm.scanStep();
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
    emit finished();
}
