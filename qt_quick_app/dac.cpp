#include "dac.h"

DAC::DAC(qint8 id) {
    m_id = id;
}

void DAC::set_value(double value) {
    if (m_value != value) {
        m_value = value;
        qDebug() << "Changing DAC value to " << m_value;
        emit value_changed();
        write();
    }
}

void DAC::init() {
    QByteArray q;
    q.push_back(m_id);
    q.push_back(RESOLUTION & 0xFF);
    q.push_back((RESOLUTION & 0x0F00) >> 8);
    CommandNode* node = new CommandNode(0x26, this, q);
    emit command_generated(node);
}

double DAC::value() {
    return m_value;
}

void DAC::read() {
    QByteArray q;
    q.push_back(m_id);
    CommandNode* node = new CommandNode(0x62, this, q);
    emit command_generated(node);
}

void DAC::write() {
    QByteArray q;
    qint16 value = m_value / double(MAX_VOLTAGE/RESOLUTION);
    q.push_back(m_id);
    q.push_back((value & 0xFF));
    q.push_back((value >> 8));
    CommandNode* node = new CommandNode(0x61, this, q);
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

