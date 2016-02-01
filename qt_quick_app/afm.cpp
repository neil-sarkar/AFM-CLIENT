#include "afm.h"
#include "dac.h"

AFM::AFM(QHash<QString, PGA*> PGA_collection, QHash<QString, DAC*> DAC_collection, QHash<QString, ADC*> ADC_collection, Motor* motor, PID* pid) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->pid = pid;

//    QHash<QString, DAC*>::iterator i;
//    for (i = DAC_collection.begin(); i != DAC_collection.end(); ++i)
//        QObject::connect(i.value(), SIGNAL(command_generated(CommandNode*)), this, SLOT(command_generated(CommandNode*)));
}
