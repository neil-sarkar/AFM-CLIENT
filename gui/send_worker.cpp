#include <send_worker.h>

using std::queue;

/***********************************************************************
* SERIAL WORKER
*   -Objective: Separate serial Read/Write from the GUI thread
*   -Methods: requestMethod(Method)
*   -Info: mainLoop will wait for methods to be requested.
*
*  This main loop will constantly check for methods to call
*  if _method matches a case in the switch statement the
*  corresponding method will be called. if _abort is ever set to
*  true the thread will exit.
***********************************************************************/

//TODO Eventually want to make this async (event-based) similiar to how
// receive worker works, instead of an endless loop.


void send_worker::mainLoop()
{
    _abort = false;
    QList<QSerialPortInfo> *detectedSerialPorts = new QList<QSerialPortInfo>();
    receivetype receivenode;
    returnType return_name;

    forever {
        if (_abort) {
            delete detectedSerialPorts;
            emit finished();
            return;
        }

        /**********************************************************
        * Dequeue the command buffer and based on the command call
        * the appropriate serial function. Then push a request to read
        * the serial port to the receiver thread
        **********************************************************/

        while (!cmd_queue.empty()) {
            commandNode *_node = cmd_queue.front();
            _command = _node->getcommandName();

            //mutex.lock();
            switch (_command) {
            case writeDAC:
                _ID = _node->getqval();
                _val = _node->getdval();
                s_afm.writeDAC((qint8)_ID, (double)_val);
                return_name = (WRITE);
                //
                break;
            case readDAC:
                _ID = (qint8)_node->getqval();
                s_afm.readDAC(_ID);
                switch (_ID) {
                case DAC_ZOFFSET_FINE:
                    return_name = DACZOFFSETFINE;
                    break;
                case DAC_ZOFFSET_COARSE:
                    return_name = DACZOFFSETCOARSE;
                    break;
                case DAC_BFRD1:
                    return_name = DACBFRD1;
                    break;
                case DAC_BFRD2:
                    return_name = DACBFRD2;
                    break;
                case DAC_BFRD3:
                    return_name = DACBFRD3;
                    break;
                case DAC_ZAMP:
                    return_name = DACZAMP;
                    break;
                case DAC_BR1:
                    return_name = DACBR1;
                    break;
                case DAC_BR2:
                    return_name = DACBR2;
                    break;
                case DAC_X1:
                    return_name = DACX1;
                    break;
                case DAC_X2:
                    return_name = DACX2;
                    break;
                case DAC_Y1:
                    return_name = DACY1;
                    break;
                case DAC_Y2:
                    return_name = DACY2;
                    break;
                case -1:
                    break;
                }
                break;
            case readADC:
                _ID = _node->getqval();
                s_afm.readADC((qint8)_ID);
                if (_ID == ADC_ZOFFSET) {
                    return_name = ADCZOFFSET;
                } else if (_ID = ADC_PHASE) {
                    return_name = ADCPHASE;
                } else {
                    return_name = ADC;
                }
                break;
            case readSignalPhaseOffset:
                s_afm.readSignalPhaseOffset();
                return_name = READSIGNALPHASEOFFSET;
                break;
            case setRasterStep:
                return_name = WRITE;
                s_afm.setRasterStep();
                break;
            case memsSetOffset:
                _val = _node->getdval();
                s_afm.memsSetOffset(_val);
                return_name = SETPGA;
                break;
            case memsSetFrequency:
                _val = _node->getdval();
                s_afm.memsSetFrequency(_val);
                return_name = SETPGA;
                break;
            case memsSetAmplitude:
                _val = _node->getdval();
                s_afm.memsSetAmplitude(_val);
                return_name = SETPGA;
                break;
            case memsSetBridgeVoltage:
                _val = _node->getdval();
                s_afm.memsSetBridgeVoltage(_val);
                return_name = WRITE;
                break;
            case stageSetStep:
                s_afm.stageSetStep();
                return_name = STAGESETSTEP;
                break;
            case pidEnable:
                s_afm.pidEnable();
                return_name = PIDENABLE;
                break;
            case pidDisable:
                s_afm.pidDisable();
                return_name = PIDDISABLE;
                break;
            case pidSetP:
                s_afm.pidSetP((float)_node->getdval());
                return_name = SETP;
                break;
            case pidSetI:
                s_afm.pidSetI((float)_node->getdval());
                return_name = SETI;
                break;
            case pidSetD:
                s_afm.pidSetD((float)_node->getdval());
                return_name = SETD;
                break;
            case pidSetPoint:
                s_afm.pidSetPoint((float)_node->getdval() * AFM_ADC_SCALING);
                return_name = SETPOINT;
                break;
            case stageSetDirBackward:
                s_afm.stageSetDirBackward();
                return_name = SETDIRBACKWARD;
                break;
            case stageSetDirForward:
                s_afm.stageSetDirForward();
                return_name = SETDIRFORWARD;
                break;
            case stageSetPulseWidth:
                s_afm.stageSetPulseWidth(_node->getqval());
                return_name = SETPULSEWIDTH;
                break;
            case afmAutoApproach:
                s_afm.autoApproach(_node->getdval());
                return_name = AUTOAPPROACH;
                break;
            case setPort:
                qDebug() << "s_afm openING" << endl;
                emit close_serial_port();
                *detectedSerialPorts = QSerialPortInfo::availablePorts();
                _node->getdval() == 0 ? _index = 0 : _index = _node->getdval();
                qDebug() << "Gonna open this one: " << detectedSerialPorts->at(_index).portName() << endl;

                if (detectedSerialPorts->size() == 0) {
                    qDebug() << "Unable to find any serial ports." << endl;
                } else {
                    emit open_serial_port(detectedSerialPorts->at(_index).portName(), AFM_BAUD_RATE);
                    qDebug() << "s_afm opened" << endl;
                }
                break;
            case setDDSSettings:
                s_afm.setDDSSettings(0, _node->getdval(), 0);
                return_name = SETDDS;
                emit updateStatusBar("DDS Set");
                break;
            case frequencySweep:
                emit updateStatusBar("Starting Frequency Sweep...");
                s_afm.frequencySweep(
                        _node->getnumPoints(),
                        _node->getstartFrequency(), _node->getstepSize());
                return_name = FREQSWEEP;
                emit updateStatusBar("Done");
                break;
            case setDacValues:
                s_afm.setDACValues(_node->getqval(), _node->getdval());
                return_name = SETDACVALUES;
                break;
            case deviceCalibration:
                emit updateStatusBar("Calibrating...");
                s_afm.deviceCalibration(_node->getdval(), 'l');
                s_afm.deviceCalibration(_node->getdval(), 'r');
                return_name = DEVICECALIBRATION;
                emit updateStatusBar("Finished calibrating");
                break;
            case scanParameters:
                emit updateStatusBar("Setting scan parameters");
                s_afm.scanParameters(_node->getvminLine(),
                                     _node->getvminScan(), _node->getvmax(),
                                     _node->getnumpts(), _node->getnumLines());
                return_name = SCANPARAMETERS;
                emit updateStatusBar("Scan parameters set");
                break;
            case startScan:
                emit updateStatusBar("Scan started");
                s_afm.startScan();
                return_name = STARTSCAN;
                break;
            case getScanData:
                s_afm.scanStep();
                return_name = SCANDATA;
                break;
            case ForceCurve:
                s_afm.forceCurve();
                return_name = FORCECURVE;
                break;
            } // end switch(_command)
         //   emit push_recv_queue(return_name);
            cmd_queue.pop();
            //mutex.unlock();
        }
        //emit updateStatusBar("Done");
        //mutex.unlock();
    }
}

void send_worker::abort()
{
    //QMutexLocker locker(&mutex);
    //mutex.unlock();
    _abort = true;

    //condition.wakeOne();
}
send_worker::~send_worker()
{
    emit finished();
}
