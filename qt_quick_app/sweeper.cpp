#include "sweeper.h"
#include "adc.h"
#include "constants.h"
#include "QFinalState"

Sweeper::Sweeper() {
    // to be loaded from a settings file
    m_num_repetitions = 4;
    m_repetitions_counter = 0;
    m_starting_center_frequency = m_current_resonant_frequency = 7000;
    m_step_sizes.append(100);
    m_step_sizes.append(20);
    m_step_sizes.append(2);
    m_step_sizes.append(1);
    m_boundaries.append(5000);
    m_boundaries.append(100);
    m_boundaries.append(10);
    m_boundaries.append(1);
}

void Sweeper::init() {
    // init DDS
    dds->init();

    // set up framework
    QState* sweep = new QState();
    QState* detect_peak = new QState();
    QFinalState* finish = new QFinalState();

    sweep->addTransition(this, SIGNAL(sweep_done()), detect_peak);
    sweep->addTransition(this, SIGNAL(machine_finished()), finish);
    detect_peak->addTransition(this, SIGNAL(peak_detection_done()), sweep);

    QObject::connect(sweep, SIGNAL(entered()), this, SLOT(frequency_sweep()));
    QObject::connect(detect_peak, SIGNAL(entered()), this, SLOT(find_peak()));

    m_state_machine.addState(sweep);
    m_state_machine.addState(detect_peak);
    m_state_machine.addState(finish);

    m_state_machine.setInitialState(sweep);
    qDebug() << "here";
}

Sweeper::data_model Sweeper::amplitude_data() {
    return m_amplitude_data;
}

Sweeper::data_model Sweeper::phase_data() {
    return m_phase_data;
}

void Sweeper::find_peak() {
    emit peak_detection_done();
}

void Sweeper::start_state_machine() {
    m_state_machine.start();
}

void Sweeper::frequency_sweep() {
    qDebug() << "here";
    if (m_repetitions_counter >= m_num_repetitions) {
        emit machine_finished();
        return;
    }
    dds->set_start_frequency(m_current_resonant_frequency - m_boundaries[m_repetitions_counter]);
    dds->set_end_frequency(m_current_resonant_frequency + m_boundaries[m_repetitions_counter]);
    dds->set_step_size(m_step_sizes[m_repetitions_counter]);
    qDebug() << "LOWER" << dds->start_frequency() << "UPPER" << dds->end_frequency();
    dds->cmd_set();
    cmd_frequency_sweep();
    m_repetitions_counter += 1;
}

void Sweeper::callback_cmd_frequency_sweep(QByteArray return_bytes) {
    for (int i = Num_Meta_Data_Bytes; i < return_bytes.size(); i += 4) {
        quint16 amplitude_value = bytes_to_word(quint8(return_bytes[i]), quint8(return_bytes[i + 1]));
        quint16 phase_value = bytes_to_word(quint8(return_bytes[i + 2]), quint8(return_bytes[i + 3]));
        m_amplitude_data.append(double(amplitude_value) * ADC::SCALE_FACTOR);
        m_phase_data.append(double(phase_value) * ADC::SCALE_FACTOR);
    }
//    qDebug() << "amplitude" << m_amplitude_data;
//    qDebug() << "phase" << m_phase_data;
    emit sweep_done();
}

void Sweeper::cmd_frequency_sweep() {
    CommandNode* node = new CommandNode(command_hash[AFM_Start_Frequency_Sweep_AD9837], bind(&Sweeper::callback_cmd_frequency_sweep));
    node->num_receive_bytes = Num_Meta_Data_Bytes + dds->num_steps() * 4; // 4 bytes per step - two for amplitude, two for phase
    emit command_generated(node);
}

Sweeper::callback_return_type Sweeper::bind(Sweeper::callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}
