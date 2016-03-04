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
    Q_PROPERTY(quint32 m_start_frequency READ start_frequency WRITE set_start_frequency NOTIFY start_frequency_changed)
    Q_PROPERTY(quint32 m_end_frequency READ end_frequency WRITE set_end_frequency NOTIFY end_frequency_changed)
    Q_PROPERTY(quint16 m_step_size READ step_size WRITE set_step_size NOTIFY step_size_changed)
public:
    typedef QVector<QPointF> data_model;
    typedef void (Sweeper::*callback_type)(QByteArray);

    explicit Sweeper(PID*);
    void init();
    data_model amplitude_data();
    data_model phase_data();
    Q_INVOKABLE void start_auto_sweep();
    Q_INVOKABLE void start_manual_sweep();
    Q_INVOKABLE void set_frequency_on_select(int);
    Q_INVOKABLE void emit_dummy_data();
    Q_INVOKABLE void set_start_frequency(quint32 start_frequency, bool enforce_validity = true);
    Q_INVOKABLE void set_step_size(quint16 step_size);
    Q_INVOKABLE void set_end_frequency(quint32 end_frequency, bool enforce_validity = true);
    Q_INVOKABLE quint32 start_frequency();
    Q_INVOKABLE quint16 step_size();
    Q_INVOKABLE quint32 end_frequency();

    DDS* dds;
    PID* pid;
    void set_settings();

signals:
    void initialization_done();
    void sweep_done();
    void peak_detection_done();
    void peak_detection_failed();
    void machine_finished();
    void new_amplitude_data(QVariantList);
    void new_phase_data(QVariantList);
    void reset();
    void start_frequency_changed(int);
    void step_size_changed(int);
    void end_frequency_changed(int);
    void num_steps_changed(double);

public slots:
    void frequency_sweep();
    void find_peak();
    void initialize_machine();
    void finish_sweep();

    void cmd_frequency_sweep();

private:
    data_model m_amplitude_data;
    data_model m_phase_data;
    QStateMachine m_state_machine;

    int m_repetitions_counter;
    int m_num_repetitions;
    quint32 m_current_resonant_frequency;
    double m_max_amplitude;
    QList<quint16> m_step_sizes;
    QList<quint32> m_boundaries; // how much +/- should we put on the max found in the previous state
    quint32 m_start_frequency;
    quint32 m_end_frequency;
    quint16 m_step_size;

    callback_return_type bind(callback_type method);
    void callback_cmd_frequency_sweep(QByteArray return_bytes);
    void set_stable_frequency();
    double calculate_num_steps();
    static const QString settings_group_name;
    const quint16 MinStepSize;
};

#endif // SWEEPER_H
