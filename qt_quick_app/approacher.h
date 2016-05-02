#ifndef APPROACHER_H
#define APPROACHER_H

#include <QObject>
#include "afm_object.h"
#include "pid.h"
#include "adc.h"

class Approacher : public AFMObject
// This class handles everything to do with the approach mechanism apart from communication

{
    Q_OBJECT
//    Q_PROPERTY(int state READ state NOTIFY new_data)
public:
    explicit Approacher(PID*, AFMObject*);
    void init();
    Q_INVOKABLE void cmd_start_auto_approach();
    Q_INVOKABLE void cmd_stop_auto_approach();
    Q_INVOKABLE void cmd_get_state();
    int state();

signals:
    void new_state(int state, int complete);

public slots:
    void handle_auto_approach_info_message(QByteArray working_response);

private:
    void callback_get_state(QByteArray payload);
    double m_setpoint;
    int m_state; // enum in MCU code
    PID* m_pid;
    ADC* m_adc;
    callback_return_type bind(void (Approacher::*method)(QByteArray));
    typedef void (Approacher::*callback_type)(QByteArray);
};

#endif // APPROACHER_H
