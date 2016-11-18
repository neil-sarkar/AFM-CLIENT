#include "approacher.h"
#include "constants.h"
#include "adc.h"
#include <QDateTime>

Approacher::Approacher(PID* pid, AFMObject* adc)
{
    m_adc = static_cast<ADC*>(adc);
    m_pid = pid;
    m_state = 0;
}

void Approacher::init() {
    m_pid->init();
    set_signal_low_limit(Approacher::DEFAULT_SIGNAL_LOW_LIMIT);
}

void Approacher::cmd_get_state() {
    emit command_generated(new CommandNode(command_hash[AFM_Get_Auto_Approach_State], bind(&Approacher::callback_get_state)));
}

void Approacher::callback_get_state(QByteArray payload) {
    m_state = payload.at(0);
    emit new_state(m_state, payload.at(1));
    if(payload.at(2) != 0) {
        emit approach_low_signal_error();
    }
}

void Approacher::cmd_start_auto_approach() {
    qDebug() << "Starting auto approach";
    quint16 scaled_setpoint = (m_pid->setpoint())/ADC::SCALE_FACTOR;
    QByteArray payload;
    payload += (scaled_setpoint & 0xFF);
    payload += ((scaled_setpoint & 0xFF00) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Begin_Auto_Approach], payload));
}

void Approacher::cmd_stop_auto_approach() {
    mutex.lock();  // TODO: look into atomic bools
    is_approaching = false;
    mutex.unlock();
    emit command_generated(new CommandNode(command_hash[AFM_Stop_Auto_Approach]));
}

int Approacher::state() {
    return m_state;
}

Approacher::callback_return_type Approacher::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}

void Approacher::handle_auto_approach_info_message(QByteArray working_response) {
    Q_UNUSED(working_response);
//     double adc_value = double(quint16((quint8(working_response.at(2)) << 8)| quint8(working_response.at(1)))) * ADC::SCALE_FACTOR;
//     m_state = working_response.at(0);
//     m_adc->update_value(adc_value);
//     if (m_state == 9) {
//         mutex.lock();
//         is_approaching = false;
//         mutex.unlock();
//     }
//     emit new_data(m_state, adc_value);
}

void Approacher::cmd_start_disengage() {
    emit command_generated(new CommandNode(command_hash[AFM_Start_Auto_Retract_Disengage]));
}

void Approacher::cmd_start_retract_fast(){
    quint16 duration = 2000;
    QByteArray payload;
    payload += (duration & 0xFF);
    payload += ((duration & 0xFF00) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Start_Auto_Retract_Fast], payload));
}

void Approacher::cmd_set_low_limit() {
    quint16 low_limit = m_low_limit/ADC::SCALE_FACTOR;
    qDebug() << "Cmd setting approach low signal threshold to " << m_low_limit << " V => " << low_limit << " codes";
    QByteArray payload;
    payload += (low_limit & 0xFF);
    payload += ((low_limit & 0xFF00) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Set_Auto_Approach_Low_Limit], payload));
}

float Approacher::signal_low_limit() {
    return m_low_limit;
}

void Approacher::set_signal_low_limit(float low_limit_in_V) {
    m_low_limit = low_limit_in_V;
    qDebug() << "Setting signal low limit to " << m_low_limit;
    emit signal_low_limit_changed(m_low_limit);
    cmd_set_low_limit();
}

const float Approacher::DEFAULT_SIGNAL_LOW_LIMIT = 0.7;
