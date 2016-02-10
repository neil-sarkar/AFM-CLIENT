#include "approacher.h"
#include "constants.h"
#include "adc.h"

Approacher::Approacher(PID* pid)
{
    m_pid = pid;
    m_state = 0;
}

void Approacher::init() {}

void Approacher::cmd_start_auto_approach() {
    quint16 scaled_setpoint = (m_pid->setpoint())/ADC::SCALE_FACTOR;
    QByteArray payload;
    payload += (scaled_setpoint & 0xFF);
    payload += ((scaled_setpoint & 0xFF00) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Begin_Auto_Approach], payload));
}

void Approacher::cmd_stop_auto_approach() {
    emit command_generated(new CommandNode(command_hash[AFM_Stop_Auto_Approach]));
}

int Approacher::state() {
    return m_state;
}

void Approacher::handle_auto_approach_info_message(QByteArray working_response) {
    double adc_value = double(quint16((quint8(working_response.at(2)) << 8)| quint8(working_response.at(1)))) * ADC::SCALE_FACTOR;
    m_state = working_response.at(0);

    // we should also store the adc value?
    qDebug() << static_cast<unsigned char>(working_response.at(0)) << "  " << adc_value;
}
