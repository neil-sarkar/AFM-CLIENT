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
#include <QStateMachine>


class AFM : public AFMObject
{
    Q_OBJECT
    public:
        explicit AFM(QHash<int, AFMObject*> PGA_collection, QHash<int, AFMObject*> DAC_collection, QHash<int, AFMObject*> ADC_collection, Motor* motor, PID* pid, Sweeper* sweeper, Approacher* approacher);
        QHash<int, AFMObject*> PGA_collection;
        QHash<int, AFMObject*> DAC_collection;
        QHash<int, AFMObject*> ADC_collection;
        Motor* motor;
        PID* pid;
        Sweeper* sweeper;
        Approacher* approacher;

        static const int DAC_Table_Block_Size;
        void callback_set_dac_table(QByteArray buffer);

    signals:
        void scanner_initialization_done();
        void set_signal_generator_done();
        void all_data_received();
        void command_generated(CommandNode* );

    public slots:
        void init();
        void set_dac_table();
        Q_INVOKABLE void start_scan_state_machine();

        // Scan state machine methods
        void scan_state_machine_setup();
        void initialize_scan_state_machine();
        void set_signal_generator();
        void receive_data();
        void end_scan_state_machine();


    private:
        // typedefs
        QStateMachine m_scan_state_machine;
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);
        void cmd_set_dac_table(int block_number);
        void cmd_set_signal_generator();
        void cmd_start_scan();
        void cmd_step_scan();
        void callback_step_scan(QByteArray payload);
        int dac_table_page_count;

        quint16 num_lines = 16;
        quint16 num_points = 16;
        quint8 ratio = 0;
        int i = 0;
};

#endif // AFM_H
