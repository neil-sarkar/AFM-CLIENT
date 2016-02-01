#ifndef PID_H
#define PID_H

#include <QObject>
#include "command_node.h"

class PID : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float proportional READ proportional WRITE set_proportional NOTIFY proportional_changed)
    Q_PROPERTY(float integral READ integral WRITE set_integral NOTIFY integral_changed)
    Q_PROPERTY(float derivative READ derivative WRITE set_derivative NOTIFY derivative_changed)
    Q_PROPERTY(float set_point READ set_point WRITE set_set_point NOTIFY set_point_changed)

public:
    explicit PID();
    float proportional();
    float integral();
    float derivative();
    float set_point();
    void set_proportional(float p);
    void set_integral(float i);
    void set_derivative(float d);
    void set_set_point(float s);

signals:
    void proportional_changed();
    void integral_changed();
    void derivative_changed();
    void set_point_changed();
    void command_generated(CommandNode* node);

public slots:

private:
    float m_proportional; // should these floats be some kind of portable type?
    float m_integral;
    float m_derivative;
    float m_set_point;
    void cmd_set_proportional();
    void cmd_set_integral();
    void cmd_set_derivative();
    void cmd_set_set_point();
    static constexpr double MAX_VOLTAGE = 2.5;
    static constexpr int RESOLUTION = 4095;
    static constexpr double SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;
};

#endif // PID_H
