#include "afm.h"
#include "dac.h"
#include "afm_object.h"
#include "serial_port.h"

AFM::AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, PID* pid) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->pid = pid;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(init()));
}

void AFM::start() {
    timer->start(1);
}

void AFM::init() {
    // This method calls the init methods of all the members
//    QHash<int, AFMObject*>::iterator i;

//    for (int i = 0; i < 242; i++) {
    for (int i = 0; i < 1; i++)
        motor->cmd_single_step();

//    }



//    for (i = DAC_collection.begin(); i != DAC_collection.end(); ++i)
//        i.value()->init();
//    for (i = ADC_collection.begin(); i != ADC_collection.end(); ++i)
//        i.value()->init();
//    for (i = PGA_collection.begin(); i != PGA_collection.end(); ++i)
//        i.value()->init();

//    motor->init();
//    pid->init();
}
