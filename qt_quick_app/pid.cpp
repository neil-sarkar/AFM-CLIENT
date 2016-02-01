#include "pid.h"

PID::PID() {
    m_proportional = 0;
    m_integral = 0;
    m_derivative = 0;
    m_enabled = 0;
}

float PID::proportional() {
    return m_proportional;
}

float PID::integral() {
    return m_integral;
}

float PID::derivative() {
    return m_derivative;
}

float PID::set_point() {
    return m_set_point;
}

bool PID::enabled() {
    qDebug() << "CALLED";
    return m_enabled;
}

void PID::set_proportional(float proportional) {
    if (m_proportional != proportional) {
        m_proportional = proportional;
        qDebug() << "Setting proportional to" << m_proportional;
        emit proportional_changed();
        cmd_set_proportional();
    }
}

void PID::set_integral(float integral) {
    if (m_integral != integral) {
        m_integral = integral;
        qDebug() << "Setting integral to" << m_integral;
        emit integral_changed();
        cmd_set_integral();
    }
}

void PID::set_derivative(float derivative) {
    if (m_derivative != derivative) {
        m_derivative = derivative;
        qDebug() << "Setting derivative to" << m_derivative;
        emit derivative_changed();
        cmd_set_derivative();
    }
}

void PID::set_enabled(bool enabled) {
    if (m_enabled != enabled) {
        m_enabled = enabled;
        qDebug() << "Setting enabled to" << m_enabled;
        emit enabled_changed();
        m_enabled ? cmd_enable() : cmd_disable(); // for some reason this line hangs  - maybe race condition
    }
}

void PID::set_disabled() {
    set_enabled(false);
}

void PID::set_set_point(float set_point) {
    if (m_set_point != set_point) {
        m_set_point = set_point;
        qDebug() << "Setting set_point to" << m_set_point;
        emit set_point_changed();
        cmd_set_set_point();
    }
}

void PID::cmd_set_proportional() {
    QByteArray payload;
    for (int i = 0; i < 4; i++)
        payload += ((char *)&m_proportional)[i];
    emit command_generated(new CommandNode(0x70, this, payload));
}

void PID::cmd_set_integral() {
    QByteArray payload;
    for (int i = 0; i < 4; i++)
        payload += ((char *)&m_integral)[i];
    emit command_generated(new CommandNode(0x69, this, payload));
}

void PID::cmd_set_derivative() {
    QByteArray payload;
    for (int i = 0; i < 4; i++)
        payload += ((char *)&m_derivative)[i];
    emit command_generated(new CommandNode(0x64, this, payload));
}

void PID::cmd_set_set_point() {
    quint16 set_point = float(m_set_point) / float(SCALE_FACTOR);
    QByteArray payload;
    payload += (set_point & 0xFF);
    payload += ((set_point & 0xFF00) >> 8);
    emit command_generated(new CommandNode(0x73, this, payload));
}

void PID::cmd_enable() {
    emit command_generated(new CommandNode(0x67, this));
}

void PID::cmd_disable() {
    emit command_generated(new CommandNode(0x68, this));
}
