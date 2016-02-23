#ifndef SWEEPER_H
#define SWEEPER_H

#include <QObject>
#include "afm_object.h"
#include "dds.h"
#include <QStateMachine>
#include <QPointF>
#include <pid.h>

class Sweeper : public AFMObject
{
    Q_OBJECT
public:
    typedef QVector<QPointF> data_model;
    typedef void (Sweeper::*callback_type)(QByteArray);

    explicit Sweeper(PID*);
    void init();
    data_model amplitude_data();
    data_model phase_data();
    Q_INVOKABLE void start_state_machine();
    Q_INVOKABLE void set_frequency_on_select(int);
    Q_INVOKABLE void emit_dummy_data();
    DDS* dds;
    PID* pid;

signals:
    void initialization_done();
    void sweep_done();
    void peak_detection_done();
    void peak_detection_failed();
    void machine_finished();
    void new_amplitude_data(QVariantList);
    void new_phase_data(QVariantList);
    void reset();

public slots:
    void frequency_sweep();
    int find_peak();
    void initialize_machine();
    void finish_sweep();

private:
    data_model m_amplitude_data;
    data_model m_phase_data;
    QStateMachine m_state_machine;

    int m_repetitions_counter;
    int m_num_repetitions;
    quint32 m_starting_center_frequency;
    quint32 m_current_resonant_frequency;
    double m_max_amplitude;
    QList<quint16> m_step_sizes;
    QList<quint32> m_boundaries; // how much +/- should we put on the max found in the previous state

    void cmd_frequency_sweep();
    callback_return_type bind(callback_type method);
    void callback_cmd_frequency_sweep(QByteArray return_bytes);
    void set_stable_frequency();

};

#endif // SWEEPER_H
