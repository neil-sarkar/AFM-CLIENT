#include "sweeper.h"
#include "adc.h"
#include "constants.h"
#include "pid.h"
#include <QPointF>
#include "QFinalState"

Sweeper::Sweeper(PID* pid_) {
    // to be loaded from a settings file
    m_num_repetitions = 3;
    m_repetitions_counter = 0;
    m_starting_center_frequency = 8000;
    m_step_sizes.append(100);
    m_boundaries.append(5000);
    m_step_sizes.append(10);
    m_boundaries.append(500);
    m_step_sizes.append(1);
    m_boundaries.append(50);
    pid = pid_;
}

void Sweeper::init() {
    // init DDS
    dds->init();

    // set up framework
    QState* initialize_machine = new QState();
    QState* sweep = new QState();
    QState* detect_peak = new QState();
    QFinalState* finish = new QFinalState();

    initialize_machine->addTransition(this, SIGNAL(initialization_done()), sweep);
    sweep->addTransition(this, SIGNAL(sweep_done()), detect_peak);
    sweep->addTransition(this, SIGNAL(machine_finished()), finish);
    detect_peak->addTransition(this, SIGNAL(peak_detection_done()), sweep);
    detect_peak->addTransition(this, SIGNAL(peak_detection_failed()), finish);

    QObject::connect(initialize_machine, SIGNAL(entered()), this, SLOT(initialize_machine()));
    QObject::connect(sweep, SIGNAL(entered()), this, SLOT(frequency_sweep()));
    QObject::connect(detect_peak, SIGNAL(entered()), this, SLOT(find_peak()));
    QObject::connect(finish, SIGNAL(entered()), this, SLOT(finish_sweep()));

    m_state_machine.addState(initialize_machine);
    m_state_machine.addState(sweep);
    m_state_machine.addState(detect_peak);
    m_state_machine.addState(finish);

    m_state_machine.setInitialState(initialize_machine);
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

void Sweeper::start_state_machine() {
    init();
    m_state_machine.start();
}

void Sweeper::initialize_machine() {
    m_repetitions_counter = 0;
    m_current_resonant_frequency = m_starting_center_frequency;
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
    qDebug() << "Math" << m_current_resonant_frequency << m_boundaries;
    qDebug() << "LOWER" << dds->start_frequency() << "UPPER" << dds->end_frequency();
    dds->cmd_set();
    cmd_frequency_sweep();
}

void Sweeper::callback_cmd_frequency_sweep(QByteArray return_bytes) {
    quint32 current_frequency;
    m_amplitude_data.clear(); // remove any past data
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
    QVariantList amplitude_data_for_js;
    QVariantList phase_data_for_js;
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

int Sweeper::find_peak() {
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
    return 0;
}

void Sweeper::set_frequency_on_select(int frequency) {
    m_current_resonant_frequency = frequency;
    set_stable_frequency();
}

//int Sweeper::find_peak() {
//    // https://github.com/xuphys/peakdetect/blob/master/peakdetect.c
//    // http://billauer.co.il/peakdet.html
//    QVector<double> data;
//    for (int i = 0; i < m_amplitude_data.size(); i++)
//        data.append(m_amplitude_data[i].y());

//    qDebug() << m_amplitude_data;
//    int data_count = data.size();
//    int emi_peaks[500];
//    int num_emi_peaks[500];
//    int max_emi_peaks = 500;
//    int absop_peaks[500];
//    int num_absop_peaks[500];
//    int max_absop_peaks = 500;
//    double delta = 1e-6;
//    int emi_first = 0;

//    int     i;
//    double  mx;
//    double  mn;
//    int     mx_pos = 0;
//    int     mn_pos = 0;
//    int     is_detecting_emi = emi_first;


//    mx = data[0];
//    mn = data[0];

//    *num_emi_peaks = 0;
//    *num_absop_peaks = 0;

//    for(i = 1; i < data_count; ++i)
//    {
//        if(data[i] > mx)
//        {
//            mx_pos = i;
//            mx = data[i];
//        }
//        if(data[i] < mn)
//        {
//            mn_pos = i;
//            mn = data[i];
//        }

//        if(is_detecting_emi &&
//                data[i] < mx - delta)
//        {
//            if(*num_emi_peaks >= max_emi_peaks) /* not enough spaces */ {
//                emit peak_detection_failed();
//                return 1;
//            }

//            emi_peaks[*num_emi_peaks] = mx_pos;
//            ++ (*num_emi_peaks);

//            is_detecting_emi = 0;

//            i = mx_pos - 1;

//            mn = data[mx_pos];
//            mn_pos = mx_pos;
//        }
//        else if((!is_detecting_emi) &&
//                data[i] > mn + delta)
//        {
//            if(*num_absop_peaks >= max_absop_peaks) {
//                emit peak_detection_failed();
//                return 2;
//            }

//            absop_peaks[*num_absop_peaks] = mn_pos;
//            ++ (*num_absop_peaks);

//            is_detecting_emi = 1;

//            i = mn_pos - 1;

//            mx = data[mn_pos];
//            mx_pos = mn_pos;
//        }
//    }
//    double max = 0;
//    int max_index = -1;
//    for (int i = 0; i < *num_emi_peaks; i++) {
//        if (data[emi_peaks[i]] > max) {
//            max = data[emi_peaks[i]];
//            max_index = emi_peaks[i];
//        }
//    }
//    qDebug() << "Max amplitude found" << max <<"Volts at" << m_amplitude_data[max_index].x() << "Hz";
//    m_current_resonant_frequency = m_amplitude_data[max_index].x();
//    emit peak_detection_done();
//    return 0;
//}
