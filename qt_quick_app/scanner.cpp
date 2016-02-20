#include "scanner.h"
#include "QFinalState"
#include <QHistoryState>
#include "constants.h"

Scanner::Scanner(PID* pid_, AFMObject* dac_fine_z_)
{
    m_num_lines = 128;
    m_num_points = 128;
    m_ratio = 4;
    m_dwell_time = 2;
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
    cmd_set_dwell_time();
    cmd_set_signal_generator();
    cmd_start_scan();

    // set up state machine framework
    QState* initialize_machine = new QState();
    QState* set_signal_generator = new QState();
    QState* receive_data = new QState();
    QFinalState* finish = new QFinalState();

    initialize_machine->addTransition(this, SIGNAL(scanner_initialization_done()), set_signal_generator);
    set_signal_generator->addTransition(this, SIGNAL(set_signal_generator_done()), receive_data);
    receive_data->addTransition(this, SIGNAL(all_data_received()), finish);

    QObject::connect(initialize_machine, SIGNAL(entered()), this, SLOT(initialize_scan_state_machine()));
    QObject::connect(set_signal_generator, SIGNAL(entered()), this, SLOT(set_signal_generator()));
    QObject::connect(receive_data, SIGNAL(entered()), this, SLOT(receive_data()));
    QObject::connect(finish, SIGNAL(entered()), this, SLOT(end_scan_state_machine()));

    m_state_machine.addState(initialize_machine);
    m_state_machine.addState(set_signal_generator);
    m_state_machine.addState(receive_data);
    m_state_machine.setInitialState(initialize_machine);
}

void Scanner::start_state_machine() {
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
    m_state_machine.start();
}

void Scanner::initialize_scan_state_machine() {
    // Old code used to set PGAs here, but we really don't need to - they should already have been set

    emit scanner_initialization_done();
    forward_data = new ScanData(m_num_lines, m_num_points, m_ratio);
    reverse_data = new ScanData(m_num_lines, m_num_points, m_ratio);
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
    if (scanning_forward && (forward_data->size() % m_num_points) == 0)
        return false;
    if (!scanning_forward && (reverse_data->size() % m_num_points) == 0)
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
        m_num_points_received += 1;
    }
    if (scanning_forward && forward_data->size() % m_num_points == 0) {
        emit new_forward_offset_data(forward_data->package_data_for_ui(m_num_points));
    } else if (!scanning_forward && reverse_data->size() % m_num_points == 0) {
        emit new_reverse_offset_data(reverse_data->package_data_for_ui(m_num_points));
    }
    receive_data();
}

void Scanner::end_scan_state_machine() {
    qDebug() << "scanning done" << m_num_points_received;
    forward_data->print();
}

void Scanner::cmd_set_signal_generator() {
    QByteArray payload;
    payload += m_ratio;
    payload += (m_num_points & 0xFF);
    payload += ((m_num_points & 0x0F00) >> 8);
    payload += (m_num_lines & 0xFF);
    payload += ((m_num_lines & 0x0F00) >> 8);
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
