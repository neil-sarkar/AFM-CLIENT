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
#include <command.h>
//#include <armadillo>
#include <globals.h>
#include <QSignalMapper>

#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE 1.5 // slider bar for amplitude for control



void MainWindow::MainWindowLoop()
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    this->showMaximized();


    Initialize();

    // temporary random number generator for plots
    qsrand(QTime::currentTime().msec());
    time = 0;

    // for reading DAC/updating plots
    //ioTimer = startTimer(200); // for reading DAC/ADC
}

void MainWindow::finishedThread() {
    qDebug() << "Finished Thread";
}

MainWindow::~MainWindow()
{
    //MAKE SURE TO TERMINATE THE THREAD ON CLOSE
    emit finished();
}
void MainWindow::abort()
{
    emit finished();
}

/* Initialization:
 *      1) Connect to ports
 *      2) Set max dac values
 *      3) Calibrate?
 *
 *
 */

void MainWindow::Initialize()
{
    /*State Variables*/
    continuousStep = false;
    isAutoApproach = false;
    useBridgeSignalAsSetpoint = false;
    freqRetVal = -1;

    /*Check Icons
      TODO: find another way to do this*/
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);

    /*DAC Values*/
    zOffsetCoarse = 0;
    zOffsetFine = 0;
    zAmp = 0;

    /*Push event to get ports from the serialworker*/
    commandQueue.push(new commandNode(getPorts,(double)0));

    /*Initialize DAC limits*/
    SetMaxDACValues();

    /*Timers*/
    generalTimer = new QTimer(this);
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(generalTimerUpdate()));
    generalTimer->start(20); // every 20 ms, we update UI elements/other tasks, like continuous coarse step

    dequeueTimer = new QTimer(this);
    connect(dequeueTimer, SIGNAL(timeout()), this, SLOT(dequeueReturnBuffer()));
    dequeueTimer->start(10);

    /*Intialize Graphs*/
    CreateGraphs();

    /* Initialize offset, amplitude, and bridge voltage with the value we have set in UI*/
    on_spnFrequencyVoltage_2_valueChanged(ui->spnFrequencyVoltage_2->value()); // set amplitude
    on_spnBridgeVoltage_valueChanged(ui->spnBridgeVoltage->value()); // set bridge voltage
    on_spnOffsetVoltage_valueChanged(ui->spnOffsetVoltage->value()); // set offset

    /* future watcher for auto approaching*/
    future = new QFuture<void>;
    watcher = new QFutureWatcher<void>;
    connect(watcher, SIGNAL(finished()),
               this, SLOT(finishedThread()));

    QSignalMapper* signalMapper = new QSignalMapper (ui->sweepButton) ;
    QSignalMapper* signalMapper2 = new QSignalMapper (ui->sweepButton) ;
    connect (ui->sweepButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect (ui->sweepButton, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    signalMapper->setMapping(ui->sweepButton, "TRUE");
    signalMapper2->setMapping(ui->sweepButton, "QLabel { color : Green; }");
    connect (signalMapper, SIGNAL(mapped(QString)), ui->freqProgressLabel, SLOT(setText(QString))) ;
    connect (signalMapper2, SIGNAL(mapped(QString)), ui->freqProgressLabel, SLOT(setStyleSheet(QString))) ;
    //connect(ui->sweepButton, SIGNAL(clicked()),ui->freqProgressLabel, SLOT(setText()));
    //connect(ui->sweepButton, SIGNAL(clicked()),ui->freqProgressLabel, SLOT(setStyleSheet()));

}

void MainWindow::CreateGraphs(){
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
}
void MainWindow::SetPorts(returnBuffer<int>* _node){

    /*Push a setPort event to the serial thread*/
    //mutex.lock();
    if (ui->cboComPortSelection){
        foreach (const QSerialPortInfo info, _node->getList()) {
            ui->cboComPortSelection->addItem(info.portName());
        }
    }
    //mutex.unlock();
}

/*
 * Need to initialize the DAC limits
 *
 *
 *
 */
void MainWindow::SetMaxDACValues(){
    commandQueue.push(new commandNode(setDacValues,DAC_BFRD1,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_BFRD2 ,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_BR2,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_ZAMP ,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_BR1,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_BFRD3,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_ZOFFSET_FINE,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_Y1,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_ZOFFSET_COARSE ,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_Y2,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_X1 ,AFM_DAC_MAX_VOLTAGE ));
    commandQueue.push(new commandNode(setDacValues,DAC_X2,AFM_DAC_MAX_VOLTAGE ));
}
/*
 * This event is called on a timer, currently every 10ms
 * The main function is to dequeue the returnBuffer and
 * call the appropriate function or set variables
 *
 * Uses the returnTypes enum to perform switch statement
 *
 */
void MainWindow::dequeueReturnBuffer() {
    currTab = ui->tabWidget->currentIndex();

    /*
     * This forces the buffer to be completely emptied
     * on each timer trigger
     */
    while(!returnQueue.empty()){
        mutex.lock();
        _buffer = returnQueue.front();
        switch(_buffer->getReturnType()) {
         case DACBFRD1:
            ui->dacValue->setValue(_buffer->getFData());
            bfrd1 = _buffer->getFData();
            returnQueue.pop();
            break;
         case DACBFRD2:
            bfrd2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACBR2:
            br2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACZAMP:
            zAmp = _buffer->getFData();
            //ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACBR1:
            br1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACBFRD3:
            bfrd3 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACZOFFSETFINE:
            //dac8=_buffer->getFData();
            zOffsetFine = _buffer->getFData();
            returnQueue.pop();
            break;
         case DACY1:
            y1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACZOFFSETCOARSE:
            //ui->dacValue->setValue(_buffer->getFData());
            zOffsetCoarse = _buffer->getFData();
            returnQueue.pop();
            break;
         case DACY2:
            y2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACX1:
            x1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case DACX2:
            x2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            returnQueue.pop();
            break;
         case AFMADCAMPLITUDEID:
            zAmp = _buffer->getFData();
            returnQueue.pop();
            break;
         case AFMDACOFFSETID:
             zOffsetFine = _buffer->getFData();
             returnQueue.pop();
             break;
         case DAC:
             ui->dacValue->setValue(_buffer->getFData());
             returnQueue.pop();
             break;
         case ADC:
             ui->adcValue->setValue(_buffer->getFData());
             returnQueue.pop();
             break;
         case FREQSWEEP:
            freqRetVal = _buffer->getData();
            returnQueue.pop();
            break;
         case GETPORTS:
            SetPorts(returnQueue.front());
            returnQueue.pop();
            break;
        }
        //approachPlot->update(time, zAmp, currTab == Approach ? true: false);
        if( isAutoApproach ) {
            approachPlot->update(time, zAmp, currTab == Approach ? true: false);
            ui->currOffsetValue->setValue(zAmp);
            time++;
        }
        if(currTab == 4){
            signalPlot1->update(time, zOffsetFine, currTab == Signal ? true: false);
            signalPlot2->update(time, zAmp - ui->spnPidSetpoint->value(), currTab == Signal ? true: false);
            time++;
        }
        mutex.unlock();
    }
}

void MainWindow::generalTimerUpdate() {

    if( useBridgeSignalAsSetpoint ) {
        ui->spnPidSetpoint->setValue(zAmp);
        ui->currPIDSetpoint->setValue(zAmp);
    }
}

// 10 ms timer
//void MainWindow::timerEvent(QTimerEvent *e) {
    //int currTab = ui->tabWidget->currentIndex();
    //int id = e->timerId();


//    if( id == ioTimer ) {
//#if AFM_MICRO_CONNECTED
//        if( continuousStep )
//            commandQueue.push(new commandNode(stageSetStep));//afm.stageSetStep();

////        adc5 = afm.readADC(AFM_ADC_AMPLTIDE_ID);
////        dac8 = afm.readDAC(AFM_DAC_OFFSET_ID);
//        commandQueue.push(new commandNode(readADC,0,0,(qint8)AFM_ADC_AMPLITUDE_ID));
//        commandQueue.push(new commandNode(readDAC,0,0,(qint8)AFM_DAC_OFFSET_ID));
//        QThread::msleep(100);
//        mutex.lock();
//        returnBuffer<int>* _buffer;
//        if(!returnQueue.empty()){
//            _buffer = returnQueue.front();
//            adc5 = _buffer->getData();
//            returnQueue.pop();
//            _buffer = returnQueue.front();
//            dac8 = _buffer->getData();
//            returnQueue.pop();
//            mutex.unlock();
//        }
//        adc5 = serialWorker->doreadADC(AFM_ADC_AMPLITUDE_ID);
//        dac8 = serialWorker->doreadDAC(AFM_DAC_OFFSET_ID);



//            commandQueue.push(new commandNode(stageSetStep));//afm.stageSetStep();

//            if ( adc5 <= 0.95*autoApproachComparison ) {
//                on_buttonAutoApproachClient_clicked(false);
//            }
//        }

//#else
//        adc5 = float(qrand())/RAND_MAX;
//        dac8 = float(qrand())/RAND_MAX;
//#endif
//    }
//}

void MainWindow::on_spnOffsetVoltage_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(memsSetOffset,(double)arg1));//afm.memsSetOffset(arg1);
    mutex.unlock();
}

