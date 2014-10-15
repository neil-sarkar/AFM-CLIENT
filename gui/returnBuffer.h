#ifndef RETURNBUFFER_H
#define RETURNBUFFER_H

#include <QEventLoop>
#include <QSerialPortInfo>

template<class a_Type>
class returnBuffer
{
    a_Type m_data;
    QList<QSerialPortInfo> m_list;
    QString m_returnFunc;
    float f_data;

public:
     returnBuffer(a_Type data) :  m_data(data) { }
     returnBuffer(float data) :  f_data(data) { }
     returnBuffer(QString returnFunc): m_returnFunc(returnFunc){}
     returnBuffer(a_Type data, QList<QSerialPortInfo> &list) : m_data(data),m_list(list){}
    ~returnBuffer() {}

     a_Type getData() { return m_data;}
     QList<QSerialPortInfo> getList() { return m_list;}
     QString getPortName() { return m_portName; }
     float getFData() { return f_data; }
     QString getFunction() {return m_returnFunc;}
};

#endif // RETURNBUFFER_H

