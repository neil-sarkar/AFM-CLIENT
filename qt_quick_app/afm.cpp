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
}

void AFM::init() {
    // This method calls the init methods of all the members
    emit initializing();
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
}

AFM::callback_return_type AFM::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
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

bool AFM::launch_folder_picker() {
    QString path = QFileDialog::getExistingDirectory(0,"", m_save_folder);
    if (path.isEmpty()) {
        return false;
    }
    set_save_folder(path);
    return true;
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
