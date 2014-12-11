#include <serialworker.h>


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
    receivetype receivenode;



    forever {

        if (_abort) {
            delete detectedSerialPorts;
            emit finished();
            return;
        }

        /**********************************************************
         * Dequeue the command buffer and based on the command call
         * the appropriate serial call. Then push a request to read
         * the serial port to the receiver thread
         **********************************************************/

        while(!m_queue.empty()){

            commandNode* _node = m_queue.front();
            _command = _node->getcommandName();

            switch(_command) {
                case writeDAC:
                    _ID = _node->getqval();
                    _val = _node->getdval();
                    s_afm.writeDAC((qint8)_ID,(double)_val);
                    receivenode.name = WRITE;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case readDAC:
                    _ID=(qint8)_node->getqval();
                    s_afm.readDAC(_ID);
                    switch(_ID){
                        case DAC_ZOFFSET_FINE:
                            receivenode.name = DACZOFFSETFINE;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_ZOFFSET_COARSE:
                            receivenode.name = DACZOFFSETCOARSE;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_BFRD1:
                            receivenode.name = DACBFRD1;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_BFRD2:
                            receivenode.name = DACBFRD2;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_BFRD3:
                            receivenode.name = DACBFRD3;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_ZAMP:
                            receivenode.name = DACZAMP;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_BR1:
                            receivenode.name = DACBR1;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_BR2:
                            receivenode.name = DACBR2;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_X1:
                            receivenode.name = DACX1;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_X2:
                            receivenode.name = DACX2;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_Y1:
                            receivenode.name = DACY1;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case DAC_Y2:
                            receivenode.name = DACY2;
                            receivenode.numBytes = 3;
                            receive_queue.push(receivenode);
                            break;
                        case -1:
                            break;
                    }
                    break;
                case readADC:
                    _ID = _node->getqval();
                    s_afm.readADC((qint8)_ID);
                    if(_ID == ADC_ZOFFSET){
                        receivenode.name = ADCZOFFSET;
                        receivenode.numBytes = 3;
                        receive_queue.push(receivenode);
                    }
                    else if(_ID = ADC_PHASE){
                        receivenode.name = ADCPHASE;
                        receivenode.numBytes = 3;
                        receive_queue.push(receivenode);
                    }
                    else{
                        receivenode.name = ADC;
                        receivenode.numBytes = 3;
                        receive_queue.push(receivenode);
                    }
                    break;
                case readSignalPhaseOffset:
                    s_afm.readSignalPhaseOffset();
                    receivenode.name = READSIGNALPHASEOFFSET;
                    receivenode.numBytes = 6;
                    receive_queue.push(receivenode);
                break;
                case setRasterStep:
                    receivenode.name = WRITE;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    s_afm.setRasterStep();
                    break;
                case memsSetOffset:
                    _val = _node->getdval();
                    s_afm.memsSetOffset(_val);
                    receivenode.name = SETPGA;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case memsSetFrequency:
                    _val = _node->getdval();
                    s_afm.memsSetFrequency(_val);
                    receivenode.name = SETPGA;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case memsSetAmplitude:
                   _val = _node->getdval();
                    s_afm.memsSetAmplitude(_val);
                    receivenode.name = SETPGA;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case memsSetBridgeVoltage:
                    _val = _node->getdval();
                    s_afm.memsSetBridgeVoltage(_val);
                    receivenode.name = WRITE;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case stageSetStep:
                    s_afm.stageSetStep();
                    receivenode.name = STAGESETSTEP;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case stageSetContinuous:
                    s_afm.stageSetContinuous();
                    receivenode.name = SETCONTINUOUS;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case stageAbortContinuous:
                    s_afm.stageAbortContinuous();
                    receivenode.name = ABORTCONTINUOUS;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case pidEnable:
                    s_afm.pidEnable();
                    receivenode.name = PIDENABLE;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case pidDisable:
                    s_afm.pidDisable();
                    receivenode.name = PIDDISABLE;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case pidSetP:
                    s_afm.pidSetP(_node->getdval());
                    receivenode.name = SETP;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case pidSetI:
                    s_afm.pidSetI(_node->getdval());
                    receivenode.name = SETI;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case pidSetD:
                    s_afm.pidSetD(_node->getdval());
                    receivenode.name = SETD;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case pidSetPoint:
                    s_afm.pidSetPoint(_node->getdval());
                    receivenode.name = SETPOINT;
                    receivenode.numBytes = 1;
                    receive_queue.push(receivenode);
                    break;
                case stageSetDirBackward:
                    s_afm.stageSetDirBackward();
                    receivenode.name = SETDIRBACKWARD;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case stageSetDirForward:
                    s_afm.stageSetDirForward();
                    receivenode.name = SETDIRFORWARD;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case stageSetPulseWidth:
                    s_afm.stageSetPulseWidth(_node->getqval());
                    receivenode.name = SETPULSEWIDTH;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    break;
                case afmAutoApproach:
                    s_afm.autoApproach(_node->getdval());
                    receivenode.name = AUTOAPPROACH;
                    receivenode.numBytes = 3;
                    receive_queue.push(receivenode);
                    break;
                case setPort:
                    s_afm.close();
                    *detectedSerialPorts = QSerialPortInfo::availablePorts();
                    _node->getdval() == 0 ? _index = 0 :_index = _node->getdval();

                    if(detectedSerialPorts->size()==0)
                        qDebug() << "Unable to find any serial ports." << endl;
                    else{
                        s_afm.setPort(detectedSerialPorts->at(_index));
                        s_afm.open(QIODevice::ReadWrite);
                        s_afm.setBaudRate(76800);
                    }
                    break;
                 case setDDSSettings:
                    s_afm.setDDSSettings(0,_node->getdval(),0);
                    receivenode.name = SETDDS;
                    receivenode.numBytes = 2;
                    receive_queue.push(receivenode);
                    emit updateStatusBar("DDS Set");
                    break;
                 case frequencySweep:
                    emit updateStatusBar("Starting Frequency Sweep...");
                    s_afm.frequencySweep(_node->getnumPoints(),_node->getstartFrequency(),_node->getstepSize());
                    receivenode.name = FREQSWEEP;
                    receivenode.numBytes = _node->getnumPoints()*4 + 1;
                    receive_queue.push(receivenode);
                    emit updateStatusBar("Done");
                    break;
                 case setDacValues:
                    s_afm.setDACValues(_node->getqval(),_node->getdval());
                    receivenode.name = SETDACVALUES;
                    receivenode.numBytes = 8;
                    receive_queue.push(receivenode);
                    break;
                 case deviceCalibration:
                    emit updateStatusBar("Calibrating...");
                    s_afm.deviceCalibration(_node->getdval(),'l');
                    s_afm.deviceCalibration(_node->getdval(),'r');
                    receivenode.name = DEVICECALIBRATION;
                    receivenode.numBytes = 16380;
                    receive_queue.push(receivenode);
                    receive_queue.push(receivenode);
                    emit updateStatusBar("Finished calibrating");
                    break;
                 case scanParameters:
                    emit updateStatusBar("Setting scan parameters");
                    s_afm.scanParameters(_node->getvminLine(),_node->getvminScan(),_node->getvmax(),_node->getnumpts(),_node->getnumLines());
                    receivenode.name = SCANPARAMETERS;
                    receivenode.numBytes = 8;
                    receive_queue.push(receivenode);
                    emit updateStatusBar("Scan parameters set");
                    break;
                 case startScan:
                    emit updateStatusBar("Scan started");
                    s_afm.startScan();
                    receivenode.name = STARTSCAN;
                    receivenode.numBytes = 8;
                    receive_queue.push(receivenode);
                    break;
                 case getScanData:
                    s_afm.scanStep();
                    receivenode.name = SCANDATA;
                    receivenode.numBytes = 48;
                    receive_queue.push(receivenode);
            }
            m_queue.pop();

        }
        //emit updateStatusBar("Done");
        //mutex.unlock();
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
