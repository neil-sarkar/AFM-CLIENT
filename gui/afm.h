#ifndef AFM_H
#define AFM_H
#define AFM_BAUD_RATE 76800

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QSerialPort> //For QT5
#include <QSerialPortInfo>
#include <QString>
//#include <QVector>
#include <math.h>

/*AFM Configuration*/
#define AFM_DEBUG                            1  // 1: display debug messages
//#define AFM_USE_DUNCAN_BOARD                 0  // 1: Duncan's Board, 0: Mahdi's Board
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

#define ADC_X1              4
#define ADC_X2              2
#define ADC_Y1              1
#define ADC_Y2              0
#define ADC_ZOFFSET         5
#define ADC_PHASE           6
//#if AFM_USE_DUNCAN_BOARD
//// DAC IDs for Duncan's Board
//#define AFM_DAC_BRIDGE1_ID                   0
//#define AFM_DAC_BRIDGE2_ID                   1
//#define AFM_DAC_X1_ID                        2
//#define AFM_DAC_X2_ID                        3
//#define AFM_DAC_Y1_ID                        4
//#define AFM_DAC_Y2_ID                        5
//#define AFM_DAC_VCO_ID                       6
//#define AFM_DAC_AMPLITUDE_ID                 7
//#define AFM_DAC_OFFSET_ID                    8

//// ADC IDs for Duncan's Board
//#define AFM_ADC_X1_ID                        0
//#define AFM_ADC_X2_ID                        1
//#define AFM_ADC_Y1_ID                        2
//#define AFM_ADC_Y2_ID                        3
//#define AFM_ADC_OFFSET_ID                    4
//#define AFM_ADC_AMPLTIDE_ID                  5
//#endif
//#if AFM_USE_MAHDI_BOARD
//// DAC IDs for Mahdi's Board
//#define AFM_DAC_BRIDGE1_ID                    3
//#define AFM_DAC_BRIDGE2_ID                    2
//#define AFM_DAC_X1_ID                         10
//#define AFM_DAC_X2_ID                         9
//#define AFM_DAC_Y1_ID                         8
//#define AFM_DAC_Y2_ID                         7
//#define AFM_DAC_VCO_ID                        4
//#define AFM_DAC_AMPLITUDE_ID                  5
//#define AFM_DAC_OFFSET_ID                     6

//// ADC IDs for Mahdi's Board
//#define AFM_ADC_X1_ID                         4
//#define AFM_ADC_X2_ID                         2
//#define AFM_ADC_Y1_ID                         1
//#define AFM_ADC_Y2_ID                         0
//#define AFM_ADC_OFFSET_ID                     5
//#define AFM_ADC_AMPLITUDE_ID                  3
//#define AFM_ADC_PHASE_ID                      6
//#endif


//#define AFM_DAC_OFFSET_ID 8
//#define AFM_DAC_FREQUENCY_ID 6
//#define AFM_DAC_AMPLITUDE_ID 7
#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE 0.4
//#define AFM_DAC_BRIDGE_VOLTAGE_ID 1

#define AFM_DAC_MAX_VOLTAGE 3.3
#define AFM_DAC_DATA_RANGE 4095
#define AFM_DAC_SCALING (double)(AFM_DAC_DATA_RANGE/AFM_DAC_MAX_VOLTAGE)

//#define AFM_ADC_BRIDGE_SIGNAL_ID 5

#define AFM_ADC_MAX_VOLTAGE 2.5
#define AFM_ADC_DATA_RANGE 4095
#define AFM_ADC_SCALING (double)(AFM_ADC_DATA_RANGE/AFM_ADC_MAX_VOLTAGE)

/*Serial Port Commands*/
#define AFM_DAC_WRITE_SELECT 'a'
#define AFM_DAC_READ_SELECT 'b'
#define AFM_ADC_READ_SELECT 'c'
#define AFM_ADC_READ_SPO 'e'

#define AFM_RASTER_STEP_SELECT 'f'