void MainWindow::on_spnBridgeVoltage_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(memsSetBridgeVoltage,(double)arg1));//afm.memsSetBridgeVoltage(arg1);
    mutex.unlock();
}

void MainWindow::on_spnFrequencyVoltage_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(memsSetFrequency,(double)arg1));//afm.memsSetFrequency(arg1);
    mutex.unlock();
}

void MainWindow::on_btnPidToggle_toggled(bool checked)
{
    if(checked){
        //mutex.lock();
        commandQueue.push(new commandNode(pidEnable));//afm.pidEnable();
        //mutex.unlock();
    }
    else{
        //mutex.lock();
        commandQueue.push(new commandNode(pidDisable));//afm.pidDisable();
        //mutex.unlock();
    }
}

void MainWindow::on_spnPidValueP_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetP,(double)arg1));//afm.pidSetP(arg1);
    mutex.unlock();
}

void MainWindow::on_spnPidValueI_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetI,(double)arg1));//afm.pidSetI(arg1);
    mutex.unlock();
}

void MainWindow::on_spnPidValueD_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetD,(double)arg1));//afm.pidSetD(arg1);
    mutex.unlock();
}

void MainWindow::on_spnPidSetpoint_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetPoint,(double)arg1));//afm.pidSetPoint(arg1);
    mutex.unlock();
}

