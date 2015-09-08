#include "afm.h"
#include <QMessageBox>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI
#define AFM_MAX_DATA_SIZE 1 //Basically write 1 character at a time
#define AFM_POLL_TIMEOUT 50 //Poll the buffer every 1ms
#define AFM_LONG_TIMEOUT 5000 //Longer timeout for large data

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

int icspiAFM::writeByte(char byte)
{
    //Change it to write sequentially.
    writeData(&byte, AFM_MAX_DATA_SIZE);
    waitForBytesWritten(1);

//    if(waitForData().at(0) == byte)
        return AFM_SUCCESS;
//    else
//        return AFM_FAIL;
}

QByteArray icspiAFM::waitForData(int timeout)
{
    QByteArray responseData;
    //TODO Use event loop and readyRead() since this is not realiable on Windows
    //See http://doc.qt.io/qt-5/qabstractsocket.html#waitForReadyRead
    while(waitForReadyRead(timeout)){
        responseData += readAll();
    }
#if AFM_DEBUG
    qDebug() << "Response Data Size:" << responseData.size();
#endif
    return responseData;
}

void icspiAFM::writeDAC(qint8 dacID, double val){
//    if(val>AFM_DAC_MAX_VOLTAGE){
//        return AFM_FAIL;
//    }
    qint16 digitalValue=AFM_DAC_SCALING*val;
#if AFM_DEBUG
    qDebug() << "DAC Digital Value to be written:" << (digitalValue);
#endif
    writeByte(AFM_DAC_WRITE_SELECT);
    writeByte(dacID);
    writeByte((digitalValue & 0xFF));
    writeByte((digitalValue >> 8));
}

void icspiAFM::readDAC(qint8 dacID){
    writeByte(AFM_DAC_READ_SELECT);
    writeByte(dacID);
#if AFM_DEBUG
    qDebug() << "Bytes Read from DAC: " << res.size();
#endif
}

void icspiAFM::readADC(qint8 adcID){
    writeByte(AFM_ADC_READ_SELECT);
    writeByte(adcID);
#if AFM_DEBUG
    qDebug() << "ADC Digital Value read" << val;
#endif


}

void icspiAFM::setRasterStep(){
//    writeByte(AFM_RASTER_STEP_SELECT);
//    writeByte();
//    writeByte();
//    writeByte();
//    writeByte();
}

void icspiAFM::memsSetOffset(double val){
    setPGA(PGA_Z_OFFSET,val);
    //There should be a comparison against a maximum value for offset voltage
}

void icspiAFM::memsSetFrequency(double val){
    setPGA(PGA_Z_OFFSET, val);
    //return AFM_SUCCESS;
}

void icspiAFM::memsSetAmplitude(double val){
    //writeDAC(DAC_ZAMP, val);
    setPGA(PGA_AMPLITUDE,val);
    //return AFM_SUCCESS;
}

void icspiAFM::memsSetBridgeVoltage(double val){
    writeDAC(DAC_BR1, val);

}

void icspiAFM::pidEnable(){
    writeByte(AFM_PID_ENABLE_SELECT);
}
void icspiAFM::pidDisable(){
    writeByte(AFM_PID_DISABLE_SELECT);
    //return AFM_SUCCESS;
}

void icspiAFM::pidSetP(float P){
    writeByte(AFM_PID_P_SELECT);
    writeByte(((char*)&P)[0]);
    writeByte(((char*)&P)[1]);
    writeByte(((char*)&P)[2]);
    writeByte(((char*)&P)[3]);
    //There should be a max allowed P value. Return FAIL if P value over the range
}

void icspiAFM::pidSetI(float I){
    writeByte(AFM_PID_I_SELECT);
    writeByte(((char*)&I)[0]);
    writeByte(((char*)&I)[1]);
    writeByte(((char*)&I)[2]);
    writeByte(((char*)&I)[3]);
    //There should be a max allowed I value. Return FAIL if I value over the range
}

void icspiAFM::pidSetD(float D){
    writeByte(AFM_PID_D_SELECT);
    writeByte(((char*)&D)[0]);
    writeByte(((char*)&D)[1]);
    writeByte(((char*)&D)[2]);
    writeByte(((char*)&D)[3]);
    //There should be a max allowed I value. Return FAIL if D value over the range
}

