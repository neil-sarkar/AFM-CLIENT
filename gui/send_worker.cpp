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
    queue_check_timer = new QTimer(this);
    connect(queue_check_timer, SIGNAL(timeout()), this, SLOT(queue_check()));
    queue_check_timer->start(2);
}

void send_worker::queue_check(){
    //TODO Inefficient. To move later
    _abort = false;
    QList<QSerialPortInfo> *detectedSerialPorts = new QList<QSerialPortInfo>();
    returnType return_name;

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
            if (_ID == ADC_Z_PZR_AMP) {
                return_name = ADCZOFFSET;
            } else if (_ID = ADC_PHASE) {
                return_name = ADCPHASE;
            } else {
                return_name = ADC;
            }
            break;
        /* CANDIDATES FOR AUTOMATIC CODE GEN */
        case readSignalPhaseOffset:
            s_afm.readSignalPhaseOffset();
            return_name = READSIGNALPHASEOFFSET;
            break;
        case setRasterStep:
            return_name = WRITE;
            s_afm.setRasterStep();
            break;
        case setPGA:
            s_afm.setPGA_pcb3(_node->getqval(),_node->getdval());
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
            s_afm.pidSetPoint((float)_node->getdval());
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
        case aappr_begin:
            s_afm.autoApproach_mcu(_node->getdval());
            return_name = AAPPR_BEGIN;
            break;
        case aappr_sta:
            s_afm.autoApproach_mcu_status();
            return_name = AAPPR_STA;
            break;
        case aappr_stop:
            s_afm.autoApproach_mcu_stop();
            return_name = AAPPR_STOP;
            break;
        case stepMotSetSpeed:
            s_afm.stepMotSetSpeed(int(_node->getdval()));
            return_name = STEPMOTSETSPEED;
            break;
        case stepMotSetDir:
            s_afm.stepMotSetDir(_node->getqval());
            return_name = STEPMOTSETDIR;
            break;
        case stepMotSetMicrostep:
            s_afm.stepMotSetMicrostep(_node->getqval());
            return_name = STEPMOTSETMICROSTEP;
            break;
        case stepMotSetState:
            s_afm.stepMotSetState(_node->getqval());
            return_name=STEPMOTSETSTATE;
            break;
        case stepMotContGo:
            s_afm.stepMotContGo();
            return_name=STEPMOTCONTGO;
            break;
        case stepMotContStop:
            s_afm.stepMotContStop();
            return_name=STEPMOTCONTSTOP;
            break;
        case stepMotSingleStep:
            s_afm.stepMotSingleStep();
            return_name=STEPMOTSINGLESTEP;
            break;
        case setPort:
            emit close_serial_port();
            *detectedSerialPorts = QSerialPortInfo::availablePorts();
            emit open_serial_port(detectedSerialPorts->at(_node->getdval()).portName(), AFM_BAUD_RATE);
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
        case setDacMaxValues:
            s_afm.setDACMaxValues(_node->getqval(), _node->getdval());
            return_name = SETDACMAXVALUES;
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
        case setDACTable:
            s_afm.setDACTable(_node->getqval());
            return_name = SETDACTABLE;
            break;
        case SigGen:
            emit updateStatusBar("Setting 4ACT SIG GEN scan parameters");
            s_afm.sigGen(_node->getqval(), _node->getnumpts(), _node->getnumLines());
            return_name = SIGGEN;
            emit updateStatusBar("Scan parameters set");
            break;
        case startScan_4act:
            s_afm.startScan_4act();
             emit updateStatusBar("Scan started");
            return_name = STARTSCAN;
            break;
        case scanStep_4act:
            s_afm.scanStep_4act();
            return_name = SCANDATA;
            break;
        } // end switch(_command)
        cmd_queue.pop();
        //mutex.unlock();
    }
    //emit updateStatusBar("Done");
    //mutex.unlock();
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
