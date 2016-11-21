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
    set_check_resistances(true);
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

void AFM::generate_get_resistances_command(callback_type method) {
    bool pid_enabled = this->scanner->pid->enabled();
    this->scanner->pid->set_disabled();
    emit command_generated(new CommandNode(command_hash[AFM_Get_Resistances], bind(method)));
    if (pid_enabled)
        this->scanner->pid->set_enabled();
}

bool AFM::check_resistance_values(QByteArray return_bytes) {
    bool resistance_ok = true;
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

    const double x_1_resistance = ADC::RESISTANCE_SCALE_FACTOR_200MV/x_1_voltage;
    const double x_2_resistance = ADC::RESISTANCE_SCALE_FACTOR_200MV/x_2_voltage;
    const double y_1_resistance = ADC::RESISTANCE_SCALE_FACTOR_200MV/y_1_voltage;
    const double y_2_resistance = ADC::RESISTANCE_SCALE_FACTOR_200MV/y_2_voltage;
    const double z_resistance = ADC::RESISTANCE_SCALE_FACTOR_50MV/z_voltage;
    const bool x_1_issue = (x_1_resistance > ADC::LATERAL_MAX_RESISTANCE) || (x_1_resistance < ADC::LATERAL_MIN_RESISTANCE);
    const bool x_2_issue = (x_2_resistance > ADC::LATERAL_MAX_RESISTANCE) || (x_2_resistance < ADC::LATERAL_MIN_RESISTANCE);
    const bool y_1_issue = (y_1_resistance > ADC::LATERAL_MAX_RESISTANCE) || (y_1_resistance < ADC::LATERAL_MIN_RESISTANCE);
    const bool y_2_issue = (y_2_resistance > ADC::LATERAL_MAX_RESISTANCE) || (y_2_resistance < ADC::LATERAL_MIN_RESISTANCE);
    const bool z_issue = (z_resistance > ADC::Z_MAX_RESISTANCE) || (z_resistance < ADC::Z_MIN_RESISTANCE);

    if(x_1_issue || x_2_issue || y_1_issue || y_2_issue || z_issue){
            // various thresholds
            resistance_ok = false;
            qDebug() << "No device or broken device Error";
            emit no_device_or_broken_device_error();
    }
    return resistance_ok;
}

void AFM::scanner_start_state_machine_initial_checks() {
    qDebug() << "Start scanner state machine with check resistance " << m_check_resistances;
    if(m_check_resistances)
        generate_get_resistances_command(&AFM::callback_scanner_start_state_machine_initial_checks);
    else
        emit scanner_start_state_machine_checks_done(true);

}

void AFM::callback_scanner_start_state_machine_initial_checks(QByteArray return_bytes) {
    emit scanner_start_state_machine_checks_done(check_resistance_values(return_bytes));
}

void AFM::auto_sweep_initial_checks() {
    qDebug() << "Start auto sweep with check resistance " << m_check_resistances;
    if(m_check_resistances)
        generate_get_resistances_command(&AFM::callback_auto_sweep_initial_checks);
    else
        emit auto_sweep_checks_done(true);
}

void AFM::callback_auto_sweep_initial_checks(QByteArray return_bytes) {
    check_resistance_values(return_bytes);
    emit auto_sweep_checks_done(true);
}

void AFM::start_approaching_initial_checks() {
    qDebug() << "Start approaching with check resistance " << m_check_resistances;
    if(m_check_resistances)
        generate_get_resistances_command(&AFM::callback_start_approaching_initial_checks);
    else
        emit start_approaching_checks_done(true);
}

void AFM::callback_start_approaching_initial_checks(QByteArray return_bytes) {
    emit start_approaching_checks_done(check_resistance_values(return_bytes));
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
    if (path.isEmpty()) {
        return;
    }
    set_save_folder(path);
}

QString AFM::save_folder() {
    return m_save_folder;
}

void AFM::set_save_folder(QString save_folder) {
    m_save_folder = save_folder;
    qDebug() << "Setting save folder to " << m_save_folder;
    emit save_folder_changed(m_save_folder);
    update_settings(settings_group_name, "save_folder", QVariant(m_save_folder));
}

QString AFM::save_scan_data() {
    QString status_message = scanner->save_data(m_save_folder);
    return status_message;
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

bool AFM::check_resistances() {
    return m_check_resistances;
}

void AFM::set_check_resistances(bool check) {
    m_check_resistances = check;
    qDebug() << "Setting check_resistances to " << m_check_resistances;
    emit check_resistances_changed(m_check_resistances);
}

const int AFM::DAC_Table_Block_Size = 256;
const QString AFM::settings_group_name = "afm";
