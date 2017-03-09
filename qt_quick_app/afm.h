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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

// This class is at the top of the object tree for the main gui thread
// It contains references to all of the peripherals either directly or through additional wrapper objects
class AFM : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_save_folder READ save_folder NOTIFY save_folder_changed)
    public:
        explicit AFM(peripheral_collection PGA_collection, peripheral_collection DAC_collection, peripheral_collection ADC_collection, Motor* motor, Sweeper* sweeper, Approacher* approacher, Scanner* scanner, ForceCurveGenerator* force_curve_generator);
        ~AFM();
        peripheral_collection PGA_collection;
        peripheral_collection DAC_collection;
        peripheral_collection ADC_collection;
        Motor* motor;
        Sweeper* sweeper;
        Approacher* approacher;
        Scanner* scanner;
        ForceCurveGenerator* force_curve_generator;
        QNetworkAccessManager* network_manager;

        Q_INVOKABLE void read_all_ADCs();
        Q_INVOKABLE void cmd_get_resistances();
        Q_INVOKABLE void callback_get_resistances(QByteArray return_bytes);
        Q_INVOKABLE void restore_defaults();
        Q_INVOKABLE void launch_folder_picker();
        Q_INVOKABLE QString save_folder();
        Q_INVOKABLE QString save_scan_data();
        Q_INVOKABLE void save_force_curve_data();
        Q_INVOKABLE void release_port();
        Q_INVOKABLE void scanner_start_state_machine_initial_checks();
//        Q_INVOKABLE void callback_scanner_start_state_machine_initial_checks(QByteArray return_bytes);
        Q_INVOKABLE void auto_sweep_initial_checks();
        Q_INVOKABLE void start_reapproaching_initial_checks();
        Q_INVOKABLE void callback_auto_sweep_initial_checks(QByteArray return_bytes);
        Q_INVOKABLE void start_approaching_initial_checks();
        Q_INVOKABLE void callback_start_approaching_initial_checks(QByteArray return_bytes);
        Q_INVOKABLE bool check_resistances();
        Q_INVOKABLE void set_check_resistances(bool check);
        Q_INVOKABLE void contact_server();
        Q_INVOKABLE void cmd_get_firmware_version();
        Q_INVOKABLE void callback_get_firmware_version(QByteArray return_bytes);
        Q_INVOKABLE QString get_software_version();
        Q_INVOKABLE QString get_firmware_version();
        Q_INVOKABLE bool get_done_init_resistances();

        static const int DAC_Table_Block_Size;

    signals:
        void trigger_mcu_reset();
        void enter_bootloader();
        void new_resistance_values(double, double, double, double, double);
        void save_folder_changed(QString);
        void scanner_start_state_machine_checks_done(bool);
        void auto_sweep_checks_done(bool);
        void start_approaching_checks_done(bool);
        void no_device_or_broken_device_error();
        void network_error();
        void check_resistances_changed(bool);
        void new_firmware_version(QString);
        void new_server_data(QVariant);
        void new_server_message(QString);

        // used strictly for UI updating - helps us show what state we're in in terms of setting up the afm
        void init_complete();
        void initializing();
        void disconnected();

    public slots:
        void init();
        void contact_server_reply(QNetworkReply*);
        void generate_get_resistances_command(const QString* master);

    private:
        // typedefs
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);

        void set_save_folder(QString);
        void set_settings();
        void init_get_resistances_command(const QString *master);
        bool check_resistance_values(QByteArray return_bytes);
        double voltage_resistance_equation(double);

        bool is_initializing;
        bool m_check_resistances;
        QString m_save_folder;
        QString m_firmware_version;
        bool m_done_init_resistances;

        static const QString GENERAL;
        static const QString AUTOSWEEP;
        static const QString APPROACH;
        static const QString settings_group_name;
        void reset_all_pga_command();
};

#endif // AFM_H
