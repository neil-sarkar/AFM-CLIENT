#include "afm.h"

AFM::AFM(QHash<QString, PGA*> PGA_collection, QHash<QString, DAC*> DAC_collection, QHash<QString, ADC*> ADC_collection, Motor* motor, PID* pid) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->pid = pid;
}
