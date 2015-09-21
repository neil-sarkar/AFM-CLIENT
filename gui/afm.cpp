#include "afm.h"
#include <QMessageBox>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI
#define AFM_MAX_DATA_SIZE 1     //Basically write 1 character at a time
#define AFM_POLL_TIMEOUT 50     //Poll the buffer every 1ms
#define AFM_LONG_TIMEOUT 5000   //Longer timeout for large data

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

int icspiAFM::writeByte(char byte)
{
    if (write(&byte, AFM_MAX_DATA_SIZE) > -1) {
        return AFM_SUCCESS;
    } else {
#if AFM_DEBUG
        QString hex_equivalent_print = QString("%1").arg(byte, 0, 16);
        qDebug() << "icspiAFM::writeByte failed to write 0x" << hex_equivalent_print;
#endif
        return AFM_FAIL;
    }
}

/*
 * Collects the bytes to send
 * After all the bytes are collected, call writeMsg() to actually send it out
 */
int icspiAFM::addPayloadByte(char byte)
{
    payload_out_buffer += byte;
}

/*
 * Clear the payload out buffer before sending anything
 */
void icspiAFM::clearPayloadBuffer()
{
    payload_out_buffer.clear();
}

/*
 * A wrapper function for sending serial message.
 * writeByte should not be used, since it does not escape special characters.
 */
int icspiAFM::writeMsg(char msg_id, QByteArray payload)
{
    int writeByte_result; //local var for debugging only

    //Close the last message, in case the last message was bad
    writeByte_result = writeByte(SERIAL_MSG_NEWLINE);

    //Increment and Write the message tag
    message_tag++;

    if (message_tag >= 255)
        message_tag = 1;
    else if (message_tag == SERIAL_MSG_NEWLINE || message_tag == SERIAL_MSG_ESCAPE)
        message_tag++; // Assumes the special characters are not consecutive...

    writeByte_result = writeByte(message_tag);

    //Write the message ID
    writeByte_result = writeByte(msg_id);

    //Write the message payload, and mask as nessessary
    for (auto payload_byte : payload) {
        // Special Bytes
        if (payload_byte == SERIAL_MSG_NEWLINE || payload_byte == SERIAL_MSG_ESCAPE) {
            writeByte(SERIAL_MSG_ESCAPE);
            writeByte(payload_byte | SERIAL_MSG_MASK);
        } else {
            writeByte(payload_byte);
        }
    }

    //Close the message
    writeByte(SERIAL_MSG_NEWLINE);

#if AFM_DEBUG
    qDebug() << "Sent TAG " << QString().sprintf("%2p", message_tag) << " ID " << msg_id << " " << QString().sprintf("%2p", msg_id) << " payload 0x" << payload.toHex();
#endif

    return AFM_SUCCESS;
}

/*
 * Send a message with msg_id using payload that is currently stored.
 */
int icspiAFM::writeMsg(char msg_id)
{
    int result = writeMsg(msg_id, payload_out_buffer);

    payload_out_buffer.clear();

    return result;
}

//QByteArray icspiAFM::getNextMsg(){
//    serial_incoming_buffer += this->readAll();

//}

/*
 * Blocking Function.
 * Waits until there is a complete message received, then returns that message.
 *
 * It should only return one message at a time. Masking will be removed.
 */
QByteArray icspiAFM::waitForMsg(int timeout)
{
    QByteArray incoming_message;
    char incoming_byte = 0x00;
    bool message_complete = false, escape_char_received = false;
    int msg_length = 0;

    if (serial_incoming_buffer.isEmpty() && bytesAvailable() > 0) {
            serial_incoming_buffer += this->readAll();
//#if AFM_DEBUG
////    qDebug() << "readAll 0x" << serial_incoming_buffer.toHex();
//#endif
   } // else APPEND!!!

    while (!message_complete) {
        //Read one byte at a time
         //while(waitForReadyRead(10)); //Wait indefinitely until we get something
       // if (bytesAvailable() > 0)
      //      int status = this->read(&incoming_byte, 1);
        //qDebug() << " SR" << status;
// QByteArray test_message = readAll();
        // qDebug() << "  0x" << test_message.toHex();

        //  if(incoming_byte != '\0' && status > 0){

        if (!serial_incoming_buffer.isEmpty()) {
            incoming_byte = serial_incoming_buffer.at(msg_length);
            msg_length++;
            printf(" 0x%02x", incoming_byte);
        } else {
            // The incoming buffer is empty but the last message was not a complete one
            return "";
        }

        // Take care of the incoming byte...

        if (incoming_byte == SERIAL_MSG_NEWLINE) {
            // Newline char received. Is everything we got so far a valid message?
            if (incoming_message.size() >= 2) {
                // Check length... should be at least two bytes
                message_complete = true;
                break;
            } else {
                // Otherwise, it was an empty or invalid message. Discard and move on.
                incoming_message.clear();
            }
        } else if (incoming_byte == SERIAL_MSG_ESCAPE && !escape_char_received) {
            // Is this escape char?
            escape_char_received = true;
        } else if (escape_char_received) {
            // Do we need to unmask this?
            incoming_message += incoming_byte & ~SERIAL_MSG_MASK;
            escape_char_received = false;
        } else {
            // None of the above. Collect it in message QByteArray
            incoming_message += incoming_byte;
        }
    }

    serial_incoming_buffer.remove(0, msg_length);

#if AFM_DEBUG
    if (incoming_message.size() > 0) {
        //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
        qDebug()	<< "  0x" << incoming_message.toHex()
                << " Size:" << incoming_message.size();
    }
#endif

    return incoming_message;
}


