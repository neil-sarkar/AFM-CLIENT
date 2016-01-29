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
        m_state == StatusConstants.Asleep  ? cmd_set_state_asleep() : cmd_set_state_awake();
    }
}

void Motor::cmd_run_continuous() {
    QByteArray q;
    emit command_generated(new CommandNode(Commands.RunContinuous, this, q));
}

void Motor::cmd_stop_continuous() {
    QByteArray q;
    emit command_generated(new CommandNode(Commands.StopContinuous, this, q));
}

void Motor::cmd_single_step() {
    QByteArray q;
    emit command_generated(new CommandNode(Commands.SetSingleStep, this, q));
}

void Motor::cmd_set_speed() {
    QByteArray q;
    q.push_back(qint8(m_speed)); // low byte
    q.push_back(qint8(m_speed >> 8)); // high byte
    CommandNode* node = new CommandNode(Commands.SetSpeed, this, q);
    emit command_generated(node);
}

void Motor::cmd_set_direction() {
    QByteArray payload;
    if (m_direction == StatusConstants.Approach)
        payload += PayloadConstants.MotorApproach;
    else
        payload += PayloadConstants.MotorRetract;

    CommandNode* node = new CommandNode(Commands.SetDirection, this, payload);
    emit command_generated(node);
}

void Motor::cmd_set_state_asleep() {
    QByteArray q;
    emit command_generated(new CommandNode(Commands.SetStateAsleep, this, q));
}

void Motor::cmd_set_state_awake() {
    QByteArray q;
    emit command_generated(new CommandNode(Commands.SetStateAwake, this, q));
}

void Motor::cmd_set_micro_step() {
    QByteArray q;
    q += m_microstep;
    emit command_generated(new CommandNode(Commands.SetMicroStep, this, q));
}
