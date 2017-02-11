#include "pga.h"
#include "command_node.h"
#include "constants.h"
#include <math.h>

PGA::PGA(qint8 id, double default_value) {
    m_id = id;
    m_default_value = default_value;
}

void PGA::set_value(double value) {
    if (m_value != value) {
        m_value = value;
        qDebug() << "Setting PGA " << m_id << "value to " << value;
        emit value_changed(m_value);
        update_settings(settings_group_name, QString::number(m_id), QVariant(m_value));
        cmd_set_value(m_value, false);
    }
}

void PGA::transient_set_value(bool is_callback, const QString* master) {
    qDebug() << "Setting PGA(Transient) " << m_id << "value to " << 100;
    m_caller = master;
    cmd_set_value(double(100), is_callback);
}

void PGA::restore_user_value() {
    qDebug() << "Setting PGA(Restore) " << m_id << "value to " << m_value;
    cmd_set_value(m_value, false);
}

void PGA::set_settings() {
    settings.beginGroup(settings_group_name);
    set_value(settings.contains(QString::number(m_id)) ? settings.value(QString::number(m_id)).toDouble() : m_default_value);
    settings.endGroup();
}

qint8 PGA::get_id() {
    return m_id;
}

double PGA::value() {
    return m_value;
}

void PGA::init() {
    set_settings();
}

void PGA::cmd_set_value(double value, bool is_callback) {
    QByteArray payload;
    payload += m_id;
    payload += value_to_pga(value);
    if (!is_callback) 
        emit command_generated(new CommandNode(command_hash[PGA_Set], payload));
    else
        emit command_generated(new CommandNode(command_hash[PGA_Set], bind(&PGA::callback_value_set), payload));
}

void PGA::callback_value_set(QByteArray return_bytes) {
    emit pga_callback_received(m_caller);
}

qint8 PGA::value_to_pga(double value) {
    return (round(20 * log10(value / 100))  * 2 + 210);
}

PGA::callback_return_type PGA::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

const QString PGA::settings_group_name = "pga";


