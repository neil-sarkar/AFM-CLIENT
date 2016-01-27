#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QTimer>
#include <QQuickItem>

class Motor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed WRITE set_speed NOTIFY speed_changed)
    Q_PROPERTY(double direction READ direction WRITE set_direction NOTIFY direction_changed)


public:
    explicit Motor(QObject *parent = 0);
    void set_direction(int direction);
    void set_speed(double speed);
    void set_state(int state);
    double speed();
    int direction();

signals:
    void speed_changed();
    void direction_changed();

public slots:
    void run();

private:
    int m_direction;
    int m_state;
    double m_speed;
    QTimer* sleep_timer;

    // UI
    QObject* root_ui_object;

};

#endif // MOTOR_H
