#include "motor.h"
#include "command_node.h"
#include <QDebug>
#include <QtGlobal>

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

int Motor::state() {
    return m_state;
}

void Motor::set_speed(double speed) {
    if (speed != m_speed) {
        m_speed = speed;
//        qDebug() << "Changing speed to" << m_speed;
        emit speed_changed();
        generate_set_speed_command();
    }
}

void Motor::set_direction(int direction) {
    if (direction != m_direction) {
        m_direction = direction;
        qDebug() << "Changing direction to" << m_direction;
        emit direction_changed();
    }
}

void Motor::set_state(int state) {
    if (state != m_state) {
        m_state = state;
        qDebug() << "Changing state to" << m_state;
        emit state_changed();
    }
}

void Motor::generate_set_speed_command() {
    auto command = std::bind(&Motor::generate_set_speed_bytes, this);
    CommandNode* node = new CommandNode(command, NULL, NULL);
    emit command_generated(node);
}

void Motor::generate_set_direction_command() {
}

void Motor::generate_set_state_command() {

}

QByteArray Motor::generate_set_speed_bytes() {
    QByteArray q;
    q.push_back(qrand());
    return q;
}
