#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QTime>
#include "serialworker.h"
#include <QThread>
#include <QObject>
//#include <armadillo>

#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE 1.5 // slider bar for amplitude for control


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    useBridgeSignalAsSetpoint(false),
    isAutoApproach(false),
    continuousStep(false)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    // Serial Thread
    serialThread = new QThread();
    serialWorker = new serialworker();

    serialWorker->moveToThread(serialThread);
    connect(serialThread, SIGNAL(started()), serialWorker, SLOT(mainLoop()));
    connect(serialWorker, SIGNAL(finished()), serialThread, SLOT(quit()), Qt::DirectConnection);
    serialThread->start();

    // Serial port
    detectedSerialPorts= QSerialPortInfo::availablePorts();
    if(detectedSerialPorts.size()==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to find any serial ports.");
        msgBox.exec();
    }
    else
    {
        afm.setPort(detectedSerialPorts.at(0));
        afm.open(QIODevice::ReadWrite);
    }

    foreach (const QSerialPortInfo &info, detectedSerialPorts) {
        ui->cboComPortSelection->addItem(info.portName());
    }

    // temporary random number generator for plots
    qsrand(QTime::currentTime().msec());
    time = 0;

    // for reading DAC/updating plots
    ioTimer = startTimer(200); // for reading DAC/ADC
    generalTimer = new QTimer(this);
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(generalTimerUpdate()));
    generalTimer->start(20); // every 20 ms, we update UI elements/other tasks, like continuous coarse step

    graphTimer = new QTimer(this);
    connect(graphTimer, SIGNAL(timeout()), this, SLOT(updateGraph()));
    graphTimer->start(ui->refreshSpinBox->value());

    // add frequency sweep plot
    PlotFields fields("Frequency Sweep", true, "Frequency (V)", "Amplitude (V)",\
                      QPair<double,double>(3800,4800), QPair<double,double>(0,0.12), QColor("Red"),
                      false, true);
    freqPlot = new Plot( fields, ui->freqWidget );
    ui->gridLayout_17->setSpacing(0);
    ui->gridLayout_17->addWidget(freqPlot, 1, 0);
    freqPlot->resize(500, 300);
    freqPlot->show();
    //connect(freqPlot, SIGNAL(mousePressEvent), this, )

    // add approach plot
    fields = PlotFields("Bridge Signal", true, "Time", "Bridge Voltage (V)",\
                        QPair<double,double>(0,300), QPair<double,double>(0,1), QColor("Red"),
                        false);
    approachPlot = new Plot( fields, ui->approachWidget );
    ui->gridLayout_24->setSpacing(0);
    ui->gridLayout_24->addWidget(approachPlot, 1, 0);
    approachPlot->resize( 500, 300 );
    approachPlot->show();

    ui->gridLayout_10->setSpacing(0);
    // add signal plot 1
    fields = PlotFields("Z Offset", false, "Time", "Z Offset (V)",\
                        QPair<double,double>(0,300), QPair<double,double>(0,1), QColor("Red"),
                        false);
    signalPlot1 = new Plot( fields, ui->signalWidget );

    ui->gridLayout_10->addWidget(signalPlot1, 1, 0);
    signalPlot1->resize( 500, 100 );
    signalPlot1->show();

    // add signal plot 2
    fields = PlotFields("Error (V)", false, "Time", "Error)",\
                        QPair<double,double>(0,300), QPair<double,double>(0,1), QColor("Red"),
                        false);
    signalPlot2 = new Plot( fields, ui->signalWidget );

    ui->gridLayout_10->addWidget(signalPlot2, 2, 0);
    signalPlot2->resize( 500, 100 );
    signalPlot2->show();

    // Initialize offset, amplitude, and bridge voltage with the value we have set in UI
    on_spnFrequencyVoltage_2_valueChanged(ui->spnFrequencyVoltage_2->value()); // set amplitude
    on_spnBridgeVoltage_valueChanged(ui->spnBridgeVoltage->value()); // set bridge voltage
    on_spnOffsetVoltage_valueChanged(ui->spnOffsetVoltage->value()); // set offset

    // future watcher for auto approaching
    future = new QFuture<void>;
    watcher = new QFutureWatcher<void>;
    connect(watcher, SIGNAL(finished()),
               this, SLOT(finishedThread()));
}

void MainWindow::finishedThread() {
    qDebug() << "Finished Thread";
}

MainWindow::~MainWindow()
{
    afm.close();
    delete ui;
}

void MainWindow::updateGraph() {
    int currTab = ui->tabWidget->currentIndex();
    if ( !isAutoApproach ) {
        approachPlot->update(time, adc5, currTab == Approach ? true: false);
        signalPlot1->update(time, dac8, currTab == Signal ? true: false);
        signalPlot2->update(time, adc5 - ui->spnPidSetpoint->value(), currTab == Signal ? true: false);
        time++;
     }
}

void MainWindow::generalTimerUpdate() {

    if( useBridgeSignalAsSetpoint ) {
        ui->spnPidSetpoint->setValue(adc5);
        ui->currPIDSetpoint->setValue(adc5);
    }
}