QByteArray icspiAFM::waitForData(int timeout)
{
    QByteArray responseData;

    while (waitForReadyRead(timeout))
        responseData += readAll(); //Causes segmentation fault?

#if AFM_DEBUG
    qDebug() << "Response Data Size:" << responseData.size();
#endif
    return responseData;
}

void icspiAFM::writeDAC(qint8 dacID, double val)
{
//    if(val>AFM_DAC_MAX_VOLTAGE){
//        return AFM_FAIL;
//    }
    qint16 digitalValue = AFM_DAC_SCALING * val;

#if AFM_DEBUG
    qDebug() << "DAC Digital Value to be written:" << (digitalValue);
#endif

    addPayloadByte(dacID);
    addPayloadByte((digitalValue & 0xFF));
    addPayloadByte((digitalValue >> 8));

    writeMsg(AFM_DAC_WRITE_SELECT);
}

void icspiAFM::readDAC(qint8 dacID)
{
    addPayloadByte(AFM_DAC_READ_SELECT);
    addPayloadByte(dacID);
//#if AFM_DEBUG
//    qDebug() << "Bytes Read from DAC: " << res.size();
//#endif
}

void icspiAFM::readADC(qint8 adcID)
{
    addPayloadByte(AFM_ADC_READ_SELECT);
    addPayloadByte(adcID);
//#if AFM_DEBUG
//   qDebug() << "ADC Digital Value read" << val;
//#endif
}

void icspiAFM::setRasterStep()
{
//    writeByte(AFM_RASTER_STEP_SELECT);
//    writeByte();
//    writeByte();
//    writeByte();
//    writeByte();
}

void icspiAFM::memsSetOffset(double val)
{
    setPGA(PGA_Z_OFFSET, val);
    //There should be a comparison against a maximum value for offset voltage
}

void icspiAFM::memsSetFrequency(double val)
{
    setPGA(PGA_Z_OFFSET, val);
    //return AFM_SUCCESS;
}

void icspiAFM::memsSetAmplitude(double val)
{
    //writeDAC(DAC_ZAMP, val);
    setPGA(PGA_AMPLITUDE, val);
    //return AFM_SUCCESS;
}

void icspiAFM::memsSetBridgeVoltage(double val)
{
    writeDAC(DAC_BR1, val);
}

void icspiAFM::pidEnable()
{
    addPayloadByte(AFM_PID_ENABLE_SELECT);
}

void icspiAFM::pidDisable()
{
    addPayloadByte(AFM_PID_DISABLE_SELECT);
    //return AFM_SUCCESS;
}

void icspiAFM::pidSetP(float P)
{
    addPayloadByte(AFM_PID_P_SELECT);
    addPayloadByte(((char *)&P)[0]);
    addPayloadByte(((char *)&P)[1]);
    addPayloadByte(((char *)&P)[2]);
    addPayloadByte(((char *)&P)[3]);
    //There should be a max allowed P value. Return FAIL if P value over the range
}

void icspiAFM::pidSetI(float I)
{
    addPayloadByte(AFM_PID_I_SELECT);
    addPayloadByte(((char *)&I)[0]);
    addPayloadByte(((char *)&I)[1]);
    addPayloadByte(((char *)&I)[2]);
    addPayloadByte(((char *)&I)[3]);
    //There should be a max allowed I value. Return FAIL if I value over the range
}

