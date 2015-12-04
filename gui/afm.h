#ifndef AFM_H
#define AFM_H
#define AFM_BAUD_RATE 76800

#include <QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QSerialPort> //For QT5
#include <QSerialPortInfo>
#include <QString>
#include <QVector>
#include <math.h>
#include <QTimer>
#include <QtCore/qmath.h>
#include <vector>
#include <cmath>
#include <icspi_products.h>

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
#define ADC_Z_PZR_AMP       5
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
//#define AFM_DAC_BRIDGE_VOLTAGE_ID 1

//#define AFM_ADC_BRIDGE_SIGNAL_ID 5



/*
 * === COMMON ENUM BLOCK ===
 * Serial Messaging Protocol Constants
 * Serial Port Commands
 * Automatically generated by cog via Python
 * "RSPLEN" is Expected response length. The receive_worker switch case
 * uses this information to check length of the response before attempting
 * to access it, to avoid segmentation fault.
 */
/* Automatically Code Generation BEGIN
[[[cog
from CodeValet import CodeValet
c = CodeValet()
c.afm_h_define()
]]]*/
/* Automatically Generated Code - Editing is futile! */
#define AFM_DAC_WRITE_SELECT  0x61
#define AFM_DAC_WRITE_SELECT_RSPLEN    2
#define AFM_DAC_READ_SELECT  0x62
#define AFM_DAC_READ_SELECT_RSPLEN    5
#define AFM_ADC_READ_SELECT  0x63
#define AFM_ADC_READ_SELECT_RSPLEN    4
#define AFM_READ_SPO  0x65
#define AFM_READ_SPO_RSPLEN    8
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
#define AFM_DDS_AD5932_SET  0x75
#define AFM_DDS_AD5932_SET_RSPLEN    2
#define AFM_PCBMOT_STAGE_DIR_FWD_SELECT  0x6C
#define AFM_PCBMOT_STAGE_DIR_FWD_SELECT_RSPLEN    3
#define AFM_PCBMOT_STAGE_DIR_REVERSE_SELECT  0x6B
#define AFM_PCBMOT_STAGE_DIR_REVERSE_SELECT_RSPLEN    3
#define AFM_AUTOAPPROACH_SELECT  0x76
#define AFM_AUTOAPPROACH_SELECT_RSPLEN    3
#define AFM_SET_DAC_MAX  0x26
#define AFM_SET_DAC_MAX_RSPLEN    4
#define AFM_DEVICE_CALIBRATE  0x6F
#define AFM_DEVICE_CALIBRATE_RSPLEN    5
#define AFM_SCAN_PARAMETERS  0x40
#define AFM_SCAN_PARAMETERS_RSPLEN    3
#define AFM_START_SCAN  0x23
#define AFM_START_SCAN_RSPLEN    2
#define AFM_SCAN_STEP  0x5E
#define AFM_SCAN_STEP_RSPLEN    2
#define AFM_SET_DACTABLE  0x53
#define AFM_SET_DACTABLE_RSPLEN    3
#define AFM_SET_PGA  0x2A
#define AFM_SET_PGA_RSPLEN    3
#define AFM_SET_PGA_PCB3  0x54
#define AFM_SET_PGA_PCB3_RSPLEN    2
#define AFM_SET_SIGGEN  0x50
#define AFM_SET_SIGGEN_RSPLEN    2
#define AFM_START_SCAN_4ACT  0x51
#define AFM_START_SCAN_4ACT_RSPLEN    2
#define AFM_SCAN_STEP_4ACT  0x52
#define AFM_SCAN_STEP_4ACT_RSPLEN    2
#define AFM_FORCE_CURVE  0x4E
#define AFM_FORCE_CURVE_RSPLEN    
#define AFM_CMD_NOTFOUND  0xF1
#define AFM_CMD_NOTFOUND_RSPLEN    0
#define AFM_STEPMOT_WAKE  0x35
#define AFM_STEPMOT_WAKE_RSPLEN    2
#define AFM_STEPMOT_SLEEP  0x34
#define AFM_STEPMOT_SLEEP_RSPLEN    2
#define AFM_STEPMOT_SPEED  0x32
#define AFM_STEPMOT_SPEED_RSPLEN    2
#define AFM_STEPMOT_DIR  0x36
#define AFM_STEPMOT_DIR_RSPLEN    2
#define AFM_STEPMOT_CONT_GO  0x33
#define AFM_STEPMOT_CONT_GO_RSPLEN    2
#define AFM_STEPMOT_CONT_STOP  0x37
#define AFM_STEPMOT_CONT_STOP_RSPLEN    2
#define AFM_STEPMOT_MICROSTEP  0x30
#define AFM_STEPMOT_MICROSTEP_RSPLEN    2
#define AFM_STEPMOT_SINGLESTEP  0x31
#define AFM_STEPMOT_SINGLESTEP_RSPLEN    2
#define AFM_AUTOAPPR_BEGIN  0x9a
#define AFM_AUTOAPPR_BEGIN_RSPLEN    0
#define AFM_AUTOAPPR_STOP  0x9b
#define AFM_AUTOAPPR_STOP_RSPLEN    2
#define AFM_AUTOAPPR_STATUS  0x9c
#define AFM_AUTOAPPR_STATUS_RSPLEN    5
#define SERIAL_MSG_NEWLINE  0x0A
#define SERIAL_MSG_ESCAPE  0x10
#define SERIAL_MSG_MASK  0x80
#define SERIAL_MSG_SPECIAL_TAG  0xF2
#define PGA_X1  1
#define PGA_X2  2
#define PGA_Y1  3
#define PGA_Y2  4
#define PGA_ZFINE  5
#define PGA_DDS_AMPLITUDE  6
#define PGA_ZCOARSE  7
#define PGA_LEVELING  8
#define RATIO_7_1  8
#define RATIO_3_1  4
#define RATIO_1_1  2
#define RATIO_0_1  1
#define AFM_ADC_MAX_VOLTAGE  2.5
#define AFM_ADC_DATA_RANGE  4095
#define AFM_DAC_MAX_VOLTAGE  3.3
#define AFM_DAC_DATA_RANGE  4095
#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE  0.4
//[[[end]]] (checksum: b0925dc37a9403545e88ddcb47cb0adf)

