#include "afm.h"
#include "dac.h"
#include "afm_object.h"

AFM::AFM(QHash<QString, AFMObject*> PGA_collection, QHash<QString, AFMObject*> DAC_collection, QHash<QString, AFMObject*> ADC_collection, Motor* motor, PID* pid) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->pid = pid;
}
