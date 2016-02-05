#ifndef APPROACHER_H
#define APPROACHER_H

#include <QObject>
#include "afm_object.h"

class Approacher : public AFMObject
{
    Q_OBJECT
public:
    explicit Approacher();
    void init();
    Q_INVOKABLE void cmd_start_auto_approach();
    Q_INVOKABLE void cmd_stop_auto_approach();

signals:

public slots:

private:
    int m_setpoint;
    int m_state; // enum in MCU code
};

#endif // APPROACHER_H
