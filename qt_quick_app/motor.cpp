#include "motor.h"
#include "command_node.h"
#include <QDebug>
#include <QtGlobal>
#include "constants.h"

Motor::Motor() {
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

int Motor::microstep() {
    return m_microstep;
}

void Motor::set_speed(double speed) {
    m_speed = speed;
    qDebug() << "Changing speed to" << m_speed;
    emit speed_changed();
    cmd_set_speed();
}

void Motor::set_direction(int direction) {
    m_direction = direction;
    qDebug() << "Changing direction to" << m_direction;
    emit direction_changed();
    cmd_set_direction();
}

void Motor::set_state(int state) {
    m_state = state;
    qDebug() << "Changing state to" << m_state;
    emit state_changed();
    m_state == StatusConstants.Asleep  ? cmd_set_state_asleep() : cmd_set_state_awake();
}

void Motor::set_microstep(int microstep) {
    m_microstep = microstep;
    qDebug() << "Changing microstep to" << m_microstep;
    emit microstep_changed();
    cmd_set_micro_step();
}

void Motor::init() {
    cmd_set_direction();
    cmd_set_speed();
    cmd_set_state_asleep();
}

void Motor::run_continuous() {
    cmd_run_continuous();
    cmd_set_speed(); // for some reason this is necessary
}

void Motor::cmd_run_continuous() {
    emit command_generated(new CommandNode(command_hash[Motor_Run_Continuous], this));
}

void Motor::cmd_stop_continuous() {
    emit command_generated(new CommandNode(command_hash[Motor_Stop_Continuous], this));
}

void Motor::cmd_single_step() {
    emit command_generated(new CommandNode(command_hash[Motor_Set_Single_Step], this));
}

void Motor::cmd_set_speed() {
    QByteArray q;
    q.push_back(qint8(m_speed)); // low byte
    q.push_back(qint8(m_speed >> 8)); // high byte
    CommandNode* node = new CommandNode(command_hash[Motor_Set_Speed], bind(&Motor::callback), q);
    emit command_generated(node);
}

void Motor::cmd_set_direction() {
    QByteArray payload;
    if (m_direction == StatusConstants.Approach)
        payload += PayloadConstants.MotorApproach;
    else
        payload += PayloadConstants.MotorRetract;

    CommandNode* node = new CommandNode(command_hash[Motor_Set_Direction], this, payload);
    emit command_generated(node);
}

void Motor::cmd_set_state_asleep() {
    emit command_generated(new CommandNode(command_hash[Motor_Set_State_Asleep], bind(&Motor::callback)));
}

void Motor::cmd_set_state_awake() {
    qDebug() << "Setting state awake";
    emit command_generated(new CommandNode(command_hash[Motor_Set_State_Awake], this));
}

void Motor::cmd_set_micro_step() {
    QByteArray q;
    q += m_microstep;
    emit command_generated(new CommandNode(command_hash[Motor_Set_Microstep], this, q));
}

void Motor::callback(QByteArray payload) {
}

Motor::callback_return_type Motor::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}