void MainWindow::on_cboComPortSelection_currentIndexChanged(int index)
{

    //afm.close(); //Close any existing ports
    //afm.setPort(detectedSerialPorts.at(index));
    //afm.open(QIODevice::ReadWrite);
    //displayComPortInfo(detectedSerialPorts.at(index));
    commandQueue.push(new commandNode(setPort,(double)index));


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
    dequeueTimer->setInterval(arg1);
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
    mutex.lock();
    commandQueue.push(new commandNode(stageSetDirBackward));//afm.stageSetDirBackward();
    mutex.unlock();
}

void MainWindow::on_approachButton_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stageSetDirForward));//afm.stageSetDirForward();
    mutex.unlock();
}

void MainWindow::on_sldAmplitudeVoltage_3_valueChanged(int value)
{
    ui->lblAmplitude->setText(QString::number(value));
    mutex.lock();
    commandQueue.push(new commandNode(stageSetPulseWidth,0,0,(qint8)value));//afm.stageSetPulseWidth(value);
    mutex.unlock();
}

void MainWindow::on_buttonCurrValuePidSetpoint_clicked(bool checked)
{
    useBridgeSignalAsSetpoint = checked;
}

void MainWindow::autoApproach(nanoiAFM* afm) {
    qDebug() << "In the threaded coarse approach";
    mutex.lock();
    float initVal = afm->readADC(AFM_ADC_AMPLITUDE_ID);
    commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)3));    //afm->stageSetPulseWidth(3);
    commandQueue.push(new commandNode(stageSetDirBackward));    //afm->stageSetDirBackward();
    mutex.unlock();



    mutex.lock();
    float bridgeVal;
    for( ;; ) {
//        commandQueue.push(new commandNode(stageSetStep));

        commandQueue.push(new commandNode(stageSetStep)); //afm->stageSetStep(); // take a step
        bridgeVal = afm->readADC(AFM_ADC_AMPLITUDE_ID);
//        commandQueue.push(new commandNode(readADC,0,0,(qint8)AFM_ADC_AMPLITUDE_ID));
//        QThread::msleep(100);
//        mutex.lock();
//        bridgeVal = return_queue.front();
//        returnQueue.pop();
//        mutex.unlock();
        // if we're less than 95% of init, then slow down
        if (bridgeVal < 0.95*initVal) {
            //commandQueue.push(new commandNode(stageSetPulseWidth,0,0,0));
            commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)0)); //afm->stageSetPulseWidth(0);
        }
        // if we're within 90% of init, then autoapproach complete
        else if (bridgeVal < 0.9*initVal) {
            break;
        }
    }
    mutex.unlock();
}

