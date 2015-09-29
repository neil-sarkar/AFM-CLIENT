#include "receive_worker.h"
#include <QTime>

void receive_worker::mainLoop()
{
//	forever {
    /**********************************************************
    * check to see if the buffer is not empty. If !empty read
    * data from the serial port. Based on the node in the queue
    * shift the serial buffer by the appropriate number of bytes.
    * Push a node onto the return queue with the data
    * Repeat.
    **********************************************************/

//	} // end forever
}               // end main loop



/*
 * The overloaded push_recv_queue function is to be invoked from both
 * afm_worker (which provides the message ID, TAG, and Result) and
 * send_worker (provides returnType)
 *
 * Since we do not know which worker will call first, the flag
 * next_command_clear_to_write is used to indicate if data has
 * already been received from afm or send worker.
 *
 * TODO There might be a better way to do this.
 *
 */
void receive_worker::push_recv_queue(returnType name){
    if(next_command_clear_to_write){
        next_command_name = name;
        next_command_clear_to_write = false;
    } else {
        receivetype receivenode;
        receivenode.name = name;
        receivenode.message_id = next_command_message_id;
        receivenode.message_tag = next_command_message_tag;
        receivenode.writeByte_result = next_command_writeByte_result;
        receive_queue.push(receivenode);
        next_command_clear_to_write = true;
    }
}

void receive_worker::push_recv_queue(char message_id, char message_tag, int writeByte_result){
    if(next_command_clear_to_write){
        next_command_message_id = message_id;
        next_command_message_tag = message_tag;
        next_command_writeByte_result = writeByte_result;
        next_command_clear_to_write = false;
    } else {
        receivetype receivenode;
        receivenode.name = next_command_name;
        receivenode.message_id = message_id;
        receivenode.message_tag = message_tag;
        receivenode.writeByte_result = writeByte_result;
        receive_queue.push(receivenode);
        next_command_clear_to_write = true;
    }
}

/*
 * Async callback. afm_worker will call this to initiate process of
 * received UART messages. No more infinite loops!
 *
 */

