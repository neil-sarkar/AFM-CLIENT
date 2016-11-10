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
    m_last_row = false;
    fwd_offset_data = NULL;
    fwd_phase_data = NULL;
    fwd_error_data = NULL;
    rev_offset_data = NULL;
    rev_phase_data = NULL;
    rev_error_data = NULL;
    m_z_actuator_scale_factor = 1.0;
    m_x_actuator_scale_factor = 1.0;
    m_y_actuator_scale_factor = 1.0;
    m_x_offset = 0.0;
    m_y_offset = 0.0;
    m_zoom_scale = 1.0;

    connect(&watcher_fo, SIGNAL(finished()), this, SLOT(handleFinished_fo()));
    connect(&watcher_ro, SIGNAL(finished()), this, SLOT(handleFinished_ro()));
    connect(&watcher_fp, SIGNAL(finished()), this, SLOT(handleFinished_fp()));
    connect(&watcher_rp, SIGNAL(finished()), this, SLOT(handleFinished_rp()));
    connect(&watcher_fe, SIGNAL(finished()), this, SLOT(handleFinished_fe()));
    connect(&watcher_re, SIGNAL(finished()), this, SLOT(handleFinished_re()));
}

void Scanner::handleFinished_fo() {
    QVariantList result = watcher_fo.future().result();
    emit new_forward_offset_data(result);

    current_fwd_offset_line_profile.clear();
    int y = result[0].toInt(); //index of new line
    for(int x = 0; x < m_num_columns; x++) {
        current_fwd_offset_line_profile.append(x_index_in_um(x));
        current_fwd_offset_line_profile.append(y);
        if(m_use_level)
            current_fwd_offset_line_profile.append(z_fine_dac_to_nm(fwd_offset_data->leveled_lines[y][x]));
        else
            current_fwd_offset_line_profile.append(z_fine_dac_to_nm(fwd_offset_data->raw_data[y]->data[x]));
    }
    QVariant minimum = z_fine_dac_to_nm(DAC::RESOLUTION);
    for (int i = 2; i < current_fwd_offset_line_profile.size(); i += 3) {
        if (current_fwd_offset_line_profile[i] < minimum) {
            minimum = current_fwd_offset_line_profile[i];
        }
    }
    for (int i = 2; i < current_fwd_offset_line_profile.size(); i += 3) {
        current_fwd_offset_line_profile[i] = current_fwd_offset_line_profile[i].toDouble() - minimum.toDouble();
    }
    emit new_forward_offset_profile(current_fwd_offset_line_profile);
    handle_last_line_process_complete();
}

void Scanner::handleFinished_ro() {
    QVariantList result = watcher_ro.future().result();
    emit new_reverse_offset_data(result);

    current_rev_offset_line_profile.clear();
    int y = result[0].toInt(); //index of new line
    for(int x = 0; x < m_num_columns; x++) {
        current_rev_offset_line_profile.append(x_index_in_um(x));
        current_rev_offset_line_profile.append(y);
        if(m_use_level)
            current_rev_offset_line_profile.append(z_fine_dac_to_nm(rev_offset_data->leveled_lines[y][x]));
        else
            current_rev_offset_line_profile.append(z_fine_dac_to_nm(rev_offset_data->raw_data[y]->data[x]));
    }
    QVariant minimum = z_fine_dac_to_nm(DAC::RESOLUTION);
    for (int i = 2; i < current_rev_offset_line_profile.size(); i += 3) {
        if (current_rev_offset_line_profile[i] < minimum) {
            minimum = current_rev_offset_line_profile[i];
        }
    }
    for (int i = 2; i < current_rev_offset_line_profile.size(); i += 3) {
        current_rev_offset_line_profile[i] = current_rev_offset_line_profile[i].toDouble() - minimum.toDouble();
    }
    emit new_reverse_offset_profile(current_rev_offset_line_profile);
    handle_last_line_process_complete();
}

void Scanner::handleFinished_fp() {
    emit new_forward_phase_data(watcher_fp.future().result());
    handle_last_line_process_complete();
}

void Scanner::handleFinished_rp() {
    emit new_reverse_phase_data(watcher_rp.future().result());
    handle_last_line_process_complete();
}

