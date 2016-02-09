#include "dac.h"
#include "constants.h"

DAC::DAC(qint8 id) {
    m_id = id;
}

void DAC::set_value(double value, bool cmd) {
    if (m_value != value) {
        m_value = value;
        emit value_changed();
        qDebug() << "Changing DAC " <<  m_id << "value to " << m_value;
        if (cmd) {
            cmd_set_value();
        }
    }
}

void DAC::init() {
    QByteArray q;
    q.push_back(m_id);
    q.push_back(RESOLUTION & 0xFF);
    q.push_back((RESOLUTION & 0x0F00) >> 8);
    qDebug() << "here" << q;
    CommandNode* node = new CommandNode(command_hash[DAC_Set_Max_Value], q); // Set the maximum value of the DAC - make its own method
    emit command_generated(node);
    cmd_set_value(); // set the DAC to the value m_value
}

double DAC::value() {
    return m_value;
}

void DAC::cmd_read_value() {
    QByteArray payload;
    payload.push_back(m_id);
    CommandNode* node = new CommandNode(command_hash[DAC_Read], bind(&DAC::callback_read_value), payload);
    emit command_generated(node);
}

void DAC::callback_read_value(QByteArray return_bytes) {
    // comes back as DAC # (id), byte 1, byte 2
//    qDebug() << "UPDATING VALUE";
//    qDebug() << return_bytes;
//    qDebug() << bytes_to_word(return_bytes.at(1), return_bytes.at(2));
    set_value(bytes_to_word(return_bytes.at(1), return_bytes.at(2)) * DAC::SCALE_FACTOR, false);
//    qDebug() << m_value;
}

void DAC::cmd_set_value() {
    QByteArray payload;
    qint16 value = m_value / DAC::SCALE_FACTOR;
    payload.push_back(m_id);
    payload.push_back((value & 0xFF));
    payload.push_back((value & 0x0F00) >> 8);
    CommandNode* node = new CommandNode(command_hash[DAC_Write], payload);
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

DAC::callback_return_type DAC::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
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

const quint16 DAC::RESOLUTION = 4095;
const double DAC::MAX_VOLTAGE = 3.3;
const double DAC::SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;
