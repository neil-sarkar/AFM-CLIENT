#include "pga.h"
#include "command_node.h"
#include <math.h>

PGA::PGA(qint8 id) {
    m_id = id;
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
    emit command_generated(new CommandNode(Commands.Set, this, payload));
}

qint8 PGA::value_to_pga() {
    return round(20 * log10(m_value / 100) * 2 + 210);
}

const int PGA::X_1 = 1;
const int PGA::X_2 = 2;
const int PGA::Y_1 = 3;
const int PGA::Y_2 = 4;
const int PGA::Z_Fine = 5;
const int PGA::DDS_Amplitude = 6;
const int PGA::Z_Coarse = 7;
const int PGA::Leveling = 8;
