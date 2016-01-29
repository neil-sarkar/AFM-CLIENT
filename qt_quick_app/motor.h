#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QTimer>
#include <QQuickItem>
#include <QString>
#include "command_node.h"

class Motor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE set_speed NOTIFY speed_changed)
    Q_PROPERTY(int direction READ direction WRITE set_direction NOTIFY direction_changed)
    Q_PROPERTY(int state READ state WRITE set_state NOTIFY state_changed)

public:
    explicit Motor(QObject *parent = 0);
    void set_direction(int direction);
    void set_speed(double speed);
    void set_state(int state);
    int speed();
    int direction();
    int state();
    Q_INVOKABLE void cmd_single_step();
    Q_INVOKABLE void cmd_run_continuous();
    Q_INVOKABLE void cmd_stop_continuous();

signals:
    // MODIFY signals for Q_PROPERTY macros
    void speed_changed();
    void direction_changed();
    void state_changed();

    // Cross-Thread
    void command_generated(CommandNode*);

public slots:


private:
    int m_direction;
    int m_state;
    int m_speed;
    int m_microstep;
    void cmd_set_speed();
    void cmd_set_direction();
    void cmd_set_state();
    void cmd_set_micro_step();

    struct Commands {
        const unsigned char SetDirection = 0x36;
        const unsigned char SetStateAwake = 0x35; // might want to have one function for each sleep and awake
        const unsigned char SetStateAsleep = 0x34;
        const unsigned char SetSpeed = 0x32;
        const unsigned char RunContinuous = 0x33;
        const unsigned char StopContinuous = 0x37;
        const unsigned char SetSingleStep = 0x31;
        const unsigned char SetMicroStep = 0x30;
    } Commands;

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

};

#endif // MOTOR_H
