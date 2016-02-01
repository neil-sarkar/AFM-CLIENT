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
        explicit AFM(QHash<QString, AFMObject*> PGA_collection, QHash<QString, AFMObject*> DAC_collection, QHash<QString, AFMObject*> ADC_collection, Motor* motor, PID* pid);
        QHash<QString, AFMObject*> PGA_collection;
        QHash<QString, AFMObject*> DAC_collection;
        QHash<QString, AFMObject*> ADC_collection;
        Motor* motor;
        PID* pid;

    signals:

    public slots:
    private:
        void init();


};

#endif // AFM_H
