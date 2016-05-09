#include "motor.h"
#include "command_node.h"
#include <QDebug>
#include <QtGlobal>
#include "constants.h"

Motor::Motor() {
    m_speed = 0;
    m_direction = 0;
    m_state = 0;
    m_microstep = 0;
    timeout_timer = NULL;
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

void Motor::set_speed(int speed) {
    m_speed = speed;
    qDebug() << "Changing speed to" << m_speed;
    emit speed_changed(m_speed);
    cmd_set_speed();
}

void Motor::set_direction(int direction) {
    m_direction = direction;
    qDebug() << "Changing direction to" << m_direction;
    emit direction_changed(m_direction);
    cmd_set_direction();
}

void Motor::set_state(int state) {
    m_state = state;
    qDebug() << "Changing state to" << m_state;
    emit state_changed(m_state);
    m_state == StatusConstants.Asleep  ? cmd_set_state_asleep() : cmd_set_state_awake();
}

void Motor::set_microstep(int microstep) {
    m_microstep = microstep;
    qDebug() << "Changing microstep to" << m_microstep;
    emit microstep_changed(m_microstep);
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
    emit command_generated(new CommandNode(command_hash[Motor_Run_Continuous]));
    if (timeout_timer)
        timeout_timer->stop();
}

void Motor::cmd_stop_continuous() {
    emit command_generated(new CommandNode(command_hash[Motor_Stop_Continuous], bind(&Motor::reset_timeout_timer)));
}

void Motor::cmd_single_step() {
    emit command_generated(new CommandNode(command_hash[Motor_Set_Single_Step], bind(&Motor::reset_timeout_timer)));
}

void Motor::cmd_set_speed() {
    QByteArray payload;
    payload.push_back(qint8(m_speed)); // low byte
    payload.push_back(qint8(m_speed >> 8)); // high byte
    CommandNode* node = new CommandNode(command_hash[Motor_Set_Speed], payload);
    emit command_generated(node);
}

void Motor::cmd_set_direction() {
    QByteArray payload;
    if (m_direction == StatusConstants.Approach)
        payload += PayloadConstants.MotorApproach;
    else
        payload += PayloadConstants.MotorRetract;

    CommandNode* node = new CommandNode(command_hash[Motor_Set_Direction], payload);
    emit command_generated(node);
}

void Motor::cmd_set_state_asleep() {
    qDebug() << "Setting state asleep";
    emit command_generated(new CommandNode(command_hash[Motor_Set_State_Asleep]));
}

void Motor::cmd_set_state_awake() {
    qDebug() << "Setting state awake";
    emit command_generated(new CommandNode(command_hash[Motor_Set_State_Awake]));
}

void Motor::cmd_set_micro_step() {
    QByteArray payload;
    payload += m_microstep;
    emit command_generated(new CommandNode(command_hash[Motor_Set_Microstep], payload));
}

void Motor::reset_timeout_timer(QByteArray result) {
    Q_UNUSED(result);
    if (timeout_timer)
        timeout_timer->stop();
    timeout_timer = new QTimer();
    timeout_timer->setSingleShot(true);
    QObject::connect(timeout_timer, SIGNAL(timeout()), this, SLOT(cmd_set_state_asleep()));
    timeout_timer->start(Motor::Timeout_Milliseconds);
}

Motor::callback_return_type Motor::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}


const int Motor::Timeout_Milliseconds = 5000;
