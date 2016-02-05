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
}

Sweeper::data_model Sweeper::amplitude_data() {
    return m_amplitude_data;
}

Sweeper::data_model Sweeper::phase_data() {
    return m_phase_data;
}

void Sweeper::start_state_machine() {
    m_state_machine.start();
}

void Sweeper::frequency_sweep() {
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
    qDebug() << "amplitude" << m_amplitude_data;
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


int Sweeper::find_peak() {
    // https://github.com/xuphys/peakdetect/blob/master/peakdetect.c
    data_model data = this->m_amplitude_data;
    int data_count = this->m_amplitude_data.size();
    int emi_peaks[500];
    int num_emi_peaks[500];
    int max_emi_peaks = 500;
    int absop_peaks[500];
    int num_absop_peaks[500];
    int max_absop_peaks = 500;
    double delta = 1e-6;
    int emi_first = 0;
//            const double*   data, /* the data */
//            int             data_count, /* row count of data */
//            int*            emi_peaks, /* emission peaks will be put here */
//            int*            num_emi_peaks, /* number of emission peaks found */
//            int             max_emi_peaks, /* maximum number of emission peaks */
//            int*            absop_peaks, /* absorption peaks will be put here */
//            int*            num_absop_peaks, /* number of absorption peaks found */
//            int             max_absop_peaks, /* maximum number of absorption peaks
//                                                */
//            double          delta, /* delta used for distinguishing peaks */
//            int             emi_first /* should we search emission peak first of
//                                         absorption peak first? */
//            )
//    {
    int     i;
    double  mx;
    double  mn;
    int     mx_pos = 0;
    int     mn_pos = 0;
    int     is_detecting_emi = emi_first;


    mx = data[0];
    mn = data[0];

    *num_emi_peaks = 0;
    *num_absop_peaks = 0;

    for(i = 1; i < data_count; ++i)
    {
        if(data[i] > mx)
        {
            mx_pos = i;
            mx = data[i];
        }
        if(data[i] < mn)
        {
            mn_pos = i;
            mn = data[i];
        }

        if(is_detecting_emi &&
                data[i] < mx - delta)
        {
            if(*num_emi_peaks >= max_emi_peaks) /* not enough spaces */
                return 1;

            emi_peaks[*num_emi_peaks] = mx_pos;
            ++ (*num_emi_peaks);

            is_detecting_emi = 0;

            i = mx_pos - 1;

            mn = data[mx_pos];
            mn_pos = mx_pos;
        }
        else if((!is_detecting_emi) &&
                data[i] > mn + delta)
        {
            if(*num_absop_peaks >= max_absop_peaks)
                return 2;

            absop_peaks[*num_absop_peaks] = mn_pos;
            ++ (*num_absop_peaks);

            is_detecting_emi = 1;

            i = mn_pos - 1;

            mx = data[mn_pos];
            mx_pos = mn_pos;
        }
    }
    emit peak_detection_done();
    qDebug() << "here";
    double max = 0;
    int max_index = -1;
    for (int i = 0; i < *num_emi_peaks; i++) {
        if (data[emi_peaks[i]] > max) {
            max = data[emi_peaks[i]];
            max_index = i;
        }
    }
    qDebug() << "max amp" << max << max_index;
    return 0;
}