void icspiAFM::pidSetD(float D)
{
    addPayloadByte(AFM_PID_D_SELECT);
    addPayloadByte(((char *)&D)[0]);
    addPayloadByte(((char *)&D)[1]);
    addPayloadByte(((char *)&D)[2]);
    addPayloadByte(((char *)&D)[3]);
    //There should be a max allowed I value. Return FAIL if D value over the range
}

void icspiAFM::pidSetValues(qint8 P, qint8 I, qint8 D)
{
    pidSetP(P);
    pidSetI(I);
    pidSetD(D);
}

void icspiAFM::pidSetPoint(float val)
{
    addPayloadByte(AFM_PID_SETPOINT_SELECT);

    addPayloadByte(((char *)&val)[0]);
    addPayloadByte(((char *)&val)[1]);
    //return AFM_SUCCESS; //Should be checked against a value range
}

void icspiAFM::stageSetPulseWidth(qint8 val)
{
    //Val should be checked against a value range
    addPayloadByte(val);
    writeMsg(AFM_STAGE_PW_SELECT);
}

void icspiAFM::stageSetDirForward()
{
    writeMsg(AFM_STAGE_DIR_FWD_SELECT);
}

void icspiAFM::stageSetDirBackward()
{
    writeMsg(AFM_STAGE_DIR_REVERSE_SELECT);
}

void icspiAFM::stageSetStep()
{
    writeMsg(AFM_STAGE_PULSE_STEP);
}

void icspiAFM::stageStepForward()
{
    stageSetDirForward();
    stageSetStep();
}

void icspiAFM::stageStepBackward()
{
    stageSetDirBackward();
    stageSetStep();
}

void icspiAFM::stageMoveForward()
{
    stageSetDirForward();
}

void icspiAFM::stageMoveBackward()
{
    stageSetDirBackward();
}

void icspiAFM::setDDSSettings(quint16	numPoints,
                  quint16	startFrequency,
                  quint16	stepSize)
{
    qDebug() << "Writing to DDS settings";
    // Set DDS settings

    qDebug() << "Start Freq -> High Byte: " << (quint16)(startFrequency >> 8) << " Low Byte: " << (quint8)startFrequency;
    // start freq
    addPayloadByte((qint8)startFrequency);                  // low byte
    addPayloadByte((qint8)(startFrequency >> 8));           // high bye

    qDebug() << "Step Size -> High Byte: " << (quint16)(stepSize >> 8) << " Low Byte: " << (quint8)stepSize;
    // step size
    addPayloadByte((qint8)stepSize);                // low byte
    addPayloadByte((qint8)(stepSize >> 8));         // high bye

    qDebug() << "Num Points -> High Byte: " << (quint16)(numPoints >> 8) << " Low Byte: " << (quint8)numPoints;
    // num points
    addPayloadByte((qint8)numPoints);               // low byte
    addPayloadByte((qint8)(numPoints >> 8));        // high bye

    writeMsg(AFM_DDS_SWEEP_SET);
}

// Start the frequency sweep. The data will be fetched from the receiver
void icspiAFM::frequencySweep(quint16	numPoints,
                  quint16	startFrequency,
                  quint16	stepSize)
{
    //writeDAC(AFM_DAC_VCO_ID, 0); // write 0V
    setDDSSettings(numPoints, startFrequency, stepSize);

    // start frequency sweep ASSUMING REV 2 BOARD!!!
    writeMsg(AFM_FREQ_SWEEP_AD5932);
}

void icspiAFM::rasterStep(float /*val1*/, float /*val2*/)
{
    //Not too sure about this function
}

void icspiAFM::autoApproach(double setpoint)
{
    qint16 _setpoint = AFM_DAC_SCALING * setpoint;

    addPayloadByte((_setpoint & 0xFF));
    addPayloadByte((_setpoint & 0x0F00) >> 8);

    addPayloadByte((150));
    addPayloadByte(0);

    writeMsg(AFM_AUTOAPPROACH_SELECT);
}

