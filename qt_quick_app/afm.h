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
#include <QStateMachine>


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

        QStateMachine* sweep_machine;
        QVector<double> amplitude_data;
        QVector<double> phase_data;


    signals:
        void sweep_done();
        void peak_detection_done();


    public slots:
        void init();
        Q_INVOKABLE void coarse_frequency_sweep();
        Q_INVOKABLE void fine_frequency_sweep();
        Q_INVOKABLE void start_state_machine();
        void find_peak();

    private:

        void cmd_frequency_sweep();
        void callback_cmd_frequency_sweep(QByteArray);



        // typedefs
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);







};

#endif // AFM_H
