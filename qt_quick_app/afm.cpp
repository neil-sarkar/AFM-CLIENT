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
    this->m_firmware_version = "";
    this->m_mcu_bin_file = "";
    this->m_setting_lock = true;
    this->network_manager = new QNetworkAccessManager(this);
    connect(network_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(contact_server_reply(QNetworkReply*)));
    contact_server();
}

AFM::~AFM() {
    delete this->network_manager;
}

void AFM::init() {
    // This method calls the init methods of all the members
    emit initializing();
    cmd_get_firmware_version();
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

QString AFM::get_firmware_version() {
    return m_firmware_version;
}

bool AFM::setting_lock() {
    return m_setting_lock;
}

void AFM::toggle_setting_lock(){
    m_setting_lock = !m_setting_lock;
    emit setting_lock_toggled(m_setting_lock);
}

void AFM::read_all_ADCs() {
    qDebug() << "Reading all ADCs";
    peripheral_collection ::iterator i;
    for (i = ADC_collection.begin(); i != ADC_collection.end(); ++i)
        static_cast<ADC*>(i.value())->read();
}

void AFM::cmd_get_firmware_version() {
    emit command_generated(new CommandNode(command_hash[AFM_Get_Firmware_Version], bind(&AFM::callback_get_firmware_version)));
}

void AFM::callback_get_firmware_version(QByteArray return_bytes) {
    quint8 version_0 = return_bytes.at(0);
    quint8 version_1 = return_bytes.at(1);
    quint8 version_2 = return_bytes.at(2);
    quint8 version_3 = return_bytes.at(3);
    QString version_string = QString("%1.%2.%3.%4").arg(QString::number(version_0),QString::number(version_1),QString::number(version_2),QString::number(version_3));
    qDebug() << "Firware Version is " << version_string;
    m_firmware_version = version_string;
    emit new_firmware_version(version_string);
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

void AFM::choose_mcu_bin(){
    //not a setting yet, dunno about use case.
    QString file = QFileDialog::getOpenFileName(0,
                                                tr("Select Firmware Binary"),
                                                QDir::homePath(),
                                                "Binaries (*.bin)");
    if (file.isEmpty()){
        return;
    }
    m_mcu_bin_file = file;
    emit mcu_bin_changed(m_mcu_bin_file);
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

QString AFM::mcu_bin_file(){
    return m_mcu_bin_file;
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

void AFM::contact_server() {
    if(network_manager->networkAccessible() == QNetworkAccessManager::Accessible) {
        QNetworkRequest request;
        request.setUrl(QUrl("http://35.164.23.41/gui_update_check.py"));
        request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
        network_manager->get(request);
    } else {
        emit network_error();
    }
}

void AFM::contact_server_reply(QNetworkReply * reply) {
    reply->deleteLater();
    if(reply->error() == QNetworkReply::NoError){
        QByteArray raw_data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(raw_data);
        QJsonObject json_obj = doc.object();
        emit new_server_data(doc.toVariant());
        emit new_server_message(json_obj["message"].toString());
        qDebug() << "Server Message " << json_obj["message"].toString();
        qDebug() << "Network Reply " << (QString) raw_data;
    } else {
        qDebug() << "Network Error " << reply->error();
        emit network_error();
    }
}

QString AFM::get_software_version() {
    return Software_Version;
}

void AFM::push_to_AFM(QString message){
    emit push_message_to_NM(message);
}

void AFM::boot_loader_entered() {
    emit push_message_to_NM(QString("Bootloader Entered."));
}

const int AFM::DAC_Table_Block_Size = 256;
const QString AFM::settings_group_name = "afm";