void icspiAFM::setDACValues(char dacID, double _val)
{
    clearPayloadBuffer();

    qint16 _max = AFM_DAC_SCALING * _val;

    addPayloadByte((char)dacID);
    addPayloadByte((_max & 0xFF));
    addPayloadByte((_max & 0x0F00) >> 8);

    writeMsg(AFM_SET_DAC_MAX);
}
void icspiAFM::deviceCalibration(double val, char side)
{
    qint16 _max = AFM_DAC_SCALING * val;
    float a = 0.0000000003438;
    float b = 0.0000001379;
    float c = -0.0000545;
    float d = 0;
    float e = 0;
    float f = 0;

    char _a[sizeof(float)];

    memcpy(_a, &a, sizeof(float));

    char _b[sizeof(float)];
    memcpy(_b, &b, sizeof(float));

    char _c[sizeof(float)];
    memcpy(_c, &c, sizeof(float));

    char _d[sizeof(float)];
    memcpy(_d, &d, sizeof(float));

    char _e[sizeof(float)];
    memcpy(_e, &e, sizeof(float));

    char _f[sizeof(float)];
    memcpy(_f, &f, sizeof(float));


    //4 bytes (o, ‘l’/’r’/‘z’, max_voltage byte 1, max_voltage byte 2)
    addPayloadByte(AFM_DEVICE_CALIBRATE);
    addPayloadByte(side);
    addPayloadByte((_max & 0xFF));
    addPayloadByte((_max & 0x0F00) >> 8);

    //12 bytes (a, b, c) – fitted quadratic polynomial coefficients for direct p-v relation (single precision floating point)
    addPayloadByte(_a[0]);
    addPayloadByte(_a[1]);
    addPayloadByte(_a[2]);
    addPayloadByte(_a[3]);
    addPayloadByte(_b[0]);
    addPayloadByte(_b[1]);
    addPayloadByte(_b[2]);
    addPayloadByte(_b[3]);
    addPayloadByte(_c[0]);
    addPayloadByte(_c[1]);
    addPayloadByte(_c[2]);
    addPayloadByte(_c[3]);

    //12 bytes (d, e, f) – fitted quadratic polynomial coefficients for coupling r-v relation (single precision floating point)
    addPayloadByte(_d[0]);
    addPayloadByte(_d[1]);
    addPayloadByte(_d[2]);
    addPayloadByte(_d[3]);
    addPayloadByte(_e[0]);
    addPayloadByte(_e[1]);
    addPayloadByte(_e[2]);
    addPayloadByte(_e[3]);
    addPayloadByte(_f[0]);
    addPayloadByte(_f[1]);
    addPayloadByte(_f[2]);
    addPayloadByte(_f[3]);
}

void icspiAFM::scanParameters(double	vmin_line,
                  double	vmin_scan,
                  double	vmax,
                  double	numpts,
                  double	numlines)
{
    /* We need to check that these parameters are valid
     * How?
     *
     *
     * */
    //qDebug() << AFM_DAC_SCALING << endl;
    qint16 _vminLine = AFM_DAC_SCALING * vmin_line;
    qint16 _vminScan = AFM_DAC_SCALING * vmin_scan;
    qint16 _vmax = AFM_DAC_SCALING * vmax;
    qint16 _numpts = numpts;
    qint16 _numLines = numlines;

    addPayloadByte(AFM_SCAN_PARAMETERS); //TODO FIX ME

    addPayloadByte(_vminLine & 0xFF);
    addPayloadByte((_vminLine & 0x0F00) >> 8);

    addPayloadByte(_vminScan & 0xFF);
    addPayloadByte((_vminScan & 0x0F00) >> 8);

    addPayloadByte(_vmax & 0xFF);
    addPayloadByte((_vmax & 0x0F00) >> 8);

    addPayloadByte(_numpts & 0xFF);
    addPayloadByte((_numpts & 0x0F00) >> 8);

    addPayloadByte(_numLines & 0xFF);
    addPayloadByte((_numLines & 0x0F00) >> 8);
}
void icspiAFM::startScan()
{
    writeMsg(AFM_START_SCAN);
}

void icspiAFM::scanStep()
{
    writeMsg(AFM_SCAN_STEP);
}

void icspiAFM::setPGA(char channel, double val)
{
    clearPayloadBuffer();
    addPayloadByte(channel);

    if (channel == PGA_AMPLITUDE || channel == PGA_Z_OFFSET) {
        qint8 newval = abs(20 * log10(val / 100));
        addPayloadByte(newval);
    } else {
        qint8 newval = (((20 * log10(val / 100)) - 31.5) / 0.5) + 255;
        addPayloadByte(newval);
    }

    writeMsg(AFM_SET_PGA);
}

void icspiAFM::readSignalPhaseOffset()
{
    writeMsg(AFM_ADC_READ_SPO);
}

void icspiAFM::forceCurve()
{
    addPayloadByte('N');
}
