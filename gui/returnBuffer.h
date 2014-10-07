#ifndef RETURNBUFFER_H
#define RETURNBUFFER_H

#include <QEventLoop>
#include <QSerialPortInfo>

template<class a_Type>
class returnBuffer
{
    char m_type;
    a_Type m_data;
    QList<QSerialPortInfo> m_list;
    QString m_portName;

public:
     returnBuffer(char type, a_Type data) : m_type(type), m_data(data) { }
     returnBuffer(char type, a_Type data, QList<QSerialPortInfo> &list):m_type(type),m_data(data),m_list(list){}
     returnBuffer(char type, a_Type data, QString portName):m_type(type),m_data(data),m_portName(portName){}
    ~returnBuffer() {}

     a_Type getData() { return m_data;}
     QList<QSerialPortInfo> getList() { return m_list;}
     QString getPortName() { return m_portName; }
};

#endif // RETURNBUFFER_H

