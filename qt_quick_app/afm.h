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
        explicit AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, PID* pid);
        QHash<int, AFMObject*> PGA_collection;
        QHash<int, AFMObject*> DAC_collection;
        QHash<int, AFMObject*> ADC_collection;
        Motor* motor;
        PID* pid;

    signals:

    public slots:
        void init();

    private:





};

#endif // AFM_H
