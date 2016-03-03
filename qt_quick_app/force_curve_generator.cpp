#include "force_curve_generator.h"
#include "adc.h"
#include "constants.h"

ForceCurveGenerator::ForceCurveGenerator() : Initial_Z(2500), Step_Size(5)
{
}

void ForceCurveGenerator::init() {
}

void ForceCurveGenerator::clear_buffers() {
    m_approaching_amplitude.clear();
    m_approaching_phase.clear();
    m_retracting_amplitude.clear();
    m_retracting_phase.clear();
}

void ForceCurveGenerator::cmd_generate_force_curve() {
    emit command_generated(new CommandNode(command_hash[AFM_Generate_Force_Curve], bind(&ForceCurveGenerator::callback_generate_force_curve)));
}

void ForceCurveGenerator::callback_generate_force_curve(QByteArray return_bytes) {
    clear_buffers();
    int half_resp_length = return_bytes.length() / 2;
    for (int i = 0; i < half_resp_length; i += 4) {
        QVariant z_value = double(Initial_Z - Step_Size * i/4) / ADC::RESOLUTION;
        m_approaching_amplitude.append(z_value);
        m_approaching_amplitude.append(bytes_to_word(return_bytes.at(i), return_bytes.at(i+1)) * ADC::SCALE_FACTOR);
        m_approaching_phase.append(z_value);
        m_approaching_phase.append(bytes_to_word(return_bytes.at(i+2), return_bytes.at(i+3)) * ADC::SCALE_FACTOR);

        int j = half_resp_length + i;
        z_value = double(Step_Size * i/4) / ADC::RESOLUTION;
        m_retracting_amplitude.append(z_value);
        m_retracting_amplitude.append(bytes_to_word(return_bytes.at(j), return_bytes.at(j+1)) * ADC::SCALE_FACTOR);
        m_retracting_phase.append(z_value);
        m_retracting_phase.append(bytes_to_word(return_bytes.at(j+2), return_bytes.at(j+3)) * ADC::SCALE_FACTOR);
    }
    emit new_approaching_amplitude_data(m_approaching_amplitude);
    emit new_approaching_phase_data(m_approaching_phase);
    emit new_retracting_amplitude_data(m_retracting_amplitude);
    emit new_retracting_phase_data(m_retracting_phase);
}

ForceCurveGenerator::callback_return_type ForceCurveGenerator::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}
