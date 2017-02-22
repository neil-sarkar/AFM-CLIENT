#include "adc.h"
#include "command_node.h"
#include "constants.h"

ADC::ADC(qint8 id)
{
    m_id = id;
}

void ADC::update_value(double value , bool is_resistance) {
    m_value = value;
    qDebug() << "Setting ADC" << m_id << "value to " << value;
    if (is_resistance)
        emit new_resistance_value(voltage_resistance_equation(m_value, m_id));
    else
        emit value_changed(m_value);
}

double ADC::value() {
    return m_value;
}

void ADC::read() {
    cmd_read();
}

double ADC::voltage_resistance_equation(double voltage, qint8 id) {
    return (id == ADC_Z_1_ID) ? (0.05 / voltage * 200)*(0.05 / voltage * 200): (0.2 / voltage * 200); // not sure if we need this conditional
    // 200 is the gain on the amplifier
    // 0.2 is the 200 mV that we pass through the actuators in a get resistances
}

void ADC::cmd_read() {
    QByteArray payload;
    payload += m_id;
    CommandNode* node = new CommandNode(command_hash[ADC_Read], bind(&ADC::callback_read), payload);
    command_generated(node);
}

void ADC::callback_read(QByteArray return_bytes) {
    update_value(bytes_to_word(return_bytes.at(0), return_bytes.at(1)) * ADC::SCALE_FACTOR , false);
}

void ADC::init() {
    read();  
} // no hardware initialization required for ADC

bool ADC::is_actuator_connected(double voltage, quint8 id) {
    double resistance = voltage_resistance_equation(voltage, id);
    return Min_Resistance < resistance && Max_Resistance > resistance;
}

ADC::callback_return_type ADC::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}

const double ADC::MAX_VOLTAGE = 3.3;
const int ADC::RESOLUTION = 4095;
const double ADC::SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;
const double ADC::PHASE_SCALE_FACTOR = double(180.0*2.0/RESOLUTION);

const int ADC::ADC_Z_1_ID = 23;
const int ADC::Min_Resistance = 20;
const int ADC::Max_Resistance = 700;
const double ADC::SENSE_RESISTOR_AMPLIFIER_GAIN = 200;
const double ADC::RESISTANCE_SCALE_FACTOR_50MV = 0.05*SENSE_RESISTOR_AMPLIFIER_GAIN;
const double ADC::RESISTANCE_SCALE_FACTOR_200MV = 0.2*SENSE_RESISTOR_AMPLIFIER_GAIN;
const double ADC::LATERAL_MAX_RESISTANCE = 230;
const double ADC::LATERAL_MIN_RESISTANCE = 40;
const double ADC::Z_MAX_RESISTANCE = 400;
const double ADC::Z_MIN_RESISTANCE = 100;
