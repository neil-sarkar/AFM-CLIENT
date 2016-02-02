#include "dac.h"
#include "constants.h"

DAC::DAC(qint8 id) {
    m_id = id;
}

void DAC::set_value(double value) {
    if (m_value != value) {
        m_value = value;
        qDebug() << "Changing DAC value to " << m_value;
        emit value_changed();
        cmd_set_value();
    }
}

void DAC::init() {
    QByteArray q;
    q.push_back(m_id);
    q.push_back(RESOLUTION & 0xFF);
    q.push_back((RESOLUTION & 0x0F00) >> 8);
    CommandNode* node = new CommandNode(command_hash[DAC_Set_Max_Value], this, q); // Set the maximum value of the DAC
    emit command_generated(node);
    cmd_set_value(); // set the DAC to the value m_value
}

double DAC::value() {
    return m_value;
}

void DAC::cmd_read_value() {
    QByteArray q;
    q.push_back(m_id);
    CommandNode* node = new CommandNode(command_hash[DAC_Read], this, q);
    emit command_generated(node);
}

void DAC::cmd_set_value() {
    QByteArray q;
    qint16 value = m_value / double(MAX_VOLTAGE/RESOLUTION);
    q.push_back(m_id);
    q.push_back((value & 0xFF));
    q.push_back((value >> 8));
    CommandNode* node = new CommandNode(command_hash[DAC_Write], this, q);
    emit command_generated(node);
}

void DAC::set_id(qint8 id) {
    if (m_id != id) {
        m_id = id;
        qDebug() << "Changing DAC id to " << m_id;
        emit id_changed();
    }
}

qint8 DAC::id() {
    return m_id;
}

const int DAC::Buffered_1 = 0;
const int DAC::Buffered_2 = 1;
const int DAC::Board_2 = 2;
const int DAC::Z_Amplitude = 3;
const int DAC::Board_1 = 4;
const int DAC::Buffered_3 = 5;
const int DAC::Z_Offset_Fine = 6;
const int DAC::Y_1 = 7;
const int DAC::Z_Offset_Coarse = 8;
const int DAC::Y_2 = 9;
const int DAC::X_1 = 10;
const int DAC::X_2 = 11;
