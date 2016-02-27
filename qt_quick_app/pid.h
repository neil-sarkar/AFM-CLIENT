#ifndef PID_H
#define PID_H

#include <QObject>
#include "command_node.h"
#include "afm_object.h"

class PID : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(float proportional READ proportional WRITE set_proportional NOTIFY proportional_changed)
    Q_PROPERTY(float integral READ integral WRITE set_integral NOTIFY integral_changed)
    Q_PROPERTY(float derivative READ derivative WRITE set_derivative NOTIFY derivative_changed)
    Q_PROPERTY(float setpoint READ setpoint WRITE set_setpoint NOTIFY setpoint_changed)
    Q_PROPERTY(bool enabled READ enabled WRITE set_enabled NOTIFY enabled_changed)

public:
    explicit PID();
    Q_INVOKABLE float proportional();
    Q_INVOKABLE float integral();
    Q_INVOKABLE float derivative();
    Q_INVOKABLE float setpoint();
    Q_INVOKABLE bool enabled();
    Q_INVOKABLE void set_proportional(float p);
    Q_INVOKABLE void set_integral(float i);
    void set_derivative(float d);
    Q_INVOKABLE void set_setpoint(float s);
    void init();
    Q_INVOKABLE void set_enabled(bool e = true);
    Q_INVOKABLE void set_disabled();
    void set_settings();
    void update_settings(QString, QVariant);

    static constexpr double MAX_VOLTAGE = 2.5; // redundant - from ADC
    static constexpr int RESOLUTION = 4095;
    static constexpr double SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;


signals:
    void proportional_changed(float);
    void integral_changed(float);
    void derivative_changed(float);
    void setpoint_changed(float);
    void enabled_changed(bool);

public slots:

private:
    float m_proportional; // should these floats be some kind of portable type?
    float m_integral;
    float m_derivative;
    float m_setpoint;
    bool m_enabled;
    void cmd_set_proportional();
    void cmd_set_integral();
    void cmd_set_derivative();
    void cmd_set_setpoint();
    void cmd_enable();
    void cmd_disable();
    static const QString settings_group_name;
};

#endif // PID_H
