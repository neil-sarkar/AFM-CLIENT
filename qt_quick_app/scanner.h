#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include "afm_object.h"
#include <QStateMachine>
#include "pid.h"

class Scanner : public AFMObject
{
    Q_OBJECT
public:
    explicit Scanner(PID*);
    void init();
    PID* pid;

signals:
    void scanner_initialization_done();
    void set_signal_generator_done();
    void all_data_received();

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
    void cmd_set_signal_generator();
    void cmd_start_scan();
    void cmd_step_scan();
    void callback_step_scan(QByteArray payload);
    callback_return_type bind(void (Scanner::*method)(QByteArray));
    typedef void (Scanner::*callback_type)(QByteArray);
};

#endif // SCANNER_H
