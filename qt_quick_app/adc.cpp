#include "adc.h"
#include "command_node.h"

ADC::ADC(qint8 id, QObject *parent)
{
    m_id = id;
}


void ADC::read() {
    QByteArray q;
    q += m_id;
    CommandNode* node = new CommandNode(0x63, this, q);
    command_generated(node);
}
