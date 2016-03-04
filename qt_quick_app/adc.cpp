#include "adc.h"
#include "command_node.h"
#include "constants.h"

ADC::ADC(qint8 id)
{
    m_id = id;
}

void ADC::update_value(double value) {
    m_value = value;
    qDebug() << "Setting ADC" << m_id << "value to " << value;
    emit value_changed(m_value);
    emit new_resistance_value(voltage_resistance_equation(m_value));
}

double ADC::value() {
    return m_value;
}

void ADC::read() {
    cmd_read();
}

double ADC::voltage_resistance_equation(double voltage) {
    return 0.2 / voltage * 200;
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
    update_value(bytes_to_word(return_bytes.at(1), return_bytes.at(2)) * ADC::SCALE_FACTOR);
}

void ADC::init() {
    read();  
} // no hardware initialization required for ADC

bool ADC::is_actuator_connected(double voltage) {
    double resistance = voltage_resistance_equation(voltage);
    return Min_Resistance < resistance && Max_Resistance > resistance;
}

ADC::callback_return_type ADC::bind(callback_type method) {
    // If keeping the instance alive by the time the command is called becomes an issue, use the trick showed in this post:
    // http://stackoverflow.com/questions/9281172/how-do-i-write-a-pointer-to-member-function-with-stdfunction
    return std::bind(method, this, std::placeholders::_1);
}


const int ADC::X_1 = 3;
const int ADC::X_2 = 7;
const int ADC::Y_1 = 6;
const int ADC::Y_2 = 8;
const int ADC::Z = 2;
const int ADC::Z_Piezoresistor_Amplitude = 5;
const int ADC::Phase = 0;

const double ADC::MAX_VOLTAGE = 2.5;
const int ADC::RESOLUTION = 4095;
const double ADC::SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;

const int ADC::Min_Resistance = 20;
const int ADC::Max_Resistance = 500
        ;
