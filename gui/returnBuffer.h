#ifndef RETURNBUFFER_H
#define RETURNBUFFER_H


template<class a_Type>
class returnBuffer
{
    char m_type;
    a_Type m_data;

public:
     returnBuffer(char type, a_Type data) : m_type(type), m_data(data) { }
    ~returnBuffer() {}

     a_Type getData() { return m_data;}
};

#endif // RETURNBUFFER_H

