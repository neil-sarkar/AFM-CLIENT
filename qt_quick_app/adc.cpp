#include "adc.h"
#include "command_node.h"
#include "constants.h"

ADC::ADC(qint8 id)
{
    m_id = id;
}

void ADC::update_value(double value) {
    if (value != m_value) {
        m_value = value;
        qDebug() << "Setting ADC" << m_id << "value to " << value;
        emit value_changed();
    }
}

double ADC::value() {
    return m_value;
}

void ADC::read() {
    cmd_read();
}

void ADC::cmd_read() {
    QByteArray payload;
    payload += m_id;
    CommandNode* node = new CommandNode(command_hash[ADC_Read], bind(&ADC::callback_read), payload);
    command_generated(node);
}

void ADC::callback_read(QByteArray return_bytes) {
    update_value(bytes_to_word(return_bytes.at(1), return_bytes.at(2)));
}

void ADC::init() {} // no initialization required for ADC


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