// 10 ms timer
void MainWindow::timerEvent(QTimerEvent *e) {
    int currTab = ui->tabWidget->currentIndex();
    int id = e->timerId();

    if( id == ioTimer ) {
#if AFM_MICRO_CONNECTED
        if( continuousStep )
            afm.stageSetStep();

        adc5 = afm.readADC(AFM_ADC_AMPLTIDE_ID);
        dac8 = afm.readDAC(AFM_DAC_OFFSET_ID);

        if( isAutoApproach ) {
            approachPlot->update(time, adc5, currTab == Approach ? true: false);
            ui->currOffsetValue->setValue(adc5);
            time++;

            afm.stageSetStep();

            if ( adc5 <= 0.95*autoApproachComparison ) {
                on_buttonAutoApproachClient_clicked(false);
            }
        }

#else
        adc5 = float(qrand())/RAND_MAX;
        dac8 = float(qrand())/RAND_MAX;
#endif
    }
}

void MainWindow::on_spnOffsetVoltage_valueChanged(double arg1)
{
    afm.memsSetOffset(arg1);
}

void MainWindow::on_spnBridgeVoltage_valueChanged(double arg1)
{
    afm.memsSetBridgeVoltage(arg1);
}

void MainWindow::on_spnFrequencyVoltage_valueChanged(double arg1)
{
    afm.memsSetFrequency(arg1);
}

void MainWindow::on_btnPidToggle_toggled(bool checked)
{
    if(checked){
        afm.pidEnable();
    }
    else{
        afm.pidDisable();
    }
}

void MainWindow::on_spnPidValueP_valueChanged(double arg1)
{
    afm.pidSetP(arg1);
}

void MainWindow::on_spnPidValueI_valueChanged(double arg1)
{
    afm.pidSetI(arg1);
}

void MainWindow::on_spnPidValueD_valueChanged(double arg1)
{
    afm.pidSetD(arg1);
}

void MainWindow::on_spnPidSetpoint_valueChanged(double arg1)
{
    afm.pidSetPoint(arg1);
}

void MainWindow::on_cboComPortSelection_currentIndexChanged(int index)
{

    afm.close(); //Close any existing ports
    afm.setPort(detectedSerialPorts.at(index));
    afm.open(QIODevice::ReadWrite);
    //displayComPortInfo(detectedSerialPorts.at(index));

    serialWorker->requestMethod(serialworker::writeByte);
}

void MainWindow::displayComPortInfo(const QSerialPortInfo& info)
{
    QMessageBox msgBox;
    msgBox.setText("Comport Selected: " + info.portName() + "\n"
                   "Description: " + info.manufacturer() + "\n"
                   "Manufacturer: " + info.description());
    msgBox.exec();
}

void MainWindow::on_refreshSpinBox_valueChanged(int arg1)
{
    graphTimer->setInterval(arg1);
}

void MainWindow::on_pushButton_22_clicked(bool checked)
{
    approachPlot->setAutoScale(checked);
}

void MainWindow::on_pushButton_4_clicked(bool checked)
{
    signalPlot2->setAutoScale(checked);
}

void MainWindow::on_pushButton_5_clicked(bool checked)
{
    signalPlot1->setAutoScale(checked);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    freqPlot->setMarker(checked);
}

// retr direction for pcb motor
// TODO: verify retr is backwards aka 'l'
void MainWindow::on_retreatButton_clicked()
{
    afm.stageSetDirBackward();
}

void MainWindow::on_sldAmplitudeVoltage_3_valueChanged(int value)
{
    afm.stageSetPulseWidth(value);
}

void MainWindow::on_buttonCurrValuePidSetpoint_clicked(bool checked)
{
    useBridgeSignalAsSetpoint = checked;
}

void MainWindow::autoApproach(nanoiAFM* afm) {
    qDebug() << "In the threaded coarse approach";
    float initVal = afm->readADC(AFM_ADC_AMPLTIDE_ID);
    afm->stageSetPulseWidth(3);
    afm->stageSetDirBackward();

    float bridgeVal;
    for( ;; ) {
        afm->stageSetStep(); // take a step
        bridgeVal = afm->readADC(AFM_ADC_AMPLTIDE_ID);

        // if we're less than 95% of init, then slow down
        if (bridgeVal < 0.95*initVal) {
            afm->stageSetPulseWidth(0);
        }
        // if we're within 90% of init, then autoapproach complete
        else if (bridgeVal < 0.9*initVal) {
            break;
        }
    }
}

// Button for autoapproach
// TODO: verify autoapproach
void MainWindow::on_buttonAutoApproachClient_clicked(bool checked)
{
    if(checked) {
        autoApproachComparison = adc5; // comparison value before starting motor
        ui->comparisonValue->setValue(adc5);
        afm.stageSetPulseWidth(19);
        afm.stageSetDirBackward();
        isAutoApproach = true;
        //*future = QtConcurrent::run(this, &MainWindow::autoApproach, &afm);
        //watcher->setFuture(*future);
    }
    // TODO: does unchecking autoapproach do anything in original software?
    // Set the values of motor back to what they were before
    else {
        isAutoApproach = false;
        afm.stageSetPulseWidth(ui->sldAmplitudeVoltage_3->value());
        ui->retreatButton->isChecked() == true ? afm.stageSetDirBackward() : \
                                                 afm.stageSetDirForward();
    }
}

