#include "receive_worker.h"


void receive_worker::mainLoop()
{
    //Initial setup

    //Doesn't seem to need anything...
}

/*
 * The push_recv_queue function is to invoked from
 * afm_worker (which provides the message ID, TAG, and Result)
 */
void receive_worker::push_recv_queue(unsigned char message_id, unsigned char message_tag, int writeByte_result){
    receivetype receivenode;
    receivenode.message_id = message_id;
    receivenode.message_tag = message_tag;
    receivenode.writeByte_result = writeByte_result;
    receive_queue.push_back(receivenode);
}

void receive_worker::handle_error(short error_id){
    unsigned i = 0;
    bool match_found = false;

    switch(error_id) {
    case ERR_MSG_ID_MISMATCH:
        /*
         * The message ID received differs from what was recorded
         * in receive_queue. This should never happen. Check MCU code.
         */
        //emit serialError();
        qDebug() << 'S' << "ERR_MSG_ID_MISMATCH for 0x" << uart_resp.toHex();
        break;
    case ERR_MSG_TAG_MISMATCH:
        /* The message tag received differs from what is expected.
         * Possible causes include:
         * - Qt missed some messages sent by MCU
         * - MCU reply arrived before receive_queue has received a record of it
         *        (possible, but highly unlikely!)
         * - MCU firmware bugs
         * Remedy algorithm:
         * - Loop through all elements in the receive_queue, and see if the said tag
         *   already exists AND matches the ID expected. (Although tag rolling counter
         *   is only 255, the probability of having a matching tag and ID is low)
         * - If a match is found, that means receive_queue is behind in time with MCU.
         *   Disregard all messages prior to the match, and announce them as missing.
         * - If cannot find a match, then silently disregard this message
         */
        for(auto _node:receive_queue) {
            if((unsigned char)uart_resp.at(0) == _node.message_tag && (unsigned char)uart_resp.at(1) == _node.message_id) {
                match_found = true;
                break;
            }
            i++;
        }

        if(match_found) {
            for(int j=0; j<i; j++) {
                return_queue.push(new returnBuffer(ERR_MSG_MISSED, receive_queue.at(0).message_tag,receive_queue.at(0).message_id));
                receive_queue.pop_front();
            }
            process_uart_resp(uart_resp);
        }

        qDebug() << 'S' << "ERR_MSG_TAG_MISMATCH for 0x" << uart_resp.toHex() << "Match found? " << match_found;
        break;
    case ERR_MSG_SIZE_MISMATCH:
        /*
         * The message received has correct ID and tag but size is incorrect.
         * Check MCU code.
         */
        receive_queue.pop_front();
        qDebug() << 'S'<< "ERR_MSG_SIZE_MISMATCH - Check MCU Code?";
        break;
    case ERR_MSG_UNSOLICITED:
        qDebug() << 'S' << "ERR_MSG_UNSOLICITED 0x" << uart_resp.toHex();
        break;
    default:
        /*
         * All other cases... do nothing and move on.
         * ERR_MSG_UNSOLICITED We received a message but we aren't expecting anything.
         */
        qDebug() << 'S' << "Error for incoming serial message 0x" << uart_resp.toHex() << " Error ID " << error_id;
        break;
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

    // 0. Is this an empty message? or a "magic message"?
    // "magic messages" include reboot messages, so they
    // will be handled here
    if(uart_resp.at(0) == SERIAL_MSG_NEWLINE) {
        return;
    } else if((unsigned char)uart_resp.at(0) == SERIAL_MSG_SPECIAL_TAG &&
              (unsigned char)uart_resp.at(1) == 0x61 &&
              (unsigned char)uart_resp.at(2) == 0x66 &&
              (unsigned char)uart_resp.at(3) == 0x6d &&
              (unsigned char)uart_resp.at(4) == 0x21
              ) {
        qDebug() << 'S' << "PCB Restart Detected, receive_queue cleared" << uart_resp.toHex();
        return_queue.push(new returnBuffer(AFMREBOOT, AFM_SUCCESS));
        receive_queue.clear(); //Also reset the pending messages
        return;
    }

    // 1. Are we expecting to receive something? Or is it a special message?
    if ((unsigned char)uart_resp.at(0) == SERIAL_MSG_SPECIAL_TAG){
        qDebug() << "Special TAG received. _node.message_id is now the special Tag message";
        _node.message_tag = SERIAL_MSG_SPECIAL_TAG;
        _node.message_id = (unsigned char)uart_resp.at(1);
    } else if (!receive_queue.empty()) {
        _node = receive_queue.front();
        //Check if this is a reboot (Magic string)
    } else {
        handle_error(ERR_MSG_UNSOLICITED);
        return; //TODO change these to like, error handlers or something
    }

    // 2. Make sure the uart_resp array actually has things inside
    if (uart_resp.isEmpty() || uart_resp.isNull()) {
        qDebug() << "An empty or null uart_resp is received at receive_worker::process_uart_resp. This should not happen. ";
        return;
    }

    /* Now look at the next element in receive_queue (_node)
     * Compare this _node with what is received in uart_resp
     * Do they match? They should match, by temporal sequence.
     * If they do not, throw serial error, then empty the uart_resp.
     * Wait to be called by the afm_worker signal next time.
     *
     */

    // The checking of message legitimacy should be done before the switch statement.
    // It is redundant to check it in every case.

    // 3. The message TAG shall match, unless it is SERIAL_MSG_SPECIAL_TAG (A special message)
    // If not, start the investigation sequence, throw error, pop, and continue
    if((unsigned char)uart_resp.at(0) != _node.message_tag && (unsigned char)uart_resp.at(0) != SERIAL_MSG_SPECIAL_TAG) {
        handle_error(ERR_MSG_TAG_MISMATCH);
        return;
    }


    if (uart_resp.size() > 0) {
        //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
        qDebug() << "receive_worker now processing 0x" << uart_resp.toHex();
    }

    // 4. All looks good. Let's start actually processing!
    /*
     * IMPORTANT NOTICE
     * Only uart_resp.at(0) and uart_resp.at(1) are guaranteed to have data.
     * In order to acess data beyond index 1, the case processor MUST check
     * size of uart_resp. Neglecting to do this will result in ASSERT/Segmentation!
     */
    //Initialize first (crosses initialization)
    returnType type = NONE;
    switch (_node.message_id) {
    // Manual logic required
    case AFM_SET_DAC_MAX:
        if (uart_resp.at(1) != AFM_SET_DAC_MAX) {
            handle_error(ERR_MSG_ID_MISMATCH);
            return_queue.push(new returnBuffer(ADCZOFFSET, AFM_FAIL));
            break;
        }
        if (uart_resp.size() < AFM_SET_DAC_MAX_RSPLEN) {
            handle_error(ERR_MSG_SIZE_MISMATCH);
            return_queue.push(new returnBuffer(ADCZOFFSET, AFM_FAIL));
            break;
        }
        if (uart_resp.at(3) == 'o') {
            return_queue.push(new returnBuffer(ADCZOFFSET, AFM_SUCCESS));
        }else{
            handle_error(ERR_COMMAND_FAILED);
            return_queue.push(new returnBuffer(ADCZOFFSET, AFM_FAIL));
        }
        break;
    case AFM_DAC_READ_SELECT:
        if (uart_resp.at(1) != AFM_DAC_READ_SELECT) {
            handle_error(ERR_MSG_ID_MISMATCH);
            break;
        }
        if(uart_resp.size() < AFM_DAC_READ_SELECT_RSPLEN) {
            handle_error(ERR_MSG_SIZE_MISMATCH);
            break;
        }
        val = (((unsigned char)uart_resp.at(4) << 8) | (unsigned char)uart_resp.at(3));
        switch(uart_resp.at(2)) {
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
            handle_error(ERR_COMMAND_FAILED);
            break;
        }
        return_queue.push(new returnBuffer(type, float(((float)val) * AFM_DAC_SCALING)));
        break;
    case AFM_ADC_READ_SELECT:
        if (uart_resp.at(1) != AFM_ADC_READ_SELECT) {
            handle_error(ERR_MSG_ID_MISMATCH);
            break;
        }
        if(uart_resp.size() < AFM_ADC_READ_SELECT_RSPLEN) {
            handle_error(ERR_MSG_SIZE_MISMATCH);
            break;
        }
        val = (((unsigned char)uart_resp.at(4) << 8) | (unsigned char)uart_resp.at(3));
        switch(uart_resp.at(2)) {
        case ADC_Z_PZR_AMP:
            type=ADCZOFFSET;
            break;
        case ADC_PHASE:
            type=ADCPHASE;
            break;
        default:
            type=ADC;
        }
        return_queue.push(new returnBuffer(type, float(((float)val) * AFM_ADC_SCALING)));
        break;
    case AFM_FREQ_SWEEP_AD9837:
    case AFM_FREQ_SWEEP_AD5932:
        if ((uart_resp.at(1) == AFM_FREQ_SWEEP_AD5932 || uart_resp.at(1) == AFM_FREQ_SWEEP_AD9837) && uart_resp.size() >= 6) {
            int bytesRead;
            int success;
            bytesRead = uart_resp.size();

            quint16 ampVal;
            quint16 phaseVal;

            // y data
            amplitudeData->clear();
            phaseData->clear();

            for (int i = 2; i < uart_resp.size(); i += 4) {
                ampVal = BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i + 1]);
                phaseVal = BYTES_TO_WORD((quint8)uart_resp[i + 2], (quint8)uart_resp[i + 3]);

                amplitudeData->append(double(ampVal) * AFM_ADC_SCALING);
                phaseData->append(double(phaseVal) * AFM_ADC_SCALING);

                // qDebug() << "Freq Sweep Amplitude: " << double(ampVal) * AFM_ADC_SCALING << " Phase: " << double(phaseVal) * AFM_ADC_SCALING;
            }

            return_queue.push(new returnBuffer(FREQSWEEP, AFM_SUCCESS, *amplitudeData, *phaseData, bytesRead));
        } else {
            handle_error(ERR_COMMAND_FAILED);
        }
        break;
    case AFM_FORCE_CURVE:
        if (uart_resp.at(1) == AFM_FORCE_CURVE) {
            amplitudeData->clear();
            phaseData->clear();
            quint16 intVal;
            //quint16 phaseVal;
            for (int i = 2; i < uart_resp.size(); i++) {
                intVal = BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i++]);
                //phaseVal = BYTES_TO_WORD((quint8)uart_resp[i+2],(quint8)uart_resp[i+3]);
                amplitudeData->append(double(intVal) * AFM_ADC_SCALING);
                phaseData->append(0);
            }
            return_queue.push(new returnBuffer(FORCECURVE, 0, *amplitudeData, *phaseData, uart_resp.size()));

        } else {
            handle_error(ERR_COMMAND_FAILED);
        }
        break;
    case AFM_SCAN_STEP_4ACT:
        if (uart_resp.at(1) != AFM_SCAN_STEP_4ACT) {
            handle_error(ERR_MSG_ID_MISMATCH);
            break;
        }
        if(uart_resp.size() < AFM_SCAN_STEP_4ACT_RSPLEN) {
            handle_error(ERR_MSG_SIZE_MISMATCH);
            break;
        }
        /*
         * Receive up to however many points we need.
         * For 4ACT PCB3, Eight points of data received.
         * Clear the three scan data buffers, and store the new data in.
         * z_offset_adc,  z_amp_adc, and z_phase_adc are cleared each time
         * this function is called, so make sure you do not request new data
         * until the existing data has been saved
         */
        z_offset_adc->clear();
        z_amp_adc->clear();
        z_phase_adc->clear();
        if(uart_resp.size() > AFM_SCAN_STEP_4ACT_RSPLEN &&
           ((uart_resp.size()-2) % 6 == 0)) {
            for (int i = 2; i < uart_resp.size(); i+=6) {
                // ampVal = ;
                // phaseVal = BYTES_TO_WORD((quint8)uart_resp[i + 2], (quint8)uart_resp[i + 3]);
                z_amp_adc->append((double)BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i+1]));
                z_offset_adc->append((double)BYTES_TO_WORD((quint8)uart_resp[i+2], (quint8)uart_resp[i+3]));
                z_phase_adc->append((double)BYTES_TO_WORD((quint8)uart_resp[i+4], (quint8)uart_resp[i+5]));
            }
            return_queue.push(new returnBuffer(SCANDATA, AFM_SUCCESS, *z_offset_adc, *z_amp_adc, *z_phase_adc));
        } else {
            qDebug() << 'S' << "!!! Bad scan data.";
            return_queue.push(new returnBuffer(SCANDATA, AFM_FAIL, *z_offset_adc, *z_amp_adc, *z_phase_adc));
        }
        break;
    case AFM_READ_SPO:
        if (uart_resp.at(1) != AFM_READ_SPO) {
            handle_error(ERR_MSG_ID_MISMATCH);
            break;
        }
        if(uart_resp.size() < AFM_READ_SPO_RSPLEN) {
            handle_error(ERR_MSG_SIZE_MISMATCH);
            break;
        }
        {
            int i=2;
            signal = (double)BYTES_TO_WORD((quint8)uart_resp[i], (quint8)uart_resp[i+1]);
            offset = (double)BYTES_TO_WORD((quint8)uart_resp[i+2], (quint8)uart_resp[i+3]);
            phase = (double)BYTES_TO_WORD((quint8)uart_resp[i+4], (quint8)uart_resp[i+5]);
            graph_queue.push(new returnBuffer(READSIGNALPHASEOFFSET, AFM_SUCCESS, signal * AFM_ADC_SCALING, offset * AFM_DAC_SCALING, phase * AFM_ADC_SCALING));
            return_queue.push(new returnBuffer(READSIGNALPHASEOFFSET, AFM_SUCCESS, signal * AFM_ADC_SCALING, offset * AFM_DAC_SCALING, phase * AFM_ADC_SCALING));
        }
        break;
    case AFM_AUTOAPPR_STATUS:
        if ((unsigned char)uart_resp.at(1) != AFM_AUTOAPPR_STATUS) {
            handle_error(ERR_MSG_ID_MISMATCH);
            break;
        }
        if(uart_resp.size() <AFM_AUTOAPPR_STATUS_RSPLEN) {
            handle_error(ERR_MSG_SIZE_MISMATCH);
            break;
        }
        {
            val = (((unsigned char)uart_resp.at(4) << 8) | (unsigned char)uart_resp.at(3));
            return_queue.push(new returnBuffer(AAPPR_STA,
                                               (quint8)uart_resp[2],
                                               float(((float)val) * AFM_ADC_SCALING),
                                               0.0,
                                               0.0));
        }
        break;
    //ANCIENT CODE BELOW:
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

    //    case AFM_ABORT:
    //        if (uart_resp.at(2) == 'o' && uart_resp.at(1) == AFM_ABORT) {
    //            return_queue.push(new returnBuffer(ABORTAUTOAPPROACH, AFM_SUCCESS));
    //        } else {
    //            isError = true;
    //        }
    //        break;

    /* AUTOMATIC CODE GENERATION */
    /* Automatically Code Generation BEGIN
       [[[cog
       from CodeValet import CodeValet
       c = CodeValet()
       c.receive_worker_switch()
       ]]]*/
       case AFM_DAC_WRITE_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_DAC_WRITE_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(WRITE, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_DAC_WRITE_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(WRITE, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(WRITE, AFM_SUCCESS));
       break;
       case AFM_PID_ENABLE_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PID_ENABLE_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(PIDENABLE, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PID_ENABLE_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(PIDENABLE, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(PIDENABLE, AFM_SUCCESS));
       break;
       case AFM_PID_DISABLE_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PID_DISABLE_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(PIDDISABLE, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PID_DISABLE_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(PIDDISABLE, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(PIDDISABLE, AFM_SUCCESS));
       break;
       case AFM_PID_P_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PID_P_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETP, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PID_P_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETP, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETP, AFM_SUCCESS));
       break;
       case AFM_PID_I_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PID_I_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETI, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PID_I_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETI, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETI, AFM_SUCCESS));
       break;
       case AFM_PID_D_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PID_D_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETD, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PID_D_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETD, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETD, AFM_SUCCESS));
       break;
       case AFM_PID_SETPOINT_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PID_SETPOINT_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETPOINT, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PID_SETPOINT_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETPOINT, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETPOINT, AFM_SUCCESS));
       break;
       case AFM_STAGE_PW_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STAGE_PW_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETPULSEWIDTH, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STAGE_PW_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETPULSEWIDTH, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(SETPULSEWIDTH, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(SETPULSEWIDTH, AFM_FAIL));}
       break;
       case AFM_DDS_AD9837_SET:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_DDS_AD9837_SET) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETDDS, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_DDS_AD9837_SET_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETDDS, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETDDS, AFM_SUCCESS));
       break;
       case AFM_DDS_AD5932_SET:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_DDS_AD5932_SET) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETDDS, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_DDS_AD5932_SET_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETDDS, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETDDS, AFM_SUCCESS));
       break;
       case AFM_PCBMOT_STAGE_DIR_FWD_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PCBMOT_STAGE_DIR_FWD_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETDIRFORWARD, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PCBMOT_STAGE_DIR_FWD_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETDIRFORWARD, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(SETDIRFORWARD, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(SETDIRFORWARD, AFM_FAIL));}
       break;
       case AFM_PCBMOT_STAGE_DIR_REVERSE_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_PCBMOT_STAGE_DIR_REVERSE_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETDIRBACKWARD, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_PCBMOT_STAGE_DIR_REVERSE_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETDIRBACKWARD, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(SETDIRBACKWARD, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(SETDIRBACKWARD, AFM_FAIL));}
       break;
       case AFM_AUTOAPPROACH_SELECT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_AUTOAPPROACH_SELECT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_AUTOAPPROACH_SELECT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(AUTOAPPROACH, AFM_FAIL));}
       break;
       case AFM_DEVICE_CALIBRATE:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_DEVICE_CALIBRATE) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(DEVICECALIBRATION, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_DEVICE_CALIBRATE_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(DEVICECALIBRATION, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(DEVICECALIBRATION, AFM_SUCCESS));
       break;
       case AFM_SCAN_PARAMETERS:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_SCAN_PARAMETERS) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SCANPARAMETERS, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_SCAN_PARAMETERS_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SCANPARAMETERS, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(SCANPARAMETERS, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(SCANPARAMETERS, AFM_FAIL));}
       break;
       case AFM_START_SCAN:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_START_SCAN) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STARTSCAN, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_START_SCAN_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STARTSCAN, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STARTSCAN, AFM_SUCCESS));
       break;
       case AFM_SET_DACTABLE:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_SET_DACTABLE) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETDACTABLE, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_SET_DACTABLE_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETDACTABLE, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(SETDACTABLE, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(SETDACTABLE, AFM_FAIL));}
       break;
       case AFM_SET_PGA:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_SET_PGA) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETPGA, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_SET_PGA_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETPGA, AFM_FAIL));
       break;}
       if (uart_resp.at(2) == 'o') {
       return_queue.push(new returnBuffer(SETPGA, AFM_SUCCESS));
       }else{handle_error(ERR_COMMAND_FAILED);
       return_queue.push(new returnBuffer(SETPGA, AFM_FAIL));}
       break;
       case AFM_SET_PGA_PCB3:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_SET_PGA_PCB3) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SETPGA, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_SET_PGA_PCB3_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SETPGA, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SETPGA, AFM_SUCCESS));
       break;
       case AFM_SET_SIGGEN:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_SET_SIGGEN) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(SIGGEN, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_SET_SIGGEN_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(SIGGEN, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(SIGGEN, AFM_SUCCESS));
       break;
       case AFM_START_SCAN_4ACT:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_START_SCAN_4ACT) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STARTSCAN_4ACT, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_START_SCAN_4ACT_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STARTSCAN_4ACT, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STARTSCAN_4ACT, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_WAKE:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_WAKE) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETSTATE, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_WAKE_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETSTATE, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTSETSTATE, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_SLEEP:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_SLEEP) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETSTATE, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_SLEEP_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETSTATE, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTSETSTATE, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_SPEED:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_SPEED) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETSPEED, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_SPEED_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETSPEED, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTSETSPEED, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_DIR:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_DIR) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETDIR, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_DIR_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETDIR, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTSETDIR, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_CONT_GO:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_CONT_GO) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTCONTGO, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_CONT_GO_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTCONTGO, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTCONTGO, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_CONT_STOP:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_CONT_STOP) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTCONTSTOP, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_CONT_STOP_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTCONTSTOP, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTCONTSTOP, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_MICROSTEP:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_MICROSTEP) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETMICROSTEP, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_MICROSTEP_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSETMICROSTEP, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTSETMICROSTEP, AFM_SUCCESS));
       break;
       case AFM_STEPMOT_SINGLESTEP:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_STEPMOT_SINGLESTEP) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSINGLESTEP, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_STEPMOT_SINGLESTEP_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(STEPMOTSINGLESTEP, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(STEPMOTSINGLESTEP, AFM_SUCCESS));
       break;
       case AFM_AUTOAPPR_BEGIN:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_AUTOAPPR_BEGIN) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(AAPPR_BEGIN, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_AUTOAPPR_BEGIN_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(AAPPR_BEGIN, AFM_FAIL));
       break;}
       break;
       case AFM_AUTOAPPR_STOP:   //CodeValet autogen
       if ((unsigned char)uart_resp.at(1) != AFM_AUTOAPPR_STOP) {
       handle_error(ERR_MSG_ID_MISMATCH);
       return_queue.push(new returnBuffer(AAPPR_STOP, AFM_FAIL));
       break;}
       if (uart_resp.size() < AFM_AUTOAPPR_STOP_RSPLEN) {
       handle_error(ERR_MSG_SIZE_MISMATCH);
       return_queue.push(new returnBuffer(AAPPR_STOP, AFM_FAIL));
       break;}
       return_queue.push(new returnBuffer(AAPPR_STOP, AFM_SUCCESS));
       break;
        //[[[end]]]
    } // End switch

    /* IMPORTANT! */
    // Cool, the message was processed without errors.
    //If this was NOT a special message, then pop the front element from receive queue
    if((unsigned char)uart_resp.at(0) != SERIAL_MSG_SPECIAL_TAG && receive_queue.size()>0){
        receive_queue.pop_front();
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
