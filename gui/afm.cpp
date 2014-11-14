#include "afm.h"
#include <QMessageBox>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI
#define AFM_MAX_DATA_SIZE 1 //Basically write 1 character at a time
#define AFM_POLL_TIMEOUT 50 //Poll the buffer every 1ms
#define AFM_LONG_TIMEOUT 5000 //Longer timeout for large data

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

int nanoiAFM::writeByte(char byte)
{
    //Change it to write sequentially.
    writeData(&byte, AFM_MAX_DATA_SIZE);
    waitForBytesWritten(1);

//    if(waitForData().at(0) == byte)
        return AFM_SUCCESS;
//    else
//        return AFM_FAIL;
}

QByteArray nanoiAFM::waitForData(int timeout)
{
    QByteArray responseData;
    while(waitForReadyRead(timeout)){
        responseData+= readAll();
    }
#if AFM_DEBUG
    qDebug() << "Response Data Size:" << responseData.size();
#endif
    return responseData;
}

int nanoiAFM::writeDAC(qint8 dacID, double val){
    if(val>AFM_DAC_MAX_VOLTAGE){
        return AFM_FAIL;
    }
    qint16 digitalValue=AFM_DAC_SCALING*val;
#if AFM_DEBUG
    qDebug() << "DAC Digital Value to be written:" << (digitalValue);
#endif
    writeByte(AFM_DAC_WRITE_SELECT);
    writeByte(dacID);
    writeByte((digitalValue & 0xFF));
    writeByte((digitalValue >> 8));

    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_DAC_WRITE_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}
    }
    else {return AFM_FAIL;}
}

float nanoiAFM::readDAC(qint8 dacID){
    quint16 val;
    writeByte(AFM_DAC_READ_SELECT);
    writeByte(dacID);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
#if AFM_DEBUG
    qDebug() << "Bytes Read from DAC: " << res.size();
#endif
    if(!res.isEmpty() || !res.isNull()){
        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));

        if(res.at(2) == AFM_DAC_READ_SELECT){ return ((float)val)/AFM_DAC_SCALING;}
        else{ return AFM_FAIL;}
    }
    else{ return AFM_FAIL;}
}

float nanoiAFM::readADC(qint8 adcID){
    quint16 val;
//    QByteArray responseData;
    writeByte(AFM_ADC_READ_SELECT);
    writeByte(adcID);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
#if AFM_DEBUG
    qDebug() << "ADC Digital Value read" << val;
#endif
        if(res.at(2) == AFM_ADC_READ_SELECT){ return ((float)val)/AFM_ADC_SCALING;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}

}

int nanoiAFM::setRasterStep(){
//    QByteArray responseData;
//    while(waitForReadyRead(AFM_POLL_TIMOUT)){
//        responseData+= readAll();
//    }

//    if(responseData.at(0) == 'f')
//        return AFM_SUCCESS;
//    else
//        return AFM_FAIL;
    return AFM_SUCCESS;
}

int nanoiAFM::memsSetOffset(double val){

    writeDAC(DAC_ZOFFSET_FINE, val);

    return AFM_SUCCESS; //There should be a comparison against a maximum value for offset voltage
}

int nanoiAFM::memsSetFrequency(double val){
    //writeDAC(AFM_DAC_VCO_ID, val);
    return AFM_SUCCESS;
}

int nanoiAFM::memsSetAmplitude(double val){
    writeDAC(DAC_ZAMP, val);
    return AFM_SUCCESS;
}

int nanoiAFM::memsSetBridgeVoltage(double val){
    if(writeDAC(DAC_BR1, val))
        return AFM_SUCCESS;
    else
        return AFM_FAIL;
}

int nanoiAFM::pidEnable(){
    writeByte(AFM_PID_ENABLE_SELECT);
    if(waitForData(AFM_POLL_TIMEOUT).at(0) == AFM_PID_ENABLE_SELECT)
        return AFM_SUCCESS;
    else
        return AFM_FAIL;
}
int nanoiAFM::pidDisable(){
    writeByte(AFM_PID_DISABLE_SELECT);
    return AFM_SUCCESS;
}

