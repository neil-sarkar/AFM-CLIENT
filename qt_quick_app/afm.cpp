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

AFM::AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor,  Sweeper* sweeper, Approacher* approacher, Scanner* scanner) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->sweeper = sweeper;
    this->approacher = approacher;
    this->scanner = scanner;
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
    sweeper->init();
    approacher->init();
    scanner->init();
}

AFM::callback_return_type AFM::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

void AFM::set_dac_table() {
    // This method gets recalled in callback_set_dac_table
    // We can't simply queue up all of these commands because
    // that would be too many bytes for the MCU to handle at once
    // Therefore, we have to string together these commands only after one has completely executed
    if (dac_table_page_count < 16) {
        cmd_set_dac_table(dac_table_page_count);
    } else {
        dac_table_page_count = 0; // after writing 16 pages to the flash, we're done.
        emit dac_table_set();
    }
}

void AFM::callback_set_dac_table(QByteArray buffer) {
    assert(static_cast<unsigned char>(buffer.at(0)) == AFM_Success_Response); // ensure that the previous dac table page was successfully set
    dac_table_page_count += 1;
    set_dac_table();
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

void AFM::cmd_generate_force_curve() {
    emit command_generated(new CommandNode(command_hash[AFM_Generate_Force_Curve], bind(&AFM::callback_generate_force_curve)));
}

void AFM::callback_generate_force_curve(QByteArray return_bytes) {
    qDebug() << return_bytes;
}

const int AFM::DAC_Table_Block_Size = 256;
