#include "builder.h"
#include "afm.h"
#include "dac.h"
#include "adc.h"
#include "pga.h"
#include "serial_port.h"
#include "send_worker.h"
#include "receive_worker.h"

Builder::Builder() {}

AFM* Builder::build_afm() {
    // Create the collection of DACs
    QHash<int, AFMObject*> dac_collection;
    dac_collection[DAC::Buffered_1] = new DAC(DAC::Buffered_1);
    dac_collection[DAC::Buffered_2] = new DAC(DAC::Buffered_2);
    dac_collection[DAC::Board_2] = new DAC(DAC::Board_2);
    dac_collection[DAC::Z_Amplitude] = new DAC(DAC::Z_Amplitude);
    dac_collection[DAC::Board_1] = new DAC(DAC::Board_1);
    dac_collection[DAC::Buffered_3] = new DAC(DAC::Buffered_3);
    dac_collection[DAC::Z_Offset_Fine] = new DAC(DAC::Z_Offset_Fine);
    dac_collection[DAC::Y_1] = new DAC(DAC::Y_1);
    dac_collection[DAC::Z_Offset_Coarse] = new DAC(DAC::Z_Offset_Coarse);
    dac_collection[DAC::Y_2] = new DAC(DAC::Y_2);
    dac_collection[DAC::X_1] = new DAC(DAC::X_1);
    dac_collection[DAC::X_2] = new DAC(DAC::X_2);

    // Create the collection of ADC
    QHash<int, AFMObject*> adc_collection;
    adc_collection[ADC::X_1] = new ADC(ADC::X_1);
    adc_collection[ADC::X_2] = new ADC(ADC::X_2);
    adc_collection[ADC::Y_1] = new ADC(ADC::Y_1);
    adc_collection[ADC::Y_2] = new ADC(ADC::Y_2);
    adc_collection[ADC::Z] = new ADC(ADC::Z);
    adc_collection[ADC::Z_Piezoresistor_Amplitude] = new ADC(ADC::Z_Piezoresistor_Amplitude);
    adc_collection[ADC::Phase] = new ADC(ADC::Phase);

    // PGA
    QHash<int, AFMObject*> pga_collection;
    pga_collection[PGA::X_1] = new PGA(PGA::X_1);
    pga_collection[PGA::X_2] = new PGA(PGA::X_2);
    pga_collection[PGA::Y_1] = new PGA(PGA::Y_1);
    pga_collection[PGA::Y_2] = new PGA(PGA::Y_2);
    pga_collection[PGA::Z_Fine] = new PGA(PGA::Z_Fine);
    pga_collection[PGA::DDS_Amplitude] = new PGA(PGA::DDS_Amplitude);
    pga_collection[PGA::Z_Coarse] = new PGA(PGA::Z_Coarse);
    pga_collection[PGA::Leveling] = new PGA(PGA::Leveling);

    Motor* motor = new Motor();
    PID* pid = new PID();

    return new AFM(pga_collection, dac_collection, adc_collection, motor, pid);
}


void Builder::wire_hash_command_generated(QHash<int, AFMObject*> & collection, SendWorker* & send_worker) {
    QHash<int, AFMObject*>::iterator i;
    for (i = collection.begin(); i != collection.end(); ++i)
        QObject::connect(i.value(), SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
}

void Builder::wire(AFM* & afm, SerialPort* & serial_port, SendWorker* & send_worker, ReceiveWorker* & receive_worker) {
    // Wire command_generated signal
    // There is likely a cleaner way to connect all the command_generated SIGNALS to the enqueue_command SLOT as command_generated is inherited from AFMObject
    QObject::connect(afm->motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(afm->pid, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    wire_hash_command_generated(afm->ADC_collection, send_worker);
    wire_hash_command_generated(afm->DAC_collection, send_worker);
    wire_hash_command_generated(afm->PGA_collection, send_worker);

    // Misc connections
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect(serial_port, SIGNAL(connected()), afm, SLOT(init()));
}

