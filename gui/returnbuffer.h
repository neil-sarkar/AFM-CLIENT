#ifndef RETURNBUFFER_H
#define RETURNBUFFER_H

#include <QEventLoop>
#include <QSerialPortInfo>
#include <QMetaType>

//TODO: make constructor template
enum returnType{
    ERR_MSG_MISSED,
    NONE,
    DACBFRD1,
    DACBFRD2,
    DACBR2,
    DACZAMP,
    DACBR1,
    DACBFRD3,
    DACZOFFSETFINE,
    DACY1,
    DACZOFFSETCOARSE,
    DACY2,
    DACX1,
    DACX2,
    FREQSWEEP,
    ADC,
    DAC,
    AFMADCAMPLITUDEID,
    AFMDACOFFSETID,
    PIDENABLE,
    PIDDISABLE,
    DEVICECALIBRATION,
    SCANPARAMETERS,
    SCANDATA,
    ADCZOFFSET,
    WRITE,
    SETDACVALUES,
    STAGESETSTEP,
    SETPULSEWIDTH,
    SETDIRFORWARD,
    SETDIRBACKWARD,
    STARTSCAN,
    SCANSTEP,
    AUTOAPPROACH,
    SETCONTINUOUS,
    ABORTAUTOAPPROACH,
    SETP,
    SETI,
    SETD,
    SETPOINT,
    SETDDS,
    SETPGA,
    ADCPHASE,
    READSIGNALPHASEOFFSET,
    FORCECURVE
};

Q_DECLARE_METATYPE(returnType)

class returnBuffer
{


    returnType m_returnType;
    int i_data;
    char cdata_1;
    char cdata_2;
    QVector<double> m_amplitude;
    QVector<double> m_phase;
    int m_bytesRead;
    float f_data;
    QList<QSerialPortInfo> m_list;
    QVector<double> m_zoffset;
    QVector<double> m_zamp;
    QVector<double> m_zphase;
    double d_signal;
    double d_offset;
    double d_phase;

public:
     returnBuffer(returnType _returnType) :
         m_returnType(_returnType) { }

     returnBuffer(returnType _returnType,
                  int idata) :
         m_returnType(_returnType),
         i_data(idata) { }

     returnBuffer(returnType _returnType,
                  char cdata1,
                  char cdata2) :
         m_returnType(_returnType),
         cdata_1(cdata1),
         cdata_2(cdata2)   { }

     returnBuffer(returnType _returnType,
                  float data) :
         m_returnType(_returnType),
         f_data(data) { }

     returnBuffer(returnType _returnType,
                  int success,
                  QVector<double>& _amplitude,
                  QVector<double>& _phase,
                  int _bytesRead):
         m_returnType(_returnType),
         i_data(success),
         m_amplitude(_amplitude),
         m_phase(_phase),
         m_bytesRead(_bytesRead) { }

     returnBuffer(returnType _returnType,
                  int success,
                  double signal,
                  double offset,
                  double phase):
         m_returnType(_returnType),
         i_data(success),
         d_signal(signal),
         d_offset(offset),
         d_phase(phase) { }

     returnBuffer(returnType _returnType,
                  int _success,
                  QVector<double>& z_offset_adc,
                  QVector<double> z_amp_adc,
                  QVector<double> z_phase_adc):
         m_returnType(_returnType),
         i_data(_success),
         m_zoffset(z_offset_adc),
         m_zamp(z_amp_adc),
         m_zphase(z_phase_adc){}

     returnBuffer(returnType _returnType,
                  QList<QSerialPortInfo> &list) :
         m_returnType(_returnType),
         m_list(list){}

    ~returnBuffer() {}

     int getData(){ return i_data;}
     QList<QSerialPortInfo> getList() { return m_list;}
     float getFData() { return f_data; }
     returnType getReturnType() {return m_returnType;}
     QVector<double> getAmplitude() { return m_amplitude; }
     QVector<double> getPhase() { return m_phase; }
     int getBytesRead() { return m_bytesRead; }
     QVector<double> getzoffset() {return m_zoffset;}
     QVector<double> getzamp() {return m_zamp;}
     QVector<double> getzphase() {return m_zphase;}
     double getdsignal() { return d_signal;}
     double getdoffset() { return d_offset;}
     double getdphase() { return d_phase;}

};

#endif // RETURNBUFFER_H