void icspiAFM::pidSetValues(qint8 P,qint8 I,qint8 D){
    pidSetP(P);
    pidSetI(I);
    pidSetD(D);
}

void icspiAFM::pidSetPoint(float val){
    writeByte(AFM_PID_SETPOINT_SELECT);

    writeByte(((char*)&val)[0]);
    writeByte(((char*)&val)[1]);
    //return AFM_SUCCESS; //Should be checked against a value range
}

void icspiAFM::stageSetPulseWidth(qint8 val){
    //Val should be checked against a value range
    writeByte(AFM_STAGE_PW_SELECT);
    writeByte(val);
}

void icspiAFM::stageSetDirForward(){
    writeByte(AFM_STAGE_DIR_FORW_SELECT);
}

void icspiAFM::stageSetDirBackward(){
    writeByte(AFM_STAGE_DIR_REVERSE_SELECT);
}

void icspiAFM::stageSetStep(){
    writeByte(AFM_STAGE_STEP_SELECT);
}

void icspiAFM::stageSetContinuous(){
    writeByte(AFM_STAGE_CONT_SELECT);
}

void icspiAFM::stageAbortContinuous(){
    writeByte(AFM_ABORT_AUTO_APPROACH);
}

void icspiAFM::stageStepForward(){
    stageSetDirForward();
    stageSetStep();
}

void icspiAFM::stageStepBackward(){
    stageSetDirBackward();
    stageSetStep();
}

void icspiAFM::stageMoveForward(){
    stageSetDirForward();
    stageSetContinuous();
}

void icspiAFM::stageMoveBackward(){
    stageSetDirBackward();
    stageSetContinuous();
}

void icspiAFM::setDDSSettings(quint16 numPoints,
                             quint16 startFrequency,
                             quint16 stepSize) {

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

// Start the frequency sweep. The data will be fetched from the receiver
void icspiAFM::frequencySweep(quint16 numPoints,
                             quint16 startFrequency,
                             quint16 stepSize){

    //writeDAC(AFM_DAC_VCO_ID, 0); // write 0V
    setDDSSettings(numPoints, startFrequency, stepSize);

    // start frequency sweep
    writeByte(AFM_SWEEP_START);

}

void icspiAFM::rasterStep(float /*val1*/, float /*val2*/){
 //Not too sure about this function
}

void icspiAFM::autoApproach(double setpoint){
    writeByte(AFM_AUTOAPPROACH_SELECT);

    qint16 _setpoint = AFM_DAC_SCALING*setpoint;

    writeByte((_setpoint & 0xFF));
    writeByte((_setpoint & 0x0F00) >> 8);

    writeByte((150));
    writeByte(0);

}
void icspiAFM::setDACValues(char dacID, double _val){

    writeByte(AFM_SET_DAC_MAX);
    qint16 _max = AFM_DAC_SCALING*_val;

    writeByte((char)dacID);
    writeByte((_max & 0xFF));
    writeByte((_max & 0x0F00) >> 8);

}
void icspiAFM::deviceCalibration(double val, char side){


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

}

void icspiAFM::scanParameters(double vmin_line,
                             double vmin_scan,
                             double vmax,
                             double numpts,
                             double numlines){

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

}
void icspiAFM::startScan()
{
    writeByte(AFM_START_SCAN);

}

void icspiAFM::scanStep(){

    writeByte(AFM_SCAN_STEP);

}

void icspiAFM::setPGA(char channel, double val){
    writeByte(AFM_SET_PGA);
    writeByte(channel);
    //writeByte(val);
    if(channel == PGA_AMPLITUDE || channel == PGA_Z_OFFSET){
        qint8 newval = abs(20 * log10(val/100));
        writeByte(newval);
    }
    else{
        qint8 newval = (((20 * log10(val/100)) - 31.5)/0.5) + 255;
        writeByte(newval);
    }
}

void icspiAFM::readSignalPhaseOffset(){
    writeByte(AFM_ADC_READ_SPO);
}

void icspiAFM::forceCurve(){
    writeByte('N');
}