// Misc Program-Specific Enums
#define MOT_FWD 1
#define MOT_BACK 2
#define MOT_SLEEP 1
#define MOT_WAKE 2
#define AFM_AUTOAPPR_ADC 5
#define AFM_DACTABLE_BLK_SIZE 256
#define AFM_ADC_SCALING (double)(AFM_ADC_MAX_VOLTAGE/AFM_ADC_DATA_RANGE)
#define AFM_DAC_SCALING (double)(AFM_DAC_MAX_VOLTAGE/AFM_DAC_DATA_RANGE)

/*
 *  Serial Communication Specifics
 */

//Maximum size allowed for a message before it is discarded. For protection against bad serial connection.
#define SERIAL_MSG_MAX_SIZE 50000



#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

class icspiAFM: public QObject{
    Q_OBJECT

signals:
   bool open(char *serialPortName, qint32 baud_rate);
   void close();

   // Used for afm_worker
   void clearPayloadBuffer();
   int addPayloadByte(char byte);
   int writeByte(unsigned char byte);
   int writeMsg(unsigned char msg_id);
   QByteArray waitForMsg();
   bool isOpen();

   // For callback to mainwindow
   void afm_callback(int callback);

public:
//    icspiAFM(QThread** afm_thread_temp_var):
//        afmThread(afm_thread_temp_var) {}
    int writeMsg(unsigned char msg_id, QByteArray payload);
    void writeDAC(qint8 dacID,
                 double val);

    void readDAC(qint8 dacID);
    void readADC(qint8 adcID);
    void setPGA_pcb3(int channel, double val);
    void setRasterStep();

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
    void setDDSSettings(quint16 numPoints,
                       quint32 startFrequency,
                       quint16 stepSize);
    void frequencySweep(quint16 numPoints,
                       quint16 startFrequency,
                       quint16 stepSize);
    void rasterStep(float val1,
                    float val2);

    void autoApproach_mcu(double setpoint);
    void autoApproach_mcu_status();
    void autoApproach_mcu_stop();
    void setDACMaxValues(char dacID,
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
    void startScan_4act();
    void scanStep_4act();
    void readSignalPhaseOffset();
    void forceCurve();
    void stepMotSetSpeed(int speed);
    void stepMotSetState(int state);
    void stepMotSetDir(int dir);
    void stepMotSetMicrostep(int microstep_enum);
    void stepMotContGo();
    void stepMotContStop();
    void stepMotSingleStep();
    void setDACTable(int block);
    void sigGen(quint8 ratio,
                 double numpts,
                 double numlines);

};

#endif // AFM_H

