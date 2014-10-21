#include "afm.h"
#include <QMessageBox>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI
#define AFM_MAX_DATA_SIZE 1 //Basically write 1 character at a time
#define AFM_POLL_TIMOUT 50 //Poll the buffer every 1ms

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

QByteArray nanoiAFM::waitForData()
{
    QByteArray responseData;
    while(waitForReadyRead(AFM_POLL_TIMOUT)){
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

    QByteArray res=waitForData();
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
    QByteArray res=waitForData();
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
    QByteArray res=waitForData();
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

    writeDAC(AFM_DAC_OFFSET_ID, val);

    return AFM_SUCCESS; //There should be a comparison against a maximum value for offset voltage
}

int nanoiAFM::memsSetFrequency(double val){
    writeDAC(AFM_DAC_VCO_ID, val);
    return AFM_SUCCESS;
}

int nanoiAFM::memsSetAmplitude(double val){
    writeDAC(AFM_DAC_AMPLITUDE_ID, val);
    return AFM_SUCCESS;
}

int nanoiAFM::memsSetBridgeVoltage(double val){
    writeDAC(AFM_DAC_BRIDGE1_ID, val);
    return AFM_SUCCESS;
}

int nanoiAFM::pidEnable(){
    writeByte(AFM_PID_ENABLE_SELECT);
    if(waitForData().at(0) == AFM_PID_ENABLE_SELECT)
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
    QByteArray res=waitForData();
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
    QByteArray res=waitForData();
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
    QByteArray res=waitForData();
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
    return AFM_SUCCESS; //Should be checked against a value range
}

void nanoiAFM::stageSetDirForward(){
    writeByte(AFM_STAGE_DIR_FORW_SELECT);
}

void nanoiAFM::stageSetDirBackward(){
    writeByte(AFM_STAGE_DIR_REVERSE_SELECT);
}

void nanoiAFM::stageSetStep(){
    writeByte(AFM_STAGE_STEP_SELECT);
}

void nanoiAFM::stageSetContinuous(){
    writeByte(AFM_STAGE_CONT_SELECT);
}

void nanoiAFM::stageAbortContinuous(){
    writeByte('q');
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

void nanoiAFM::setDDSSettings(quint16 numPoints, quint16 startFrequency, quint16 stepSize) {
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
}

// If we don't read back numPoints*2, return AFM_FAIL
// Otherwise, the data field is filled with numPoints doubles
int nanoiAFM::frequencySweep(quint16 numPoints, quint16 startFrequency, quint16 stepSize, \
                             QVector<double>& amplitudeData, QVector<double>& frequencyData, int& bytesRead){
    //writeDAC(AFM_DAC_VCO_ID, 0); // write 0V
    setDDSSettings(numPoints, startFrequency, stepSize);
    // start frequency sweep
    writeByte(AFM_SWEEP_START);

    // read numPoints*2 bytes of data back
    QByteArray freqData = waitForData();
    bytesRead = freqData.size();
    qDebug() << "Bytes Read: " << bytesRead << " Bytes Expected: " << numPoints*2;
    bytesRead[freqData.cend()];
    if (bytesRead != numPoints*4 + 2) {
        return AFM_FAIL;
    }

    quint16 intVal;
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
    for(int i = 0; i < freqData.size(); i+=2) {
        qDebug() << "Int Val: " << intVal;
        intVal = BYTES_TO_WORD((quint8)freqData[i], (quint8)freqData[i+1]);
        amplitudeData.append( double(intVal)/AFM_ADC_SCALING );
    }

    // x-data
    frequencyData.clear();
    for(int i = startFrequency; i < (startFrequency + stepSize*numPoints); i+= stepSize) {
        frequencyData.append(double(i));
    }

    return AFM_SUCCESS;
}

void nanoiAFM::rasterStep(float /*val1*/, float /*val2*/){
 //Not too sure about this function
}

void nanoiAFM::autoApproach(){
    writeByte(AFM_AUTOAPPROACH_SELECT);
}
int nanoiAFM::setDACValues(char dacID, double _val){

    writeByte(AFM_SET_DAC_MAX);
    char _max = AFM_DAC_SCALING*_val;

    writeByte((char)dacID);
    writeByte((_max & 0xFF));
    writeByte((_max & 0x0F00) >> 8);

    QByteArray res=waitForData();
    if(!res.isEmpty() || !res.isNull()){
        if(res.at(0) == AFM_SET_DAC_MAX){ return AFM_SUCCESS;}
        else{ return AFM_FAIL;}

    }
    else{ return AFM_FAIL;}
}