int nanoiAFM::pidSetP(float P){
    writeByte(AFM_PID_P_SELECT);
    writeByte(((char*)&P)[0]);
    writeByte(((char*)&P)[1]);
    writeByte(((char*)&P)[2]);
    writeByte(((char*)&P)[3]);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_PID_P_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL; }
    //return AFM_SUCCESS; //There should be a max allowed P value. Return FAIL if P value over the range
}

int nanoiAFM::pidSetI(float I){
    writeByte(AFM_PID_I_SELECT);
    writeByte(((char*)&I)[0]);
    writeByte(((char*)&I)[1]);
    writeByte(((char*)&I)[2]);
    writeByte(((char*)&I)[3]);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_PID_I_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{  return AFM_FAIL;}
    //return AFM_SUCCESS; //There should be a max allowed I value. Return FAIL if I value over the range
}

int nanoiAFM::pidSetD(float D){
    writeByte(AFM_PID_D_SELECT);
    writeByte(((char*)&D)[0]);
    writeByte(((char*)&D)[1]);
    writeByte(((char*)&D)[2]);
    writeByte(((char*)&D)[3]);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_PID_D_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
    //return AFM_SUCCESS; //There should be a max allowed I value. Return FAIL if D value over the range
}

int nanoiAFM::pidSetValues(qint8 P,qint8 I,qint8 D){
    if(pidSetP(P)==AFM_FAIL || pidSetI(I)==AFM_FAIL || pidSetD(D)==AFM_FAIL){
        return AFM_FAIL;
    }
    return AFM_SUCCESS;
}

int nanoiAFM::pidSetPoint(float val){
    writeByte(AFM_PID_SETPOINT_SELECT);
    writeByte(((char*)&val)[0]);
    writeByte(((char*)&val)[1]);
    return AFM_SUCCESS; //Should be checked against a value range
}

int nanoiAFM::stageSetPulseWidth(qint8 val){
    writeByte(AFM_STAGE_PW_SELECT);
    writeByte(val);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_PW_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
    //return AFM_SUCCESS; //Should be checked against a value range
}

int nanoiAFM::stageSetDirForward(){
    writeByte(AFM_STAGE_DIR_FORW_SELECT);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_DIR_FORW_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}

int nanoiAFM::stageSetDirBackward(){
    writeByte(AFM_STAGE_DIR_REVERSE_SELECT);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_DIR_REVERSE_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}

int nanoiAFM::stageSetStep(){
    writeByte(AFM_STAGE_STEP_SELECT);
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_STEP_SELECT){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}

void nanoiAFM::stageSetContinuous(){
    writeByte(AFM_STAGE_CONT_SELECT);
}

int nanoiAFM::stageAbortContinuous(){
    writeByte('q');
    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o'){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}

void nanoiAFM::stageStepForward(){
    stageSetDirForward();
    stageSetStep();
}

void nanoiAFM::stageStepBackward(){
    stageSetDirBackward();
    stageSetStep();
}

void nanoiAFM::stageMoveForward(){
    stageSetDirForward();
    stageSetContinuous();
}

void nanoiAFM::stageMoveBackward(){
    stageSetDirBackward();
    stageSetContinuous();
}

int nanoiAFM::setDDSSettings(quint16 numPoints, quint16 startFrequency, quint16 stepSize) {
    qDebug() << "Writing to DDS settings";
    // Set DDS settings
    writeByte(AFM_DDS_SWEEP_SET);

    qDebug() << "Start Freq -> High Byte: " << (quint16)(startFrequency >> 8) << " Low Byte: " << (quint8)startFrequency;
    // start freq
    writeByte((qint8)startFrequency); // low byte
    writeByte((qint8)(startFrequency>>8)); // high bye

    qDebug() << "Step Size -> High Byte: " << (quint16)(stepSize >> 8) << " Low Byte: " << (quint8)stepSize;
    // step size
    writeByte((qint8)stepSize); // low byte
    writeByte((qint8)(stepSize>>8)); // high bye

    qDebug() << "Num Points -> High Byte: " << (quint16)(numPoints >> 8) << " Low Byte: " << (quint8)numPoints;
    // num points
    writeByte((qint8)numPoints); // low byte
    writeByte((qint8)(numPoints>>8)); // high bye

    QByteArray res = waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'u'){
            return AFM_SUCCESS;
        }
        else{ return AFM_FAIL;}
    }
    else{ return AFM_FAIL;}
}