void Scanner::handleFinished_fe() {
    emit new_forward_error_data(watcher_fe.future().result());
    handle_last_line_process_complete();
}

void Scanner::handleFinished_re() {
    emit new_reverse_error_data(watcher_re.future().result());
    handle_last_line_process_complete();
}

void Scanner::handle_last_line_process_complete(){
    if(m_last_row && check_all_watchers_finish()) {
        qDebug() << "All processing done for image";
        m_last_row = false;
        emit all_processing_done();
    }
}

bool Scanner::check_all_watchers_finish(){
    return watcher_fo.isFinished() && watcher_ro.isFinished() && \
            watcher_fp.isFinished() && watcher_rp.isFinished() && \
              watcher_fe.isFinished() && watcher_re.isFinished();
}

void Scanner::update_z_actuator_scale_factor(double fine_z_pga_value) {
    m_z_actuator_scale_factor = fine_z_pga_value / 20.0;
}

void Scanner::update_x_actuator_scale_factor(double fine_x_1_pga_value) {
    m_x_actuator_scale_factor = fine_x_1_pga_value * fine_x_1_pga_value * 0.0001;
}

void Scanner::update_y_actuator_scale_factor(double fine_y_1_pga_value) {
    m_y_actuator_scale_factor = fine_y_1_pga_value * fine_y_1_pga_value * 0.0001;
}

void Scanner::pause_state_machine() {
    m_should_pause = true;
    record_metadata();
}

void Scanner::resume_state_machine() {
    m_should_pause = false;
    receive_data();
}

void Scanner::set_settings() {
    settings.beginGroup(settings_group_name);
    set_num_averages(settings.contains("num_averages") ? settings.value("num_averages").toInt() : 5);
    set_send_back_count(settings.contains("send_back_count") ? settings.value("send_back_count").toInt() : 256);
    set_dwell_time(settings.contains("dwell_time") ? settings.value("dwell_time").toInt() : 50);
    set_num_columns(settings.contains("num_columns") ? settings.value("num_columns").toInt() : 256);
    set_num_rows(settings.contains("num_rows") ? settings.value("num_rows").toInt() : 256);
    set_rms_threshold(settings.contains("rms_threshold") ? settings.value("rms_threshold").toInt() : 1.5);
    set_ratio(settings.contains("ratio") ? settings.value("ratio").toInt() : 4);
    set_base_file_name(settings.contains("base_file_name") ? settings.value("base_file_name").toString() : "scan");
    set_leveling_direction(settings.contains("leveling_direction") ? settings.value("leveling_direction").toChar() : 'f');
    set_save_format(settings.contains("save_format") ? settings.value("save_format").toInt() : gsf);
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
    m_last_row = false;
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

    fwd_offset_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(),"nm", true, z_fine_dac_to_nm(1));
    fwd_phase_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(),"deg", false, 1);
    fwd_error_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(),"V", false, 1);
    rev_offset_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(),"nm", true, z_fine_dac_to_nm(1));
    rev_phase_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(),"deg", false, 1);
    rev_error_data = new ScanData(m_num_columns, m_num_rows, m_ratio, get_delta_x_from_ratio(), get_delta_y_from_ratio(),"V", false, 1);
}

void Scanner::set_signal_generator() {
    cmd_set_signal_generator();
    cmd_start_scan();
    emit set_signal_generator_done();
}

