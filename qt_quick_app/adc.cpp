#include "adc.h"
#include "command_node.h"
#include "constants.h"

ADC::ADC(qint8 id)
{
    m_id = id;
}


void ADC::cmd_read() {
    QByteArray q;
    q += m_id;
    CommandNode* node = new CommandNode(command_hash[ADC_Read], this, q);
    command_generated(node);
}

void ADC::init() {} // no initialization required for ADC

const int ADC::X_1 = 3;
const int ADC::X_2 = 7;
const int ADC::Y_1 = 6;
const int ADC::Y_2 = 8;
const int ADC::Z = 2;
const int ADC::Z_Piezoresistor_Amplitude = 5;
const int ADC::Phase = 0;
