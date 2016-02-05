#ifndef APPROACHER_H
#define APPROACHER_H

#include <QObject>
#include "afm_object.h"

class Approacher : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(double setpoint READ setpoint WRITE set_setpoint NOTIFY setpoint_changed)
    Q_PROPERTY(int state READ state NOTIFY state_changed)
public:
    explicit Approacher();
    void init();
    Q_INVOKABLE void cmd_start_auto_approach();
    Q_INVOKABLE void cmd_stop_auto_approach();
    void set_setpoint(double setpoint);
    double setpoint();
    int state();

signals:
    void setpoint_changed();
    void state_changed();

public slots:
    void handle_auto_approach_info_message(QByteArray working_response);

private:
    double m_setpoint;
    int m_state; // enum in MCU code
};

#endif // APPROACHER_H
