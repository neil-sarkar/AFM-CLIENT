#ifndef AFM_H
#define AFM_H

#include <QObject>
#include "pga.h"
#include "adc.h"
#include "dac.h"
#include "motor.h"
#include "pid.h"

class AFM : public QObject
{
    Q_OBJECT
    public:
        explicit AFM(QHash<QString, PGA*> PGA_collection, QHash<QString, DAC*> DAC_collection, QHash<QString, ADC*> ADC_collection, Motor* motor, PID* pid);
        QHash<QString, PGA*> PGA_collection;
        QHash<QString, DAC*> DAC_collection;
        QHash<QString, ADC*> ADC_collection;
        Motor* motor;
        PID* pid;

    signals:

    public slots:
    private:


};

#endif // AFM_H
