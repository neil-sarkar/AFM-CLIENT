#include "scanner.h"
#include "QFinalState"
#include "constants.h"

Scanner::Scanner(PID* pid_)
{
    m_num_lines = 16;
    m_num_points = 256;
    m_ratio = 0;
    pid = pid_;
}

void Scanner::init() {
    // set up framework
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
    m_state_machine.addState(finish);
    m_state_machine.setInitialState(initialize_machine);
}

void Scanner::start_state_machine() {
    m_state_machine.start();
}



void Scanner::initialize_scan_state_machine() {
    // Old code used to set PGAs here, but we really don't need to - they should already have been set
    pid->set_enabled();
    emit scanner_initialization_done();
}


void Scanner::set_signal_generator() {
    qDebug() << "Setting sig gen";
    cmd_set_signal_generator();
    cmd_start_scan();
    emit set_signal_generator_done();
}

void Scanner::receive_data() {
    qDebug() << "Receiving data";
//        cmd_step_scan();
//    return;
    emit all_data_received();
}

void Scanner::cmd_step_scan() {
    emit command_generated(new CommandNode(command_hash[AFM_Step_Scan], bind(&Scanner::callback_step_scan)));
}

void Scanner::callback_step_scan(QByteArray payload) {
    receive_data();
}

void Scanner::end_scan_state_machine() {
    qDebug() << "scanning done";
}

void Scanner::cmd_set_signal_generator() {
    QByteArray payload;
    payload += m_ratio;
    payload += (m_num_points & 0xFF);
    payload += ((m_num_points & 0xFF) >> 8);
    payload += (m_num_lines & 0xFF);
    payload += ((m_num_lines & 0xFF) >> 8);
    emit command_generated(new CommandNode(command_hash[AFM_Set_Signal_Generation],  payload));
}

void Scanner::cmd_start_scan() {
    emit command_generated(new CommandNode(command_hash[AFM_Start_Scan]));
}

Scanner::callback_return_type Scanner::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

