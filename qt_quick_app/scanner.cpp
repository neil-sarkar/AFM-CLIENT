#include "scanner.h"
#include "QFinalState"
#include <QHistoryState>
#include <QTemporaryFile>
#include <QtConcurrent>
#include <QTextStream>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QTimer>
#include "scan_data.h"
#include "constants.h"
#include "adc.h"


Scanner::Scanner(PID* pid_, AFMObject* dac_fine_z_)
{
    pid = pid_;
    fine_z = static_cast<DAC*>(dac_fine_z_);
    m_should_pause = false;
    connect(&watcher_fo, SIGNAL(finished()), this, SLOT(handleFinished_fo()));
    connect(&watcher_ro, SIGNAL(finished()), this, SLOT(handleFinished_ro()));
    connect(&watcher_fp, SIGNAL(finished()), this, SLOT(handleFinished_fp()));
    connect(&watcher_rp, SIGNAL(finished()), this, SLOT(handleFinished_rp()));
    connect(&watcher_fe, SIGNAL(finished()), this, SLOT(handleFinished_fe()));
    connect(&watcher_re, SIGNAL(finished()), this, SLOT(handleFinished_re()));
}

void Scanner::handleFinished_fo() {
    emit new_forward_offset_data(watcher_fo.future());
}

void Scanner::handleFinished_ro() {
    emit new_reverse_offset_data(watcher_ro.future());
}
void Scanner::handleFinished_fp() {
    emit new_forward_phase_data(watcher_fp.future());
}
void Scanner::handleFinished_rp() {
    emit new_reverse_phase_data(watcher_rp.future());
}
void Scanner::handleFinished_fe() {
    emit new_forward_error_data(watcher_fe.future());
}
void Scanner::handleFinished_re() {
    emit new_reverse_error_data(watcher_re.future());
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


void Scanner::start_state_machine() {
    m_state_machine.start();
}

void Scanner::initialize_scan_state_machine() {
    // Old code used to set PGAs here, but we really don't need to - they should already have been set
    qDebug() << "Initializing";
    m_should_pause = false;
    scanning_forward = true;
    m_x_index = -1;
    m_y_index = -1;
    emit scanner_initialization_done();

    if (fwd_offset_data != NULL)  {
        delete fwd_offset_data;
        delete fwd_phase_data;
        delete fwd_error_data;
        delete rev_offset_data;
        delete rev_phase_data;
        delete rev_error_data;
    }

    fwd_offset_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio());
    fwd_phase_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio());
    fwd_error_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio());
    rev_offset_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio());
    rev_phase_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio());
    rev_error_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio());
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

    if (m_x_index < m_num_columns - 1 || m_y_index < m_num_rows - 1) {
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
    if (fwd_offset_data->size() == 0)
        return true;
    if (scanning_forward && (fwd_offset_data->size() % m_num_columns) == 0)
        return false;
    if (!scanning_forward && (rev_offset_data->size() % m_num_columns) == 0)
        return true;
    return scanning_forward;
}

