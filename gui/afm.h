#ifndef AFM_H
#define AFM_H
#define BAUD_RATE 76800

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>
#include <QString>
#include <QVector>

/*AFM Configuration*/
#define AFM_DEBUG                            0  // 1: display debug messages
#define AFM_USE_DUNCAN_BOARD                 0  // 1: Duncan's Board, 0: Mahdi's Board
#define AFM_MICRO_CONNECTED                  1  // 1: microcontroller, 0: uC not plugged in

#define DAC_BFRD1           0
#define DAC_BFRD2           1
#define DAC_BR2             2
#define DAC_ZAMP            3
#define DAC_BR1             4
#define DAC_BFRD3           5
#define DAC_ZOFFSET_FINE	6/**/
#define DAC_Y1              7/**/
#define DAC_ZOFFSET_COARSE	8/**/
#define DAC_Y2              9/**/
#define DAC_X1              10/**/
#define DAC_X2              11/**/

#if AFM_USE_DUNCAN_BOARD
// DAC IDs for Duncan's Board
#define AFM_DAC_BRIDGE1_ID                   0
#define AFM_DAC_BRIDGE2_ID                   1
#define AFM_DAC_X1_ID                        2
#define AFM_DAC_X2_ID                        3
#define AFM_DAC_Y1_ID                        4
#define AFM_DAC_Y2_ID                        5
#define AFM_DAC_VCO_ID                       6
#define AFM_DAC_AMPLITUDE_ID                 7
#define AFM_DAC_OFFSET_ID                    8

// ADC IDs for Duncan's Board
#define AFM_ADC_X1_ID                        0
#define AFM_ADC_X2_ID                        1
#define AFM_ADC_Y1_ID                        2
#define AFM_ADC_Y2_ID                        3
#define AFM_ADC_OFFSET_ID                    4
#define AFM_ADC_AMPLTIDE_ID                  5
#else
// DAC IDs for Mahdi's Board
#define AFM_DAC_BRIDGE1_ID                    3
#define AFM_DAC_BRIDGE2_ID                    2
#define AFM_DAC_X1_ID                         10
#define AFM_DAC_X2_ID                         9
#define AFM_DAC_Y1_ID                         8
#define AFM_DAC_Y2_ID                         7
#define AFM_DAC_VCO_ID                        4
#define AFM_DAC_AMPLITUDE_ID                  5
#define AFM_DAC_OFFSET_ID                     6

// ADC IDs for Mahdi's Board
#define AFM_ADC_X1_ID                         4
#define AFM_ADC_X2_ID                         2
#define AFM_ADC_Y1_ID                         1
#define AFM_ADC_Y2_ID                         0
#define AFM_ADC_OFFSET_ID                     5
#define AFM_ADC_AMPLITUDE_ID                  3
#define AFM_ADC_PHASE_ID                      6
#endif


//#define AFM_DAC_OFFSET_ID 8
//#define AFM_DAC_FREQUENCY_ID 6
//#define AFM_DAC_AMPLITUDE_ID 7
#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE 0.4
//#define AFM_DAC_BRIDGE_VOLTAGE_ID 1

#define AFM_DAC_MAX_VOLTAGE 3.3
#define AFM_DAC_DATA_RANGE 4095
#define AFM_DAC_SCALING (AFM_DAC_DATA_RANGE/AFM_DAC_MAX_VOLTAGE)

//#define AFM_ADC_BRIDGE_SIGNAL_ID 5

#define AFM_ADC_MAX_VOLTAGE 2.5
#define AFM_ADC_DATA_RANGE 4095
#define AFM_ADC_SCALING (AFM_ADC_DATA_RANGE/AFM_ADC_MAX_VOLTAGE)

/*Serial Port Commands*/
#define AFM_DAC_WRITE_SELECT 'a'
#define AFM_DAC_READ_SELECT 'b'
#define AFM_ADC_READ_SELECT 'c'
#define AFM_ADC5_DAC8_READ_SELECT 'e'

#define AFM_RASTER_STEP_SELECT 'f'

#define AFM_PID_ENABLE_SELECT 'g'
#define AFM_PID_DISABLE_SELECT 'h'
#define AFM_PID_P_SELECT 'p'
#define AFM_PID_I_SELECT 'i'
#define AFM_PID_D_SELECT 'd'
#define AFM_PID_SETPOINT_SELECT 's'

#define AFM_STAGE_PW_SELECT 'j'
#define AFM_STAGE_STEP_SELECT 'm'
#define AFM_STAGE_CONT_SELECT 'n'
#define AFM_ABORT_AUTO_APPROACH 'q'
#define AFM_STAGE_DIR_FORW_SELECT 'l'
#define AFM_STAGE_DIR_REVERSE_SELECT 'k'

#define AFM_SWEEP_START 'r'

#define AFM_DDS_SWEEP_SET 'u'

#define AFM_AUTOAPPROACH_SELECT 'v'

#define AFM_SET_DAC_MAX '&'

#define AFM_DEVICE_CALIBRATE 'o'

#define AFM_SCAN_PARAMETERS '@'

#define AFM_START_SCAN '#'

#define AFM_SCAN_STEP '^'


enum {
    AFM_SUCCESS = 0,
    AFM_FAIL = -1
};

class nanoiAFM: public QSerialPort{

private:

public:

    int writeByte(char byte);
    QByteArray waitForData(int timeout);
    int writeDAC(qint8 dacID, double val);
    float readDAC(qint8 dacID);
    float readADC(qint8 adcID);
    int setRasterStep();
    int memsSetOffset(double val);
    int memsSetFrequency(double val);
    int memsSetAmplitude(double val);
    int memsSetBridgeVoltage(double val);
    int pidEnable();
    int pidDisable();
    int pidSetP(float P);
    int pidSetI(float I);
    int pidSetD(float D);
    int pidSetValues(qint8 P,qint8 I,qint8 D);
    int pidSetPoint(float val);
    int stageSetPulseWidth(qint8 val);
    void stageSetDirForward();
    void stageSetDirBackward();
    void stageSetStep();
    void stageSetContinuous();
    void stageAbortContinuous();
    void stageStepForward();
    void stageStepBackward();
    void stageMoveForward();
    void stageMoveBackward();
    void setDDSSettings(quint16 numPoints, quint16 startFrequency, quint16 stepSize);
    int frequencySweep(quint16 numPoints, quint16 startFrequency, quint16 stepSize, QVector<double>& amplitude, QVector<double>& frequency, int& bytesRead);
    void rasterStep(float val1, float val2);
    void autoApproach();
    int setDACValues(char dacID, double _val);
    int deviceCalibration(double val, char side);
    int scanParameters(double vmin_line, double vmin_scan, double vmax, double numpts, double numlines);
    int startScan();
    int scanStep(QVector<char>& z_offset_adc, QVector<char>& z_amp_adc, QVector<char>& z_phase_adc);
};

#endif // AFM_H
