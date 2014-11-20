#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QTime>
#include <serialworker.h>
#include <QThread>
#include <QObject>
#include <command.h>
//#include <armadillo>
#include <globals.h>
#include <QSignalMapper>
#include <XYgenerator.h>
#include <QStatusBar>

#include <math.h>
#include <qapplication.h>
#include <qwt3d_gridplot.h>
#include <qwt3d_function.h>

//#include <gwyddion.h>

#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE 1.5 // slider bar for amplitude for control

/* Conrad Sanderson.
 * Armadillo: An Open Source C++ Linear Algebra Library for
 * Fast Prototyping and Computationally Intensive Experiments.
 * Technical Report, NICTA, 2010.
 *
 *
 */

using namespace Qwt3D;

class Rosenbrock : public Function
{
public:

  Rosenbrock(GridPlot& pw)
  :Function(pw)
  {
  }

  double operator()(double x, double y)
  {
    return log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8;
  }
};

void MainWindow::MainWindowLoop()
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    this->showMaximized();

    updateStatusBar("Working...");

    //gwy_math_lin_solve();

    Initialize();

    // temporary random number generator for plots
    qsrand(QTime::currentTime().msec());
    time = 0;

    //ui->tabScan->setLayout(grid);
    updateStatusBar("Ready");

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
 *      3) Create graphs
 *      4) set variables
 *      5) Calibrate?
 *              device calibration
 *              set scan parameters
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

    approachTimer = new QTimer(this);
    connect(approachTimer, SIGNAL(timeout()),this,SLOT(approachTimerUp()));
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

    /*Event mapping for setting labels and statuses - I DONT THINK THIS IS NEEDED*/
    QSignalMapper* signalMapper = new QSignalMapper (ui->sweepButton) ;
    QSignalMapper* signalMapper2 = new QSignalMapper (ui->sweepButton) ;
    connect (ui->sweepButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect (ui->sweepButton, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    connect(this, SIGNAL(SweepFinished()),signalMapper,SLOT(map()));
    connect(this, SIGNAL(SweepFinished()),signalMapper2,SLOT(map()));
    signalMapper->setMapping(ui->sweepButton, "TRUE");
    signalMapper2->setMapping(ui->sweepButton, "QLabel { color : Green; }");
    signalMapper->setMapping(this, "FALSE");
    signalMapper2->setMapping(this, "QLabel { color : Red; }");
    connect (signalMapper, SIGNAL(mapped(QString)), ui->freqProgressLabel, SLOT(setText(QString))) ;
    connect (signalMapper2, SIGNAL(mapped(QString)), ui->freqProgressLabel, SLOT(setStyleSheet(QString))) ;

    /*The follow action groups and SIGNALS/SLOTS are for the scan toolbar*/
    QActionGroup* coord = new QActionGroup(this);
    coord->addAction(ui->Box);
    coord->addAction(ui->Frame);
    coord->addAction(ui->None);

    QActionGroup* plotstyle = new QActionGroup(this);
    plotstyle->addAction(ui->pointstyle);
    plotstyle->addAction(ui->wireframe);
    plotstyle->addAction(ui->hiddenline);
    plotstyle->addAction(ui->polygon);
    plotstyle->addAction(ui->filledmesh);
    plotstyle->addAction(ui->nodata);

    QActionGroup* grids = new QActionGroup(this);
    grids->addAction(ui->front);
    grids->addAction(ui->back);
    grids->addAction(ui->right);
    grids->addAction(ui->left);
    grids->addAction(ui->ceil);
    grids->addAction(ui->floor);
    grids->setExclusive(false);

    QActionGroup* floorstyle = new QActionGroup(this);
    floorstyle->addAction(ui->floordata);
    floorstyle->addAction(ui->flooriso);
    floorstyle->addAction(ui->floornone);

    connect( ui->left, SIGNAL( toggled( bool ) ), this, SLOT( setLeftGrid( bool ) ) );
    connect( ui->right, SIGNAL( toggled( bool ) ), this, SLOT( setRightGrid( bool ) ) );
    connect( ui->ceil, SIGNAL( toggled( bool ) ), this, SLOT( setCeilGrid( bool ) ) );
    connect( ui->floor, SIGNAL( toggled( bool ) ), this, SLOT( setFloorGrid( bool ) ) );
    connect( ui->back, SIGNAL( toggled( bool ) ), this, SLOT( setBackGrid( bool ) ) );
    connect( ui->front, SIGNAL( toggled( bool ) ), this, SLOT( setFrontGrid( bool ) ) );
    connect( plotstyle, SIGNAL( triggered( QAction* ) ), this, SLOT( pickPlotStyle( QAction* ) ) );
    connect( coord, SIGNAL( triggered( QAction* ) ), this, SLOT( pickCoordSystem( QAction* ) ) );
    connect( floorstyle, SIGNAL( triggered( QAction* ) ), this, SLOT( pickFloorStyle( QAction* ) ) );
    connect(ui->normals, SIGNAL( toggled(bool) ), this, SLOT( showNormals(bool)));
    //connect(ui->sweepButton, SIGNAL(clicked()),ui->freqProgressLabel, SLOT(setText()));
    //connect(ui->sweepButton, SIGNAL(clicked()),ui->freqProgressLabel, SLOT(setStyleSheet()));

}

void MainWindow::CreateGraphs(){
    //freqPlot = new Plot();


    //scanPlot = GridPlot(ui->frame);
    scanPlot.setTitle("Forward");

    Rosenbrock rosenbrock(scanPlot);

    rosenbrock.setMesh(41,31);
    rosenbrock.setDomain(-1.73,1.5,-1.5,1.5);
    rosenbrock.setMinZ(-20);

    rosenbrock.create();

    scanPlot.setRotation(30,0,15);
    scanPlot.setScale(1,1,1);
    scanPlot.setShift(0.15,0,0);
    scanPlot.setZoom(0.9);

    for (unsigned i=0; i!=scanPlot.coordinates()->axes.size(); ++i)
    {
      scanPlot.coordinates()->axes[i].setMajors(7);
      scanPlot.coordinates()->axes[i].setMinors(4);
    }

    scanPlot.coordinates()->axes[X1].setLabelString("x-axis");
    scanPlot.coordinates()->axes[Y1].setLabelString("y-axis");
    //scanPlot.coordinates()->axes[Z1].setLabelString(QChar(0x38f)); // Omega - see http://www.unicode.org/charts/


    scanPlot.setCoordinateStyle(BOX);
    scanPlot.showColorLegend(true);
    scanPlot.updateData();
    scanPlot.updateGL();
    scanPlot.show();

    ui->gridLayout_11->setSpacing(0);
    ui->gridLayout_11->addWidget(&scanPlot, 0, 0);

    // add frequency sweep plot
    MyPlot::PlotFields fields = MyPlot::PlotFields("", true, "Frequency (Hz)", "Amplitude (V)",\
                      QPair<double,double>(3800,4800), QPair<double,double>(0,0.12), QColor("Red"),
                      false, true);

    freqPlot.SetPlot( fields, ui->freqWidget);
    ui->gridLayout_17->setSpacing(0);
    ui->gridLayout_17->addWidget(&freqPlot, 1, 0);
    freqPlot.enableAxis(QwtPlot::xBottom);
    freqPlot.enableAxis(QwtPlot::yLeft);
    //freqPlot.resize(500, 300);
    freqPlot.show();


    //phase plot
    fields = MyPlot::PlotFields("", true, "Frequency (Hz)", "Phase (Deg)",\
                      QPair<double,double>(3800,4800), QPair<double,double>(0,0.12), QColor("Red"),
                      false, true);

    phasePlot.SetPlot( fields, ui->freqWidget);
    ui->gridLayout_17->addWidget(&phasePlot, 2, 0);
    phasePlot.enableAxis(QwtPlot::xBottom);
    phasePlot.enableAxis(QwtPlot::yLeft);
    //phasePlot.resize(500, 300);
    phasePlot.show();

    // add approach plot
    fields = MyPlot::PlotFields("Bridge Signal", true, "Time", "Bridge Voltage (V)",\
                        QPair<double,double>(0,300), QPair<double,double>(0,1), QColor("Red"),
                        false);
    approachPlot.SetPlot( fields, ui->approachWidget );
    ui->gridLayout_24->setSpacing(0);
    ui->gridLayout_24->addWidget(&approachPlot, 1, 0);
    approachPlot.resize( 500, 300 );
    approachPlot.show();



    // add signal plot 1
    fields = MyPlot::PlotFields("Z Offset", false, "Time", "Z Offset (V)",\
                        QPair<double,double>(0,300), QPair<double,double>(0,1), QColor("Red"),
                        false);
    signalPlot1.SetPlot( fields, ui->signalWidget );
    ui->gridLayout_10->setSpacing(0);
    ui->gridLayout_10->addWidget(&signalPlot1, 1, 0);
    signalPlot1.resize( 500, 100 );
    signalPlot1.show();

    // add signal plot 2
    fields = MyPlot::PlotFields("Error (V)", false, "Time", "Error",\
                        QPair<double,double>(0,300), QPair<double,double>(0,1), QColor("Red"),
                        false);
    signalPlot2.SetPlot( fields, ui->signalWidget );

    ui->gridLayout_10->addWidget(&signalPlot2, 2, 0);
    signalPlot2.resize( 500, 100 );
    signalPlot2.show();
}
void MainWindow::SetPorts(returnBuffer *_node){

    /*Populate the port combobox*/
    //mutex.lock();
    ui->cboComPortSelection->clear();
    if (ui->cboComPortSelection){
        foreach (const QSerialPortInfo info, _node->getList()) {
            ui->cboComPortSelection->addItem(info.portName());
        }
        ui->cboComPortSelection->addItem("Refresh");
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

void MainWindow::approachTimerUp(){
    commandQueue.push(new commandNode(stageSetStep));
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
    //QCoreApplication::processEvents();
    mutex.lock();



    while(!returnQueue.empty()){
        //updateStatusBar("Working...");
        _buffer = returnQueue.front();
        switch(_buffer->getReturnType()) {
         case DACBFRD1:
            ui->dacValue->setValue(_buffer->getFData());
            bfrd1 = _buffer->getFData();
            //returnQueue.pop();
            break;
         case DACBFRD2:
            bfrd2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACBR2:
            br2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACZAMP:
            zAmp = _buffer->getFData();
            //ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACBR1:
            br1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACBFRD3:
            bfrd3 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACZOFFSETFINE:
            zOffsetFine = _buffer->getFData();
            //returnQueue.pop();
            break;
         case DACY1:
            y1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACZOFFSETCOARSE:
            //ui->dacValue->setValue(_buffer->getFData());
            zOffsetCoarse = _buffer->getFData();
            //returnQueue.pop();
            break;
         case DACY2:
            y2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACX1:
            x1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case DACX2:
            x2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            //returnQueue.pop();
            break;
         case ADCZOFFSET:
            bfrd3 = _buffer->getFData();
            if( useBridgeSignalAsSetpoint ) {
                //ui->spnPidSetpoint->setValue(double(bfrd3));
                //ui->currPIDSetpoint->setValue(double(bfrd3));
            }
            //returnQueue.pop();
            break;
         case AFMADCAMPLITUDEID:
            zAmp = _buffer->getFData();
            //returnQueue.pop();
            break;
         case AFMDACOFFSETID:
             zOffsetFine = _buffer->getFData();
             returnQueue.pop();
             break;
         case DAC:
             ui->dacValue->setValue(_buffer->getFData());
             //returnQueue.pop();
             break;
         case ADC:
             ui->adcValue->setValue(_buffer->getFData());
             //returnQueue.pop();
             break;
         case FREQSWEEP:
            freqRetVal = _buffer->getData();
            //returnQueue.pop();
            emit SweepFinished();
            break;
         case GETPORTS:
            SetPorts(returnQueue.front());
            //returnQueue.pop();
            break;
         case DEVICECALIBRATION:
            if(_buffer->getData() == AFM_SUCCESS)
            {
                ui->label_13->setPixmap((QString)":/icons/icons/1413858979_ballgreen-24.png");
            }
            else{
                ui->label_13->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
            }
            //returnQueue.pop();
            break;
         case SCANPARAMETERS:

            QApplication::restoreOverrideCursor();

            if(_buffer->getData() == AFM_SUCCESS){
                ui->label_13->setPixmap((QString)":/icons/icons/1413858979_ballgreen-24.png");
            }
            else{
                ui->label_13->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
            }
            //returnQueue.pop();
            break;
          case SCANDATA:
            //update GRAPH

            if(_buffer->getData() == AFM_SUCCESS){
                QVector<double> zamp = _buffer->getzamp();
                //int _size = zamp.size();
                for (int i = 0; i < 16; i++)
                {
                    scandata[i] = new double[16];

                    for (int j = 0; j < 16; j++)
                    {
                        scandata[i][j] = zamp.at(i);
                    }
                }
                scanPlot.createDataset(scandata, 16, 16, 0, 16, 0, 16);
                scanPlot.updateGL();
            }

            break;
        }

        if( currTab == 3 ) {
            approachPlot.update(time, bfrd3, currTab == Approach ? true: false);
            ui->currOffsetValue->setValue(br1);
            time++;
        }
        if(currTab == 4){
            signalPlot1.update(time, zOffsetFine, currTab == Signal ? true: false);
            signalPlot2.update(time, zAmp - ui->spnPidSetpoint->value(), currTab == Signal ? true: false);
            time++;
        }
        returnQueue.pop();

    }        

    mutex.unlock();
}

void MainWindow::generalTimerUpdate() {


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
    if(index != -1){
        if(ui->cboComPortSelection->itemText(index) == "Refresh" && index != 0)
            commandQueue.push(new commandNode(getPorts));
        else
            commandQueue.push(new commandNode(setPort,(double)index));
    }
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
    approachPlot.setAutoScale(checked);
}

void MainWindow::on_pushButton_4_clicked(bool checked)
{
    signalPlot2.setAutoScale(checked);
}

void MainWindow::on_pushButton_5_clicked(bool checked)
{
    signalPlot1.setAutoScale(checked);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    freqPlot.setMarker(checked);
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
    commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)value));//afm.stageSetPulseWidth(value);
    mutex.unlock();
}

