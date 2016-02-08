#include "pga.h"
#include "command_node.h"
#include "constants.h"
#include <math.h>

PGA::PGA(qint8 id) {
    m_id = id;
    m_value = default_value(id); // attenuation amount (%)
}

void PGA::set_value(double value) {
    if (m_value != value) {
        m_value = value;
        qDebug() << "Setting PGA value to " << value;
        emit value_changed();
        cmd_set_value();
    }
}

double PGA::value() {
    return m_value;
}

void PGA::init() {
    cmd_set_value();
}

void PGA::cmd_set_value() {
    QByteArray payload;
    payload += m_id;
    payload += value_to_pga();
    qDebug() << m_id << m_value << value_to_pga();
    emit command_generated(new CommandNode(command_hash[PGA_Set], payload));
}

qint8 PGA::value_to_pga() {
//    qDebug() << "ID" << m_id;
//    qDebug() << (m_value) / 100;
//    qDebug() << 10 * log10((m_value) / 100);
//    qDebug() << 20 * log10((m_value) / 100);
//    qDebug() << 20 * log10((m_value) / 100) + 210;
    qDebug() << "here" << m_id;
    qDebug() << (round(20 * log10(double(m_value) / 100))  * 2 + 210);
    qDebug() << qint8((round(20 * log10(double(m_value) / 100))  * 2 + 210));
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


int PGA::default_value(int id) {
    switch (id) {
        case PGA::X_1:
        case PGA::X_2:
        case PGA::Y_1:
        case PGA::Y_2:
        case PGA::Z_Coarse:
            return 100;
        case PGA::Leveling:
            return 0;
        case PGA::Z_Fine:
            return 5;
        case PGA::DDS_Amplitude:
            return 40;
    }
}

