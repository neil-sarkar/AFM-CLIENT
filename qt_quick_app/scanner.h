#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include "afm_object.h"
#include <QStateMachine>
#include "pid.h"
#include "dac.h"
#include "scan_data.h"

class Scanner : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 m_num_averages READ num_averages WRITE set_num_averages NOTIFY num_averages_changed)
public:
    explicit Scanner(PID*, AFMObject* dac);
    void init();
    PID* pid;
    DAC* fine_z;

    Q_INVOKABLE quint8 num_averages();
    Q_INVOKABLE void set_num_averages(int num_averages);

signals:
    void scanner_initialization_done();
    void set_signal_generator_done();
    void all_data_received();
    void reset();
    void new_forward_offset_data(QVariantList); // eventually make it convert the data struct into json
    void new_reverse_offset_data(QVariantList);
    void started_scan_state_machine();

    // property changes
    void num_averages_changed(int);

public slots:
    // Scan state machine methods
    void initialize_scan_state_machine();
    void set_signal_generator();
    void receive_data();
    void end_scan_state_machine();
    Q_INVOKABLE void start_state_machine();
    Q_INVOKABLE void pause_state_machine();
    Q_INVOKABLE void resume_state_machine();
    Q_INVOKABLE void emit_dummy_data();

private:
    QStateMachine m_state_machine;
    quint16 m_num_lines;
    quint16 m_num_points;
    quint8 m_ratio;
    quint8 m_dwell_time;
    quint8 m_num_averages;

    int m_num_points_received;
    void cmd_set_signal_generator();
    void cmd_start_scan();
    void cmd_step_scan();
    void cmd_set_dwell_time();
    void cmd_set_num_averages();
    void callback_step_scan(QByteArray payload);
    bool is_scanning_forward();
    callback_return_type bind(void (Scanner::*method)(QByteArray));
    typedef void (Scanner::*callback_type)(QByteArray);
    bool scanning_forward;
    bool m_should_pause;

    ScanData* forward_data;
    ScanData* reverse_data;
};

#endif // SCANNER_H