void MainWindow::on_buttonCurrValuePidSetpoint_clicked(bool checked)
{
    useBridgeSignalAsSetpoint = checked;
}

//void MainWindow::autoApproach(nanoiAFM* afm) {
//    qDebug() << "In the threaded coarse approach";
//    mutex.lock();
//    float initVal = afm->readADC(AFM_ADC_AMPLITUDE_ID);
//    commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)3));    //afm->stageSetPulseWidth(3);
//    commandQueue.push(new commandNode(stageSetDirBackward));    //afm->stageSetDirBackward();
//    mutex.unlock();



//    mutex.lock();
//    float bridgeVal;
//    for( ;; ) {
////        commandQueue.push(new commandNode(stageSetStep));

//        commandQueue.push(new commandNode(stageSetStep)); //afm->stageSetStep(); // take a step
//        bridgeVal = afm->readADC(AFM_ADC_AMPLITUDE_ID);
////        commandQueue.push(new commandNode(readADC,0,0,(qint8)AFM_ADC_AMPLITUDE_ID));
////        QThread::msleep(100);
////        mutex.lock();
////        bridgeVal = return_queue.front();
////        returnQueue.pop();
////        mutex.unlock();
//        // if we're less than 95% of init, then slow down
//        if (bridgeVal < 0.95*initVal) {
//            //commandQueue.push(new commandNode(stageSetPulseWidth,0,0,0));
//            commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)0)); //afm->stageSetPulseWidth(0);
//        }
//        // if we're within 90% of init, then autoapproach complete
//        else if (bridgeVal < 0.9*initVal) {
//            break;
//        }
//    }
//    mutex.unlock();
//}

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
/*        ui->retreatButton->isChecked() == true ? afm.stageSetDirBackward() : \
                                                 afm.stageSetDirForward();*/
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
//    mutex.lock();
//    if (checked) {
//        commandQueue.push(new commandNode(stageSetContinuous));
//        continuousStep = true;

