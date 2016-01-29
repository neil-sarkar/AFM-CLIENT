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


int Motor::speed() {
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
        qDebug() << "Changing speed to" << m_speed;
        emit speed_changed();
        cmd_set_speed();
    }
}

void Motor::set_direction(int direction) {
    if (direction != m_direction) {
        m_direction = direction;
        qDebug() << "Changing direction to" << m_direction;
        emit direction_changed();
        cmd_set_direction();
    }
}

void Motor::set_state(int state) {
    if (state != m_state) {
        m_state = state;
        qDebug() << "Changing state to" << m_state;
        emit state_changed();
        cmd_set_state();
    }
}

void Motor::run_continuous() {
    QByteArray q;
    emit command_generated(new CommandNode(0x33, this, q));
}

void Motor::single_step() {
    QByteArray q;
    emit command_generated(new CommandNode(0x31, this, q));
}

void Motor::cmd_set_speed() {
    QByteArray q;
    q.push_back(qint8(m_speed)); // low byte
    q.push_back(qint8(m_speed >> 8)); // high byte
    CommandNode* node = new CommandNode(0x32, this, q);
    emit command_generated(node);
}

void Motor::cmd_set_direction() {
    QByteArray q;
    q += m_direction ? 0x66 : 0x62;
    CommandNode* node = new CommandNode(0x36, this, q);
    emit command_generated(node);
}

void Motor::cmd_set_state() {
    QByteArray q;
    CommandNode* node = m_state ? new CommandNode(0x35, this, q) : new CommandNode(0x34, this, q);
    emit command_generated(node);
}
