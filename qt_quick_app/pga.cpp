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

void PGA::cmd_set_value() {
    QByteArray payload;
    payload += m_id;
    payload += value_to_pga();
    emit command_generated(new CommandNode(Commands.Set, this, payload));
}

qint8 PGA::value_to_pga() {
    return round(20 * log10(m_value / 100) * 2 + 210);
}