// Button for autoapproach
// TODO: verify autoapproach
void MainWindow::on_buttonAutoApproachClient_clicked(bool checked)
{
    if(checked) {
        mutex.lock();
        autoApproachComparison = adc5; // comparison value before starting motor
        ui->comparisonValue->setValue(adc5);
        mutex.unlock();


        mutex.lock();
        commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)19));
        commandQueue.push(new commandNode(stageSetDirBackward));
        mutex.unlock();

//        afm.stageSetPulseWidth(19);
//        afm.stageSetDirBackward();
        isAutoApproach = true;
        //*future = QtConcurrent::run(this, &MainWindow::autoApproach, &afm);
        //watcher->setFuture(*future);
    }
    // TODO: does unchecking autoapproach do anything in original software?
    // Set the values of motor back to what they were before
    else {
        isAutoApproach = false;
        mutex.lock();
        commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)ui->sldAmplitudeVoltage_3->value()));

        //afm.stageSetPulseWidth(ui->sldAmplitudeVoltage_3->value());
//        ui->retreatButton->isChecked() == true ? afm.stageSetDirBackward() : \
//                                                 afm.stageSetDirForward();
        ui->retreatButton->isChecked() == true ? commandQueue.push(new commandNode(stageSetDirBackward)) : \
                                                 commandQueue.push(new commandNode(stageSetDirForward));

        mutex.unlock();
    }
}

void MainWindow::on_stepButton_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stageSetStep));//afm.stageSetStep();
    mutex.unlock();
}

void MainWindow::on_continuousButton_clicked(bool checked)
{
    mutex.lock();
    if (checked) {
        commandQueue.push(new commandNode(stageSetContinuous));
        continuousStep = true;

    }
    else {
        commandQueue.push(new commandNode(stageAbortContinuous));
        continuousStep = false;
    }
    mutex.unlock();
}

// Frequency sweep
void MainWindow::on_sweepButton_clicked()
{
    QVector<double>& frequencyData = QVector<double>();
    QVector<double>& amplitudeData = QVector<double>();
    int bytesRead;

    //connect(ui->sweepButton, SIGNAL(clicked()), ui->freqProgressLabel, SLOT(setText("Boo!")));
    ui->freqProgressLabel->setText("TRUE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : Green; }");

    freqPlot->clearData();

    mutex.lock();
    commandQueue.push(new commandNode(frequencySweep,ui->numFreqPoints->value(), ui->startFrequency->value(), ui->stepSize->value(),\
                                      amplitudeData, frequencyData, bytesRead));

    mutex.unlock();
    //commandQueue.push(new commandNode(frequencySweep,ui->numFreqPoints->value(), ui->startFrequency->value(), ui->stepSize->value(),\
     //                               amplitudeData, frequencyData, bytesRead);

    //QThread::msleep(100);
    //int retVal = returnQueue.front();
    mutex.lock();
    if(freqRetVal = -1){

        queue<returnBuffer<int>*> temp = returnQueue;
        returnBuffer<int>* _buffer;
        while(!temp.empty()){
            _buffer = temp.front();
            if(_buffer->getReturnType() == FREQSWEEP){
                freqRetVal = _buffer->getData();
                amplitudeData = _buffer->getAmplitude();
                frequencyData = _buffer->getFrequency();
                bytesRead = _buffer->getBytesRead();
                temp.pop();
            }
        }
    }
    mutex.unlock();

    if ( freqRetVal != AFM_SUCCESS) {
        QMessageBox msg;
        msg.setText(QString("Size of Freq Data: %1. Expected Size: %2").arg(\
                                QString::number(bytesRead), QString::number(ui->numFreqPoints->value()*4) ));
        msg.exec();
    }
    else {
        qDebug() << "Size of X Data: " << frequencyData.size() << "Size of Y Data: " << amplitudeData.size();
        for(int i = 0; i < ui->numFreqPoints->value(); i++ ) {
            qDebug() << "Freq: " << frequencyData[i] << " Amplitude: " << amplitudeData[i];
            freqPlot->update(frequencyData[i], amplitudeData[i], false); // add points to graph but don't replot
        }
        freqPlot->replot(); // show the frequency sweep
    }

    ui->freqProgressLabel->setText("FALSE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : red; }");
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
    ui->label_13->setPixmap((QString)"C:\\Users\\Nick\\Documents\\code\\AFM-CLIENT\\icons\\1413858979_ballgreen-24.png");

}

