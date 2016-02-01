#include "afm.h"

AFM::AFM(QHash<QString, PGA*> PGA_collection, QHash<QString, DAC*> DAC_collection, QHash<QString, ADC*> ADC_collection, Motor* motor, PID* pid) {
    m_PGA_collection = PGA_collection;
    m_ADC_collection = ADC_collection;
    m_DAC_collection = DAC_collection;
    m_motor = motor;
    m_pid = pid;
}

