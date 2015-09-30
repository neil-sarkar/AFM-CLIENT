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
//void receive_worker::push_recv_queue(returnType name){
//    if(next_command_clear_to_write) {
//        next_command_name = name;
//        next_command_clear_to_write = false;
//    } else {
//        receivetype receivenode;
//        receivenode.name = name;
//        receivenode.message_id = next_command_message_id;
//        receivenode.message_tag = next_command_message_tag;
//        receivenode.writeByte_result = next_command_writeByte_result;
//        receive_queue.push(receivenode);
//        next_command_clear_to_write = true;
//    }
//}

void receive_worker::push_recv_queue(char message_id, char message_tag, int writeByte_result){

    receivetype receivenode;
    //  receivenode.name = next_command_name;
    receivenode.message_id = message_id;
    receivenode.message_tag = message_tag;
    receivenode.writeByte_result = writeByte_result;
    receive_queue.push(receivenode);
    //  next_command_clear_to_write = true;

}

/*
 * Async callback. afm_worker will call this to initiate process of
 * received UART messages. No more infinite loops!
 *
 */

void receive_worker::process_uart_resp(QByteArray new_uart_resp){

    uart_resp = new_uart_resp;
    receivetype _node;

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

    if (_abort) {
        emit finished();
        return;
    }

#if AFM_DEBUG
    if (uart_resp.size() > 0) {
        //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
        qDebug() << "receive_worker get resp  0x" << uart_resp.toHex();
    }
#endif

    // 1. Are we expecting to receive something?
    if (!receive_queue.empty()) {
        isError = false;
        _node = receive_queue.front();
    } else {
        return; //TODO change these to like, error handlers or something
    }

    // 2. Make sure the uart_resp array actually has things inside
    if (uart_resp.isEmpty() || uart_resp.isNull()) {
        return;
    }
    /* Now look at the next element in receive_queue (_node)
     * Compare this _node with what is received in uart_resp
     * Do they match? They should match, by temporal sequence.
     * If they do not, throw serial error, then empty the uart_resp.
     * Wait to be called by the afm_worker signal next time!
     *
     */

    // The checking of message legitimacy should be done before the switch statement.
    // It is redundant to check it in every case.

    // 3. The message ID shall match.
    // If not, start the investigation sequence, throw error, pop, and continue
    if(uart_resp.at(0) != _node.message_tag) {
        isError=true;
        return;
    }

    // 4. All looks good. Let's start actually processing!
    switch (_node.message_id) {
    case AFM_DAC_WRITE_SELECT:
        if (uart_resp.at(1) == AFM_DAC_WRITE_SELECT) {
            return_queue.push(new returnBuffer(WRITE, AFM_SUCCESS));

        } else {
            isError = true;
        }
        break;
    case AFM_DAC_READ_SELECT:
        if (uart_resp.at(1) == AFM_DAC_READ_SELECT) {
            //TODO change me!
            val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
            returnType type = NONE;
            switch(uart_resp.at(3)) {
            case DAC_ZOFFSET_FINE:
                type = DACZOFFSETFINE;
                break;
            case DAC_ZOFFSET_COARSE:
                type=DACZOFFSETCOARSE;
                break;
            case DAC_BFRD1:
                type=DACBFRD1;
                break;
            case DAC_BFRD2:
                type=DACBFRD2;
                break;
            case DAC_BFRD3:
                type=DACBFRD3;
                break;
            case DAC_ZAMP:
                type=DACZAMP;
                break;
            case DAC_BR1:
                type=DACBR1;
                break;
            case DAC_BR2:
                type=DACBR2;
                break;
            case DAC_X1:
                type=DACX1;
                break;
            case DAC_X2:
                type=DACX2;
                break;
            case DAC_Y1:
                type=DACY1;
                break;
            case DAC_Y2:
                type=DACY2;
                break;
            default:
                isError=true;
            }
            return_queue.push(new returnBuffer(type, float(((float)val) / AFM_DAC_SCALING)));
        } else {
            isError = true;
        }
        break;
    case AFM_ADC_READ_SELECT:
        if (uart_resp.at(1) == AFM_ADC_READ_SELECT) {
            //TODO change me!
            val = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
            returnType type = NONE;
            switch(uart_resp.at(2)) {
            case ADC_ZOFFSET:
                type=ADCZOFFSET;
                break;
            case ADC_PHASE:
                type=ADCPHASE;
                break;
            default:
                type=ADC;
            }
            return_queue.push(new returnBuffer(type, float(((float)val) / AFM_ADC_SCALING)));
        } else {
            isError=true;
        }
//    case READSIGNALPHASEOFFSET:
//        if (uart_resp.at(1) == AFM_ADC_READ_SPO) {
//            signal = (((unsigned char)uart_resp.at(1) << 8) | (unsigned char)uart_resp.at(0));
//            offset = (((unsigned char)uart_resp.at(3) << 8) | (unsigned char)uart_resp.at(1));
//            phase = (((unsigned char)uart_resp.at(5) << 8) | (unsigned char)uart_resp.at(4));
//            graph_queue.push(new returnBuffer(READSIGNALPHASEOFFSET, AFM_SUCCESS, signal / AFM_DAC_SCALING, offset / AFM_DAC_SCALING, phase / AFM_DAC_SCALING));

//        } else {
//            isError = true;
//        }
//        break;
    case AFM_SET_DAC_MAX:
        if (uart_resp.at(1) == AFM_SET_DAC_MAX) {
            return_queue.push(new returnBuffer(ADCZOFFSET, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
//    case SETDIRBACKWARD:
//        if (uart_resp.at(1) == 'o' && uart_resp.at(1) == AFM_STAGE_DIR_REVERSE_SELECT) {
//            return_queue.push(new returnBuffer(SETDIRBACKWARD, AFM_SUCCESS));

//        } else {
//            isError = true;
//        }
//        break;
//    case SETPULSEWIDTH:
//        if (uart_resp.at(1) == 'o' && uart_resp.at(1) == AFM_STAGE_PW_SELECT) {
//            return_queue.push(new returnBuffer(SETPULSEWIDTH, AFM_SUCCESS));

//        } else {
//            isError = true;
//        }
//        break;
//    case ABORTAUTOAPPROACH:
//        if (uart_resp.at(1) == 'o' && uart_resp.at(1) == AFM_ABORT) {
//            return_queue.push(new returnBuffer(ABORTAUTOAPPROACH, AFM_SUCCESS));

//        } else {
//            isError = true;
//        }
//        break;
//    case AUTOAPPROACH:
//        if (uart_resp.at(1) == 'o' && uart_resp.at(1) == AFM_AUTOAPPROACH_SELECT) {
//            return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_SUCCESS));

//        } else if (uart_resp.at(1) == 'f') {
//            return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_FAIL));
//        } else {
//            isError = true;
//        }
//        break;
//    case SCANPARAMETERS:
//        if (uart_resp.at(1) == AFM_SCAN_PARAMETERS && uart_resp.at(0) == 'o') {
//            return_queue.push(new returnBuffer(SCANPARAMETERS, AFM_SUCCESS));
//        } else {
//            isError = true;
//        }
//        break;
//    case STARTSCAN:
//        if (uart_resp.at(1) == AFM_START_SCAN) {
//            return_queue.push(new returnBuffer(STARTSCAN, AFM_SUCCESS));
//        } else {
//            isError = true;
//        }
//        break;
//    case SCANDATA:
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
//        break;
    case AFM_PID_ENABLE_SELECT:
        if (uart_resp.at(1) == AFM_PID_ENABLE_SELECT) {
            return_queue.push(new returnBuffer(PIDENABLE, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_PID_DISABLE_SELECT:
        if (uart_resp.at(1) == AFM_PID_DISABLE_SELECT) {
            return_queue.push(new returnBuffer(PIDDISABLE, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_PID_P_SELECT:
        if (uart_resp.at(1) == AFM_PID_P_SELECT) {
            return_queue.push(new returnBuffer(SETP, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_PID_I_SELECT:
        if (uart_resp.at(1) == AFM_PID_I_SELECT) {
            return_queue.push(new returnBuffer(SETI, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_PID_D_SELECT:
        if (uart_resp.at(1) == AFM_PID_D_SELECT) {
            return_queue.push(new returnBuffer(SETD, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_PID_SETPOINT_SELECT:
        if (uart_resp.at(1) == AFM_PID_SETPOINT_SELECT) {
            return_queue.push(new returnBuffer(SETPOINT, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_DDS_SWEEP_SET:
        if (uart_resp.at(1) == AFM_DDS_SWEEP_SET) {
            return_queue.push(new returnBuffer(SETDDS, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
    case AFM_SET_PGA:
        if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_SET_PGA) {
            return_queue.push(new returnBuffer(SETPGA, AFM_SUCCESS));
        } else {
            isError = true;
        }
        break;
//            case DEVICECALIBRATION:
//                if (uart_resp.at(1) == 'o') {
//                    return_queue.push(new returnBuffer(DEVICECALIBRATION, AFM_SUCCESS));
//                     //acknowledge byte
//                } else {
//                    isError = true;
//                }
//                break;
//            case FORCECURVE:
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
//            isError=false;     //temp placeholder
//            break;
    case AFM_FREQ_SWEEP_AD5932:
        if (uart_resp.at(1) == AFM_FREQ_SWEEP_AD5932 && uart_resp.size() >= (4+2)) {
            int bytesRead;
            int success;
            bytesRead = uart_resp.size();

            quint16 ampVal;
            quint16 phaseVal;

            // y data
            amplitudeData->clear();
            phaseData->clear();

            for (int i = 0; i < uart_resp.size(); i += 4) {
                ampVal = BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i + 1]);
                phaseVal = BYTES_TO_WORD((quint8)uart_resp[i + 2], (quint8)uart_resp[i + 3]);

                amplitudeData->append(double(ampVal) / AFM_ADC_SCALING);
                phaseData->append(double(phaseVal) / AFM_ADC_SCALING);

                qDebug() << "Freq Sweep Amplitude: " << double(ampVal) / AFM_ADC_SCALING << " Phase: " << double(phaseVal) / AFM_ADC_SCALING;
            }

            return_queue.push(new returnBuffer(FREQSWEEP, AFM_SUCCESS, *amplitudeData, *phaseData, bytesRead));
        } else {
            isError = true;
        }
        break;

    }     // End switch

    // Post-processing
    /* If there is a serial comm mismatch or error, clear the following to 'reset':
     * 1. Receive queue
     * 2. Serial incoming buffer
     * 3. Serial incoming array (uart_resp)
     */
    if (isError) {
        if (!receive_queue.empty()) {
            receive_queue.pop();
        }
        uart_resp.clear();
        emit serialError(); // this isn't necessary for release
    } else {
        //we good
        receive_queue.pop();
        //clear the current msg, so that the next one may be read
        uart_resp.clear();
    }

} // end process_uart_resp


void receive_worker::abort()
{
    _abort = true;
}
receive_worker::~receive_worker()
{
    emit finished();
}
