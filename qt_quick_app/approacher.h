#ifndef APPROACHER_H
#define APPROACHER_H

#include <QObject>
#include "afm_object.h"
#include "pid.h"
#include "adc.h"

class Approacher : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(int state READ state NOTIFY state_changed)
public:
    explicit Approacher(PID*, AFMObject*);
    void init();
    Q_INVOKABLE void cmd_start_auto_approach();
    Q_INVOKABLE void cmd_stop_auto_approach();
    int state();

signals:
    void state_changed();

public slots:
    void handle_auto_approach_info_message(QByteArray working_response);

private:
    double m_setpoint;
    int m_state; // enum in MCU code
    PID* m_pid;
    ADC* m_adc;
};

#endif // APPROACHER_H
