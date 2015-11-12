#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QMessageBox>
#include <myplot.h>
#include <qtimer.h>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <queue>
#include <returnBuffer.h>
#include <math.h>
#include <qwt3d_gridplot.h>
#include <qwt3d_function.h>
#include <ui_mainwindow.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QTime>
#include <send_worker.h>
#include <QThread>
#include <QObject>
//#include <armadillo>
#include <globals.h>
#include <QSignalMapper>
#include <QStatusBar>
#include <commandNode.h>

#include <QProcess>

#define MAX_AUTOAPPR_FAULT_COUNT 20

using std::queue;
using namespace Qwt3D;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    queue<commandNode*>& commandQueue;
    queue<returnBuffer*>& returnQueue;
    afm_data * scan_result;

    enum UserStepMotOp {APPR, RETR, STOP};
    //Also needs constexpr int MainWindow::UserSpd_to_Microsteps[]; in the global scope of C++ file to work
    constexpr static  int UserSpd_to_Microsteps[5] = {3,3,4,3,1};
    constexpr static  double UserSpd_to_Speed[5] = {0,20000,26300,26300,26300};

public:
    //nanoiAFM afm;
    QList<QSerialPortInfo> detectedSerialPortsList; //buffer for serial ports
    MainWindow(QWidget *parent,
               queue<commandNode*>& _queue,
               queue<returnBuffer*>& _returnqueue) :
        QMainWindow(parent),
        commandQueue(_queue),
        returnQueue(_returnqueue){}

    //public functions
    void abort();
    void refreshPortsList();
    void SetMaxDACValues();
    void Initialize();
    void CreateFreqSweepGraph(QVector<double> amplitudeData,
                              QVector<double> phaseData,
                              int bytesRead);
    void setADC5(float val){adc5 = val;}
    void setDAC8(float val){dac8 = val;}
    bool getContinuousStep(){return continuousStep;}
    bool getAutoApproach(){return isAutoApproach;}
    float getAutoApproachComparison(){return autoApproachComparison;}
    float getADC5(){return adc5;}
    int getCurrTab(){return currTab;}

    void closeEvent(QCloseEvent *event);
    ~MainWindow();

protected:
    //void timerEvent( QTimerEvent * );

signals:
    void finished();
    void SweepFinished();

public slots:
    //used for the scan graph settings
    void on_buttonAutoApproachClient_clicked(bool checked);
    void updateStatusBar(QString _string);
    void pickPlotStyle( QAction* );
    void setLeftGrid( bool b );
    void setRightGrid( bool b );
    void setCeilGrid( bool b );
    void setFloorGrid( bool b );
    void setFrontGrid( bool b );
    void setBackGrid( bool b );
    void setGrid( Qwt3D::SIDE, bool );
    void pickCoordSystem( QAction* );
    void pickFloorStyle( QAction* );
    void showNormals(bool val);
    //slots for updates from other threads
    void serialError();
    void afmWorkerError();
    void setDDSFrequency(const QPointF &p);
    void updatePlot(double _signal, int _plot);

private:
    QMessageBox msgBox;
    //eventworker *eventWorker;
    //QMutex mutex;
    enum TabType{
        Control,
        Scan,
        Frequency,
        Approach,
        Signal,
        NumTabs
    };
    Ui::MainWindow *ui;

    void CreateGraphs();
    void displayComPortInfo(const QSerialPortInfo& info);

    int ioTimer;            // timer id for ADC/DAC read
    QTimer *dequeueTimer;     // dequeue timer to empty the return buffer
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
    QTimer *approachTimer;
    MyPlot::Plot freqPlot;
    MyPlot::Plot phasePlot;
    MyPlot::Plot approachPlot;
    MyPlot::Plot signalPlot1;
    MyPlot::Plot signalPlot2;
    MyPlot::Plot forceCurve;
    GridPlot scanPlot;
    int time;
    int freqRetVal;
    int currTab;
    float dac8;
    float adc5;
    bool useBridgeSignalAsSetpoint;
    bool continuousStep;
    bool isAutoApproach;
    float autoApproachComparison;
    QFuture<void> *future;
    QFutureWatcher<void> *watcher;

    /* Auto Approach Feature */
    QTimer *task1_timer;   //For auto approach
    int autoapproach_state = 0;
    bool autoapproach_abort = false;
    double autoapproach_setpoint = 0;
    double autoappr_setpoint = 1; //A made-up value so we dont crash and burnnnn
    double autoappr_measurement_init = 1;
    double autoappr_measurement = 1;
    int autoapproach_fault_count = 0;

    //placeholders for returned data
    returnBuffer* _buffer;
    float zOffsetCoarse;
    float zOffsetFine;
    float bfrd1;
    float bfrd2;
    float bfrd3;
    float adcZ;
    float br2;
    float br1;
    float zAmp;
    float y1;
    float y2;
    float x1;
    float x2;
    double signal;
    double offset;
    double phase;
    double *scandata[256];
    int row;


    void stepmot_user_control(UserStepMotOp operation, bool isStep);
    UserStepMotOp stepmot_callback_operation;

    int auto_freqsweep_state=0;
    void auto_freqsweep(double max_amp, double max_amp_freq);

    int dac_table_current_block=0;
    void set_DAC_table_state_machine(int type);

    int scan_state = 0;

