#include "receiver.h"
#include <QTime>

#define AFM_SHORT_TIMEOUT 50
#define AFM_LONG_TIMEOUT 9000 //debateable -- does it really need to be this long?

void delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void receiver::mainLoop()
{
    receivetype _node;
    QByteArray res;
    int shift = 0;

    _abort = false;
    quint16 val;

    double signal;
    double offset;
    double phase;

    /********************Return Buffers********************/
    QVector<double> *amplitudeData = new QVector<double>();
    QVector<double> *phaseData = new QVector<double>();
    QVector<double> *frequencyData = new QVector<double>();
    QVector<double> *z_offset_adc = new QVector<double>();
    QVector<double> *z_amp_adc = new QVector<double>();
    QVector<double> *z_phase_adc = new QVector<double>();

    forever {
        /**********************************************************
        * check to see if the buffer is not empty. If !empty read
        * data from the serial port. Based on the node in the queue
        * shift the serial buffer by the appropriate number of bytes.
        * Push a node onto the return queue with the data
        * Repeat.
        **********************************************************/

        if (_abort) {
            delete amplitudeData;
            delete phaseData;
            delete frequencyData;
            delete z_offset_adc;
            delete z_amp_adc;
            delete z_phase_adc;
            emit finished();
            return;
        }

        // mutex.lock();
        //TODO: Currently there is a major bug where if there are a ton of events sent to the MCU
        //they get out of order. If i am attempting to read a signal in order to plot and do a continuous
        //approach the events get out of order.
        if (!recv_queue.empty()) {
            isError = false;
            _node = recv_queue.front();

            // Collect serial rx buffer from SerialObject, and put into the local QByteArray res.
            // Using res.isEmpty() as an indicator of when to read from serial rx buffer is bad,
            // because there might be partial data that reside within res when we last read serial rx.
            // It is much better to use an EOL or End of Message indicator, so that we know a message
            // inside res is incomplete. Now we go fetch it from the serial rx buffer, and so forth and
            // so on. This way we don't care if it was collected midway (Another option is to make r_afm
            // only return full messages, which would be the case if we use QIODevice readLine)


            /*
             * Replacing receive buffer with command buffer... using deque!
             *
             * mainThread and eventThread mydeque.push_back(), then serialThread would read and modify the front element.
             *
             * Potential algorithm for QIODevice.readLine():
             *  Read a line, pass to res
             *      After we read a line, we would be sure that the next line is a full msg.
             *  res handlers do its thing. If it was not a full msg, we would discard it
             * >>> What if we miss a message? Does that ever happen?
             * >>> QT logic: look for matching Tag AND Cmd/Msg ID by look into the cmd deque
             *     Search through cmd deque with mydeque.at(i)
             *     If found a matching item, then mydeque.erase(mydeque.begin()+i); and proceed as usual
             *          (we missed those messages)
             *     If we did not find matching item, then increment error counter by 1. Load res with the next Line
             *          (unknown state. when err counter reaches some value, show error on UI and clear the deque with mydeque.clear())
             *
             *
             *
             */



            while (res.isEmpty()) {
                //mutex.lock();
                if (_abort) {
                    emit finished();
                    return;
                }

                // Logic to decide when to collect the serial rx buffer
                // If we collect too fast, data might get cut-off halfway through.

                if (_node.name == DEVICECALIBRATION || _node.name == AUTOAPPROACH) {
                    res = r_afm.waitForData(AFM_LONG_TIMEOUT);
                }
                //waitForData doesn't actually wait for anything... if there happens to be data in the buffer, it will take it.
                //and we cannot ensure that all of the data are in yet.
                //maybe just enforce a wait?
                else if (_node.name == FREQSWEEP) {
                    delay(3000); //Force a wait
                    res = r_afm.waitForData(AFM_LONG_TIMEOUT);
                } else {
                    res = r_afm.waitForData(AFM_SHORT_TIMEOUT);
                }
                //mutex.unlock();
            }

            // First make sure the res array actually has things inside
            if (!res.isEmpty() || !res.isNull()) {
                /* Now look at the next element in recv_queue (_node)
                 * Compare this _node with what is received in res
                 * Do they match? They should match, by temporal sequence.
                 * If they do not, throw serial error, then empty the res.
                 * > Is this reasonable? We might have useful things in res which we are throwing out each time there's a serial error.
                 * > ...and the viscious cycle continues
                 *
                 */
                switch (_node.name) {
                case WRITE:
                    if (res.at(0) == AFM_DAC_WRITE_SELECT) {
                        rtn_queue.push(new returnBuffer(WRITE,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACZOFFSETFINE:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACZOFFSETFINE,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACZOFFSETCOARSE:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACZOFFSETCOARSE,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    }
                    break;
                case DACBFRD1:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACBFRD1,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACBFRD2:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACBFRD2,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = 3;
                    } else {
                        isError = true;
                    }
                    break;
                case DACBFRD3:
                    val =
                        (((unsigned char)res.at(1) << 8) |
                         (unsigned char)res.at(0));
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        rtn_queue.push(new returnBuffer(DACBFRD3,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACZAMP:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACZAMP,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACBR1:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACBR1,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACBR2:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACBR2,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACX1:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACX1,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACX2:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACX2,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACY1:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACY1,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case DACY2:
                    if (res.at(2) == AFM_DAC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(DACY2,
                                        float(((float)val) /
                                              AFM_DAC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case ADCZOFFSET:
                    if (res.at(2) == AFM_ADC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(ADCZOFFSET,
                                        float(((float)val) /
                                              AFM_ADC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case ADCPHASE:
                    if (res.at(2) == AFM_ADC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(ADCPHASE,
                                        float(((float)val) /
                                              AFM_ADC_SCALING)));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case ADC:
                    if (res.at(2) == AFM_ADC_READ_SELECT) {
                        val =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        rtn_queue.push(new returnBuffer(ADC,
                                        float(((float)val) /
                                              AFM_ADC_SCALING)));
                        shift = 3;
                    } else {
                        isError = true;
                    }
                    break;
                case READSIGNALPHASEOFFSET:
                    if (res.at(_node.numBytes) == AFM_ADC_READ_SPO) {
                        signal =
                            (((unsigned char)res.at(1) << 8) |
                             (unsigned char)res.at(0));
                        offset =
                            (((unsigned char)res.at(3) << 8) |
                             (unsigned char)res.at(2));
                        phase =
                            (((unsigned char)res.at(5) << 8) |
                             (unsigned char)res.at(4));
                        graph_queue.push(new returnBuffer(
                                     READSIGNALPHASEOFFSET,
                                     AFM_SUCCESS,
                                     signal / AFM_DAC_SCALING,
                                     offset / AFM_DAC_SCALING,
                                     phase / AFM_DAC_SCALING));
                        shift = _node.numBytes + 1;
                    } else {
                        isError = true;
                    }
                    break;
                case SETDACVALUES:
                    if (res.at(0) == 'o' && res.at(1) == AFM_SET_DAC_MAX) {
                        rtn_queue.push(new returnBuffer(ADCZOFFSET,
                                        AFM_SUCCESS));
                        shift = 2;
                    } else if (res.at(0) == 'f') {
                        rtn_queue.push(new returnBuffer(ADCZOFFSET,
                                        AFM_FAIL));
                        shift = 2;
                    } else {
                        isError = true;
                    }
                    break;
                case STAGESETSTEP:
                    if (res.at(0) == 'o' && res.at(1) == AFM_STAGE_PULSE_STEP) {
                        rtn_queue.push(new returnBuffer(STAGESETSTEP,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETDIRFORWARD:
                    if (res.at(0) == 'o' &&
                        res.at(1) == AFM_STAGE_DIR_FWD_SELECT) {
                        rtn_queue.push(new returnBuffer(SETDIRFORWARD,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETDIRBACKWARD:
                    if (res.at(0) == 'o' &&
                        res.at(1) == AFM_STAGE_DIR_REVERSE_SELECT) {
                        rtn_queue.push(new returnBuffer(SETDIRBACKWARD,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETPULSEWIDTH:
                    if (res.at(0) == 'o' && res.at(1) == AFM_STAGE_PW_SELECT) {
                        rtn_queue.push(new returnBuffer(SETPULSEWIDTH,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case ABORTAUTOAPPROACH:
                    if (res.at(0) == 'o' && res.at(1) == AFM_ABORT) {
                        rtn_queue.push(new returnBuffer(ABORTAUTOAPPROACH,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case AUTOAPPROACH:
                    if (res.at(0) == 'o' &&
                        res.at(_node.numBytes) == AFM_AUTOAPPROACH_SELECT) {
                        rtn_queue.push(new returnBuffer(AUTOAPPROACH,
                                        AFM_SUCCESS));
                        shift = _node.numBytes + 1;
                    } else if (res.at(0) == 'f') {
                        rtn_queue.push(new returnBuffer(AUTOAPPROACH,
                                        AFM_FAIL));
                        shift = 2;
                    } else {
                        isError = true;
                    }
                    break;
                case SCANPARAMETERS:
                    if (res.at(0) == 'o' &&
                        res.at(1) == AFM_SCAN_PARAMETERS) {
                        shift = 2;
                        rtn_queue.push(new returnBuffer(SCANPARAMETERS,
                                        AFM_SUCCESS));
                    } else {
                        isError = true;
                    }
                    break;
                case STARTSCAN:
                    if (res.at(0) == AFM_START_SCAN) {
                        rtn_queue.push(new returnBuffer(STARTSCAN,
                                        AFM_SUCCESS));
                        shift = 1;
                    } else {
                        isError = true;
                    }
                    break;
                case SCANDATA:
                    for (int i = 0; i < _node.numBytes - 1; i++) {
                        z_offset_adc->append(res.at(i) & res.at(++i));
                        z_amp_adc->append(res.at(++i) & res.at(++i));
                        z_phase_adc->append(res.at(++i) & res.at(++i));
                    }

                    if (res.at(_node.numBytes) == AFM_SCAN_STEP) {
                        rtn_queue.push(new returnBuffer(SCANDATA,
                                        AFM_SUCCESS,
                                        *z_offset_adc,
                                        *z_amp_adc,
                                        *z_phase_adc));
                        shift = _node.numBytes + 1; //plus one for acknowledgement byte
                    } else {
                        isError = true;
                    }
                    break;
                case PIDENABLE:
                    if (res.at(0) == AFM_PID_ENABLE_SELECT) {
                        rtn_queue.push(new returnBuffer(PIDENABLE,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case PIDDISABLE:
                    if (res.at(0) == AFM_PID_DISABLE_SELECT) {
                        rtn_queue.push(new returnBuffer(PIDDISABLE,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETP:
                    if (res.at(0) == AFM_PID_P_SELECT) {
                        rtn_queue.push(new returnBuffer(SETP, AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETI:
                    if (res.at(0) == AFM_PID_I_SELECT) {
                        rtn_queue.push(new returnBuffer(SETI, AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETD:
                    if (res.at(0) == AFM_PID_D_SELECT) {
                        rtn_queue.push(new returnBuffer(SETD, AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETPOINT:
                    if (res.at(0) == AFM_PID_SETPOINT_SELECT) {
                        rtn_queue.push(new returnBuffer(SETPOINT,
                                        AFM_SUCCESS));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case SETDDS:
                    if (res.at(0) == AFM_DDS_SWEEP_SET) {
                        rtn_queue.push(new returnBuffer(SETDDS,
                                        AFM_SUCCESS));
                        shift = 1;
                    } else {
                        isError = true;
                    }
                    break;
                case SETPGA:
                    if (res.at(0) == 'o' && res.at(1) == AFM_SET_PGA) {
                        rtn_queue.push(new returnBuffer(SETPGA,
                                        AFM_SUCCESS));
                        shift = 2;
                    } else {
                        isError = true;
                    }
                    break;
                case DEVICECALIBRATION:
                    if (res.at(_node.numBytes) == 'o') {
                        rtn_queue.push(new returnBuffer(DEVICECALIBRATION,
                                        AFM_SUCCESS));
                        shift = _node.numBytes + 1; //acknowledge byte
                    } else {
                        isError = true;
                    }
                    break;
                case FORCECURVE:
                    if (res.at(_node.numBytes - 1) == 'N') {
                        amplitudeData->clear();
                        phaseData->clear();
                        quint16 intVal;
                        //quint16 phaseVal;
                        for (int i = 0; i < _node.numBytes - 1; i++) {
                            intVal =
                                BYTES_TO_WORD((quint8)res[i],
                                          (quint8)res[i++]);
                            //phaseVal = BYTES_TO_WORD((quint8)res[i+2],(quint8)res[i+3]);
                            amplitudeData->append(
                                double(intVal) / AFM_ADC_SCALING);
                            phaseData->append(0);
                        }
                        rtn_queue.push(new returnBuffer(FORCECURVE, 0,
                                        *amplitudeData,
                                        *phaseData,
                                        _node.numBytes));
                        shift = _node.numBytes;
                    } else {
                        isError = true;
                    }
                    break;
                case FREQSWEEP:
                    int bytesRead;
                    int success;

                    /* clear the ack from dds settings */
                    if (res.at(0) == AFM_DDS_SWEEP_SET) {
                        shift = 1;
                        res = res.remove(0, shift);
                        bytesRead = res.size();
                    }
                    if (bytesRead != _node.numBytes)
                        success = AFM_FAIL;

                    quint16 ampVal;
                    quint16 phaseVal;

                    // y data
                    amplitudeData->clear();
                    phaseData->clear();
                    for (int i = 0; i < _node.numBytes - 1; i += 4) {
                        ampVal =
                            BYTES_TO_WORD((quint8)res[i],
                                      (quint8)res[i + 1]);
                        phaseVal = BYTES_TO_WORD((quint8)res[i + 2],
                                     (quint8)res[i + 3]);

                        amplitudeData->append(
                            double(ampVal) / AFM_ADC_SCALING);
                        phaseData->append(double(phaseVal) /
                                  AFM_ADC_SCALING);

                        qDebug() << "Freq Sweep Amplitude: " <<
                            double(ampVal) / AFM_ADC_SCALING <<
                            " Phase: " <<
                            double(phaseVal) / AFM_ADC_SCALING;
                    }

                    //  if(res.at(bytesRead-1) == AFM_SWEEP_START){
                    // ^ not sure what that thing does. it crashes the program.
                    if (true) {
                        shift = _node.numBytes;
                        success = AFM_SUCCESS;
                        rtn_queue.push(new returnBuffer(FREQSWEEP,
                                        success,
                                        *amplitudeData,
                                        *phaseData,
                                        bytesRead));
                    }

                    break;
                } // End switch

                // Post-processing
                /* If there is a serial comm mismatch or error, clear the following to 'reset':
                 * 1. Receive queue
                 * 2. Serial incoming buffer
                 * 3. Serial incoming array (res)
                 */
                if (isError) {
                    while (!recv_queue.empty())
                        recv_queue.pop();
                    res.clear();
                    emit serialError(); // this isn't necessary for release
                } else {
                    //we good
                    recv_queue.pop();
                    //shift the buffer to the next set of data
                    res = res.remove(0, shift);
                }

            }
            //mutex.unlock();
            else {
                //sometimes there are extra bytes in the buffer when we do an
                //approach. So if there is nothing in the receive queue just
                //empty the buffer to make sure
                res.clear();
            }
        }       // end if(!recv_queue.empty())
    }           // end forever
}               // end main loop
void receiver::abort()
{
    _abort = true;
}
receiver::~receiver()
{
    emit finished();
}
