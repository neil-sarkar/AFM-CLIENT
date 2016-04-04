#include "scanner.h"
#include "QFinalState"
#include <QHistoryState>
#include <QTemporaryFile>
#include <QTextStream>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QTimer>
#include "constants.h"
#include "adc.h"


Scanner::Scanner(PID* pid_, AFMObject* dac_fine_z_)
{
    pid = pid_;
    scanning_forward = true;
    fine_z = static_cast<DAC*>(dac_fine_z_);
    m_should_pause = false;
}

void Scanner::pause_state_machine() {
    m_should_pause = true;
}

void Scanner::resume_state_machine() {
    m_should_pause = false;
    receive_data();
}

void Scanner::set_settings() {
    settings.beginGroup(settings_group_name);
    set_num_averages(settings.contains("num_averages") ? settings.value("num_averages").toInt() : 5);
    set_send_back_count(settings.contains("send_back_count") ? settings.value("send_back_count").toInt() : 32);
    set_dwell_time(settings.contains("dwell_time") ? settings.value("dwell_time").toInt() : 2);
    set_num_columns(settings.contains("num_columns") ? settings.value("num_columns").toInt() : 16);
    set_num_rows(settings.contains("num_rows") ? settings.value("num_rows").toInt() : 16);
    set_rms_threshold(settings.contains("rms_threshold") ? settings.value("rms_threshold").toInt() : 1.5);
    set_ratio(settings.contains("ratio") ? settings.value("ratio").toInt() : 4);
    set_base_file_name(settings.contains("base_file_name") ? settings.value("base_file_name").toString() : "scan");
    set_leveling_direction(settings.contains("leveling_direction") ? settings.value("leveling_direction").toChar() : 'f');
    settings.endGroup();
}

void Scanner::init() {
    // set up state machine framework

    //TODO: add a waiting for data state
    QState* running_state = new QState();
    QState* initialize_machine = new QState(running_state);
    QState* set_signal_generator = new QState(running_state);
    QState* receive_data = new QState(running_state);
    QFinalState* finish = new QFinalState();

    initialize_machine->addTransition(this, SIGNAL(scanner_initialization_done()), set_signal_generator);
    set_signal_generator->addTransition(this, SIGNAL(set_signal_generator_done()), receive_data);
    receive_data->addTransition(this, SIGNAL(all_data_received()), finish);
    running_state->addTransition(this, SIGNAL(reset()), finish);

    QObject::connect(initialize_machine, SIGNAL(entered()), this, SLOT(initialize_scan_state_machine()));
    QObject::connect(set_signal_generator, SIGNAL(entered()), this, SLOT(set_signal_generator()));
    QObject::connect(receive_data, SIGNAL(entered()), this, SLOT(receive_data()));
    QObject::connect(finish, SIGNAL(entered()), this, SLOT(end_scan_state_machine()));

    m_state_machine.addState(running_state);
    running_state->setInitialState(initialize_machine);
    m_state_machine.addState(finish);
    m_state_machine.setInitialState(running_state);

    set_settings();
    move_to_starting_point();
}

void Scanner::move_to_starting_point() {
    cmd_set_signal_generator();
    cmd_start_scan();
}

void Scanner::emit_dummy_data() {
    emit started_scan_state_machine();
    QVariantList data;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            data.append(i);
            data.append(j);
            data.append(i*j);
        }
    }
    emit new_offset_data(data);
    // emit new_phase_data(data);
    // emit new_error_data(data);
    return;
}

void Scanner::start_state_machine() {
    m_state_machine.start();
}

void Scanner::initialize_scan_state_machine() {
    // Old code used to set PGAs here, but we really don't need to - they should already have been set
    qDebug() << "Initializing";
    m_should_pause = false;
    emit scanner_initialization_done();
    forward_data = new ScanData(m_num_rows, m_num_columns, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(), true);
    reverse_data = new ScanData(m_num_rows, m_num_columns, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(), false);
}

void Scanner::set_signal_generator() {
    cmd_set_signal_generator();
    cmd_start_scan();
    emit set_signal_generator_done();
}

void Scanner::receive_data() {
    if (m_should_pause) {
        return;
    }

    if (!(forward_data->is_full() && reverse_data->is_full())) {
         cmd_step_scan();
    }
    else {
        emit all_data_received();
    }
}

void Scanner::cmd_step_scan() {
    CommandNode* node = new CommandNode(command_hash[AFM_Step_Scan], bind(&Scanner::callback_step_scan));
    node->num_receive_bytes = Num_Meta_Data_Bytes + m_send_back_count * 6; // 6 bytes per step - two for each type of Z, multiplies by 2 for fwd and rev
    emit command_generated(node);
}

bool Scanner::is_scanning_forward() {
    if (scanning_forward && (forward_data->size() % m_num_columns) == 0)
        return false;
    if (!scanning_forward && (reverse_data->size() % m_num_columns) == 0)
        return true;
    return scanning_forward;
}