/*
 *
 *
 * Push a write event to be processed by the serialworker
 */
void MainWindow::on_buttonWriteToDAC_clicked()
{


    double valueToWrite = ui->valToWrite->value();
    if (valueToWrite <= AFM_ADC_MAX_VOLTAGE && valueToWrite >= 0) {
        commandNode* _node = new commandNode(writeDAC,ui->dacNumber->value(),valueToWrite);
        commandQueue.push(_node);
    }
}

/*
 *
 *
 * Push a read event to be processed by the serialworker
 */
void MainWindow::on_buttonReadIO_clicked()
{
    //ui->dacValue->setValue(afm.readDAC(ui->dacNumber->value()));
    commandNode* _node = new commandNode(readDAC,(qint8)ui->dacNumber->value());
    commandQueue.push(_node);
    _node = new commandNode(readADC,(qint8)ui->adcNumber->value());
    commandQueue.push(_node);
}

void MainWindow::on_btnPidToggle_clicked(bool checked)
{
//    commandQueue.push(new commandNode(pidEnable));
//    QThread::msleep(100);
//    bool _pidEnable = returnQueue.front();
//    returnQueue.pop();

//    commandQueue.push(new commandNode(pidDisable));
//    QThread::msleep(100);
//    bool _pidDisable = returnQueue.front();
//    returnQueue.pop();

//    checked == true ? _pidEnable : _pidDisable;
}

void MainWindow::on_freqAutoScale_clicked(bool checked)
{
    freqPlot->setAutoScale(checked);
    ui->freqAutoScale->setChecked(checked);
}

void MainWindow::on_spnFrequencyVoltage_2_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(memsSetAmplitude,arg1));//afm.memsSetAmplitude(arg1);
    mutex.unlock();
}

void MainWindow::on_buttonSendSweep_clicked()
{
    //mutex.lock();
    commandQueue.push(new commandNode(setDDSSettings,(qint16)ui->numFreqPoints->value(), (qint16)ui->currFreqVal->value(),(qint16) ui->stepSize->value()));//afm.setDDSSettings(ui->numFreqPoints->value(), ui->currFreqVal->value(), ui->stepSize->value());
   // mutex.unlock();
}


void MainWindow::on_buttonAutoApproachMCU_clicked()
{
    mutex.lock();
    if(!isAutoApproach){
        commandQueue.push(new commandNode(stageSetContinuous));
        isAutoApproach = true;
    }
    else{
        commandQueue.push(new commandNode(stageAbortContinuous));//afm.autoApproach();
        isAutoApproach = false;
    }
    mutex.unlock();
}

void MainWindow::on_writeCharacter_clicked()
{
    //afm.writeByte('z');
//    char data[2];
//    qDebug() << "Num bytes from click read: " << afm.readData(data, 2);
//    adc5 = (float)((data[1] << 8) | data[0]);
//    QByteArray res = afm.waitForData();
//    quint16 val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
//    adc5 = ((float)val)/AFM_ADC_SCALING;
}



void MainWindow::on_setMaxDACValuesButton_clicked()
{
   commandQueue.push(new commandNode(setDacValues,DAC_Y1,ui->latSpinBox->value()));
   commandQueue.push(new commandNode(setDacValues,DAC_Y2,ui->latSpinBox->value()));
   commandQueue.push(new commandNode(setDacValues,DAC_X1,ui->latSpinBox->value()));
   commandQueue.push(new commandNode(setDacValues,DAC_X2,ui->latSpinBox->value()));
   commandQueue.push(new commandNode(setDacValues,DAC_ZOFFSET_COARSE,ui->ZfineSpinBox->value()));
   commandQueue.push(new commandNode(setDacValues,DAC_ZOFFSET_FINE,ui->ZcoarseSpinBox->value()));
   mutex.lock();
   ui->label_10->setVisible(true);
   ui->label_11->setVisible(true);
   ui->label_12->setVisible(true);
   mutex.unlock();
}


