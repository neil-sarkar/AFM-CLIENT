#include "afm.h"
#include <QMessageBox>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))



void icspiAFM::writeDAC(qint8 dacID, double val)
{
//    if(val>AFM_DAC_MAX_VOLTAGE){
//        return AFM_FAIL;
//    }
    qint16 digitalValue = AFM_DAC_SCALING * val;

#if AFM_DEBUG
    qDebug() << "DAC Digital Value to be written:" << (digitalValue);
#endif

    emit addPayloadByte(dacID);
    emit addPayloadByte((digitalValue & 0xFF));
    emit addPayloadByte((digitalValue >> 8));

    emit writeMsg(AFM_DAC_WRITE_SELECT);

     //qDebug() << "afmThread.isRunning: " << *afmThread->isRunning();
}

void icspiAFM::readDAC(qint8 dacID)
{
    emit addPayloadByte(dacID);
    emit writeMsg(AFM_DAC_READ_SELECT);
//#if AFM_DEBUG
//    qDebug() << "Bytes Read from DAC: " << res.size();
//#endif
}

void icspiAFM::readADC(qint8 adcID)
{
    emit addPayloadByte(adcID);
    emit writeMsg(AFM_ADC_READ_SELECT);
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
    emit addPayloadByte(AFM_PID_ENABLE_SELECT);
}

void icspiAFM::pidDisable()
{
    emit addPayloadByte(AFM_PID_DISABLE_SELECT);
    //return AFM_SUCCESS;
}

void icspiAFM::pidSetP(float P)
{
    emit addPayloadByte(((char *)&P)[0]);
    emit addPayloadByte(((char *)&P)[1]);
    emit addPayloadByte(((char *)&P)[2]);
    emit addPayloadByte(((char *)&P)[3]);
    //There should be a max allowed P value. Return FAIL if P value over the range
    emit writeMsg(AFM_PID_P_SELECT);
}

void icspiAFM::pidSetI(float I)
{
    emit addPayloadByte(((char *)&I)[0]);
    emit addPayloadByte(((char *)&I)[1]);
    emit addPayloadByte(((char *)&I)[2]);
    emit addPayloadByte(((char *)&I)[3]);
    //There should be a max allowed I value. Return FAIL if I value over the range
    emit writeMsg(AFM_PID_I_SELECT);
}

void icspiAFM::pidSetD(float D)
{
    emit addPayloadByte(((char *)&D)[0]);
    emit addPayloadByte(((char *)&D)[1]);
    emit addPayloadByte(((char *)&D)[2]);
    emit addPayloadByte(((char *)&D)[3]);
    //There should be a max allowed I value. Return FAIL if D value over the range
    emit writeMsg(AFM_PID_D_SELECT);
}

void icspiAFM::pidSetValues(qint8 P, qint8 I, qint8 D)
{
    pidSetP(P);
    pidSetI(I);
    pidSetD(D);
}

void icspiAFM::pidSetPoint(float val)
{
    emit addPayloadByte(((char *)&val)[0]);
    emit addPayloadByte(((char *)&val)[1]);
    //return AFM_SUCCESS; //Should be checked against a value range
    emit writeMsg(AFM_PID_SETPOINT_SELECT);
}

void icspiAFM::stageSetPulseWidth(qint8 val)
{
    //Val should be checked against a value range
    emit addPayloadByte(val);
    emit writeMsg(AFM_STAGE_PW_SELECT);
}

void icspiAFM::stageSetDirForward()
{
    emit writeMsg(AFM_STAGE_DIR_FWD_SELECT);
}

void icspiAFM::stageSetDirBackward()
{
    emit writeMsg(AFM_STAGE_DIR_REVERSE_SELECT);
}

void icspiAFM::stageSetStep()
{
    emit writeMsg(AFM_STAGE_PULSE_STEP);
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
    emit addPayloadByte((qint8)startFrequency);                     // low byte
    emit addPayloadByte((qint8)(startFrequency >> 8));              // high bye

    qDebug() << "Step Size -> High Byte: " << (quint16)(stepSize >> 8) << " Low Byte: " << (quint8)stepSize;
    // step size
    emit addPayloadByte((qint8)stepSize);                   // low byte
    emit addPayloadByte((qint8)(stepSize >> 8));            // high bye

    qDebug() << "Num Points -> High Byte: " << (quint16)(numPoints >> 8) << " Low Byte: " << (quint8)numPoints;
    // num points
    emit addPayloadByte((qint8)numPoints);                  // low byte
    emit addPayloadByte((qint8)(numPoints >> 8));           // high bye

    emit writeMsg(AFM_DDS_SWEEP_SET);
}