void MainWindow::on_stepButton_clicked()
{
    afm.stageSetStep();
}

void MainWindow::on_continuousButton_clicked(bool checked)
{
    if (checked) {
        continuousStep = true;
    }
    else {
        continuousStep = false;
    }

}

// Frequency sweep
void MainWindow::on_sweepButton_clicked()
{
    QVector<double> frequencyData;
    QVector<double> amplitudeData;
    int bytesRead;

    freqPlot->clearData();
    ui->freqProgressLabel->setText("TRUE");
    int retVal = afm.frequencySweep(ui->numFreqPoints->value(), ui->startFrequency->value(), ui->stepSize->value(),\
                                    amplitudeData, frequencyData, bytesRead);
    if ( retVal != AFM_SUCCESS) {
        QMessageBox msg;
        msg.setText(QString("Size of Freq Data: %1. Expected Size: %2").arg(\
                                QString::number(bytesRead), QString::number(ui->numFreqPoints->value()*2) ));
        msg.exec();
    }
    else {
        qDebug() << "Size of X Data: " << frequencyData.size() << "Size of Y Data: " << amplitudeData.size();
        for(int i = 0; i < ui->numFreqPoints->value(); i++ ) {
            qDebug() << "Freq: " << frequencyData[i] << " Amplitude: " << amplitudeData[i];
            freqPlot->update(frequencyData[i], amplitudeData[i], true); // add points to graph but don't replot
        }
        freqPlot->replot(); // show the frequency sweep
    }
    ui->freqProgressLabel->setText("FALSE");
}

void MainWindow::on_useCurrFreqVal_clicked()
{
    ui->spnFrequencyVoltage->setValue(ui->currFreqVal->value());
}
void MainWindow::on_pushButton_6_clicked()
{
    //XYGenerator dynamically resizes these values
    /*arma::mat X_points;
    arma::mat Y_points;

    //Convert all the values to digital values based on a resolution of 4095
    int vMax=ui->spnScanVmax->value()*AFM_DAC_SCALING;
    int vMin=ui->spnScanVmax->value()*AFM_DAC_SCALING;
    int vMin2=ui->spnScanVmax->value()*AFM_DAC_SCALING;
    int numPoints=ui->spnScanNumLines->value();
    int numLines=ui->spnScanNumPoints->value();
    int ret_fail=XYGENERATOR_FAIL;

    if((generateXYVoltages(vMax, vMin, vMin2, numLines, numPoints, X_points, Y_points) == ret_fail)){
            QMessageBox msgBox;
            msgBox.setText("Unable to generate scan points");
            msgBox.exec();
            return;
    }

    //Write X Y actuator voltages to AFM and read Z. A seperate matrix should be created

    mat Z_values(X_points.n_rows, X_points.n_cols);

    //DANGER: Verifiy these values are bein written properly
    for(int i=0; i < X_points.n_rows; i++){
        for(int j=0; j < X_points.n_rows; j++){
            //Write DAC for X voltage
            //Write DAC for Y Voltage
            //Wait for Z values to be populated. How long should we wait?
        }
    }*/

}


void MainWindow::on_buttonWriteToDAC_clicked()
{
    double valueToWrite = ui->valToWrite->value();
    if (valueToWrite <= AFM_ADC_MAX_VOLTAGE && valueToWrite >= 0) {
        afm.writeDAC(ui->dacNumber->value(), ui->valToWrite->value());
    }
    ui->dacValue->setValue(afm.readDAC(ui->dacNumber->value()));
    ui->adcValue->setValue(afm.readADC(ui->adcNumber->value()));
}

void MainWindow::on_buttonReadIO_clicked()
{
    ui->dacValue->setValue(afm.readDAC(ui->dacNumber->value()));
    ui->adcValue->setValue(afm.readADC(ui->adcNumber->value()));
}

void MainWindow::on_btnPidToggle_clicked(bool checked)
{
    checked == true ? afm.pidEnable() : afm.pidDisable();
}

void MainWindow::on_freqAutoScale_clicked(bool checked)
{
    freqPlot->setAutoScale(checked);
}

void MainWindow::on_spnFrequencyVoltage_2_valueChanged(double arg1)
{
    afm.memsSetAmplitude(arg1);
}

void MainWindow::on_buttonSendSweep_clicked()
{
    afm.setDDSSettings(ui->numFreqPoints->value(), ui->currFreqVal->value(), ui->stepSize->value());
}

void MainWindow::on_buttonAutoApproachMCU_clicked()
{
    afm.autoApproach();
    //isAutoApproach = true;
}

void MainWindow::on_writeCharacter_clicked()
{
    afm.writeByte('z');
//    char data[2];
//    qDebug() << "Num bytes from click read: " << afm.readData(data, 2);
//    adc5 = (float)((data[1] << 8) | data[0]);
//    QByteArray res = afm.waitForData();
//    quint16 val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
//    adc5 = ((float)val)/AFM_ADC_SCALING;
}
