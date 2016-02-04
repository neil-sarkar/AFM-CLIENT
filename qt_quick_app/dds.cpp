#include "dds.h"
#include "constants.h"
#include <QDebug>

DDS::DDS() {
    m_start_frequency = 0;
    m_end_frequency = 0;
    m_step_size = 0; 
}

void DDS::init() {
    cmd_set();
}

void DDS::set_start_frequency(quint32 start_frequency) {
    if (m_start_frequency != start_frequency) {
        m_start_frequency = start_frequency;
        qDebug() << "Changing DDS start frequency to" << m_start_frequency;
        emit start_frequency_changed();
        cmd_set();
    }
}

void DDS::set_step_size(quint16 step_size) {
    if (m_step_size != step_size) {
        m_step_size = step_size;
        qDebug() << "Changing DDS step size to" << m_step_size;
        emit step_size_changed();
        cmd_set();
    }
}

void DDS::set_end_frequency(quint16 end_frequency) {
    if (m_end_frequency != end_frequency) {
        m_end_frequency = end_frequency;
        qDebug() << "Changing DDS end frequency to" << m_end_frequency;
        emit end_frequency_changed();
        cmd_set();
    }
}

quint16 DDS::num_steps() {
    return double(m_end_frequency - m_start_frequency) / m_step_size; // cast to double to avoid divide by 0 error
}

quint32 DDS::start_frequency() {
    return m_start_frequency;
}

quint16 DDS::step_size() {
    return m_step_size;
}

quint16 DDS::end_frequency() {
    return m_end_frequency;
}

void DDS::cmd_set() {
    QByteArray payload;
    quint32 scaled_start_frequency = m_start_frequency * SCALE_FACTOR;
    quint16 scaled_step_size = m_step_size * SCALE_FACTOR;
    quint16 _num_steps = num_steps();
    payload += qint8(scaled_start_frequency);
    payload += qint8(scaled_start_frequency >> 8);
    payload += qint8(scaled_start_frequency >> 16);
    payload += qint8(scaled_start_frequency >> 24);
    payload += qint8(scaled_step_size);
    payload += qint8(scaled_step_size >> 8);
    payload += qint8(_num_steps);
    payload += qint8(_num_steps >> 8);
    emit command_generated(new CommandNode(command_hash[DDS_Set_AD9837], payload));
}
