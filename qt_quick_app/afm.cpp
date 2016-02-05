#include "afm.h"
#include "dac.h"
#include "dds.h"
#include "afm_object.h"
#include "constants.h"
#include "serial_port.h"

AFM::AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, PID* pid, DDS* dds) {
    this->PGA_collection = PGA_collection;
    this->ADC_collection = ADC_collection;
    this->DAC_collection = DAC_collection;
    this->motor = motor;
    this->pid = pid;
    this->dds = dds;
}

void AFM::init() {
    // This method calls the init methods of all the members


    QHash<int, AFMObject*>::iterator i;
    for (i = DAC_collection.begin(); i != DAC_collection.end(); ++i)
        i.value()->init();
    for (i = ADC_collection.begin(); i != ADC_collection.end(); ++i)
        i.value()->init();
    for (i = PGA_collection.begin(); i != PGA_collection.end(); ++i)
        i.value()->init();

    motor->init();
    pid->init();
    dds->init();
}

void AFM::cmd_frequency_sweep() {
    CommandNode* node = new CommandNode(command_hash[AFM_Start_Frequency_Sweep_AD9837], bind(&AFM::callback_cmd_frequency_sweep));
    node->num_receive_bytes = Num_Meta_Data_Bytes + dds->num_steps() * 4; // 4 bytes per step - two for amplitude, two for phase
    emit command_generated(node);
}

AFM::callback_return_type AFM::bind(callback_type method) {
    return std::bind(method, this, std::placeholders::_1);
}

void AFM::callback_cmd_frequency_sweep(QByteArray return_bytes) {
    QVector<double> amplitude_data;
    QVector<double> phase_data;

    for (int i = Num_Meta_Data_Bytes; i < return_bytes.size(); i += 4) {
        quint16 amplitude_value = bytes_to_word(quint8(return_bytes[i]), quint8(return_bytes[i + 1]));
        quint16 phase_value = bytes_to_word(quint8(return_bytes[i + 2]), quint8(return_bytes[i + 3]));
        amplitude_data.append(double(amplitude_value) * ADC::SCALE_FACTOR);
        phase_data.append(double(phase_value) * ADC::SCALE_FACTOR);
    }
    qDebug() << "amplitude" << amplitude_data;
    qDebug() << "phase" << phase_data;
    emit sweep_done();
}


void AFM::coarse_frequency_sweep() {
    dds->set_start_frequency(5000);
    dds->set_end_frequency(15000);
    dds->set_step_size(100);
    dds->cmd_set();
    cmd_frequency_sweep();
}

void AFM::fine_frequency_sweep() {
    dds->set_start_frequency(6000);
    dds->set_end_frequency(8000);
    dds->set_step_size(20);
    dds->cmd_set();
    cmd_frequency_sweep();
}

void AFM::find_peak() {
    emit peak_detection_done();
}

void AFM::start_state_machine() {
    sweep_machine->start();
}
