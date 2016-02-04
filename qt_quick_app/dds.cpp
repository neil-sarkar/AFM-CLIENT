#include "dds.h"
#include "constants.h"
#include <QDebug>

DDS::DDS() {
    m_start_frequency = 0;
    m_step_size = 0;
    m_num_points = 0;
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
        qDebug() << "Changing DDS start frequency to" << m_step_size;
        emit step_size_changed();
        cmd_set();
    }
}

void DDS::set_num_points(quint16 num_points) {
    if (m_num_points != num_points) {
        m_num_points = num_points;
        qDebug() << "Changing DDS start frequency to" << m_num_points;
        emit num_points_changed();
        cmd_set();
    }
}

quint32 DDS::start_frequency() {
    return m_start_frequency;
}

quint16 DDS::step_size() {
    return m_step_size;
}

quint16 DDS::num_points() {
    return m_num_points;
}

void DDS::cmd_set() {
    QByteArray payload;
    quint32 scaled_start_frequency = m_start_frequency * SCALE_FACTOR;
    quint16 scaled_step_size = m_step_size * SCALE_FACTOR;
    payload += qint8(scaled_start_frequency);
    payload += qint8(scaled_start_frequency >> 8);
    payload += qint8(scaled_start_frequency >> 16);
    payload += qint8(scaled_start_frequency >> 24);
    payload += qint8(scaled_step_size);
    payload += qint8(scaled_step_size >> 8);
    payload += qint8(m_num_points);
    payload += qint8(m_num_points >> 8);
    emit command_generated(new CommandNode(command_hash[DDS_Set_AD9837], payload));
}