#define AFM_PID_ENABLE_SELECT 'g'
#define AFM_PID_DISABLE_SELECT 'h'
#define AFM_PID_P_SELECT 'p'
#define AFM_PID_I_SELECT 'i'
#define AFM_PID_D_SELECT 'd'
#define AFM_PID_SETPOINT_SELECT 's'

#define AFM_STAGE_PW_SELECT 'j'
#define AFM_STAGE_PULSE_STEP 'm'
#define AFM_STAGE_DIR_FWD_SELECT 'l'
#define AFM_STAGE_DIR_REVERSE_SELECT 'k'

#define AFM_ABORT 'q'
#define AFM_DDS_AD9837_SET 'n'
#define AFM_FREQ_SWEEP_AD9837 'q'
#define AFM_FREQ_SWEEP_AD5932 'r'
#define AFM_DDS_SWEEP_SET 'u'

#define AFM_AUTOAPPROACH_SELECT 'v'

#define AFM_SET_DAC_MAX '&'

#define AFM_DEVICE_CALIBRATE 'o'

#define AFM_SCAN_PARAMETERS '@'

#define AFM_START_SCAN '#'

#define AFM_SCAN_STEP '^'

#define AFM_SET_PGA '*'
#define PGA_Z_OFFSET 'z'
#define PGA_AMPLITUDE 'a'

/*
 *  Serial Communication Specifics
 */

//Maximum size allowed for a message before it is discarded. For protection against bad serial connection.
#define SERIAL_MSG_MAX_SIZE 50000
#define SERIAL_MSG_NEWLINE 0x0A
#define SERIAL_MSG_ESCAPE 0x10
#define SERIAL_MSG_MASK 0x80


#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))
enum {
    AFM_SUCCESS = 0,
    AFM_FAIL = -1
};

class icspiAFM: public QSerialPort{


private:
    unsigned __int8 message_tag = 1;
    QByteArray payload_out_buffer, serial_incoming_buffer;

public:

    /*
     * All the functions that will write to the MCU
     * They are all void because the receiver thread handles the return
     */
    void clearPayloadBuffer();
    int addPayloadByte(char byte);
    int writeByte(char byte);
    int writeMsg(char msg_id);
    int writeMsg(char msg_id, QByteArray payload);

    QByteArray waitForData(int timeout);
    QByteArray waitForMsg(int timeout);

    void writeDAC(qint8 dacID,
                 double val);

    void readDAC(qint8 dacID);
    void readADC(qint8 adcID);
    void setPGA(char channel, double val);
    void setRasterStep();

    void memsSetOffset(double val);
    void memsSetFrequency(double val);
    void memsSetAmplitude(double val);
    void memsSetBridgeVoltage(double val);

    void pidEnable();
    void pidDisable();

    void pidSetP(float P);
    void pidSetI(float I);
    void pidSetD(float D);

    void pidSetValues(qint8 P,
                     qint8 I,
                     qint8 D);

    void pidSetPoint(float val);

    void stageSetPulseWidth(qint8 val);

    void stageSetDirForward();
    void stageSetDirBackward();
    void stageSetStep();
    void stageSetContinuous();
    void stageAbortContinuous();
    void stageStepForward();
    void stageStepBackward();
    void stageMoveForward();
    void stageMoveBackward();

    void setDDSSettings(quint16 numPoints,
                       quint16 startFrequency,
                       quint16 stepSize);

    void frequencySweep(quint16 numPoints,
                       quint16 startFrequency,
                       quint16 stepSize);

    void rasterStep(float val1,
                    float val2);

    void autoApproach(double setpoint);

    void setDACValues(char dacID,
                     double _val);

    void deviceCalibration(double val,
                          char side);

    void scanParameters(double vmin_line,
                       double vmin_scan,
                       double vmax,
                       double numpts,
                       double numlines);
    void startScan();

    void scanStep();

    void readSignalPhaseOffset();

    void forceCurve();
};

#endif // AFM_H
