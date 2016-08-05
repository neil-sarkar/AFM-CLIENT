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


// This class is at the top of the object tree for the main gui thread
// It contains references to all of the peripherals either directly or through additional wrapper objects
class AFM : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_save_folder READ save_folder NOTIFY save_folder_changed)
    public:
        explicit AFM(peripheral_collection PGA_collection, peripheral_collection DAC_collection, peripheral_collection ADC_collection, Motor* motor, Sweeper* sweeper, Approacher* approacher, Scanner* scanner, ForceCurveGenerator* force_curve_generator);
        peripheral_collection PGA_collection;
        peripheral_collection DAC_collection;
        peripheral_collection ADC_collection;
        Motor* motor;
        Sweeper* sweeper;
        Approacher* approacher;
        Scanner* scanner;
        ForceCurveGenerator* force_curve_generator;

        Q_INVOKABLE void read_all_ADCs();
        Q_INVOKABLE void cmd_get_resistances();
        Q_INVOKABLE void callback_get_resistances(QByteArray return_bytes);
        Q_INVOKABLE void restore_defaults();
        Q_INVOKABLE bool launch_folder_picker();
        Q_INVOKABLE QString save_folder();
        Q_INVOKABLE void save_scan_data();
        Q_INVOKABLE void save_force_curve_data();
        Q_INVOKABLE void release_port();

        static const int DAC_Table_Block_Size;

    signals:
        void command_generated(CommandNode*);
        void trigger_mcu_reset();
        void new_resistance_values(double, double, double, double, double);
        void save_folder_changed(QString);
        
        // used strictly for UI updating - helps us show what state we're in in terms of setting up the afm
        void init_complete();
        void initializing();
        void disconnected();

    public slots:
        void init();

    private:
        // typedefs
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);

        void set_save_folder(QString);
        void set_settings();
        double voltage_resistance_equation(double);

        bool is_initializing;
        QString m_save_folder;
        static const QString settings_group_name;
};

#endif // AFM_H
