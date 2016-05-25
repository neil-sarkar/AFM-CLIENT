#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QTimer>
#include <QQuickItem>
#include <QString>
#include "command_node.h"
#include "afm_object.h"

class Motor : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(int m_speed READ speed WRITE set_speed NOTIFY speed_changed)
    Q_PROPERTY(int m_direction READ direction WRITE set_direction NOTIFY direction_changed)
    Q_PROPERTY(int m_state READ state WRITE set_state NOTIFY state_changed)
    Q_PROPERTY(int m_microstep READ microstep WRITE set_microstep NOTIFY microstep_changed)

public:
    explicit Motor();
    int speed();
    int direction();
    int state();
    int microstep();
    void init();
    Q_INVOKABLE void cmd_single_step();
    Q_INVOKABLE void run_continuous();
    Q_INVOKABLE void cmd_stop_continuous();
    Q_INVOKABLE void cmd_set_micro_step();
    Q_INVOKABLE void set_direction(int direction);
    Q_INVOKABLE void set_speed(int speed);
    Q_INVOKABLE void set_state(int state);
    Q_INVOKABLE void set_microstep(int microstep);

signals:
    void speed_changed(int);
    void direction_changed(int);
    void state_changed(int);
    void microstep_changed(int);

private slots:
    void cmd_set_state_asleep();

private:
    int m_direction;
    int m_state;
    int m_speed;
    int m_microstep;
    void cmd_set_speed();
    void cmd_set_direction();
    void cmd_set_state_awake();
    void cmd_run_continuous();
    void reset_timeout_timer(QByteArray result);
    callback_return_type bind(void (Motor::*method)(QByteArray));
    typedef void (Motor::*callback_type)(QByteArray);
    QTimer* timeout_timer;

    struct PayloadConstants {
        const unsigned char MotorApproach = 0x62;
        const unsigned char MotorRetract = 0x66;
    } PayloadConstants;

    struct StatusConstants {
        const int Approach = 1;
        const int Retract = 0;
        const int Awake = 1;
        const int Asleep = 0;

        // put these in an enum to match embedded code
        const int StepFull = 0;
        const int Step2Micro = 1;
        const int Step4 = 2;
        const int Step8 = 3;
        const int Step16 = 4;
        const int Step32 = 5;
    } StatusConstants;

    static const int Timeout_Milliseconds;

};

#endif // MOTOR_H