//    }
//    else {
//        commandQueue.push(new commandNode(stageAbortContinuous));
//        continuousStep = false;
//    }
//    mutex.unlock();
}

// Frequency sweep
void MainWindow::on_sweepButton_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QVector<double>* frequencyData = new QVector<double>();
    QVector<double>* amplitudeData = new QVector<double>();
    QVector<double>* phaseData = new QVector<double>();
    int bytesRead;

    //connect(ui->sweepButton, SIGNAL(clicked()), ui->freqProgressLabel, SLOT(setText("Boo!")));
    ui->freqProgressLabel->setText("TRUE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : Green; }");

    freqPlot.clearData();
    phasePlot.clearData();

    mutex.lock();
    commandQueue.push(new commandNode(frequencySweep,ui->numFreqPoints->value(), ui->startFrequency->value(), ui->stepSize->value(),\
                                      *amplitudeData, *phaseData,*frequencyData, bytesRead));

    mutex.unlock();
    /*commandQueue.push(new commandNode(frequencySweep,ui->numFreqPoints->value(), ui->startFrequency->value(), ui->stepSize->value(),\
                                    amplitudeData, frequencyData, bytesRead);*/

    //QThread::msleep(100);
    //int retVal = returnQueue.front();
    mutex.lock();

    queue<returnBuffer*> temp = returnQueue;
    returnBuffer* _buffer;
    while(!temp.empty()){
        _buffer = temp.front();
        if(_buffer->getReturnType() == FREQSWEEP){
            freqRetVal = _buffer->getData();
            *amplitudeData = _buffer->getAmplitude();
            *frequencyData = _buffer->getFrequency();
            *phaseData = _buffer->getPhase();
            bytesRead = _buffer->getBytesRead();
            temp.pop();
        }
    }
    mutex.unlock();
    double freqVal;
    double ampVal;
    double phaseVal;
    if ( freqRetVal != AFM_SUCCESS) {
        QApplication::restoreOverrideCursor();
        QMessageBox msg;
        msg.setText(QString("Size of Freq Data: %1. Expected Size: %2").arg(\
                                QString::number(bytesRead), QString::number(ui->numFreqPoints->value()*4) ));
        msg.exec();
    }
    else {
        qDebug() << "Size of X Data: " << frequencyData->size() << "Size of Y Data: " << amplitudeData->size();
        for(int i = 0; i < ui->numFreqPoints->value(); i++ ) {
            //qDebug() << "Freq: " << frequencyData[i] << " Amplitude: " << amplitudeData[i];
            freqVal = frequencyData->at(i);
            phaseVal = phaseData->at(i);
            ampVal = amplitudeData->at(i);
            freqPlot.update(freqVal, ampVal, false); // add points to graph but don't replot
            phasePlot.update(freqVal,phaseVal,false);
        }
        phasePlot.replot();
        freqPlot.replot(); // show the frequency sweep
    }

    frequencyData->clear();
    phaseData->clear();
    amplitudeData->clear();
    ui->freqProgressLabel->setText("FALSE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : red; }");

    QApplication::restoreOverrideCursor();
}