bool Scanner::receive_data() {
    bool last_line = false;
    if (m_should_pause) {
        return last_line;
    }

    if (m_x_index < m_num_columns - 1 || m_y_index < m_num_rows - 1) {
         is_scanning = true;
         cmd_step_scan();
    }
    else {
        record_metadata();
        emit all_data_received();
        last_line = true;
        qDebug() << "Forward Offset";
        fwd_offset_data->print();
        qDebug() << "Forward Phase";
        fwd_phase_data->print();
        qDebug() << "Forward Error";
        fwd_error_data->print();
    }
    return last_line;
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

void Scanner::fetch_line_profiles(int y, int y_averages) {
    if (!rev_error_data || !rev_error_data->is_full()) {
        // don't do this unless the scan is finished
        return;
    }
    // sanitize input
    if (y_averages < 1) y_averages = 1;
    // find limits
    int y_start = y - (y_averages+1)/2;
    int y_end = y + y_averages/2;
    // sanitize limits
    if (y_start < 0) y_start = 0;
    if (y_end > m_num_rows - 1) y_end = m_num_rows - 1;
    // recalculate number of averages
    y_averages = y_end - y_start + 1;

    current_fwd_offset_line_profile.clear();
    current_fwd_error_line_profile.clear();
    current_fwd_phase_line_profile.clear();
    current_rev_offset_line_profile.clear();
    current_rev_error_line_profile.clear();
    current_rev_phase_line_profile.clear();

    for (int x = 0; x < m_num_columns; x++) {
        current_fwd_offset_line_profile.append(x_index_in_um(x));
        current_fwd_error_line_profile.append(x_index_in_um(x));
        current_fwd_phase_line_profile.append(x_index_in_um(x));
        current_rev_offset_line_profile.append(x_index_in_um(x));
        current_rev_error_line_profile.append(x_index_in_um(x));
        current_rev_phase_line_profile.append(x_index_in_um(x));

        current_fwd_offset_line_profile.append(y);
        current_fwd_error_line_profile.append(y);
        current_fwd_phase_line_profile.append(y);
        current_rev_offset_line_profile.append(y);
        current_rev_error_line_profile.append(y);
        current_rev_phase_line_profile.append(y);

        point acc[6] = {0};
        for (int yy = y_start; yy <= y_end; yy++) {
            if(m_use_level)
            {
                acc[0] += fwd_offset_data->leveled_lines[yy][x];
                acc[3] += rev_offset_data->leveled_lines[yy][x];
            }
            else
            {
                acc[0] += fwd_offset_data->raw_data[yy]->data[x];
                acc[3] += rev_offset_data->raw_data[yy]->data[x];
            }
            acc[1] += fwd_error_data->raw_data[yy]->data[x];
            acc[2] += fwd_phase_data->raw_data[yy]->data[x];
            acc[4] += rev_error_data->raw_data[yy]->data[x];
            acc[5] += rev_phase_data->raw_data[yy]->data[x];
        }
        current_fwd_offset_line_profile.append(z_fine_dac_to_nm(acc[0]/y_averages));
        current_fwd_error_line_profile.append(acc[1]/y_averages);
        current_fwd_phase_line_profile.append(acc[2]/y_averages);
        current_rev_offset_line_profile.append(z_fine_dac_to_nm(acc[3]/y_averages));
        current_rev_error_line_profile.append(acc[4]/y_averages);
        current_rev_phase_line_profile.append(acc[5]/y_averages);
    }
    normalize_offset_line_profiles();

    emit new_forward_offset_profile(current_fwd_offset_line_profile);
    emit new_forward_error_profile(current_fwd_error_line_profile);
    emit new_forward_phase_profile(current_fwd_phase_line_profile);
    emit new_reverse_offset_profile(current_rev_offset_line_profile);
    emit new_reverse_error_profile(current_rev_error_line_profile);
    emit new_reverse_phase_profile(current_rev_phase_line_profile);
}

void Scanner::fetch_latest_offset_profiles()
{
    int y_fwd = current_fwd_offset_line_profile[1].toInt();
    int y_rev = current_rev_offset_line_profile[1].toInt();
    qDebug() << "fetch latest " << y_fwd << " " << y_rev;
    current_fwd_offset_line_profile.clear();
    current_rev_offset_line_profile.clear();
    for (int x = 0; x < m_num_columns; x++) {
        current_fwd_offset_line_profile.append(x);
        current_rev_offset_line_profile.append(x);

        current_fwd_offset_line_profile.append(y_fwd);
        current_rev_offset_line_profile.append(y_rev);

        if(m_use_level)
        {
            current_fwd_offset_line_profile.append(z_fine_dac_to_nm(fwd_offset_data->leveled_lines[y_fwd][x]));
            current_rev_offset_line_profile.append(z_fine_dac_to_nm(rev_offset_data->leveled_lines[y_rev][x]));
        }
        else
        {
            current_fwd_offset_line_profile.append(z_fine_dac_to_nm(fwd_offset_data->raw_data[y_fwd]->data[x]));
            current_rev_offset_line_profile.append(z_fine_dac_to_nm(rev_offset_data->raw_data[y_rev]->data[x]));
        }
    }
    normalize_offset_line_profiles();
    emit new_forward_offset_profile(current_fwd_offset_line_profile);
    emit new_reverse_offset_profile(current_rev_offset_line_profile);
}

void Scanner::zoom(float x, float y, float size) {
    m_x_offset += x*m_zoom_scale;
    m_y_offset += y*m_zoom_scale;
    m_zoom_scale *= size;
    cmd_set_zoom();
}

void Scanner::reset_zoom() {
    m_x_offset = 0.0;
    m_y_offset = 0.0;
    m_zoom_scale = 1.0;
    cmd_set_zoom();
}

void Scanner::callback_step_scan(QByteArray payload) {
    // Data comes back as amplitude  low, amplitude high, offset low, offset high, phase low, phase high

    bool last_line = receive_data();
    double z_amplitude, z_offset, z_phase, z_error, z_offset_nm;
    qDebug() << "Processing LINE" << m_y_index;
    for (int i = 0; i < payload.size(); i += 6) { // 6 bytes passed back per point

        m_x_index = (m_x_index + 1) % (m_num_columns * 2);
        if (m_x_index == 0) {
            m_y_index += 1;
            //current_fwd_offset_line_profile.clear();
            current_fwd_error_line_profile.clear();
            current_fwd_phase_line_profile.clear();
            //current_rev_offset_line_profile.clear();
            current_rev_error_line_profile.clear();
            current_rev_phase_line_profile.clear();
        }

        z_amplitude = bytes_to_word(payload.at(i), payload.at(i + 1));
        z_offset = bytes_to_word(payload.at(i + 2), payload.at(i + 3));
        z_phase = 0x8000 - bytes_to_word(payload.at(i + 4), payload.at(i + 5));
        z_error = pid->setpoint() / ADC::SCALE_FACTOR - z_amplitude;
        z_offset_nm = z_fine_dac_to_nm(z_offset);

        if (scanning_forward) {
            fwd_offset_data->append(m_x_index, m_y_index, z_offset);
            fwd_phase_data->append(m_x_index, m_y_index, z_phase);
            fwd_error_data->append(m_x_index, m_y_index, z_error);
            /*current_fwd_offset_line_profile.append(x_index_in_um(m_x_index));
            current_fwd_offset_line_profile.append(m_y_index);
            current_fwd_offset_line_profile.append(z_offset_nm);*/
            current_fwd_phase_line_profile.append(x_index_in_um(m_x_index));
            current_fwd_phase_line_profile.append(m_y_index);
            current_fwd_phase_line_profile.append(z_phase);
            current_fwd_error_line_profile.append(x_index_in_um(m_x_index));
            current_fwd_error_line_profile.append(m_y_index);
            current_fwd_error_line_profile.append(z_error);
        } else {
            int x_coord = 2 * m_num_columns - m_x_index - 1;
            rev_offset_data->append(x_coord, m_y_index, z_offset);
            rev_phase_data->append(x_coord, m_y_index, z_phase);
            rev_error_data->append(x_coord, m_y_index, z_error);
            /*current_rev_offset_line_profile.prepend(z_offset_nm);
            current_rev_offset_line_profile.prepend(m_y_index);
            current_rev_offset_line_profile.prepend(x_index_in_um(x_coord));*/
            current_rev_phase_line_profile.prepend(z_phase);
            current_rev_phase_line_profile.prepend(m_y_index);
            current_rev_phase_line_profile.prepend(x_index_in_um(x_coord));
            current_rev_error_line_profile.prepend(z_error);
            current_rev_error_line_profile.prepend(m_y_index);
            current_rev_error_line_profile.prepend(x_index_in_um(x_coord));
        }
        scanning_forward = is_scanning_forward();
    }
    // This condition checks to see if we should send data (should be after every line is done - fwd and rev)
    if (rev_offset_data->size() == fwd_offset_data->size() && rev_offset_data->size() % m_num_columns == 0) {
        m_last_row = m_y_index == (m_num_rows - 1);
        QFuture<QVariantList> future;
        if(!watcher_fo.isRunning() || last_line) {
            future = QtConcurrent::run(this->fwd_offset_data, &ScanData::generate_all,m_y_index);
            watcher_fo.setFuture(future);
            //emit new_forward_offset_profile(current_fwd_offset_line_profile);
        }
        if(!watcher_ro.isRunning() || last_line) {
            future = QtConcurrent::run(this->rev_offset_data, &ScanData::generate_all,m_y_index);
            watcher_ro.setFuture(future);
            //emit new_reverse_offset_profile(current_rev_offset_line_profile);
        }
        if(!watcher_fp.isRunning() || last_line) {
            future = QtConcurrent::run(this->fwd_phase_data, &ScanData::generate_all,m_y_index);
            watcher_fp.setFuture(future);
            emit new_forward_phase_profile(current_fwd_phase_line_profile);
        }
        if(!watcher_rp.isRunning() || last_line) {
            future = QtConcurrent::run(this->rev_phase_data, &ScanData::generate_all,m_y_index);
            watcher_rp.setFuture(future);
            emit new_reverse_phase_profile(current_rev_phase_line_profile);
        }
        if(!watcher_fe.isRunning() || last_line) {
            future = QtConcurrent::run(this->fwd_error_data, &ScanData::generate_all,m_y_index);
            watcher_fe.setFuture(future);
            emit new_forward_error_profile(current_fwd_error_line_profile);
        }
        if(!watcher_re.isRunning() || last_line) {
            future = QtConcurrent::run(this->rev_error_data, &ScanData::generate_all,m_y_index);
            watcher_re.setFuture(future);
            emit new_reverse_error_profile(current_rev_error_line_profile);
        }
    }
}

void Scanner::end_scan_state_machine() {
    m_should_pause = false;
    qDebug() << "scanning done";
    move_to_starting_point();
}

void Scanner::record_metadata() {
    completed_scan_metadata.num_columns = m_num_columns;
    completed_scan_metadata.num_rows = m_num_rows;
    completed_scan_metadata.dwell_time = m_dwell_time;
    completed_scan_metadata.x_range_m = x_range_in_m();
    completed_scan_metadata.y_range_m = y_range_in_m();
    completed_scan_metadata.x_offset_m = x_offset_in_m();
    completed_scan_metadata.y_offset_m = y_offset_in_m();
    completed_scan_metadata.scan_completion_time = QDateTime::currentDateTime().toString();
    completed_scan_metadata.z_actuator_scale_factor = m_z_actuator_scale_factor;
}

quint16 Scanner::num_averages() {
    return m_num_averages;
}

void Scanner::set_use_level(bool use_level) {
    m_use_level = use_level;
    qDebug() << "Use_level: " << use_level;
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
    qDebug() << m_ratio;
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

quint16 Scanner::dwell_time() {
    return m_dwell_time;
}

void Scanner::set_dwell_time(int dwell_time) {
    m_dwell_time = dwell_time;
    qDebug() << "Changing dwell time to " << m_dwell_time;
    emit dwell_time_changed(m_dwell_time);
    update_settings(settings_group_name, "dwell_time", QVariant(m_dwell_time));
    cmd_set_dwell_time();
}

int Scanner::save_format() {
    return m_save_format;
}

void Scanner::set_save_format(int format) {
    m_save_format = ((format >= 0) && (format < SAVE_FORMAT_COUNT))? format: gsf;
    qDebug() << "Changing save format to " << m_save_format;
    emit save_format_changed((int)m_save_format);
    update_settings(settings_group_name, "save_format", QVariant(m_save_format));
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

void Scanner::cmd_set_zoom() {
    QByteArray payload;
    quint16 x1 = qBound(0.f, m_x_offset, 1.f) * UINT16_MAX;
    quint16 y1 = qBound(0.f, m_y_offset, 1.f) * UINT16_MAX;
    quint16 x2 = qBound(m_x_offset, m_x_offset + m_zoom_scale, 1.f) * UINT16_MAX;
    quint16 y2 = qBound(m_y_offset, m_y_offset + m_zoom_scale, 1.f) * UINT16_MAX;
    payload += (x1 & 0xFF);
    payload += ((x1 & 0xFF00) >> 8);
    payload += (y1 & 0xFF);
    payload += ((y1 & 0xFF00) >> 8);
    payload += (x2 & 0xFF);
    payload += ((x2 & 0xFF00) >> 8);
    payload += (y2 & 0xFF);
    payload += ((y2 & 0xFF00) >> 8);
    emit command_generated (new CommandNode(command_hash[Scanner_Set_Zoom], payload));
}

QString Scanner::save_data(QString save_folder) {
    Q_UNUSED(save_folder);
    if (!fwd_offset_data)
        return "Nothing to save";
    QRegExp rx("^[\\w\\-\\s]+$");
    if(!rx.exactMatch(m_base_file_name))
        return "Invalid file name base, please use: A-Z,a-z,0-9, ,-,_";
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch());

    // Save in subfolders
    //QString folder_path = save_folder + "/" + m_base_file_name + "_"  + timestamp;
    //QDir().mkdir(folder_path);

    // Save in same folder
    QString folder_path = save_folder;
    switch(static_cast<Save_Format>(m_save_format)) {
        case gsf:
            save_raw_data_gsf(folder_path,timestamp);
        break;
        case xyz:
            save_raw_data_xyz(folder_path,timestamp);
        break;
        default:
            save_raw_data_gsf(folder_path,timestamp);
        break;
    }

    if(m_save_png)
        save_png_data(folder_path,timestamp);
    return "Save success";
}

void Scanner::save_raw_data_gsf(QString folder_path, QString timestamp) {
    QList<QString> specific_file_names;
    QList<QString> full_paths;
    QList<ScanData*> scan_data;
    specific_file_names << "offset forward" << "phase forward" << "error forward" << "offset reverse" << "phase reverse" << "error reverse";
    scan_data << fwd_offset_data << fwd_phase_data << fwd_error_data << rev_offset_data << rev_phase_data << rev_error_data;
    for (int i = 0; i < specific_file_names.length(); i++) {
        QFile file(folder_path + "/" + m_base_file_name + " " + specific_file_names[i] + " " + timestamp + ".gsf");
        if (file.open(QIODevice::WriteOnly)) {
            qDebug() << "file created" << file.fileName();
            full_paths.append(file.fileName());
        } else {
            qDebug() << "File failed to create file: " << specific_file_names[i];
        }
    }

    int x_scale = completed_scan_metadata.num_rows/completed_scan_metadata.num_columns;
    int y_scale = completed_scan_metadata.num_columns/completed_scan_metadata.num_rows;
    if (x_scale == 0) x_scale = 1;
    if (y_scale == 0) y_scale = 1;

    for (int i = 0; i < full_paths.length(); i++) {
        ScanData* data_container = scan_data[i];
        QFile file(full_paths[i]);
        if (file.open(QIODevice::Append)) {
            // Serialize header data
            QTextStream outtxt(&file);
            outtxt << "Gwyddion Simple Field 1.0\n";
            outtxt << "XRes = " << QString::number(completed_scan_metadata.num_columns) << "\n";
            outtxt << "YRes = " << QString::number(completed_scan_metadata.num_rows) << "\n";
            outtxt << "XReal = " << QString::number(completed_scan_metadata.x_range_m) << "\n";
            outtxt << "YReal = " << QString::number(completed_scan_metadata.y_range_m) << "\n";
            outtxt << "XOffset = " << QString::number(completed_scan_metadata.x_offset_m) << "\n";
            outtxt << "YOffset = " << QString::number(completed_scan_metadata.y_offset_m) << "\n";
            outtxt << "XYUnits = m\n";
            switch (specific_file_names[i][0].unicode()) {
                case 'o':
                    outtxt << "ZUnits = m\n";
                break;
                case 'p':
                    outtxt << "ZUnits = deg\n";
                break;
                case 'e':
                    outtxt << "ZUnits = V\n";
                break;
            }
            outtxt << "Title = " << m_base_file_name << " " << specific_file_names[i] << " " << timestamp << "\n";
            outtxt << "Date = " << completed_scan_metadata.scan_completion_time << "\n";
            outtxt << "DwellTime = " << QString::number(completed_scan_metadata.dwell_time) << "\n";
            outtxt.flush();

            // Serialize binary data
            QDataStream outraw(&file);
            outraw.setFloatingPointPrecision(QDataStream::SinglePrecision);
            outraw.setByteOrder(QDataStream::LittleEndian);
            outraw.writeRawData("\0\0\0\0", 4 - (file.pos()%4));
            for (int y = 0; y < completed_scan_metadata.num_rows; y++) {
                for (int x = 0; x < data_container->raw_data[y]->size; x++) {
                    if (specific_file_names[i][0] == 'o') {
                        // this is an offset. save value in meters
                        outraw << z_fine_dac_to_nm(data_container->raw_data[y]->data[x], completed_scan_metadata.z_actuator_scale_factor) * 1e-9;
                    } else {
                        outraw << data_container->raw_data[y]->data[x] * DAC::SCALE_FACTOR;
                    }
                }
            }
        }
    }
}

void Scanner::save_raw_data_xyz(QString folder_path, QString timestamp) {
    QList<QString> specific_file_names;
    QList<QString> full_paths;
    QList<ScanData*> scan_data;
    specific_file_names << "offset forward" << "phase forward" << "error forward" << "offset reverse" << "phase reverse" << "error reverse";
    scan_data << fwd_offset_data << fwd_phase_data << fwd_error_data << rev_offset_data << rev_phase_data << rev_error_data;
    for (int i = 0; i < specific_file_names.length(); i++) {
        QFile file(folder_path + "/" + m_base_file_name + " " + specific_file_names[i] + " " + timestamp + ".tsv");
        if (file.open(QIODevice::WriteOnly)) {
            qDebug() << "file created" << file.fileName();
            full_paths.append(file.fileName());
        } else {
            qDebug() << "File failed to create file: " << specific_file_names[i];
        }
    }

    int x_scale = completed_scan_metadata.num_rows/completed_scan_metadata.num_columns;
    int y_scale = completed_scan_metadata.num_columns/completed_scan_metadata.num_rows;
    if (x_scale == 0) x_scale = 1;
    if (y_scale == 0) y_scale = 1;

    for (int i = 0; i < full_paths.length(); i++) {
        ScanData* data_container = scan_data[i];
        QFile file(full_paths[i]);
        if (file.open(QIODevice::Append)) {
            // Serialize header data
            QTextStream outtxt(&file);
            outtxt << "#XRes = " << QString::number(completed_scan_metadata.num_columns) << "\n";
            outtxt << "#YRes = " << QString::number(completed_scan_metadata.num_rows) << "\n";
            outtxt << "#XReal = " << QString::number(completed_scan_metadata.x_range_m) << "\n";
            outtxt << "#YReal = " << QString::number(completed_scan_metadata.y_range_m) << "\n";
            outtxt << "#XOffset = " << QString::number(completed_scan_metadata.x_offset_m) << "\n";
            outtxt << "#YOffset = " << QString::number(completed_scan_metadata.y_offset_m) << "\n";
            outtxt << "#XYUnits = m\n";
            switch (specific_file_names[i][0].unicode()) {
                case 'o':
                    outtxt << "#ZUnits = m\n";
                break;
                case 'p':
                    outtxt << "#ZUnits = deg\n";
                break;
                case 'e':
                    outtxt << "#ZUnits = V\n";
                break;
            }
            outtxt << "#Title = " << m_base_file_name << " " << specific_file_names[i] << " " << timestamp << "\n";
            outtxt << "#Date = " << completed_scan_metadata.scan_completion_time << "\n";
            outtxt << "#DwellTime = " << QString::number(completed_scan_metadata.dwell_time) << "\n";
            for (int y = 0; y < completed_scan_metadata.num_rows; y++) {
                for (int x = 0; x < data_container->raw_data[y]->size; x++) {
                    if (specific_file_names[i][0] == 'o') {
                        // this is an offset. save value in meters
                        outtxt << QString::number(z_fine_dac_to_nm(data_container->raw_data[y]->data[x], completed_scan_metadata.z_actuator_scale_factor) * 1e-9,'e');
                    } else {
                        outtxt << QString::number(data_container->raw_data[y]->data[x] * DAC::SCALE_FACTOR, 'e');
                    }
                    if (x != (data_container->raw_data[y]->size - 1)) {
                        outtxt << "\t";
                    }
                }
                outtxt << "\n";
            }
            outtxt.flush();
        }
    }
}


void Scanner::save_png_data(QString folder_path, QString timestamp) {
    fwd_offset_data->save_png(folder_path + "/" + m_base_file_name + " " + "offset forward" + " " + timestamp);
    fwd_phase_data->save_png(folder_path + "/" + m_base_file_name + " " + "phase forward" + " " + timestamp);
    fwd_error_data->save_png(folder_path + "/" + m_base_file_name + " " + "error forward" + " " + timestamp);
    rev_offset_data->save_png(folder_path + "/" + m_base_file_name + " " + "offset reverse" + " " + timestamp);
    rev_phase_data->save_png(folder_path + "/" + m_base_file_name + " " + "phase reverse" + " " + timestamp);
    rev_error_data->save_png(folder_path + "/" + m_base_file_name + " " + "error reverse" + " " + timestamp);
}

Scanner::callback_return_type Scanner::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

int Scanner::get_delta_x_from_ratio() {
    // should enum the scan ratios
    switch (m_ratio) {
        case 1:
        case 2:
            return 1;
        case 4:
            return 3;
        case 8:
            return 7;
        default:
            return 0;
    }
}

int Scanner::get_delta_y_from_ratio() {
    // should enum the scan ratios
    switch (m_ratio) {
        case 1:
            return 0;
        case 2:
        case 4:
        case 8:
            return 1;
        default:
            return 0;
    }
}

double Scanner::z_fine_dac_to_nm(double dac_value) {
    // TODO: de-magic-ify
    return dac_value * DAC::SCALE_FACTOR * 3990.52 * m_z_actuator_scale_factor;
}

double Scanner::z_fine_dac_to_nm(double dac_value, double z_actuator_scale_factor) {
    // TODO: de-magic-ify
    return dac_value * DAC::SCALE_FACTOR * 3990.52 * z_actuator_scale_factor;
}

double Scanner::x_range_in_m() {
    // TODO: de-magic-ify 14e-6 => max square scan range with PGA 100%
    return 14e-6 * m_x_actuator_scale_factor * m_zoom_scale * ((m_ratio == 1) ? 4 : 1);
}

double Scanner::y_range_in_m() {
    return ((m_ratio == 1) ? (1.0/m_num_rows) : 1.0) * 14e-6 * m_y_actuator_scale_factor * m_zoom_scale;
}

double Scanner::x_offset_in_m() {
    return 14e-6 * m_x_actuator_scale_factor * m_x_offset * ((m_ratio == 1) ? 4 : 1);
}

double Scanner::y_offset_in_m() {
    return ((m_ratio == 1) ? 0 : (14e-6 * m_y_actuator_scale_factor * m_y_offset));
}

double Scanner::x_index_in_um(int x_index) {
    return (x_offset_in_m() + x_index/((double) m_num_columns)*x_range_in_m())*1e6;
}

void Scanner::normalize_offset_line_profiles(void) {
    QVariant minimum = z_fine_dac_to_nm(DAC::RESOLUTION);
    for (int i = 2; i < current_fwd_offset_line_profile.size(); i += 3) {
        if (current_fwd_offset_line_profile[i] < minimum) {
            minimum = current_fwd_offset_line_profile[i];
        }
    }
    for (int i = 2; i < current_fwd_offset_line_profile.size(); i += 3) {
        current_fwd_offset_line_profile[i] = current_fwd_offset_line_profile[i].toDouble() - minimum.toDouble();
    }

    minimum = z_fine_dac_to_nm(DAC::RESOLUTION);
    for (int i = 2; i < current_rev_offset_line_profile.size(); i += 3) {
        if (current_rev_offset_line_profile[i] < minimum) {
            minimum = current_rev_offset_line_profile[i];
        }
    }
    for (int i = 2; i < current_rev_offset_line_profile.size(); i += 3) {
        current_rev_offset_line_profile[i] = current_rev_offset_line_profile[i].toDouble() - minimum.toDouble();
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

void Scanner::set_save_png(bool b_save_png)
{
    m_save_png = b_save_png;
}

const QString Scanner::settings_group_name = "scanner";

