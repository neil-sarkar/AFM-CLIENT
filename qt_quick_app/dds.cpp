#include "dds.h"
#include "constants.h"
#include <QDebug>

DDS::DDS() {
    m_start_frequency = 4000;
    m_end_frequency = 10000;
    m_step_size = 50;
}

void DDS::set_settings() {
    settings.beginGroup(settings_group_name);
    set_start_frequency(settings.contains("start_frequency") ? settings.value("start_frequency").toInt() : 4000);
    set_end_frequency(settings.contains("end_frequency") ? settings.value("end_frequency").toInt() : 10000);
    set_step_size(settings.contains("step_size") ? settings.value("step_size").toInt() : 50);
    settings.endGroup();
}

void DDS::update_settings(QString key, QVariant value) {
    settings.beginGroup(settings_group_name);
    settings.setValue(key, value);
    settings.endGroup();
}

void DDS::init() {
    set_settings();
    cmd_set();
}

void DDS::set_start_frequency(quint32 start_frequency) {
    if (m_start_frequency != start_frequency) {
        m_start_frequency = start_frequency;
        qDebug() << "Changing DDS start frequency to" << m_start_frequency;
        emit start_frequency_changed(static_cast<int>(m_start_frequency));
        update_settings("start_frequency", QVariant(m_start_frequency));
    }
}

void DDS::set_step_size(quint16 step_size) {
    if (m_step_size != step_size) {
        m_step_size = step_size;
        qDebug() << "Changing DDS step size to" << m_step_size;
        emit step_size_changed(static_cast<int>(m_step_size));
        update_settings("step_size", QVariant(m_step_size));
    }
}

void DDS::set_end_frequency(quint32 end_frequency) {
    if (m_end_frequency != end_frequency) {
        m_end_frequency = end_frequency;
        qDebug() << "Changing DDS end frequency to" << m_end_frequency;
        emit end_frequency_changed(static_cast<int>(m_end_frequency));
        update_settings("end_frequency", QVariant(m_end_frequency));
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

quint32 DDS::end_frequency() {
    return m_end_frequency;
}

void DDS::cmd_set() {
    qDebug() << "Setting DDS";
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

const QString DDS::settings_group_name = "dds";
