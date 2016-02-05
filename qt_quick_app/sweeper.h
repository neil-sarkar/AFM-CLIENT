#ifndef SWEEPER_H
#define SWEEPER_H

#include <QObject>
#include "afm_object.h"
#include "dds.h"
#include <QStateMachine>
#include <QPointF>

class Sweeper : public AFMObject
{
    Q_OBJECT
public:
    typedef QVector<QPointF> data_model;
    typedef void (Sweeper::*callback_type)(QByteArray);

    explicit Sweeper();
    void init();
    data_model amplitude_data();
    data_model phase_data();
    Q_INVOKABLE void start_state_machine();
    DDS* dds;

signals:
    void sweep_done();
    void peak_detection_done();
    void peak_detection_failed();
    void machine_finished();

public slots:
    void frequency_sweep();
    int find_peak();

private:
    data_model m_amplitude_data;
    data_model m_phase_data;
    QStateMachine m_state_machine;

    int m_repetitions_counter;
    int m_num_repetitions;
    quint32 m_starting_center_frequency;
    quint32 m_current_resonant_frequency;
    QList<quint16> m_step_sizes;
    QList<quint32> m_boundaries; // how much +/- should we put on the max found in the previous state

    void cmd_frequency_sweep();
    callback_return_type bind(callback_type method);
    void callback_cmd_frequency_sweep(QByteArray return_bytes);

};

#endif // SWEEPER_H
