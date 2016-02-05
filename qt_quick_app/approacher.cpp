#include "approacher.h"
#include "constants.h"
#include "adc.h"

Approacher::Approacher()
{
    m_setpoint = 1.0; // to be loaded from settings
    m_state = 0;
}

void Approacher::init() {}

void Approacher::cmd_start_auto_approach() {
    quint16 scaled_setpoint = m_setpoint/ADC::SCALE_FACTOR;
    QByteArray payload;
    payload += (scaled_setpoint & 0xFF);
    payload += ((scaled_setpoint & 0xFF00) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Begin_Auto_Approach], payload));
}

void Approacher::cmd_stop_auto_approach() {
    emit command_generated(new CommandNode(command_hash[AFM_Stop_Auto_Approach]));
}