void MainWindow::on_useCurrFreqVal_clicked()
{
    ui->spnFrequencyVoltage->setValue(ui->currFreqVal->value());
}
void MainWindow::on_pushButton_6_clicked()
{
//    //XYGenerator dynamically resizes these values
//    arma::mat X_points;
//    arma::mat Y_points;

//    //Convert all the values to digital values based on a resolution of 4095
//    int vMax=ui->spnScanVmax->value()*AFM_DAC_SCALING;
//    int vMin=ui->spnScanVmin->value()*AFM_DAC_SCALING;
//    int vMin2=ui->spnScanVmin2->value()*AFM_DAC_SCALING;
//    int numPoints=ui->cmbScanNumLines->currentText().toInt();
//    int numLines=ui->cmbScanNumPoints->currentText().toInt();
//    int ret_fail=1;

//    if((generateXYVoltages(vMax, vMin, vMin2, numLines, numPoints, X_points, Y_points) == ret_fail)){
//            QMessageBox msgBox;
//            msgBox.setText("Unable to generate scan points");
//            msgBox.exec();
//            return;
//    }

//    //Write X Y actuator voltages to AFM and read Z. A seperate matrix should be created

//    mat Z_values(X_points.n_rows, X_points.n_cols);

//    //DANGER: Verifiy these values are bein written properly
//    for(int i=0; i < X_points.n_rows; i++){
//        for(int j=0; j < X_points.n_rows; j++){
//            //Write DAC for X voltage
//            //Write DAC for Y Voltage
//            //Wait for Z values to be populated. How long should we wait?
//        }
//    }
//    mutex.lock();
//    for(int i =0; i< 100; i++){
        commandQueue.push(new commandNode(startScan));
//    }
//    mutex.unlock();

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
    freqPlot.setAutoScale(checked);
    phasePlot.setAutoScale(checked);
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
        commandQueue.push(new commandNode(afmAutoApproach,(double)ui->spnPidSetpoint->value()));
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

    updateStatusBar("Setting DAC Values...");
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



void MainWindow::on_calibrateButton_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    double _maxLat;
    double _maxZ;

    _maxLat = ui->latSpinBox->value();
    _maxZ = ui->ZcoarseSpinBox->value();

    if(_maxLat != 0)
        commandQueue.push(new commandNode(deviceCalibration,_maxLat));

    /*IF SCAN PARAMETERS HAVE BEEN SET
        how can we check this?*/

    double numlines = ui->cmbScanNumLines->currentText().toDouble();
    double numpts = ui->cmbScanNumPoints->currentText().toDouble();
    commandQueue.push(new commandNode(scanParameters,ui->spnScanVmin->value(),ui->spnScanVmin2->value(),ui->spnScanVmax->value(),numpts,numlines));

}

