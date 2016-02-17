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
public:
    explicit Scanner(PID*, AFMObject* dac);
    void init();
    PID* pid;
    DAC* fine_z;

signals:
    void scanner_initialization_done();
    void set_signal_generator_done();
    void all_data_received();
    void new_forward_offset_data(QVariantList); // eventually make it convert the data struct into json
    void new_reverse_offset_data(QVariantList);

public slots:
    // Scan state machine methods
    void initialize_scan_state_machine();
    void set_signal_generator();
    void receive_data();
    void end_scan_state_machine();

    Q_INVOKABLE void start_state_machine();

private:
    QStateMachine m_state_machine;
    quint16 m_num_lines;
    quint16 m_num_points;
    quint8 m_ratio;
    quint8 m_dwell_time;


    int m_num_points_received;
    void cmd_set_signal_generator();
    void cmd_start_scan();
    void cmd_step_scan();
    void cmd_set_dwell_time();
    void callback_step_scan(QByteArray payload);
    bool is_scanning_forward();
    callback_return_type bind(void (Scanner::*method)(QByteArray));
    typedef void (Scanner::*callback_type)(QByteArray);
    bool scanning_forward;

    ScanData* forward_data;
    ScanData* reverse_data;
};

#endif // SCANNER_H
