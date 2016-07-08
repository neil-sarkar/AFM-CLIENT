#include "pid.h"
#include "constants.h"
#include "adc.h"

PID::PID() {
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

float PID::setpoint() {
    return m_setpoint;
}

bool PID::enabled() {
    return m_enabled;
}

void PID::set_proportional(float proportional) {
    if (m_proportional != proportional) {
        m_proportional = proportional;
        qDebug() << "Setting proportional to" << m_proportional;
        emit proportional_changed(m_proportional);
        update_settings(settings_group_name, "proportional", QVariant(m_proportional));
        cmd_set_proportional();
    }
}

void PID::set_integral(float integral) {
    if (m_integral != integral) {
        m_integral = integral;
        qDebug() << "Setting integral to" << m_integral;
        emit integral_changed(m_integral);
        update_settings(settings_group_name, "integral", QVariant(m_integral));
        cmd_set_integral();
    }
}

void PID::set_derivative(float derivative) {
    if (m_derivative != derivative) {
        m_derivative = derivative;
        qDebug() << "Setting derivative to" << m_derivative;
        emit derivative_changed(m_derivative);
        update_settings(settings_group_name, "derivative", QVariant(m_derivative));
        cmd_set_derivative();
    }
}

void PID::set_setpoint(float setpoint) {
    if (m_setpoint != setpoint) {
        m_setpoint = setpoint;
        qDebug() << "Setting set_point to" << m_setpoint;
        emit setpoint_changed(m_setpoint);
        update_settings(settings_group_name, "setpoint", QVariant(m_setpoint));
        cmd_set_setpoint();
    }
}

void PID::set_enabled(bool enabled) {
    if (m_enabled != enabled) {
        m_enabled = enabled;
        qDebug() << "Setting PID enabled to" << m_enabled;
        emit enabled_changed(m_enabled);
        m_enabled ? cmd_enable() : cmd_disable(); // for some reason this line hangs  - maybe race condition
    }
}

void PID::set_disabled() {
    set_enabled(false);
}

void PID::set_settings() {
    settings.beginGroup(settings_group_name);
    set_proportional(settings.contains("proportional") ? settings.value("proportional").toFloat() : 5);
    set_integral(settings.contains("integral") ? settings.value("integral").toFloat() : 5000);
    set_derivative(settings.contains("derivative") ? settings.value("derivative").toFloat() : 0);
    set_setpoint(settings.contains("setpoint") ? settings.value("setpoint").toFloat() : 0.7);
    settings.endGroup();
}

void PID::init() {
    set_disabled();
    set_settings();
}

void PID::cmd_set_proportional() {
    QByteArray payload;
    for (int i = 0; i < 4; i++)
        payload += (((char *)&m_proportional)[i]);
    emit command_generated(new CommandNode(command_hash[PID_Set_Proportional], payload));
}

void PID::cmd_set_integral() {
    QByteArray payload;
    for (int i = 0; i < 4; i++)
        payload += (((char *)&m_integral)[i]);
    emit command_generated(new CommandNode(command_hash[PID_Set_Integral], payload));
}

void PID::cmd_set_derivative() {
    QByteArray payload;
    for (int i = 0; i < 4; i++)
        payload += (((char *)&m_derivative)[i]);
    emit command_generated(new CommandNode(command_hash[PID_Set_Derivative], payload));
}

void PID::cmd_set_setpoint() {
    quint16 setpoint = float(m_setpoint) / float(ADC::SCALE_FACTOR);
    QByteArray payload;
    payload += (setpoint & 0xFF);
    payload += ((setpoint & 0xFF00) >> 8);
    emit command_generated(new CommandNode(command_hash[PID_Set_Setpoint], payload));
}

void PID::cmd_enable() {
    emit command_generated(new CommandNode(command_hash[PID_Enable]));
}

void PID::cmd_disable() {
    emit command_generated(new CommandNode(command_hash[PID_Disable]));
}

const QString PID::settings_group_name = "pid";
