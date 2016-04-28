#include "afm.h"
#include "dac.h"
#include "dds.h"
#include "adc.h"
#include "afm_object.h"
#include "constants.h"
#include "serial_port.h"
#include "assert.h"
#include "force_curve_generator.h"
#include <QFileDialog>
#include <QStateMachine>
#include <QFinalState>
#include "globals.h"

AFM::AFM(peripheral_collection PGA_collection, peripheral_collection DAC_collection, peripheral_collection ADC_collection, Motor* motor,  Sweeper* sweeper, Approacher* approacher, Scanner* scanner, ForceCurveGenerator* force_curve_generator) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->sweeper = sweeper;
    this->approacher = approacher;
    this->scanner = scanner;
    this->force_curve_generator = force_curve_generator;
    dac_table_page_count = 0;
}

void AFM::init() {
    // This method calls the init methods of all the members
    set_settings();
    is_initializing = true;
    peripheral_collection::iterator i;
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
    force_curve_generator->init();
    cmd_get_resistances();
}

void AFM::read_all_ADCs() {
    qDebug() << "Reading all ADCs";
    peripheral_collection ::iterator i;
    for (i = ADC_collection.begin(); i != ADC_collection.end(); ++i)
        static_cast<ADC*>(i.value())->read();
}

void AFM::cmd_get_resistances() {
    bool pid_enabled = this->scanner->pid->enabled();
    this->scanner->pid->set_disabled();
    emit command_generated(new CommandNode(command_hash[AFM_Get_Resistances], bind(&AFM::callback_get_resistances)));
    if (pid_enabled)
        this->scanner->pid->set_enabled();
}

void AFM::callback_get_resistances(QByteArray return_bytes) {
    if (is_initializing) {
        emit init_complete();
        is_initializing = false;
    }
    double x_1_voltage = bytes_to_word(return_bytes.at(0), return_bytes.at(1)) * ADC::SCALE_FACTOR;
    double x_2_voltage = bytes_to_word(return_bytes.at(2), return_bytes.at(3)) * ADC::SCALE_FACTOR;
    double y_1_voltage = bytes_to_word(return_bytes.at(4), return_bytes.at(5)) * ADC::SCALE_FACTOR;
    double y_2_voltage = bytes_to_word(return_bytes.at(6), return_bytes.at(7)) * ADC::SCALE_FACTOR;
    double z_voltage = bytes_to_word(return_bytes.at(8), return_bytes.at(9)) * ADC::SCALE_FACTOR;
    static_cast<ADC*>(ADC_collection["x_1"])->update_value(x_1_voltage);
    static_cast<ADC*>(ADC_collection["x_2"])->update_value(x_2_voltage);
    static_cast<ADC*>(ADC_collection["y_1"])->update_value(y_1_voltage);
    static_cast<ADC*>(ADC_collection["y_2"])->update_value(y_2_voltage);
    static_cast<ADC*>(ADC_collection["z_1"])->update_value(z_voltage);

    if (ADC::is_actuator_connected(z_voltage) && ADC::is_actuator_connected(x_1_voltage) && ADC::is_actuator_connected(y_1_voltage)) {
        emit chip_mounted_ok();
    }
//    else
//        cmd_get_resistances();
}

AFM::callback_return_type AFM::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

void AFM::set_dac_table() {
    // This method gets recalled in callback_set_dac_table
    // We can't simply queue up all of these commands because
    // that would be too many bytes for the MCU to handle at once
    // Therefore, we have to string together these commands only after one has completely executed
    emit setting_dac_table();
//    qDebug() << "Setting dac table";
//    if (dac_table_page_count < 16) {
//        cmd_set_dac_table(dac_table_page_count);
//    } else {
//        dac_table_page_count = 0; // after writing 16 pages to the flash, we're done.
        emit dac_table_set();
//    }
}

void AFM::callback_set_dac_table(QByteArray buffer) {
    assert(static_cast<unsigned char>(buffer.at(0)) == AFM_Success_Response); // ensure that the previous dac table page was successfully set
    dac_table_page_count += 1;
    set_dac_table();
}

void AFM::cmd_set_dac_table(int block_number) {
//    QByteArray payload;
//    int start_byte_index = block_number * AFM::DAC_Table_Block_Size;
//    for (int i = start_byte_index; i < start_byte_index + AFM::DAC_Table_Block_Size; i++) {
//        auto value = DAC_Table_Values[i];
//        payload += (value & 0xFF);
//        payload += ((value & 0x0F00) >> 8);
//    }
//    emit command_generated(new CommandNode(command_hash[AFM_Set_Dac_Table], bind(&AFM::callback_set_dac_table), payload));
}

void AFM::restore_defaults() {
    peripheral_collection::iterator i;
    settings.clear();
    scanner->set_settings();
    scanner->pid->set_settings();
    for (i = DAC_collection.begin(); i != DAC_collection.end(); ++i)
        i.value()->set_settings();
    for (i = PGA_collection.begin(); i != PGA_collection.end(); ++i)
        i.value()->set_settings();
}

void AFM::launch_folder_picker() {
    QString path = QFileDialog::getExistingDirectory(0,"", m_save_folder);
    if (!path.isEmpty())
        set_save_folder(path);
}

QString AFM::save_folder() {
    return m_save_folder;
}

void AFM::set_save_folder(QString save_folder) {
    if (m_save_folder != save_folder) {
        m_save_folder = save_folder;
        qDebug() << "Setting save folder to " << m_save_folder;
        emit save_folder_changed(m_save_folder);
        update_settings(settings_group_name, "save_folder", QVariant(m_save_folder));
    }
}

void AFM::save_scan_data() {
    scanner->save_raw_data(m_save_folder);
}

void AFM::save_force_curve_data() {
    force_curve_generator->save_raw_data(m_save_folder);
}

void AFM::set_settings() {
    settings.beginGroup(settings_group_name);
    set_save_folder(settings.contains("save_folder") ? settings.value("save_folder").toString() : QCoreApplication::applicationDirPath());
    settings.endGroup();
}

void AFM::release_port() {
    mutex.lock();
    port_writing_command = false;
    mutex.unlock();
}

const int AFM::DAC_Table_Block_Size = 256;
const QString AFM::settings_group_name = "afm";
