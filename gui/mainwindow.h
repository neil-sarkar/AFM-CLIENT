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

public:
    //nanoiAFM afm;
    QList<QSerialPortInfo> detectedSerialPortsList; //buffer for serial ports
    MainWindow(QWidget *parent,
               queue<commandNode*>& _queue,
               queue<returnBuffer*>& _returnqueue) :
        QMainWindow(parent),
        commandQueue(_queue),
        returnQueue(_returnqueue) {}

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

    ~MainWindow();

protected:
    //void timerEvent( QTimerEvent * );

private:
    QMessageBox msgBox;
    //eventworker *eventWorker;
    //QMutex mutex;

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
    void setDDSFrequency(const QPointF &p);
    void updatePlot(double _signal, int _plot);

private slots:
    void MainWindowLoop();
    void dequeueReturnBuffer();
    void generalTimerUpdate();
    void approachTimerUp();
    void finishedThread();


    // GUI elements
    void on_spnOffsetVoltage_valueChanged(double arg1);

    void on_spnBridgeVoltage_valueChanged(double arg1);

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

    void on_buttonCurrValuePidSetpoint_clicked(bool checked);

    void on_sweepButton_clicked();


    void on_useCurrFreqVal_clicked();

   // void on_retreatButton_2_clicked();

    void on_pushButton_6_clicked();

   // void on_pushButton_22_clicked();

    void on_buttonWriteToDAC_clicked();

    void on_buttonReadIO_clicked();

    void on_freqAutoScale_clicked(bool checked);

    void on_spnFrequencyVoltage_2_valueChanged(double arg1);

    void on_buttonSendSweep_clicked();

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

    //placeholders for returned data
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
    double signal;
    double offset;
    double phase;
    double *scandata[256];
    int row;
};

#endif // MAINWINDOW_H
