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
}

void Approacher::cmd_get_state() {
    emit command_generated(new CommandNode(command_hash[AFM_Get_Auto_Approach_State], bind(&Approacher::callback_get_state)));
}

void Approacher::callback_get_state(QByteArray payload) {
    m_state = payload.at(0);
    emit new_state(m_state, payload.at(1));
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
