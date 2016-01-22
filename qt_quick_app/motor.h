#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>

class motor : public QObject
{
    Q_OBJECT
public:
    explicit motor(QObject *parent = 0);

signals:

public slots:
};

#endif // MOTOR_H