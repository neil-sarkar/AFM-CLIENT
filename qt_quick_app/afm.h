#ifndef AFM_H
#define AFM_H

#include <QObject>
#include "pga.h"
#include "adc.h"
#include "dac.h"
#include "dds.h"
#include "motor.h"
#include "pid.h"
#include "afm_object.h"

class AFM : public AFMObject
{
    Q_OBJECT
    public:
        explicit AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, PID* pid, DDS* dds);
        QHash<int, AFMObject*> PGA_collection;
        QHash<int, AFMObject*> DAC_collection;
        QHash<int, AFMObject*> ADC_collection;
        Motor* motor;
        PID* pid;
        DDS* dds;

        Q_INVOKABLE void frequency_sweep();

    signals:

    public slots:
        void init();

    private:

        void cmd_frequency_sweep();
        void callback_cmd_frequency_sweep(QByteArray);

        // typedefs
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);






};

#endif // AFM_H
