#ifndef RETURNBUFFER_H
#define RETURNBUFFER_H

#include <QEventLoop>
#include <QSerialPortInfo>

enum returnType{
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
    GETPORTS,
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
    ADCZAMP
};

class returnBuffer
{


    returnType m_returnType;
    int i_data;
    QVector<double> m_amplitude;
    QVector<double> m_phase;
    QVector<double> m_frequency;
    int m_bytesRead;
    float f_data;
    QList<QSerialPortInfo> m_list;
    QVector<double> m_zoffset;
    QVector<double> m_zamp;
    QVector<double> m_zphase;

public:
     returnBuffer(returnType _returnType) :
         m_returnType(_returnType) { }

     returnBuffer(returnType _returnType,int idata) :
         m_returnType(_returnType),
         i_data(idata) { }

     returnBuffer(returnType _returnType,int success,QVector<double>& _amplitude,QVector<double>& _phase, QVector<double>& _frequency,int &_bytesRead):
         m_returnType(_returnType),
         i_data(success),
         m_amplitude(_amplitude),
         m_phase(_phase),
         m_frequency(_frequency),
         m_bytesRead(_bytesRead) { }

     returnBuffer(returnType _returnType,int _success,QVector<double>& z_offset_adc, QVector<double> z_amp_adc,QVector<double> z_phase_adc):
         m_returnType(_returnType),
         i_data(_success),
         m_zoffset(z_offset_adc),
         m_zamp(z_amp_adc),
         m_zphase(z_phase_adc){}

     returnBuffer(returnType _returnType,float data) :
         m_returnType(_returnType),
         f_data(data) { }

     returnBuffer(returnType _returnType,QList<QSerialPortInfo> &list) :
         m_returnType(_returnType),
         m_list(list){}

    ~returnBuffer() {}

     int getData(){ return i_data;}
     QList<QSerialPortInfo> getList() { return m_list;}
     float getFData() { return f_data; }
     returnType getReturnType() {return m_returnType;}
     QVector<double> getAmplitude() { return m_amplitude; }
     QVector<double> getFrequency() { return m_frequency; }
     QVector<double> getPhase() { return m_phase; }
     int getBytesRead() { return m_bytesRead; }
     QVector<double> getzoffset() {return m_zoffset;}
     QVector<double> getzamp() {return m_zamp;}
     QVector<double> getzphase() {return m_zphase;}

};

#endif // RETURNBUFFER_H