private slots:
    void MainWindowLoop();
    void dequeueReturnBuffer();
    void generalTimerUpdate();
    void approachTimerUp();
    void finishedThread();

    /* Stepper motor and auto approach */
    void autoApproach_state_machine();
    void stepmot_user_control_callback();

    /* Scan */
    void scan_state_machine();


    // GUI elements
    void on_sld_stepmot_speed_valueChanged(int value);
    void on_cbo_microstep_currentIndexChanged(int index);
    void on_btn_stepmot_cont_go_clicked();
    void on_btn_stepmot_cont_stop_clicked();
    void on_btn_stepmot_singlestep_clicked();
    void on_radio_stepmot_fwd_clicked();
    void on_radio_stepmot_back_clicked();
    void on_btn_stepmot_sleep_clicked();
    void on_btn_stepmot_wake_clicked();
    void on_btn_autoappr_go_clicked();
    void on_btn_autoappr_stop_clicked();
    void on_retreatButton_clicked();
    void on_stepButton_clicked();
    void on_spnOffsetVoltage_valueChanged(double arg1);
    void on_spnBridgeVoltage_valueChanged(double arg1);
    void on_spnPidValueP_valueChanged(double arg1);
    void on_spnPidValueI_valueChanged(double arg1);
    void on_spnPidValueD_valueChanged(double arg1);
    void on_spnPidSetpoint_valueChanged(double arg1);
    void on_cboComPortSelection_currentIndexChanged(int index);
    void on_refreshSpinBox_valueChanged(int arg1);
    void on_pushButton_22_clicked(bool checked);
    void on_pushButton_4_clicked(bool checked);
    void on_pushButton_5_clicked(bool checked);
    void on_checkBox_clicked(bool checked);
    void on_sldAmplitudeVoltage_3_valueChanged(int value);
    void on_buttonCurrValuePidSetpoint_clicked(bool checked);
    void on_sweepButton_clicked();
    void on_useCurrFreqVal_clicked();
    void on_pushButton_6_clicked();
    void on_buttonWriteToDAC_clicked();
    void on_buttonReadIO_clicked();
    void on_freqAutoScale_clicked();
    void on_spnFrequencyVoltage_2_valueChanged(double arg1);
    void on_buttonAutoApproachMCU_clicked(bool checked);
    void on_approachButton_clicked();
    void on_setMaxDACValuesButton_clicked();
    void on_calibrateButton_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_continuousButton_pressed();
    void on_continuousButton_released();
    void on_gwyddionButton_clicked();
    void on_spnBoxFineZRange_valueChanged(int arg1);
    void on_spnBoxCoarseZ_valueChanged(double arg1);
    void on_spnBoxFineZ_valueChanged(double arg1);
    void on_btnSetScanParameters_clicked();
    void on_spnFrequencyVoltage_valueChanged(double arg1);
    void on_btnForceCurve_clicked();
    void on_btn_pid_on_clicked();
    void on_btn_pid_off_clicked();
    void on_btn_stepmot_user_up_2_pressed();
    void on_btn_stepmot_user_up_2_released();
    void on_sld_stepmot_user_spd_valueChanged(int value);
    void on_btn_stepmot_user_up_pressed();
    void on_btn_stepmot_user_up_released();
    void on_btn_stepmot_user_down_pressed();
    void on_btn_stepmot_user_down_released();
    void on_btn_auto_freqsweep_clicked();
    void on_btn_setDACTable_clicked();
    void on_btn_siggen_clicked();
    void on_btn_scan_start_clicked();
    void on_btn_scan_next_clicked();
    void on_btn_re_init_clicked();
    void on_btn_scan_begin_clicked();
    void on_btn_scan_stop_clicked();
    void on_pushButton_clicked();
    void on_btn_print_offset_clicked();
    void on_btn_set_pga_clicked();
};

#endif // MAINWINDOW_H
