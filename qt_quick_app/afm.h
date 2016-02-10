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

    signals:
        void command_generated(CommandNode*);
        void dac_table_set();

    public slots:
        void init();
        void set_dac_table();

    private:
        // typedefs
        callback_return_type bind(void (AFM::*method)(QByteArray));
        typedef void (AFM::*callback_type)(QByteArray);
        void cmd_set_dac_table(int block_number);
        int dac_table_page_count;
};

#endif // AFM_H
