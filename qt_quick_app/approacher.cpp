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

void Approacher::init() {}

void Approacher::cmd_start_auto_approach() {
    for (int i = 0; i < 10; i++) {
        emit new_data(2, 0.8);
    }
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
    m_adc->update_value(adc_value);
    emit new_data(m_state, adc_value);
    qDebug() << static_cast<unsigned char>(working_response.at(0)) << "  " << adc_value;
}