// Start the frequency sweep. The data will be fetched from the receiver
void icspiAFM::frequencySweep(quint16	numPoints,
                  quint16	startFrequency,
                  quint16	stepSize)
{
    //writeDAC(AFM_DAC_VCO_ID, 0); // write 0V
    setDDSSettings(numPoints, startFrequency, stepSize);

    // start frequency sweep ASSUMING REV 2 BOARD!!!
    emit clearPayloadBuffer();
    emit writeMsg(AFM_FREQ_SWEEP_AD5932);
}

void icspiAFM::rasterStep(float /*val1*/, float /*val2*/)
{
    //Not too sure about this function
}

void icspiAFM::autoApproach(double setpoint)
{
    qint16 _setpoint = AFM_DAC_SCALING * setpoint;

    emit addPayloadByte((_setpoint & 0xFF));
    emit addPayloadByte((_setpoint & 0x0F00) >> 8);

    emit addPayloadByte((150));
    emit addPayloadByte(0);

    emit writeMsg(AFM_AUTOAPPROACH_SELECT);
}

void icspiAFM::setDACValues(char dacID, double _val)
{
    clearPayloadBuffer();

    qint16 _max = AFM_DAC_SCALING * _val;

    emit addPayloadByte((char)dacID);
    emit addPayloadByte((_max & 0xFF));
    emit addPayloadByte((_max & 0x0F00) >> 8);

    emit writeMsg(AFM_SET_DAC_MAX);
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

    emit addPayloadByte(side);
    emit addPayloadByte((_max & 0xFF));
    emit addPayloadByte((_max & 0x0F00) >> 8);

    //12 bytes (a, b, c) – fitted quadratic polynomial coefficients for direct p-v relation (single precision floating point)
    emit addPayloadByte(_a[0]);
    emit addPayloadByte(_a[1]);
    emit addPayloadByte(_a[2]);
    emit addPayloadByte(_a[3]);
    emit addPayloadByte(_b[0]);
    emit addPayloadByte(_b[1]);
    emit addPayloadByte(_b[2]);
    emit addPayloadByte(_b[3]);
    emit addPayloadByte(_c[0]);
    emit addPayloadByte(_c[1]);
    emit addPayloadByte(_c[2]);
    emit addPayloadByte(_c[3]);

    //12 bytes (d, e, f) – fitted quadratic polynomial coefficients for coupling r-v relation (single precision floating point)
    emit addPayloadByte(_d[0]);
    emit addPayloadByte(_d[1]);
    emit addPayloadByte(_d[2]);
    emit addPayloadByte(_d[3]);
    emit addPayloadByte(_e[0]);
    emit addPayloadByte(_e[1]);
    emit addPayloadByte(_e[2]);
    emit addPayloadByte(_e[3]);
    emit addPayloadByte(_f[0]);
    emit addPayloadByte(_f[1]);
    emit addPayloadByte(_f[2]);
    emit addPayloadByte(_f[3]);

    emit writeMsg(AFM_DEVICE_CALIBRATE);
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



    emit addPayloadByte(_vminLine & 0xFF);
    emit addPayloadByte((_vminLine & 0x0F00) >> 8);

    emit addPayloadByte(_vminScan & 0xFF);
    emit addPayloadByte((_vminScan & 0x0F00) >> 8);

    emit addPayloadByte(_vmax & 0xFF);
    emit addPayloadByte((_vmax & 0x0F00) >> 8);

    emit addPayloadByte(_numpts & 0xFF);
    emit addPayloadByte((_numpts & 0x0F00) >> 8);

    emit addPayloadByte(_numLines & 0xFF);
    emit addPayloadByte((_numLines & 0x0F00) >> 8);

    emit writeMsg(AFM_SCAN_PARAMETERS); //TODO FIX ME
}
void icspiAFM::startScan()
{
    emit writeMsg(AFM_START_SCAN);
}

void icspiAFM::scanStep()
{
    emit writeMsg(AFM_SCAN_STEP);
}

void icspiAFM::setPGA(char channel, double val)
{
    clearPayloadBuffer();
    emit addPayloadByte(channel);

    if (channel == PGA_AMPLITUDE || channel == PGA_Z_OFFSET) {
        qint8 newval = abs(20 * log10(val / 100));
        emit addPayloadByte(newval);
    } else {
        qint8 newval = (((20 * log10(val / 100)) - 31.5) / 0.5) + 255;
        emit addPayloadByte(newval);
    }

    emit writeMsg(AFM_SET_PGA);
}

void icspiAFM::readSignalPhaseOffset()
{
    emit writeMsg(AFM_ADC_READ_SPO);
}

void icspiAFM::forceCurve()
{
    emit writeMsg('N');
}
