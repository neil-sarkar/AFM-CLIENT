#include "pga.h"
#include "command_node.h"
#include "constants.h"
#include <math.h>

PGA::PGA(qint8 id) {
    m_id = id;
}

void PGA::set_value(double value) {
    if (m_value != value) {
        m_value = value;
        qDebug() << "Setting PGA " << m_id << "value to " << value;
        emit value_changed(m_value);
        update_settings();
        cmd_set_value();
    }
}

void PGA::update_settings() {
    settings.beginGroup(settings_group_name);
    settings.setValue(QString::number(m_id), m_value);
    settings.endGroup();
}

void PGA::set_settings() {
    settings.beginGroup(settings_group_name);
    QVariant settings_value = settings.value(QString::number(m_id));
    if (settings_value == QVariant::Invalid)
        set_value(default_value(m_id));
    else
        set_value(settings_value.toDouble());
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

const int PGA::X_1 = 1;
const int PGA::X_2 = 2;
const int PGA::Y_1 = 3;
const int PGA::Y_2 = 4;
const int PGA::Z_Fine = 5;
const int PGA::DDS_Amplitude = 6;
const int PGA::Z_Coarse = 7;
const int PGA::Leveling = 8;

const QString PGA::settings_group_name = "pga";


int PGA::default_value(int id) {
    switch (id) {
        case PGA::X_1:
            return 100;
        case PGA::X_2:
            return 100;
        case PGA::Y_1:
            return 100;
        case PGA::Y_2:
            return 100;
        case PGA::Z_Coarse:
            return 100;
        case PGA::Leveling:
            return 0;
        case PGA::Z_Fine:
            return 10;
        case PGA::DDS_Amplitude:
            return 50;
    }
    return 0;
}


