#include "afm.h"
#include "dac.h"
#include "dds.h"
#include "adc.h"
#include "afm_object.h"
#include "constants.h"
#include "serial_port.h"
#include "assert.h"
#include <QStateMachine>
#include <QFinalState>

AFM::AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, PID* pid, Sweeper* sweeper, Approacher* approacher) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->pid = pid;
    this->sweeper = sweeper;
    this->approacher = approacher;
    dac_table_page_count = 0;
}

void AFM::init() {
    // This method calls the init methods of all the members

    QHash<int, AFMObject*>::iterator i;
    for (i = DAC_collection.begin(); i != DAC_collection.end(); ++i)
        i.value()->init();
    for (i = ADC_collection.begin(); i != ADC_collection.end(); ++i)
        i.value()->init();
    for (i = PGA_collection.begin(); i != PGA_collection.end(); ++i)
        i.value()->init();

    motor->init();
    pid->init();
    sweeper->init();
    approacher->init();
    scan_state_machine_setup();
    set_dac_table();
}

AFM::callback_return_type AFM::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

void AFM::scan_state_machine_setup() {
    // set up framework
    QState* initialize_machine = new QState();
    QState* set_dac_table = new QState();
    QState* set_signal_generator = new QState();
    QState* receive_data = new QState();
    QFinalState* finish = new QFinalState();

    initialize_machine->addTransition(this, SIGNAL(scanner_initialization_done()), set_dac_table);
    set_dac_table->addTransition(this, SIGNAL(set_dac_table_done()), set_signal_generator);
    set_signal_generator->addTransition(this, SIGNAL(set_signal_generator_done()), receive_data);
    receive_data->addTransition(this, SIGNAL(all_data_received), finish);

    QObject::connect(initialize_machine, SIGNAL(entered()), this, SLOT(initialize_scan_state_machine()));
    QObject::connect(set_dac_table, SIGNAL(entered()), this, SLOT(set_dac_table()));
    QObject::connect(set_signal_generator, SIGNAL(entered()), this, SLOT(set_signal_generator()));
    QObject::connect(receive_data, SIGNAL(entered()), this, SLOT(receive_data()));

    m_scan_state_machine.addState(initialize_machine);
    m_scan_state_machine.addState(set_dac_table);
    m_scan_state_machine.addState(set_signal_generator);
    m_scan_state_machine.addState(receive_data);
    m_scan_state_machine.setInitialState(initialize_machine);
}

void AFM::initialize_scan_state_machine() {
    // Old code used to set PGAs here, but we really don't need to - they should already have been set
    pid->set_enabled();
}

void AFM::set_dac_table() {
    // This method gets recalled in callback_set_dac_table
    // We can't simply queue up all of these commands because
    // that would be too many bytes for the MCU to handle at once
    // Therefore, we have to string together these commands only after one has completely executed
    if (dac_table_page_count < 16)
        cmd_set_dac_table(dac_table_page_count);
    else
        dac_table_page_count = 0; // after writing 16 pages to the flash, we're done.

}

void AFM::set_signal_generator() {

}

void AFM::receive_data() {

}

void AFM::cmd_set_dac_table(int block_number) {
    QByteArray payload;
    int start_byte_index = block_number * AFM::DAC_Table_Block_Size;
    for (int i = start_byte_index; i < start_byte_index + AFM::DAC_Table_Block_Size; i++) {
        auto value = DAC_Table_Values[i];
        payload += (value & 0xFF);
        payload += ((value & 0x0F00) >> 8);
    }
    emit command_generated(new CommandNode(command_hash[AFM_Set_Dac_Table], bind(&AFM::callback_set_dac_table), payload));
}

void AFM::callback_set_dac_table(QByteArray buffer) {
    assert(static_cast<unsigned char>(buffer.at(0)) == AFM_Success_Response); // ensure that the previous dac table page was successfully set
    dac_table_page_count += 1;
    set_dac_table();
}


const int AFM::DAC_Table_Block_Size = 256;