void MainWindow::updateStatusBar(QString _string)
{
    this->statusBar()->showMessage(_string);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        ui->toolBar->setEnabled(true);
    }
    else{
        ui->toolBar->setEnabled(false);
    }
}

void MainWindow::pickPlotStyle( QAction* action )
{
    if (!action)
        return;

    if (action == ui->polygon)
    {
        scanPlot.setPlotStyle(FILLED);
    }
    else if (action == ui->filledmesh)
    {
        scanPlot.setPlotStyle(FILLEDMESH);
    }
    else if (action == ui->wireframe)
    {
        scanPlot.setPlotStyle(WIREFRAME);
    }
    else if (action == ui->hiddenline)
    {
        scanPlot.setPlotStyle(HIDDENLINE);
    }
    else if (action == ui->pointstyle)
    {
        scanPlot.setPlotStyle(Qwt3D::POINTS);
    }
    else
    {
        scanPlot.setPlotStyle(NOPLOT);
    }
    scanPlot.updateData();
    scanPlot.updateGL();
}

void MainWindow::setLeftGrid(bool b)
{
    setGrid(Qwt3D::LEFT,b);
}
void MainWindow::setRightGrid(bool b)
{
    setGrid(Qwt3D::RIGHT,b);
}
void MainWindow::setCeilGrid(bool b)
{
    setGrid(Qwt3D::CEIL,b);
}
void MainWindow::setFloorGrid(bool b)
{
    setGrid(Qwt3D::FLOOR,b);
}
void MainWindow::setFrontGrid(bool b)
{
    setGrid(Qwt3D::FRONT,b);
}
void MainWindow::setBackGrid(bool b)
{
    setGrid(Qwt3D::BACK,b);
}

