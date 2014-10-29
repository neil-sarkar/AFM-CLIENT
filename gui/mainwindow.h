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
#include <plot.h>
#include <qtimer.h>
//#include <XYGenerator.h>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <serialworker.h>
#include <queue>
#include <returnBuffer.h>
#include <globals.h>
#include <eventworker.h>

using std::queue;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    queue<commandNode*>& commandQueue;
    queue<returnBuffer*>& returnQueue;

public:
    //nanoiAFM afm;
    QList<QSerialPortInfo> detectedSerialPorts;
    MainWindow(QWidget *parent, queue<commandNode*>& _queue,queue<returnBuffer*>& _returnqueue) :
        QMainWindow(parent),
        commandQueue(_queue),
        returnQueue(_returnqueue) {}

    void autoApproach(nanoiAFM* afm);
    void abort();
    void SetPorts(returnBuffer*_node);
    void SetMaxDACValues();
    void Initialize();
    void setADC5(float val){adc5 = val;}
    void setDAC8(float val){dac8 = val;}
    bool getContinuousStep(){return continuousStep;}
    bool getAutoApproach(){return isAutoApproach;}
    float getAutoApproachComparison(){return autoApproachComparison;}
    float getADC5(){return adc5;}
    int getCurrTab(){return currTab;}

    ~MainWindow();

protected:
    //void timerEvent( QTimerEvent * );

private:
    QThread* serialThread;
    QThread* eventThread;
    serialworker *serialWorker;
    //eventworker *eventWorker;
    //QMutex mutex;

signals:
    void finished();
    void SweepFinished();

public slots:
    void on_buttonAutoApproachClient_clicked(bool checked);

private slots:
    void MainWindowLoop();
    void dequeueReturnBuffer();
    void generalTimerUpdate();
    void finishedThread();
    void CreateGraphs();

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

    void on_approachButton_clicked();

    void on_setMaxDACValuesButton_clicked();

    void on_calibrateButton_clicked();

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
    QTimer *dequeueTimer;     // dequeue timer to empty the return buffer
    QTimer *generalTimer;   // general purpose timer for some components. Ie. continuously stepping motor every 20ms etc
    Plot *freqPlot;
    Plot *approachPlot;
    Plot *signalPlot1;
    Plot *signalPlot2;
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
    returnBuffer* _buffer;
    float zOffsetCoarse;
    float zOffsetFine;
    float bfrd1;
    float bfrd2;
    float bfrd3;
    float br2;
    float br1;
    float zAmp;
    float y1;
    float y2;
    float x1;
    float x2;
};

#endif // MAINWINDOW_H
