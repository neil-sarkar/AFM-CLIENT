#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <afm.h>
#include <QApplication>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QMessageBox>
#include "plot.h"
#include <qtimer.h>
//#include <XYGenerator.h>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <serialworker.h>
#include <commandqueue.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    nanoiAFM afm;
    QList<QSerialPortInfo> detectedSerialPorts;

    explicit MainWindow(QWidget *parent = 0);
    void autoApproach(nanoiAFM* afm);
    ~MainWindow();

protected:
    void timerEvent( QTimerEvent * );

private:
    QThread *serialThread;
    serialworker *serialWorker;
    commandqueue *commandQueue;

private slots:
    void updateGraph();
    void generalTimerUpdate();
    void finishedThread();

    // GUI elements
    void on_spnOffsetVoltage_valueChanged(double arg1);

    void on_spnBridgeVoltage_valueChanged(double arg1);

    void on_spnFrequencyVoltage_valueChanged(double arg1);

    void on_spnPidValueP_valueChanged(double arg1);

    void on_spnPidValueI_valueChanged(double arg1);

    void on_spnPidValueD_valueChanged(double arg1);

    void on_spnPidSetpoint_valueChanged(double arg1);

    void on_btnPidToggle_toggled(bool checked);

    void on_cboComPortSelection_currentIndexChanged(int index);

    void on_refreshSpinBox_valueChanged(int arg1);


    void on_pushButton_22_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void on_pushButton_5_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

    void on_sldAmplitudeVoltage_3_valueChanged(int value);

    void on_buttonAutoApproachClient_clicked(bool checked);

    void on_retreatButton_clicked();

    void on_stepButton_clicked();

    void on_continuousButton_clicked(bool checked);

    void on_buttonCurrValuePidSetpoint_clicked(bool checked);

    void on_sweepButton_clicked();


    void on_useCurrFreqVal_clicked();

   // void on_retreatButton_2_clicked();

    void on_pushButton_6_clicked();

   // void on_pushButton_22_clicked();

    void on_buttonWriteToDAC_clicked();

    void on_buttonReadIO_clicked();

    void on_btnPidToggle_clicked(bool checked);

    void on_freqAutoScale_clicked(bool checked);

    void on_spnFrequencyVoltage_2_valueChanged(double arg1);

    void on_buttonSendSweep_clicked();

    void on_buttonAutoApproachMCU_clicked();

    void on_writeCharacter_clicked();

private:

    enum TabType{
        Control,
        Scan,
        Frequency,
        Approach,
        Signal,
        NumTabs
    };
    Ui::MainWindow *ui;

    void displayComPortInfo(const QSerialPortInfo& info);

    int ioTimer;            // timer id for ADC/DAC read
    QTimer *graphTimer;     // graph timer which can change intervals
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
    float dac8;
    float adc5;
    Plot *freqPlot;
    Plot *approachPlot;
    Plot *signalPlot1;
    Plot *signalPlot2;
    int time;
    bool useBridgeSignalAsSetpoint;
    bool continuousStep;
    bool isAutoApproach;
    float autoApproachComparison;
    QFuture<void> *future;
    QFutureWatcher<void> *watcher;
};

#endif // MAINWINDOW_H