// If we don't read back numPoints*2, return AFM_FAIL
// Otherwise, the data field is filled with numPoints doubles
int nanoiAFM::frequencySweep(quint16 numPoints, quint16 startFrequency, quint16 stepSize, \
                             QVector<double>& amplitudeData, QVector<double>& phaseData, QVector<double>& frequencyData, int& bytesRead){
    //writeDAC(AFM_DAC_VCO_ID, 0); // write 0V
    setDDSSettings(numPoints, startFrequency, stepSize);

    // start frequency sweep
    writeByte(AFM_SWEEP_START);

    // read numPoints*2 bytes of data back
    QByteArray freqData = waitForData(AFM_LONG_TIMEOUT);
    bytesRead = freqData.size();
    qDebug() << "Bytes Read: " << bytesRead << " Bytes Expected: " << numPoints*2;
    //bytesRead[freqData.cend()];
    if (bytesRead != numPoints*4 + 1) {
        return AFM_FAIL;
    }

    quint16 intVal;
    quint16 phaseVal;
    qDebug() << "Test Bytes to Word: " << BYTES_TO_WORD((quint8)startFrequency, (quint8)(startFrequency >> 8));


    /*for(int i = 0; i < numPoints; i++) {
        intVal = BYTES_TO_WORD((quint8)freqData[i*2], (quint8)freqData[i*2+1]);
        qDebug() << "intVal: " << intVal;
        amplitudeData.append( intVal/AFM_ADC_SCALING );
    }

    for(int i = 0; i < numPoints; i++) {
        frequencyData.append(double(startFrequency + i*stepSize));
    }*/

    // y data
    amplitudeData.clear();
    phaseData.clear();
    for(int i = 0; i < freqData.size() - 1; i+=4) {
        intVal = BYTES_TO_WORD((quint8)freqData[i], (quint8)freqData[i+1]);
        phaseVal = BYTES_TO_WORD((quint8)freqData[i+2],(quint8)freqData[i+3]);
        qDebug() << "Int Val: " << intVal;        
        amplitudeData.append( double(intVal)/AFM_ADC_SCALING );
        phaseData.append(double(phaseVal)/AFM_ADC_SCALING);
    }

    // x-data
    frequencyData.clear();
    for(int i = startFrequency; i < (startFrequency + stepSize*numPoints); i+= stepSize) {
        frequencyData.append(double(i));
    }

    if(freqData.at(freqData.size()-1) == 'r')
        return AFM_SUCCESS;
    else
        return AFM_FAIL;
}

void nanoiAFM::rasterStep(float /*val1*/, float /*val2*/){
 //Not too sure about this function
}

