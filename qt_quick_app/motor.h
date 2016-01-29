#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QTimer>
#include <QQuickItem>
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
    Q_INVOKABLE void single_step();
    void run_continuous();

signals:
    // MODIFY signals for Q_PROPERTY macros
    void speed_changed();
    void direction_changed();
    void state_changed();

    // Cross-Thread
    void command_generated(CommandNode*);

private slots:
    void cmd_set_speed();
    void cmd_set_direction();
    void cmd_set_state();

public slots:


private:
    int m_direction;
    int m_state;
    int m_speed;

};

#endif // MOTOR_H