void Scanner::callback_step_scan(QByteArray payload) {
    // Data comes back as amplitude  low, amplitude high, offset low, offset high, phase low, phase high
    double z_amplitude, z_offset, z_phase;
    for (int i = 0; i < payload.size(); i += 6) { // 6 bytes passed back
        z_amplitude = bytes_to_word(payload.at(i), payload.at(i + 1));
        z_offset = bytes_to_word(payload.at(i + 2), payload.at(i + 3));
        z_phase = bytes_to_word(payload.at(i + 4), payload.at(i + 5));
        if (scanning_forward) {
            forward_data->append(z_amplitude, z_offset, z_phase, pid->setpoint() / ADC::SCALE_FACTOR);
        } else {
            reverse_data->append(z_amplitude, z_offset, z_phase, pid->setpoint() / ADC::SCALE_FACTOR);
        }
        if (reverse_data->size() > 0 && reverse_data->size() % m_send_back_count == 0) {
            QVariantList offset_data = forward_data->package_data_for_ui(m_send_back_count, 0); // TODO: ENUM the 0,1,2
            offset_data.append(reverse_data->package_data_for_ui(m_send_back_count, 0));
            emit new_offset_data(offset_data);

            QVariantList phase_data = forward_data->package_data_for_ui(m_send_back_count, 1);
            phase_data.append(reverse_data->package_data_for_ui(m_send_back_count, 1));
            emit new_phase_data(phase_data);

            QVariantList error_data = forward_data->package_data_for_ui(m_send_back_count, 2);
            error_data.append(reverse_data->package_data_for_ui(m_send_back_count, 2));
            emit new_error_data(error_data);
        }
        scanning_forward = is_scanning_forward();
        m_num_columns_received += 1;
    }
    receive_data();
}

void Scanner::end_scan_state_machine() {
    m_should_pause = false;
    qDebug() << "scanning done" << m_num_columns_received;
    // forward_data->print();
    move_to_starting_point();
}

quint8 Scanner::num_averages() {
    return m_num_averages;
}

void Scanner::set_num_averages(int num_averages) {
    m_num_averages = num_averages;
    qDebug() << "Changing num averages to " << m_num_averages;
    emit num_averages_changed(m_num_averages);
    update_settings(settings_group_name, "num_averages", QVariant(m_num_averages));
    cmd_set_num_averages();
}

void Scanner::cmd_set_num_averages() {
    QByteArray payload;
    payload += m_num_averages;
    emit command_generated(new CommandNode(command_hash[Scanner_Set_Num_Averages], payload));
}

quint16 Scanner::send_back_count() {
    return m_send_back_count;
}

void Scanner::set_send_back_count(int send_back_count) {
    m_send_back_count = send_back_count;
    qDebug() << "Changing send back count to " << m_send_back_count;
    emit send_back_count_changed(static_cast<int>(m_send_back_count));
    update_settings(settings_group_name, "send_back_count", QVariant(m_send_back_count));
    cmd_set_send_back_count();
}

quint16 Scanner::num_rows() {
    return m_num_rows;
}

void Scanner::set_num_rows(int num_rows) {
    m_num_rows = num_rows;
    qDebug() << "Changing num rows to " << m_num_rows;
    emit num_rows_changed(static_cast<int>(m_num_rows));
    update_settings(settings_group_name, "num_rows", QVariant(m_num_rows));
    set_send_back_count(m_num_rows);
    cmd_set_signal_generator();
}

quint16 Scanner::num_columns() {
    return m_num_columns;
}

void Scanner::set_num_columns(int num_columns) {
    m_num_columns = num_columns;
    qDebug() << "Changing num columns to " << m_num_columns;
    emit num_columns_changed(static_cast<int>(m_num_columns));
    update_settings(settings_group_name, "num_columns", QVariant(m_num_columns));
    cmd_set_signal_generator();
}

double Scanner::rms_threshold() {
    return m_rms_threshold;
}

void Scanner::set_rms_threshold(double rms_threshold) {
    m_rms_threshold = rms_threshold;
    qDebug() << "Changing RMS threshold to " << m_rms_threshold;
    update_settings(settings_group_name, "rms_threshold", QVariant(m_rms_threshold));
    emit rms_threshold_changed(m_rms_threshold);
}

QChar Scanner::leveling_direction() {
    return m_leveling_direction;
}

void Scanner::set_leveling_direction(QChar leveling_direction) {
    m_leveling_direction = leveling_direction;
    qDebug() << "Changing leveling direction to " << m_leveling_direction;
    update_settings(settings_group_name, "leveling_direction", QVariant(m_leveling_direction));
    emit leveling_direction_changed(m_leveling_direction);
    cmd_set_leveling_direction();
}

void Scanner::cmd_set_send_back_count() {
    QByteArray payload;
    payload += (m_send_back_count & 0xFF); // low byte
    payload += ((m_send_back_count & 0xFF00) >> 8); // high byte
    emit command_generated(new CommandNode(command_hash[Scanner_Set_Send_Back_Count], payload));
}

