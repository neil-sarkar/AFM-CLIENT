#include "pid.h"

PID::PID() {
    m_proportional = 0;
    m_integral = 0;
    m_derivative = 0;
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

void PID::set_set_point(float set_point) {
    if (m_set_point != set_point) {
        m_set_point = set_point;
        qDebug() << "Setting set_point to" << m_set_point;
        emit set_point_changed();
        cmd_set_set_point();
    }
}

void PID::cmd_set_proportional() {

}

void PID::cmd_set_derivative() {

}

void PID::cmd_set_integral() {

}

void PID::cmd_set_set_point() {

}


