#include "sweeper.h"
#include "adc.h"
#include "constants.h"
#include "pid.h"
#include <QPointF>
#include "QFinalState"
#include <QtGlobal>
#include <QTimer>

Sweeper::Sweeper(PID* pid_) : MinStepSize(1) {
    // to be loaded from a settings file
    m_repetitions_counter = 0;
    pid = pid_;
}

void Sweeper::set_settings() {
    settings.beginGroup(settings_group_name);
    set_start_frequency(settings.contains("start_frequency") ? settings.value("start_frequency").toInt() : 4000, false);
    set_end_frequency(settings.contains("end_frequency") ? settings.value("end_frequency").toInt() : 10000, false);
    set_step_size(settings.contains("step_size") ? settings.value("step_size").toInt() : 100);
    settings.endGroup();
}

void Sweeper::update_settings(QString key, QVariant value) {
    settings.beginGroup(settings_group_name);
    settings.setValue(key, value);
    settings.endGroup();
}

void Sweeper::init() {
    // init DDS
    dds->init();

    // set up framework
    QState* running_state = new QState();
    QState* initialize_machine = new QState(running_state);
    QState* sweep = new QState(running_state);
    QState* detect_peak = new QState(running_state);
    QFinalState* finish = new QFinalState();

    initialize_machine->addTransition(this, SIGNAL(initialization_done()), sweep);
    sweep->addTransition(this, SIGNAL(sweep_done()), detect_peak);
    sweep->addTransition(this, SIGNAL(machine_finished()), finish);
    detect_peak->addTransition(this, SIGNAL(peak_detection_done()), sweep);
    detect_peak->addTransition(this, SIGNAL(peak_detection_failed()), finish);
    running_state->addTransition(this, SIGNAL(reset()), finish);

    QObject::connect(initialize_machine, SIGNAL(entered()), this, SLOT(initialize_machine()));
    QObject::connect(sweep, SIGNAL(entered()), this, SLOT(frequency_sweep()));
    QObject::connect(detect_peak, SIGNAL(entered()), this, SLOT(find_peak()));
    QObject::connect(finish, SIGNAL(entered()), this, SLOT(finish_sweep()));

    m_state_machine.addState(running_state);
    m_state_machine.addState(finish);
    running_state->setInitialState(initialize_machine);
    m_state_machine.setInitialState(running_state);

    set_settings();
}

Sweeper::data_model Sweeper::amplitude_data() {
    return m_amplitude_data;
}

Sweeper::data_model Sweeper::phase_data() {
    return m_phase_data;
}

void Sweeper::emit_dummy_data() {
    for (int i = 1; i < 3; i++) {
        QVariantList list;
        QVariantList lis;
        for (int j = 0; j < 10000; j += 100) {
            list.append(j);
            list.append(j * i);
            lis.append(j);
            lis.append(j/2 * i);
        }
        emit new_amplitude_data(list);
        emit new_phase_data(lis);
    }
}

void Sweeper::start_manual_sweep() {
    if (!m_state_machine.isRunning()) {
        emit reset();
        m_step_sizes.clear();
        m_boundaries.clear();
        m_step_sizes.append(m_step_size);
        m_boundaries.append((m_end_frequency - m_start_frequency) / 2);
        m_num_repetitions = 1;

    }
    m_state_machine.start(); // doesn't run if the state machine is running, but will print an error. 
    // Good to keep this outside of the if statement for debugging.
}

void Sweeper::start_auto_sweep() {
    if (!m_state_machine.isRunning()) {
        emit reset();
        m_step_sizes.clear();
        m_boundaries.clear();
        m_step_sizes.append(m_step_size);
        quint32 boundary = (m_end_frequency - m_start_frequency) / 2;
        m_boundaries.append(boundary);

        // these are hard coded in for "auto" mode - maybe we should break this out into a user panel to change
        m_step_sizes.append(m_step_size / 4);
        m_boundaries.append(boundary / 4);
        m_step_sizes.append(m_step_size / 8);
        m_boundaries.append(boundary / 8);
        m_num_repetitions = 3;
    }
    m_state_machine.start();
}

void Sweeper::initialize_machine() {
    m_repetitions_counter = 0;
    m_current_resonant_frequency = (m_end_frequency + m_start_frequency)/2;
    emit initialization_done();
}

void Sweeper::frequency_sweep() {
    if (m_repetitions_counter >= m_num_repetitions) {
        emit machine_finished();
        return;
    }
    dds->set_start_frequency(m_current_resonant_frequency - m_boundaries[m_repetitions_counter]);
    dds->set_end_frequency(m_current_resonant_frequency + m_boundaries[m_repetitions_counter]);
    dds->set_step_size(m_step_sizes[m_repetitions_counter]);
    qDebug() << "Sweeping with: start = " << dds->start_frequency() << " end = " << dds->end_frequency() << " and step size = " << dds->step_size();
    dds->cmd_set();
    cmd_frequency_sweep(); // should we delay this to allow dds to settle?
}