void Scanner::callback_step_scan(QByteArray payload) {
    // Data comes back as amplitude  low, amplitude high, offset low, offset high, phase low, phase high

    receive_data();
    double z_amplitude, z_offset, z_phase;

    for (int i = 0; i < payload.size(); i += 6) { // 6 bytes passed back

        m_x_index = (m_x_index + 1) % (m_num_columns * 2);
        if (m_x_index == 0)
            m_y_index += 1;

        z_amplitude = bytes_to_word(payload.at(i), payload.at(i + 1));
        z_offset = bytes_to_word(payload.at(i + 2), payload.at(i + 3));
        z_phase = bytes_to_word(payload.at(i + 4), payload.at(i + 5));

        if (scanning_forward) {
            fwd_offset_data->append(m_x_index, m_y_index, z_offset);
            fwd_phase_data->append(m_x_index, m_y_index, z_phase);
            fwd_error_data->append(m_x_index, m_y_index, pid->setpoint() / ADC::SCALE_FACTOR - z_amplitude);
        } else {
            int x_coord = 2 * m_num_columns - m_x_index - 1;
            rev_offset_data->append(x_coord, m_y_index, z_offset);
            rev_phase_data->append(x_coord, m_y_index, z_phase);
            rev_error_data->append(x_coord, m_y_index, pid->setpoint() / ADC::SCALE_FACTOR - z_amplitude);
        }
        // This condition checks to see if we should send data (should be every line)
         if (rev_offset_data->size() == fwd_offset_data->size() && rev_offset_data->size() % m_num_columns == 0) { // TODO: check this condition

             QFuture<QString> future = QtConcurrent::run(this->fwd_offset_data, &ScanData::generate_png);
             watcher_fo.setFuture(future);
             future = QtConcurrent::run(this->rev_offset_data, &ScanData::generate_png);
             watcher_ro.setFuture(future);
             future = QtConcurrent::run(this->fwd_phase_data, &ScanData::generate_png);
             watcher_fp.setFuture(future);
             future = QtConcurrent::run(this->rev_phase_data, &ScanData::generate_png);
             watcher_rp.setFuture(future);
             future = QtConcurrent::run(this->fwd_error_data, &ScanData::generate_png);
             watcher_fe.setFuture(future);
             future = QtConcurrent::run(this->rev_error_data, &ScanData::generate_png);
             watcher_re.setFuture(future);

             emit new_offset_line_profile(get_latest_line_profile(fwd_offset_data, rev_offset_data));
             emit new_phase_line_profile(get_latest_line_profile(fwd_phase_data, rev_phase_data));
             emit new_error_line_profile(get_latest_line_profile(fwd_error_data, rev_error_data));
         }
        scanning_forward = is_scanning_forward();
    }
}

QVariantList Scanner::get_latest_line_profile(ScanData* fwd, ScanData* rev) {
    QVariantList flat_data;
    flat_data += fwd->get_latest_line();
    flat_data += rev->get_latest_line();
    return flat_data;
}

void Scanner::end_scan_state_machine() {
    m_should_pause = false;
    qDebug() << "scanning done";
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
    set_send_back_count(m_num_columns);
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
    if (!fwd_offset_data)
        return;

//        QString folder_path = save_folder + "/" + m_base_file_name + "_"  + QString::number(QDateTime::currentMSecsSinceEpoch());
//        QDir().mkdir(folder_path);
//        QList<QString> specific_file_names;
//        QList<QString> full_paths;
//        specific_file_names << "offset forward" << "phase forward" << "error forward" << "offset reverse" << "phase reverse" << "error reverse";
//        for (int i = 0; i < specific_file_names.length(); i++) {
//            QFile file(folder_path + "/" + m_base_file_name + " " + specific_file_names[i]);
//            if (file.open(QIODevice::WriteOnly)) {
//                qDebug() << "file created" << file.fileName();
//                full_paths.append(file.fileName());
//            } else {
//                qDebug() << "File failed to create file: " << specific_file_names[i];
//            }
//        }

//        for (int i = 0; i < full_paths.length(); i++) {
//            ScanData* data_container = i < 3 ? forward_data : reverse_data;
//            QFile file(full_paths[i]);
//            if (file.open(QIODevice::Append)) {
//                QTextStream out(&file);   // we will serialize the data into the file
//                for (int j = 0; j < data_container->size(); j++) {
//                    out << QString::number(data_container->data[j].x) << " ";
//                    out << QString::number(data_container->data[j].y) << " ";
//                    switch(i % 3) {
//                        case 0:
//                             out << QString::number(data_container->data[j].z_offset);
//                            break;
//                        case 1:
//                            out << QString::number(data_container->data[j].z_phase);
//                            break;
//                        case 2:
//                            out << QString::number(data_container->data[j].z_error);
//                    }
//                    out << "\n";
//                }
//            }
//        }
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