void MainWindow::setGrid(Qwt3D::SIDE s, bool b)
{
//  if (!dataWidget)
//		return;

    int sum = scanPlot.coordinates()->grids();

    if (b)
        sum |= s;
    else
        sum &= ~s;

    scanPlot.coordinates()->setGridLines(sum!=Qwt3D::NOSIDEGRID, sum!=Qwt3D::NOSIDEGRID, sum);
    scanPlot.updateGL();
}

void MainWindow::pickCoordSystem( QAction* action)
{
    if (!action)
        return;

    //activeCoordSystem = action;

    scanPlot.setTitle("QwtPlot3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");

    if (!scanPlot.hasData())
    {
        double l = 0.6;
        scanPlot.createCoordinateSystem(Triple(-l,-l,-l), Triple(l,l,l));
        for (unsigned i=0; i!=scanPlot.coordinates()->axes.size(); ++i)
        {
            scanPlot.coordinates()->axes[i].setMajors(4);
            scanPlot.coordinates()->axes[i].setMinors(5);
        }
    }

    if (action == ui->Box || action == ui->Frame)
    {
        if (action == ui->Box)
            scanPlot.setCoordinateStyle(BOX);
        if (action == ui->Frame)
            scanPlot.setCoordinateStyle(FRAME);
        //grids->setEnabled(true);
    }
    else if (action == ui->None)
    {
        scanPlot.setTitle("QwtPlot3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");
        scanPlot.setCoordinateStyle(NOCOORD);
        //grids->setEnabled(false);
    }
}

void MainWindow::pickFloorStyle( QAction* action )
{
    if (!action)
        return;

    if (action == ui->floordata)
    {
        scanPlot.setFloorStyle(FLOORDATA);
    }
    else if (action == ui->flooriso)
    {
        scanPlot.setFloorStyle(FLOORISO);
    }
    else
    {
        scanPlot.setFloorStyle(NOFLOOR);
    }

    scanPlot.updateData();
    scanPlot.updateGL();
}

void MainWindow::showNormals(bool val)
{
    scanPlot.showNormals(val);
    scanPlot.updateNormals();
    scanPlot.updateGL();
}

void MainWindow::on_continuousButton_pressed()
{

   commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)60));
   if(approachTimer->isActive()){
       approachTimer->stop();
       approachTimer->start(10);
   }
   else
   {
       approachTimer->start(10);
   }
}

void MainWindow::on_continuousButton_released()
{
    if(approachTimer)
        approachTimer->stop();
}
