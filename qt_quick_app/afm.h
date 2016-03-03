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
#include "force_curve_generator.h"
#include <QStateMachine>


class AFM : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_save_folder READ save_folder NOTIFY save_folder_changed)
    public:
        explicit AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, Sweeper* sweeper, Approacher* approacher, Scanner* scanner, ForceCurveGenerator* force_curve_generator);
        QHash<int, AFMObject*> PGA_collection;
        QHash<int, AFMObject*> DAC_collection;
        QHash<int, AFMObject*> ADC_collection;
        Motor* motor;
        Sweeper* sweeper;
        Approacher* approacher;
        Scanner* scanner;
        ForceCurveGenerator* force_curve_generator;

        static const int DAC_Table_Block_Size;
        void callback_set_dac_table(QByteArray buffer);
        Q_INVOKABLE void read_all_ADCs();
        Q_INVOKABLE void cmd_get_resistances();
        Q_INVOKABLE void callback_get_resistances(QByteArray return_bytes);
        Q_INVOKABLE void restore_defaults();
        Q_INVOKABLE void launch_folder_picker();
        Q_INVOKABLE QString save_folder();
        Q_INVOKABLE void save_scan_data();
        Q_INVOKABLE void save_force_curve_data();

    signals:
        void command_generated(CommandNode*);
        void dac_table_set();
        void trigger_mcu_reset();
        void new_resistance_values(double, double, double, double, double);
        void save_folder_changed(QString);

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
        void set_save_folder(QString);
        QString m_save_folder;


};

#endif // AFM_H
