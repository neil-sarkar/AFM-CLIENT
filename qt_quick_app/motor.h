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
    Q_PROPERTY(double state READ state WRITE set_state NOTIFY state_changed)

public:
    explicit Motor(QObject *parent = 0);
    void set_direction(int direction);
    void set_speed(double speed);
    void set_state(int state);
    double speed();
    int direction();
    int state();
    Q_INVOKABLE void run();

signals:
    void speed_changed();
    void direction_changed();
    void state_changed();


private slots:
    void generate_set_speed_command();
    void generate_set_direction_command();
    void generate_set_state_command();

public slots:


private:
    int m_direction;
    int m_state;
    double m_speed;
    QByteArray generate_set_speed_bytes();
    QByteArray generate_set_direction_bytes();
    QByteArray generate_set_state_bytes();


};

#endif // MOTOR_H
