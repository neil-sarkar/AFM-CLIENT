#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QTimer>
#include <QQuickItem>

class Motor : public QObject
{
    Q_PROPERTY(double speed READ speed WRITE set_speed NOTIFY speed_changed)
    Q_OBJECT


public:
    explicit Motor(QObject *parent = 0);
    void set_direction(int direction);
    void set_speed(double speed);
    void set_state(int state);
    void setRootObject(QQuickItem* root);
    double speed();

signals:
    void speed_changed();

public slots:
    void run_motor();

private:
    int m_direction;
    int m_state;
    double m_speed;
    QTimer* sleep_timer;

    // UI
    QObject* root_ui_object;

};

#endif // MOTOR_H