void Sweeper::callback_cmd_frequency_sweep(QByteArray return_bytes) {
    quint32 current_frequency;
    m_amplitude_data.clear(); // remove any past data from previous sweep iterations
    m_phase_data.clear();
    for (int i = 0; i < return_bytes.size(); i += 4) {
        current_frequency = m_current_resonant_frequency - m_boundaries[m_repetitions_counter] + m_step_sizes[m_repetitions_counter] * ((i - 2) / 4);
        double amplitude_value = double(bytes_to_word(quint8(return_bytes[i]), quint8(return_bytes[i + 1]))) * ADC::SCALE_FACTOR;
        double phase_value = double(bytes_to_word(quint8(return_bytes[i + 2]), quint8(return_bytes[i + 3]))) * ADC::SCALE_FACTOR;
        QPointF amplitude_point(current_frequency, amplitude_value);
        QPointF phase_point(current_frequency, phase_value);
        m_amplitude_data.append(amplitude_point);
        m_phase_data.append(phase_point);
    }
    QVariantList amplitude_data_for_js, phase_data_for_js;
    for (int i = 0; i < m_amplitude_data.length();  i++) {
        amplitude_data_for_js.append(m_amplitude_data[i].x());
        amplitude_data_for_js.append(m_amplitude_data[i].y());
        phase_data_for_js.append(m_phase_data[i].x());
        phase_data_for_js.append(m_phase_data[i].y());
    }
    emit new_amplitude_data(amplitude_data_for_js);
    emit new_phase_data(phase_data_for_js);
    m_repetitions_counter += 1;
    emit sweep_done();
}

void Sweeper::cmd_frequency_sweep() {
    CommandNode* node = new CommandNode(command_hash[AFM_Start_Frequency_Sweep_AD9837], bind(&Sweeper::callback_cmd_frequency_sweep));
    node->num_receive_bytes = Num_Meta_Data_Bytes + dds->num_steps() * 4; // 4 bytes per step - two for amplitude, two for phase
    emit command_generated(node);
}

void Sweeper::finish_sweep() {
    set_stable_frequency();
    pid->set_setpoint(m_max_amplitude / 2);
}

void Sweeper::set_stable_frequency() {
    dds->set_step_size(0);
    dds->set_start_frequency(m_current_resonant_frequency);
    dds->set_end_frequency(m_current_resonant_frequency);
    dds->cmd_set();
    qDebug() << "Set stable frequency to " << dds->start_frequency();
}

Sweeper::callback_return_type Sweeper::bind(Sweeper::callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

void Sweeper::find_peak() {
    double max = 0;
    int max_index = -1;
    for (int i = 0; i < m_amplitude_data.size(); i++) {
        if (m_amplitude_data[i].y() > max) {
            max = m_amplitude_data[i].y();
            max_index =  m_amplitude_data[i].x();
        }
    }
    m_current_resonant_frequency = max_index;
    m_max_amplitude = max;
    qDebug() << "Found resonance at" << m_current_resonant_frequency << "Amplitude" << m_max_amplitude;
    emit peak_detection_done();
}

void Sweeper::set_frequency_on_select(int frequency) {
    m_current_resonant_frequency = frequency;
    set_stable_frequency();
}

void Sweeper::set_start_frequency(quint32 start_frequency, bool enforce_validity) {
    if (m_start_frequency != start_frequency) {
        m_start_frequency = start_frequency;
        qDebug() << "Changing Sweeper start frequency to" << m_start_frequency;
        emit start_frequency_changed(static_cast<int>(m_start_frequency));
        update_settings("start_frequency", QVariant(m_start_frequency));
        if (enforce_validity && m_start_frequency > m_end_frequency) {
            set_end_frequency(m_start_frequency);
        }
        if (enforce_validity && m_end_frequency  - m_start_frequency < m_step_size) {
            set_step_size((m_end_frequency - m_start_frequency)/4);
        }
        emit num_steps_changed(calculate_num_steps());
    }
}

void Sweeper::set_end_frequency(quint32 end_frequency, bool enforce_validity) {
    if (m_end_frequency != end_frequency) {
        m_end_frequency = end_frequency;
        qDebug() << "Changing Sweeper end frequency to" << m_end_frequency;
        emit end_frequency_changed(static_cast<int>(m_end_frequency));
        update_settings("end_frequency", QVariant(m_end_frequency));
        if (enforce_validity && m_end_frequency < m_start_frequency) {
            set_start_frequency(m_end_frequency);
        }
        if (enforce_validity && m_end_frequency - m_start_frequency < m_step_size) {
            set_step_size((m_end_frequency - m_start_frequency)/4);
        }
        emit num_steps_changed(calculate_num_steps());
    }
}

void Sweeper::set_step_size(quint16 step_size) {
    if (m_step_size != step_size) {
        m_step_size = qMax(step_size, MinStepSize); // min step size is 1
        qDebug() << "Changing Sweeper step size to" << m_step_size;
        emit step_size_changed(static_cast<int>(m_step_size));
        update_settings("step_size", QVariant(m_step_size));
        if (m_end_frequency - m_start_frequency < m_step_size) {
            set_end_frequency(m_start_frequency + step_size * 2);
        }
        emit num_steps_changed(calculate_num_steps());
    }
}

double Sweeper::calculate_num_steps() {
    return double(m_end_frequency - m_start_frequency) / m_step_size;
}

quint32 Sweeper::start_frequency() {
    return m_start_frequency;
}

quint16 Sweeper::step_size() {
    return m_step_size;
}

quint32 Sweeper::end_frequency() {
    return m_end_frequency;
}

const QString Sweeper::settings_group_name = "sweeper";
