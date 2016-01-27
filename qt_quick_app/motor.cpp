#include "motor.h"
#include <QDebug>

Motor::Motor(QObject *parent) : QObject(parent)
{
    m_speed = 0;
    m_direction = 0;
    m_state = 0;

}

void Motor::run() {
    qDebug() << "Running motor at speed " << m_speed << "and direction " << m_direction;
}

double Motor::speed() {
    return m_speed;
}

int Motor::direction() {
    return m_direction;
}

void Motor::set_speed(double speed) {
    if (speed != m_speed) {
        m_speed = speed;
        qDebug() << "Changing speed to" << m_speed;
        emit speed_changed();
    }
}

void Motor::set_direction(int direction) {
    if (direction != m_direction) {
        m_direction = direction;
        qDebug() << "Changing direction to" << m_direction;
        emit direction_changed();
    }
}

