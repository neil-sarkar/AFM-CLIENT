#include "force_curve_generator.h"
#include "adc.h"
#include "constants.h"

ForceCurveGenerator::ForceCurveGenerator()
{}

void ForceCurveGenerator::init() {
}

void ForceCurveGenerator::cmd_generate_force_curve() {
    emit command_generated(new CommandNode(command_hash[AFM_Generate_Force_Curve], bind(&ForceCurveGenerator::callback_generate_force_curve)));
}

void ForceCurveGenerator::callback_generate_force_curve(QByteArray return_bytes) {
    QVariantList approaching_amplitude, approaching_phase, retracting_amplitude, retracting_phase;
    int initial_z = 2500;
    int step_size = 5;
    int half_resp_length = return_bytes.length() / 2;
    for (int i = 0; i < half_resp_length; i += 4) {
        QVariant z_value = double(initial_z - step_size * i/4) / ADC::RESOLUTION;
        approaching_amplitude.append(z_value);
        approaching_amplitude.append(bytes_to_word(return_bytes.at(i), return_bytes.at(i+1)) * ADC::SCALE_FACTOR);
        approaching_phase.append(z_value);
        approaching_phase.append(bytes_to_word(return_bytes.at(i+2), return_bytes.at(i+3)) * ADC::SCALE_FACTOR);

        int j = half_resp_length + i;
        z_value = double(step_size * i/4) / ADC::RESOLUTION;
        retracting_amplitude.append(z_value);
        retracting_amplitude.append(bytes_to_word(return_bytes.at(j), return_bytes.at(j+1)) * ADC::SCALE_FACTOR);
        retracting_phase.append(z_value);
        retracting_phase.append(bytes_to_word(return_bytes.at(j+2), return_bytes.at(j+3)) * ADC::SCALE_FACTOR);
    }
    emit new_approaching_amplitude_data(approaching_amplitude);
    emit new_approaching_phase_data(approaching_phase);
    emit new_retracting_amplitude_data(retracting_amplitude);
    emit new_retracting_phase_data(retracting_phase);
}

ForceCurveGenerator::callback_return_type ForceCurveGenerator::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}
