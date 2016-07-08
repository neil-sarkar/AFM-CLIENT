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
        cmd_set_value();
    }
}

void PGA::set_settings() {
    settings.beginGroup(settings_group_name);
    set_value(settings.contains(QString::number(m_id)) ? settings.value(QString::number(m_id)).toDouble() : m_default_value);
    settings.endGroup();
}

double PGA::value() {
    return m_value;
}

void PGA::init() {
    set_settings();
}

void PGA::cmd_set_value() {
    QByteArray payload;
    payload += m_id;
    payload += value_to_pga();
    emit command_generated(new CommandNode(command_hash[PGA_Set], payload));
}

qint8 PGA::value_to_pga() {
    return (round(20 * log10(double(m_value) / 100))  * 2 + 210);
}

const QString PGA::settings_group_name = "pga";


