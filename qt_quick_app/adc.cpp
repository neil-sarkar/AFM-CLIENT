#include "adc.h"
#include "command_node.h"

ADC::ADC(qint8 id)
{
    m_id = id;
}


void ADC::read() {
    QByteArray q;
    q += m_id;
    CommandNode* node = new CommandNode(READ_COMMAND, this, q);
    command_generated(node);
}
