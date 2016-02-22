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
    Q_PROPERTY(quint8 m_dwell_time READ dwell_time WRITE set_dwell_time NOTIFY dwell_time_changed)
    Q_PROPERTY(quint8 m_send_back_count READ send_back_count WRITE set_send_back_count NOTIFY send_back_count_changed)
    Q_PROPERTY(quint16 m_num_rows READ num_rows WRITE set_num_rows NOTIFY num_rows_changed)
    Q_PROPERTY(quint16 m_num_columns READ num_columns WRITE set_num_columns NOTIFY num_columns_changed)
public:
    explicit Scanner(PID*, AFMObject* dac);
    void init();
    PID* pid;
    DAC* fine_z;

    Q_INVOKABLE quint8 num_averages();
    Q_INVOKABLE void set_num_averages(int num_averages);
    Q_INVOKABLE quint8 dwell_time();
    Q_INVOKABLE void set_dwell_time(int dwell_time);
    Q_INVOKABLE quint8 send_back_count();
    Q_INVOKABLE void set_send_back_count(int send_back_count);
    Q_INVOKABLE quint16 num_rows();
    Q_INVOKABLE void set_num_rows(int num_rows);
    Q_INVOKABLE quint16 num_columns();
    Q_INVOKABLE void set_num_columns(int num_columns);

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
    void dwell_time_changed(int);
    void send_back_count_changed(int);
    void num_rows_changed(int);
    void num_columns_changed(int);

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
    quint16 m_num_rows;
    quint16 m_num_columns;
    quint8 m_ratio;
    quint8 m_dwell_time;
    quint8 m_num_averages;
    quint8 m_send_back_count;

    int m_num_columns_received;
    void cmd_set_signal_generator();
    void cmd_start_scan();
    void cmd_step_scan();
    void cmd_set_dwell_time();
    void cmd_set_num_averages();
    void cmd_set_send_back_count();
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