quint8 Scanner::dwell_time() {
    return m_dwell_time;
}

void Scanner::set_dwell_time(int dwell_time) {
    m_dwell_time = dwell_time;
    qDebug() << "Changing dwell time to " << m_dwell_time;
    emit dwell_time_changed(m_dwell_time);
    update_settings(settings_group_name, "dwell_time", QVariant(m_dwell_time));
    cmd_set_dwell_time();
}

int Scanner::ratio() {
    return m_ratio;
}

void Scanner::set_ratio(int ratio) {
    m_ratio = ratio;
    qDebug() << "Changing ratio to " << m_ratio;
    emit ratio_changed(m_ratio);
    update_settings(settings_group_name, "ratio", QVariant(m_ratio));
    cmd_set_signal_generator();
}

void Scanner::cmd_set_signal_generator() {
    QByteArray payload;
    payload += m_ratio;
    payload += (m_num_columns & 0xFF); //num points
    payload += ((m_num_columns & 0x0F00) >> 8);
    payload += (m_num_rows & 0xFF); //num lines
    payload += ((m_num_rows & 0x0F00) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Set_Signal_Generation],  payload));
}

void Scanner::cmd_start_scan() {
    emit command_generated(new CommandNode(command_hash[AFM_Start_Scan]));
}

void Scanner::cmd_set_dwell_time() {
    QByteArray payload;
    payload += m_dwell_time;
    emit command_generated(new CommandNode(command_hash[Scanner_Set_Dwell_Time], payload));
}

void Scanner::cmd_set_leveling_direction() {
    QByteArray payload;
    payload += m_leveling_direction;
    emit command_generated (new CommandNode(command_hash[Scanner_Set_Leveling_Direction], payload));
}

void Scanner::save_raw_data(QString save_folder) {
    QString folder_path = save_folder + "/" + m_base_file_name + "_"  + QString::number(QDateTime::currentMSecsSinceEpoch());
    QDir().mkdir(folder_path);
    QList<QString> specific_file_names;
    QList<QString> full_paths;
    specific_file_names << "offset forward" << "phase forward" << "error forward" << "offset reverse" << "phase reverse" << "error reverse";
    for (int i = 0; i < specific_file_names.length(); i++) {
        QFile file(folder_path + "/" + m_base_file_name + " " + specific_file_names[i]);
        if (file.open(QIODevice::WriteOnly)) {
            qDebug() << "file created" << file.fileName();
            full_paths.append(file.fileName());
        } else {
            qDebug() << "File failed to create file: " << specific_file_names[i];
        }
    }

    if (!forward_data)
        return;

    for (int i = 0; i < forward_data->size(); i++) {
        for (int j = 0; j < full_paths.length() / 2; j++) {
            QFile file(full_paths[j]);
            if (file.open(QIODevice::Append)) {
                QTextStream out(&file);   // we will serialize the data into the file
                out << QString::number(forward_data->data[i].x) << " ";
                out << QString::number(forward_data->data[i].y) << " ";
                switch(j) {
                    case 0:
                         out << QString::number(forward_data->data[i].z_offset);
                        break;
                    case 1:
                        out << QString::number(forward_data->data[i].z_phase);
                        break;
                    case 2:
                        out << QString::number(forward_data->data[i].z_error);
                }
                out << "\n";
            }
        }
    }

    for (int i = 0; i < reverse_data->size(); i++) {
        for (int j = full_paths.length() / 2; j < full_paths.length(); j++) {
            QFile file(full_paths[j]);
            if (file.open(QIODevice::Append)) {
                QTextStream out(&file);   // we will serialize the data into the file
                out << QString::number(reverse_data->data[i].x) << " ";
                out << QString::number(reverse_data->data[i].y) << " ";
                switch(j) {
                    case 3:
                         out << QString::number(reverse_data->data[i].z_offset);
                        break;
                    case 4:
                        out << QString::number(reverse_data->data[i].z_phase);
                        break;
                    case 5:
                        out << QString::number(reverse_data->data[i].z_error);
                }
                out << "\n";
            }
        }
    }
}

Scanner::callback_return_type Scanner::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

int Scanner::get_delta_x_from_ratio() {
    // should enum the scan ratios
    switch (m_ratio) {
        case 1:
            return 1;
        case 2:
            return 1;
        case 3:
            return 3;
        case 4:
            return 7;
    }
}

int Scanner::get_delta_y_from_ratio() {
    // should enum the scan ratios
    switch (m_ratio) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 1;
        case 4:
            return 1;
    }
}

QString Scanner::base_file_name() {
    return m_base_file_name;
}

void Scanner::set_base_file_name(QString base_file_name) {
    m_base_file_name = base_file_name;
    qDebug() << "Setting base file name to " << m_base_file_name;
    emit base_file_name_changed(m_base_file_name);
    update_settings(settings_group_name, "base_file_name", QVariant(m_base_file_name));
}

const QString Scanner::settings_group_name = "scanner";
