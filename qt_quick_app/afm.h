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
#include "sweeper.h"
#include "approacher.h"
#include "scanner.h"
#include <QStateMachine>


class AFM : public AFMObject
{
    Q_OBJECT
    public:
        explicit AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, Sweeper* sweeper, Approacher* approacher, Scanner* scanner);
        QHash<int, AFMObject*> PGA_collection;
        QHash<int, AFMObject*> DAC_collection;
        QHash<int, AFMObject*> ADC_collection;
        Motor* motor;
        Sweeper* sweeper;
        Approacher* approacher;
        Scanner* scanner;

        static const int DAC_Table_Block_Size;
        void callback_set_dac_table(QByteArray buffer);
        void callback_generate_force_curve(QByteArray buffer);
        Q_INVOKABLE void cmd_generate_force_curve();
        Q_INVOKABLE void read_all_ADCs();
        Q_INVOKABLE void cmd_get_resistances();
        Q_INVOKABLE void callback_get_resistances(QByteArray return_bytes);
        Q_INVOKABLE void restore_defaults();

    signals:
        void command_generated(CommandNode*);
        void dac_table_set();
        void trigger_mcu_reset();
        void new_resistance_values(double, double, double, double, double);
        void new_approaching_amplitude_data(QVariantList);
        void new_approaching_phase_data(QVariantList);
        void new_retracting_amplitude_data(QVariantList);
        void new_retracting_phase_data(QVariantList);

    public slots:
        void init();
        void set_dac_table();

    private:
        // typedefs
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);
        void cmd_set_dac_table(int block_number);
        int dac_table_page_count;
        double voltage_resistance_equation(double);
};

#endif // AFM_H
