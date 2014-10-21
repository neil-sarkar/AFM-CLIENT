#ifndef RETURNBUFFER_H
#define RETURNBUFFER_H

#include <QEventLoop>
#include <QSerialPortInfo>
#include "returnTypes.h"

template<class a_Type>
class returnBuffer
{
    a_Type m_data;
    QList<QSerialPortInfo> m_list;
    returnType m_returnType;
    float f_data;
    QVector<double> m_amplitude;
    QVector<double> m_frequency;
    int m_bytesRead;

public:
     returnBuffer(returnType _returnType,a_Type data) : m_returnType(_returnType), m_data(data) { }
     returnBuffer(returnType _returnType,a_Type data,QVector<double> &_amplitude,QVector<double> &_frequency,int &_bytesRead)
         : m_returnType(_returnType), m_data(data),m_amplitude(_amplitude),m_frequency(_frequency),m_bytesRead(_bytesRead) { }
     returnBuffer(returnType _returnType,float data) : m_returnType(_returnType), f_data(data) { }
     returnBuffer(returnType _returnType,QList<QSerialPortInfo> &list) :m_returnType(_returnType), m_list(list){}
    ~returnBuffer() {}

     a_Type getData() { return m_data;}
     QList<QSerialPortInfo> getList() { return m_list;}
     QString getPortName() { return m_portName; }
     float getFData() { return f_data; }
     returnType getReturnType() {return m_returnType;}
     QVector<double> getAmplitude() { return m_amplitude; }
     QVector<double> getFrequency() { return m_frequency; }
     int getBytesRead() { return m_bytesRead; }
};

#endif // RETURNBUFFER_H