void receive_worker::process_uart_resp(QByteArray new_uart_resp){

    uart_resp = new_uart_resp;

    receivetype _node;
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

    if (!receive_queue.empty()) {
        isError = false;
        _node = receive_queue.front();

        if (_abort) {
            emit finished();
            return;
        }

        /*
         * Collect serial rx buffer from SerialObject, and put into the local QByteArray uart_resp.
         * Using uart_resp.isEmpty() as an indicator of when to read from serial rx buffer is bad,
         * because there might be partial data that reside within uart_resp when we last read serial rx.
         * It is much better to use an EOL or End of Message indicator, so that we know a message
         * inside uart_resp is incomplete. Now we go fetch it from the serial rx buffer, and so forth and
         * so on. This way we don't care if it was collected midway (Another option is to make r_afm
         * only return full messages, which would be the case if we use QIODevice readLine)
         */


        /*
         * Replacing receive buffer with command buffer... using deque!
         *
         * mainThread and eventThread mydeque.push_back(), then serialThread would read and modify the front element.
         * If the message does not need a reply, serialThread would remove that element.
         * If a reply is expected, serialThread leaves it in mydeque.
         *      receive_worker will find it and destroy it as needed.
         *
         * Potential algorithm for QIODevice.readLine():
         *  Read a line, pass to uart_resp
         *      After we read a line, we would be sure that the next line is a full msg.
         *  uart_resp handlers do its thing. If it was not a full msg, we would discard it
         * >>> What if we miss a message? Does that ever happen?
         * >>> QT logic: look for matching Tag AND Cmd/Msg ID by look into the cmd deque
         *     Search through cmd deque with mydeque.at(i)
         *     If found a matching item, then mydeque.erase(mydeque.begin()+i); and proceed as usual
         *          (we missed those messages)
         *     If we did not find matching item, then increment error counter by 1. Load uart_resp with the next Line
         *          (unknown state. when err counter reaches some value, show error on UI and clear the deque with mydeque.clear())
         */

        // Get the next message block
        if (uart_resp.isEmpty()) {
            emit getNextMsg();
            while(uart_resp.isEmpty()) ; //Wait until it is filled?
            // this is incredibly sketchy
        }


#if AFM_DEBUG
        if (uart_resp.size() > 0) {
            //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
            qDebug() << "receive_worker get resp  0x" << uart_resp.toHex();
        }
#endif

        // First make sure the uart_resp array actually has things inside
        if (!uart_resp.isEmpty() || !uart_resp.isNull()) {
            /* Now look at the next element in receive_queue (_node)
             * Compare this _node with what is received in uart_resp
             * Do they match? They should match, by temporal sequence.
             * If they do not, throw serial error, then empty the uart_resp.
             * > Is this reasonable? We might have useful things in uart_resp which we are throwing out each time there's a serial error.
             * > ...and the viscious cycle continues
             *
             */

            // The checking of message legitimacy should be done before the switch statement.
            // It is redundant to check it in every case.

            switch (_node.name) {
            case WRITE:
                if (uart_resp.at(1) == AFM_DAC_WRITE_SELECT) {
                    return_queue.push(new returnBuffer(WRITE, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case DACZOFFSETFINE:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACZOFFSETFINE, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACZOFFSETCOARSE:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACZOFFSETCOARSE, float(((float)val) / AFM_DAC_SCALING)));

                }
                break;
            case DACBFRD1:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACBFRD1, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACBFRD2:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACBFRD2, float(((float)val) / AFM_DAC_SCALING)));
                    shift = 3;
                } else {
                    isError = true;
                }
                break;
            case DACBFRD3:
                val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    return_queue.push(new returnBuffer(DACBFRD3, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACZAMP:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACZAMP, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACBR1:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACBR1, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACBR2:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACBR2, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACX1:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACX1, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACX2:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACX2, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACY1:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACY1, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case DACY2:
                if (uart_resp.at(2) == AFM_DAC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(DACY2, float(((float)val) / AFM_DAC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case ADCZOFFSET:
                if (uart_resp.at(2) == AFM_ADC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(ADCZOFFSET, float(((float)val) / AFM_ADC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case ADCPHASE:
                if (uart_resp.at(2) == AFM_ADC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(ADCPHASE, float(((float)val) / AFM_ADC_SCALING)));

                } else {
                    isError = true;
                }
                break;
            case ADC:
                if (uart_resp.at(2) == AFM_ADC_READ_SELECT) {
                    val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    return_queue.push(new returnBuffer(ADC, float(((float)val) / AFM_ADC_SCALING)));
                    shift = 3;
                } else {
                    isError = true;
                }
                break;
            case READSIGNALPHASEOFFSET:
                if (uart_resp.at(1) == AFM_ADC_READ_SPO) {
                    signal = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
                    offset = (((unsigned char)uart_resp.at(3) << 8) | (unsigned char)uart_resp.at(2));
                    phase = (((unsigned char)uart_resp.at(5) << 8) | (unsigned char)uart_resp.at(4));
                    graph_queue.push(new returnBuffer(READSIGNALPHASEOFFSET, AFM_SUCCESS, signal / AFM_DAC_SCALING, offset / AFM_DAC_SCALING, phase / AFM_DAC_SCALING));

                } else {
                    isError = true;
                }
                break;
            case SETDACVALUES:
                if (uart_resp.at(1) == AFM_SET_DAC_MAX) {
                    return_queue.push(new returnBuffer(ADCZOFFSET, AFM_SUCCESS));
                    shift = 1;
                } else {
                    isError = true;
                }
                break;
            case SETDIRBACKWARD:
                if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_STAGE_DIR_REVERSE_SELECT) {
                    return_queue.push(new returnBuffer(SETDIRBACKWARD, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case SETPULSEWIDTH:
                if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_STAGE_PW_SELECT) {
                    return_queue.push(new returnBuffer(SETPULSEWIDTH, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case ABORTAUTOAPPROACH:
                if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_ABORT) {
                    return_queue.push(new returnBuffer(ABORTAUTOAPPROACH, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case AUTOAPPROACH:
                if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_AUTOAPPROACH_SELECT) {
                    return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_SUCCESS));

                } else if (uart_resp.at(2) == 'f') {
                    return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_FAIL));
                    shift = 2;
                } else {
                    isError = true;
                }
                break;
            case SCANPARAMETERS:
                if (uart_resp.at(1) == AFM_SCAN_PARAMETERS && uart_resp.at(0) == 'o') {
                    shift = 2;
                    return_queue.push(new returnBuffer(SCANPARAMETERS, AFM_SUCCESS));
                } else {
                    isError = true;
                }
                break;
            case STARTSCAN:
                if (uart_resp.at(1) == AFM_START_SCAN) {
                    return_queue.push(new returnBuffer(STARTSCAN, AFM_SUCCESS));
                    shift = 1;
                } else {
                    isError = true;
                }
                break;
            case SCANDATA:
//                for (int i = 0; i < _node.numBytes - 1; i++) {
//                    z_offset_adc->append(uart_resp.at(i) & uart_resp.at(++i));
//                    z_amp_adc->append(uart_resp.at(++i) & uart_resp.at(++i));
//                    z_phase_adc->append(uart_resp.at(++i) & uart_resp.at(++i));
//                }

//                if (uart_resp.at(_node.numBytes) == AFM_SCAN_STEP) {
//                    return_queue.push(new returnBuffer(SCANDATA, AFM_SUCCESS, *z_offset_adc, *z_amp_adc, *z_phase_adc));
//                     //plus one for acknowledgement byte
//                } else {
//                    isError = true;
//                }
                break;
            case PIDENABLE:
                if (uart_resp.at(0) == AFM_PID_ENABLE_SELECT) {
                    return_queue.push(new returnBuffer(PIDENABLE, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case PIDDISABLE:
                if (uart_resp.at(0) == AFM_PID_DISABLE_SELECT) {
                    return_queue.push(new returnBuffer(PIDDISABLE, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case SETP:
                if (uart_resp.at(0) == AFM_PID_P_SELECT) {
                    return_queue.push(new returnBuffer(SETP, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case SETI:
                if (uart_resp.at(0) == AFM_PID_I_SELECT) {
                    return_queue.push(new returnBuffer(SETI, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case SETD:
                if (uart_resp.at(0) == AFM_PID_D_SELECT) {
                    return_queue.push(new returnBuffer(SETD, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case SETPOINT:
                if (uart_resp.at(0) == AFM_PID_SETPOINT_SELECT) {
                    return_queue.push(new returnBuffer(SETPOINT, AFM_SUCCESS));

                } else {
                    isError = true;
                }
                break;
            case SETDDS:
                if (uart_resp.at(0) == AFM_DDS_SWEEP_SET) {
                    return_queue.push(new returnBuffer(SETDDS, AFM_SUCCESS));
                    shift = 1;
                } else {
                    isError = true;
                }
                break;
            case SETPGA:
                if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_SET_PGA) {
                    return_queue.push(new returnBuffer(SETPGA, AFM_SUCCESS));
                    shift = 2;
                } else {
                    isError = true;
                }
                break;
            case DEVICECALIBRATION:
                if (uart_resp.at(2) == 'o') {
                    return_queue.push(new returnBuffer(DEVICECALIBRATION, AFM_SUCCESS));
                     //acknowledge byte
                } else {
                    isError = true;
                }
                break;
            case FORCECURVE:
//                if (uart_resp.at(_node.numBytes - 1) == 'N') {
//                    amplitudeData->clear();
//                    phaseData->clear();
//                    quint16 intVal;
//                    //quint16 phaseVal;
//                    for (int i = 0; i < _node.numBytes - 1; i++) {
//                        intVal = BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i++]);
//                        //phaseVal = BYTES_TO_WORD((quint8)uart_resp[i+2],(quint8)uart_resp[i+3]);
//                        amplitudeData->append(double(intVal) / AFM_ADC_SCALING);
//                        phaseData->append(0);
//                    }
//                    return_queue.push(new returnBuffer(FORCECURVE, 0, *amplitudeData, *phaseData, _node.numBytes));

//                } else {
//                    isError = true;
//                }
            isError=false;     //temp placeholder
            break;
            case FREQSWEEP:
                int bytesRead;
                int success;

                /* clear the ack from dds settings */
                if (uart_resp.at(0) == AFM_DDS_SWEEP_SET) {
                    shift = 1;
                    uart_resp = uart_resp.remove(0, shift);
                    bytesRead = uart_resp.size();
                }
//                if (bytesRead != _node.numBytes)
//                    success = AFM_FAIL;

                quint16 ampVal;
                quint16 phaseVal;

                // y data
                amplitudeData->clear();
                phaseData->clear();
//                for (int i = 0; i < _node.numBytes - 1; i += 4) {
//                    ampVal = BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i + 1]);
//                    phaseVal = BYTES_TO_WORD((quint8)uart_resp[i + 2], (quint8)uart_resp[i + 3]);

//                    amplitudeData->append(double(ampVal) / AFM_ADC_SCALING);
//                    phaseData->append(double(phaseVal) / AFM_ADC_SCALING);

//                    qDebug() << "Freq Sweep Amplitude: " << double(ampVal) / AFM_ADC_SCALING << " Phase: " << double(phaseVal) / AFM_ADC_SCALING;
//                }

                //  if(uart_resp.at(bytesRead-1) == AFM_SWEEP_START){
                // ^ not sure what that thing does. it crashes the program by causing segment err if uart_resp is not malformed.
                if (true) {
                    success = AFM_SUCCESS;
                    return_queue.push(new returnBuffer(FREQSWEEP, success, *amplitudeData, *phaseData, bytesRead));
                }

                break;
            } // End switch

            // Post-processing
            /* If there is a serial comm mismatch or error, clear the following to 'reset':
             * 1. Receive queue
             * 2. Serial incoming buffer
             * 3. Serial incoming array (uart_resp)
             */
            if (isError) {
                while (!receive_queue.empty())
                    receive_queue.pop();
                uart_resp.clear();
                emit serialError(); // this isn't necessary for release
            } else {
                //we good
                receive_queue.pop();
                //clear the current msg, so that the next one may be read
                uart_resp.clear();
            }
        }
        //mutex.unlock();
        else {
            // do nothing
        }
    } // end if(!receive_queue.empty())
}


void receive_worker::abort()
{
    _abort = true;
}
receive_worker::~receive_worker()
{
    emit finished();
}
