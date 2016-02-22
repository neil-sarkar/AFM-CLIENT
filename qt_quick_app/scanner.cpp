#include "scanner.h"
#include "QFinalState"
#include <QHistoryState>
#include "constants.h"

Scanner::Scanner(PID* pid_, AFMObject* dac_fine_z_)
{
    m_ratio = 4;
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

void Scanner::init() {
    // set up state machine framework
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

    // we tend to set values through their setters so
    // that their NOTIFY signals get called and the UI updates
    set_num_averages(5);
    set_send_back_count(8);
    set_dwell_time(2);
    set_num_columns(16);
    set_num_rows(16);
    cmd_set_signal_generator();
    cmd_start_scan();
}

void Scanner::emit_dummy_data() {
    emit started_scan_state_machine();
    for (int i = 0; i < 10; i++) {
        QVariantList data;
        for (int j = 0; j < 10; j++) {
            data.append(i);
            data.append(j);
            data.append(i*j);
        }
        emit new_forward_offset_data(data);
    }
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
    forward_data = new ScanData(m_num_rows, m_num_columns, m_ratio);
    reverse_data = new ScanData(m_num_rows, m_num_columns, m_ratio);
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
    emit command_generated(new CommandNode(command_hash[AFM_Step_Scan], bind(&Scanner::callback_step_scan)));
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

    for (int i = 0; i < payload.size(); i += 6) { // 6 bytes passed back
        double z_amplitude = bytes_to_word(payload.at(i), payload.at(i + 1));
        double z_offset = bytes_to_word(payload.at(i + 2), payload.at(i + 3));
        double z_phase = bytes_to_word(payload.at(i + 4), payload.at(i + 5));
        if (scanning_forward)
            forward_data->append(z_amplitude, z_offset, z_phase);
        else
            reverse_data->append(z_amplitude, z_offset, z_phase);
        scanning_forward = is_scanning_forward();
        m_num_columns_received += 1;
    }
    if (scanning_forward && forward_data->size() % m_num_columns == 0) {
        emit new_forward_offset_data(forward_data->package_data_for_ui(m_num_columns));
    } else if (!scanning_forward && reverse_data->size() % m_num_columns == 0) {
        emit new_reverse_offset_data(reverse_data->package_data_for_ui(m_num_columns));
    }
    receive_data();
}

void Scanner::end_scan_state_machine() {
    m_should_pause = false;
    qDebug() << "scanning done" << m_num_columns_received;
    forward_data->print();
}

quint8 Scanner::num_averages() {
    return m_num_averages;
}

void Scanner::set_num_averages(int num_averages) {
    if (m_num_averages != num_averages) {
        m_num_averages = num_averages;
        qDebug() << "Changing num averages to " << m_num_averages;
        emit num_averages_changed(static_cast<int>(m_num_averages));
        cmd_set_num_averages();
    }
}

void Scanner::cmd_set_num_averages() {
    QByteArray payload;
    payload += m_num_averages;
    emit command_generated(new CommandNode(command_hash[Scanner_Set_Num_Averages], payload));
}

quint8 Scanner::send_back_count() {
    return m_send_back_count;
}

void Scanner::set_send_back_count(int send_back_count) {
    if (m_send_back_count != send_back_count) {
        m_send_back_count = send_back_count;
        qDebug() << "Changing num averages to " << m_send_back_count;
        emit send_back_count_changed(static_cast<int>(m_send_back_count));
        cmd_set_send_back_count();
    }
}

quint16 Scanner::num_rows() {
    return m_num_rows;
}

void Scanner::set_num_rows(int num_rows) {
    if (m_num_rows != num_rows) {
        m_num_rows = num_rows;
        qDebug() << "Changing num averages to " << m_num_rows;
        emit num_rows_changed(static_cast<int>(m_num_rows));
        cmd_set_signal_generator();
    }
}

quint16 Scanner::num_columns() {
    return m_num_columns;
}

void Scanner::set_num_columns(int num_columns) {
    if (m_num_columns != num_columns) {
        m_num_columns = num_columns;
        qDebug() << "Changing num averages to " << m_num_columns;
        emit num_columns_changed(static_cast<int>(m_num_columns));
        cmd_set_signal_generator();
    }
}

void Scanner::cmd_set_send_back_count() {
    QByteArray payload;
    payload += m_send_back_count;
    emit command_generated(new CommandNode(command_hash[Scanner_Set_Send_Back_Count], payload));
}

quint8 Scanner::dwell_time() {
    return m_dwell_time;
}

void Scanner::set_dwell_time(int dwell_time) {
    if (m_dwell_time != dwell_time) {
        m_dwell_time = dwell_time;
        qDebug() << "Changing dwell time to " << m_dwell_time;
        emit dwell_time_changed(static_cast<int>(m_dwell_time));
        cmd_set_dwell_time();
    }
}

void Scanner::cmd_set_signal_generator() {
    QByteArray payload;
    payload += m_ratio;
    payload += (m_num_columns & 0xFF);
    payload += ((m_num_columns & 0x0F00) >> 8);
    payload += (m_num_rows & 0xFF);
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


Scanner::callback_return_type Scanner::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}
