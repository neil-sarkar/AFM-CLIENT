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
    SCANDATA
};

class returnBuffer
{


    returnType m_returnType;
    int i_data;
    QVector<double> m_amplitude;
    QVector<double> m_frequency;
    int m_bytesRead;
    float f_data;
    QList<QSerialPortInfo> m_list;
    QVector<char> m_zoffset;
    QVector<char> m_zamp;
    QVector<char> m_zphase;

public:
     returnBuffer(returnType _returnType) :
         m_returnType(_returnType) { }

     returnBuffer(returnType _returnType,int idata) :
         m_returnType(_returnType),
         i_data(idata) { }

     returnBuffer(returnType _returnType,int success,QVector<double>& _amplitude,QVector<double>& _frequency,int &_bytesRead):
         m_returnType(_returnType),
         i_data(success),
         m_amplitude(_amplitude),
         m_frequency(_frequency),
         m_bytesRead(_bytesRead) { }

     returnBuffer(returnType _returnType,int _success,QVector<char>& z_offset_adc, QVector<char> z_amp_adc,QVector<char> z_phase_adc):
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
     int getBytesRead() { return m_bytesRead; }
     QVector<char> getzoffset() {return m_zoffset;}
     QVector<char> getzamp() {return m_zamp;}
     QVector<char> getzphase() {return m_zphase;}
};

#endif // RETURNBUFFER_H