int nanoiAFM::autoApproach(double setpoint){
    writeByte(AFM_AUTOAPPROACH_SELECT);

    qint16 _setpoint = AFM_DAC_SCALING*setpoint;

    writeByte((_setpoint & 0xFF));
    writeByte((_setpoint & 0x0F00) >> 8);

    writeByte((150));
    writeByte(0);

    QByteArray res=waitForData(AFM_LONG_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o'){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}
int nanoiAFM::setDACValues(char dacID, double _val){

    writeByte(AFM_SET_DAC_MAX);
    qint16 _max = AFM_DAC_SCALING*_val;

    writeByte((char)dacID);
    writeByte((_max & 0xFF));
    writeByte((_max & 0x0F00) >> 8);

    QByteArray res=waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_SET_DAC_MAX){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}
int nanoiAFM::deviceCalibration(double val, char side){


    qint16 _max = AFM_DAC_SCALING*val;
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
    writeByte(AFM_DEVICE_CALIBRATE);
    writeByte(side);
    writeByte((_max & 0xFF));
    writeByte((_max & 0x0F00) >> 8);

    //16, 384 bytes
    QByteArray res=waitForData(AFM_LONG_TIMEOUT);
    //int bytes = res.size();
//    while(bytes < 16300){
//        res+=waitForData();
//        bytes = res.size();
//    }

    //12 bytes (a, b, c) – fitted quadratic polynomial coefficients for direct p-v relation (single precision floating point)
    writeByte(_a[0]);
    writeByte(_a[1]);
    writeByte(_a[2]);
    writeByte(_a[3]);
    writeByte(_b[0]);
    writeByte(_b[1]);
    writeByte(_b[2]);
    writeByte(_b[3]);
    writeByte(_c[0]);
    writeByte(_c[1]);
    writeByte(_c[2]);
    writeByte(_c[3]);
    //12 bytes (d, e, f) – fitted quadratic polynomial coefficients for coupling r-v relation (single precision floating point)
    writeByte(_d[0]);
    writeByte(_d[1]);
    writeByte(_d[2]);
    writeByte(_d[3]);
    writeByte(_e[0]);
    writeByte(_e[1]);
    writeByte(_e[2]);
    writeByte(_e[3]);
    writeByte(_f[0]);
    writeByte(_f[1]);
    writeByte(_f[2]);
    writeByte(_f[3]);



    //waitForReadyRead(100);

    res = waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == 'o'){ return AFM_SUCCESS; }
        else{ return AFM_FAIL; }
    }
    else{ return AFM_FAIL; }
}

int nanoiAFM::scanParameters(double vmin_line, double vmin_scan, double vmax, double numpts, double numlines){

    /* We need to check that these parameters are valid
     * How?
     *
     *
     * */
    //qDebug() << AFM_DAC_SCALING << endl;
    qint16 _vminLine = AFM_DAC_SCALING*vmin_line;
    qint16 _vminScan = AFM_DAC_SCALING*vmin_scan;
    qint16 _vmax = AFM_DAC_SCALING*vmax;
    qint16 _numpts = numpts;
    qint16 _numLines = numlines;

    writeByte(AFM_SCAN_PARAMETERS);

    writeByte(_vminLine & 0xFF);
    writeByte((_vminLine & 0x0F00) >> 8);

    writeByte(_vminScan & 0xFF);
    writeByte((_vminScan & 0x0F00) >> 8);

    writeByte(_vmax & 0xFF);
    writeByte((_vmax & 0x0F00) >> 8);

    writeByte(_numpts & 0xFF);
    writeByte((_numpts & 0x0F00) >> 8);

    writeByte(_numLines & 0xFF);
    writeByte((_numLines & 0x0F00) >> 8);



    QByteArray res = waitForData(AFM_LONG_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(1) == '@' && res.at(0) == 'o'){
            return AFM_SUCCESS;
        }
        else{ return AFM_FAIL; }

    }
    else{ return AFM_FAIL; }
}
int nanoiAFM::startScan()
{
    writeByte(AFM_START_SCAN);

    QByteArray res = waitForData(AFM_POLL_TIMEOUT);
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_START_SCAN){
            return AFM_SUCCESS;
        }
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}

int nanoiAFM::scanStep(QVector<double> &z_offset_adc,
                        QVector<double> &z_amp_adc,
                        QVector<double> &z_phase_adc){

    writeByte(AFM_SCAN_STEP);

    //receives: 8 points of 6 bytes each:
    //(z_offset_adc byte 1, z_offset_adc byte 2, z_amp_adc byte 1, z_amp_adc byte 2, z_phase_adc byte 1, z_phase_adc byte 2))
    QByteArray res = waitForData(AFM_POLL_TIMEOUT);


    for(int i = 0; i < res.length() - 1; i++){
        z_offset_adc.append(res.at(i)&res.at(++i));
        z_amp_adc.append(res.at(++i)&res.at(++i));
        z_phase_adc.append(res.at(++i)&res.at(++i));
    }


    if(!res.isEmpty() || !res.isNull()){
        if(res.at(res.length() - 1) == AFM_SCAN_STEP){
            return AFM_SUCCESS;
        }
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}





