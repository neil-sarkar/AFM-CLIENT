#ifndef AFM_H
#define AFM_H
#define AFM_BAUD_RATE 76800

#include <QObject>
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

/*
 * Serial Port Commands
 * Automatically generated by cog via Python
 * "RSPLEN" is Expected response length. The receive_worker switch case
 * uses this information to check length of the response before attempting
 * to access it, to avoid segmentation fault.
 */
/* Automatically Generated Code - Editing is futile!
[[[cog
from CodeValet import CodeValet
c = CodeValet()
c.msg_id_define()
]]]*/
#define AFM_DAC_WRITE_SELECT  0x61
#define AFM_DAC_WRITE_SELECT_RSPLEN    2
#define AFM_DAC_READ_SELECT  0x62
#define AFM_DAC_READ_SELECT_RSPLEN    4
#define AFM_ADC_READ_SELECT  0x63
#define AFM_ADC_READ_SELECT_RSPLEN    4
#define AFM_ADC_READ_SPO  0x65
#define AFM_ADC_READ_SPO_RSPLEN    8
#define AFM_RASTER_STEP_SELECT  0x66
#define AFM_RASTER_STEP_SELECT_RSPLEN    2
#define AFM_PID_ENABLE_SELECT  0x67
#define AFM_PID_ENABLE_SELECT_RSPLEN    2
#define AFM_PID_DISABLE_SELECT  0x68
#define AFM_PID_DISABLE_SELECT_RSPLEN    2
#define AFM_PID_P_SELECT  0x70
#define AFM_PID_P_SELECT_RSPLEN    2
#define AFM_PID_I_SELECT  0x69
#define AFM_PID_I_SELECT_RSPLEN    2
#define AFM_PID_D_SELECT  0x64
#define AFM_PID_D_SELECT_RSPLEN    2
#define AFM_PID_SETPOINT_SELECT  0x73
#define AFM_PID_SETPOINT_SELECT_RSPLEN    2
#define AFM_STAGE_PW_SELECT  0x6A
#define AFM_STAGE_PW_SELECT_RSPLEN    3
#define AFM_STAGE_PULSE_STEP  0x6D
#define AFM_STAGE_PULSE_STEP_RSPLEN    3
#define AFM_DDS_AD9837_SET  0x6E
#define AFM_DDS_AD9837_SET_RSPLEN    2
#define AFM_FREQ_SWEEP_AD9837  0x71
#define AFM_FREQ_SWEEP_AD9837_RSPLEN    6
#define AFM_FREQ_SWEEP_AD5932  0x72
#define AFM_FREQ_SWEEP_AD5932_RSPLEN    6
#define AFM_DDS_SWEEP_SET  0x75
#define AFM_DDS_SWEEP_SET_RSPLEN    2
#define AFM_STAGE_DIR_FWD_SELECT  0x6C
#define AFM_STAGE_DIR_FWD_SELECT_RSPLEN    3
#define AFM_STAGE_DIR_REVERSE_SELECT  0x6B
#define AFM_STAGE_DIR_REVERSE_SELECT_RSPLEN    3
#define AFM_AUTOAPPROACH_SELECT  0x76
#define AFM_AUTOAPPROACH_SELECT_RSPLEN    3
#define AFM_SET_DAC_MAX  0x26
#define AFM_SET_DAC_MAX_RSPLEN    3
#define AFM_DEVICE_CALIBRATE  0x6F
#define AFM_DEVICE_CALIBRATE_RSPLEN    5
#define AFM_SCAN_PARAMETERS  0x40
#define AFM_SCAN_PARAMETERS_RSPLEN    3
#define AFM_START_SCAN  0x23
#define AFM_START_SCAN_RSPLEN    2
#define AFM_SCAN_STEP  0x5E
#define AFM_SCAN_STEP_RSPLEN    49
#define AFM_SET_PGA 0x2A
#define AFM_SET_PGA_RSPLEN    3
//[[[end]]]

// Misc Enums
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

class icspiAFM: public QObject{
    Q_OBJECT

signals:
   bool open(char *serialPortName, qint32 baud_rate);
   void close();

   // Used for afm_worker
   void clearPayloadBuffer();
   int addPayloadByte(char byte);
   int writeByte(char byte);
   int writeMsg(char msg_id);
   QByteArray waitForMsg();
   bool isOpen();

public:
//    icspiAFM(QThread** afm_thread_temp_var):
//        afmThread(afm_thread_temp_var) {}
    int writeMsg(char msg_id, QByteArray payload);
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
