#include <mainwindow.h>
#include <QDateTime>


//#include <gwyddion.h>

//#define AFM_DAC_AMPLITUDE_MAX_VOLTAGE 1.5 // slider bar for amplitude for control

/* Conrad Sanderson.
 * Armadillo: An Open Source C++ Linear Algebra Library for
 * Fast Prototyping and Computationally Intensive Experiments.
 * Technical Report, NICTA, 2010.
 *
 *
 */

using namespace Qwt3D;

constexpr int MainWindow::UserSpd_to_Microsteps[];
constexpr double MainWindow::UserSpd_to_Speed[];

class Rosenbrock : public Function
{
public:

Rosenbrock(GridPlot& pw)
    : Function(pw)
{
}

double operator()(double x, double y)
{
    return log((1 - x) * (1 - x) + 100 * (y - x * x) * (y - x * x)) / 8;
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
    row = 0;
    //ui->tabScan->setLayout(grid);
    updateStatusBar("Ready");

    // for reading DAC/updating plots
    //ioTimer = startTimer(200); // for reading DAC/ADC
}

void MainWindow::finishedThread()
{
    qDebug() << "Finished mainwindow Thread";
}

MainWindow::~MainWindow()
{
    //MAKE SURE TO TERMINATE THE THREAD ON CLOSE
    emit finished();
}
void MainWindow::abort()
{
    qDebug() << "MainWindow::abort()";
    emit finished();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent()";
    emit finished();
    QMainWindow::closeEvent(event);
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
    qDebug() << "AFM-CLIENT Debug Started: " << QDateTime::currentDateTime().toString() << endl;

    /*State Variables*/
    continuousStep = false;
    isAutoApproach = false;
    useBridgeSignalAsSetpoint = false;
    freqRetVal = -1;

    /*Check Icons
     * TODO: find another way to do this*/
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);

    /*DAC Values*/
    zOffsetCoarse = 0;
    zOffsetFine = 0;
    zAmp = 0;

    scan_result = new afm_data(0,0,1);

    /*Push event to get ports from the serialworker*/
    //commandQueue.push(new commandNode(getPorts,(double)0));
    refreshPortsList();

    /*Initialize DAC limits*/
    init_DAC_PGA();

    //on_spnFrequencyVoltage_2_valueChanged(ui->spnFrequencyVoltage_2->value());      // set amplitude
    //on_spnBridgeVoltage_valueChanged(ui->spnBridgeVoltage->value());                // set bridge voltage
    //on_spnOffsetVoltage_valueChanged(ui->spnOffsetVoltage->value()); // set offset

    /*Timers*/
    //QT-based auto approach
    task1_timer = new QTimer(this);

    generalTimer = new QTimer(this);
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(generalTimerUpdate()));
    generalTimer->start(20); // every 20 ms, we update UI elements/other tasks, like continuous coarse step

    dequeueTimer = new QTimer(this);
    connect(dequeueTimer, SIGNAL(timeout()), this, SLOT(dequeueReturnBuffer()));
    dequeueTimer->start(10);

    approachTimer = new QTimer(this);
    connect(approachTimer, SIGNAL(timeout()), this, SLOT(approachTimerUp()));

    /*Intialize Graphs*/
    CreateGraphs();

    // Stepper Motor controls and static variable initialization
    QStringList microstep_options;
    microstep_options << "1" << "1/2" << "1/4" << "1/8" << "1/16" << "1/32";
    ui->cbo_microstep->addItems(microstep_options);

    /* future watcher for auto approaching*/
    future = new QFuture<void>;
    watcher = new QFutureWatcher<void>;
    connect(watcher, SIGNAL(finished()),this, SLOT(finishedThread()));

    /*Event mapping for setting labels and statuses - I DONT THINK THIS IS NEEDED*/
    QSignalMapper *signalMapper = new QSignalMapper(ui->sweepButton);
    QSignalMapper *signalMapper2 = new QSignalMapper(ui->sweepButton);
    connect(ui->sweepButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->sweepButton, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    connect(this, SIGNAL(SweepFinished()), signalMapper, SLOT(map()));
    connect(this, SIGNAL(SweepFinished()), signalMapper2, SLOT(map()));
    signalMapper->setMapping(ui->sweepButton, "TRUE");
    signalMapper2->setMapping(ui->sweepButton, "QLabel { color : Green; }");
    signalMapper->setMapping(this, "FALSE");
    signalMapper2->setMapping(this, "QLabel { color : Red; }");
    connect(signalMapper, SIGNAL(mapped(QString)), ui->freqProgressLabel, SLOT(setText(QString)));
    connect(signalMapper2, SIGNAL(mapped(QString)), ui->freqProgressLabel, SLOT(setStyleSheet(QString)));

    /*The follow action groups and SIGNALS/SLOTS are for the scan toolbar*/
    QActionGroup *coord = new QActionGroup(this);
    coord->addAction(ui->Box);
    coord->addAction(ui->Frame);
    coord->addAction(ui->None);

    QActionGroup *plotstyle = new QActionGroup(this);
    plotstyle->addAction(ui->pointstyle);
    plotstyle->addAction(ui->wireframe);
    plotstyle->addAction(ui->hiddenline);
    plotstyle->addAction(ui->polygon);
    plotstyle->addAction(ui->filledmesh);
    plotstyle->addAction(ui->nodata);

    QActionGroup *grids = new QActionGroup(this);
    grids->addAction(ui->front);
    grids->addAction(ui->back);
    grids->addAction(ui->right);
    grids->addAction(ui->left);
    grids->addAction(ui->ceil);
    grids->addAction(ui->floor);
    grids->setExclusive(false);

    QActionGroup *floorstyle = new QActionGroup(this);
    floorstyle->addAction(ui->floordata);
    floorstyle->addAction(ui->flooriso);
    floorstyle->addAction(ui->floornone);

    connect(ui->left, SIGNAL(toggled(bool)), this, SLOT(setLeftGrid(bool)));
    connect(ui->right, SIGNAL(toggled(bool)), this, SLOT(setRightGrid(bool)));
    connect(ui->ceil, SIGNAL(toggled(bool)), this, SLOT(setCeilGrid(bool)));
    connect(ui->floor, SIGNAL(toggled(bool)), this, SLOT(setFloorGrid(bool)));
    connect(ui->back, SIGNAL(toggled(bool)), this, SLOT(setBackGrid(bool)));
    connect(ui->front, SIGNAL(toggled(bool)), this, SLOT(setFrontGrid(bool)));
    connect(plotstyle, SIGNAL(triggered(QAction *)), this, SLOT(pickPlotStyle(QAction *)));
    connect(coord, SIGNAL(triggered(QAction *)), this, SLOT(pickCoordSystem(QAction *)));
    connect(floorstyle, SIGNAL(triggered(QAction *)), this, SLOT(pickFloorStyle(QAction *)));
    connect(ui->normals, SIGNAL(toggled(bool)), this, SLOT(showNormals(bool)));
    //connect(ui->sweepButton, SIGNAL(clicked()),ui->freqProgressLabel, SLOT(setText()));
    //connect(ui->sweepButton, SIGNAL(clicked()),ui->freqProgressLabel, SLOT(setStyleSheet()));
}

void MainWindow::CreateGraphs()
{
    //freqPlot = new Plot();


    //scanPlot = GridPlot(ui->frame);
    scanPlot.setTitle("Forward");

    Rosenbrock rosenbrock(scanPlot);

    rosenbrock.setMesh(41, 31);
    rosenbrock.setDomain(-1.73, 1.5, -1.5, 1.5);
    rosenbrock.setMinZ(-20);

    rosenbrock.create();

    scanPlot.setRotation(30, 0, 15);
    scanPlot.setScale(1, 1, 1);
    scanPlot.setShift(0.15, 0, 0);
    scanPlot.setZoom(0.9);

    for (unsigned i = 0; i != scanPlot.coordinates()->axes.size(); ++i) {
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
    MyPlot::PlotFields fields = MyPlot::PlotFields("", true, "Frequency (Hz)", "Amplitude (V)", \
                                                   QPair<double, double>(3000, 12000), QPair<double, double>(0, 3), QColor("Red"),
                                                   false, true);

    freqPlot.SetPlot(fields, ui->freqWidget);
    ui->gridLayout_17->setSpacing(0);
    ui->gridLayout_17->addWidget(&freqPlot, 1, 0);
    freqPlot.enableAxis(QwtPlot::xBottom);
    freqPlot.enableAxis(QwtPlot::yLeft);
    //freqPlot.resize(500, 300);
    freqPlot.show();

    connect(&freqPlot, SIGNAL(setDDSFrequency(QPointF)), this, SLOT(setDDSFrequency(QPointF)));
    //connect(freqPlot,SIGNAL(clicked()),freqPlot,SLOT(displayPoint(const QPointF&)));
    //freqPlot.connect(freqPlot,SIGNAL(),freqPlot,SLOT(displayPoint(const QPointF&)));

    //phase plot
    fields = MyPlot::PlotFields("", true, "Frequency (Hz)", "Phase (Deg)", \
                                QPair<double, double>(3000, 12000), QPair<double, double>(0, 3), QColor("Blue"),
                                false, true);

    phasePlot.SetPlot(fields, ui->freqWidget);
    ui->gridLayout_17->addWidget(&phasePlot, 2, 0);
    phasePlot.enableAxis(QwtPlot::xBottom);
    phasePlot.enableAxis(QwtPlot::yLeft);
    //phasePlot.resize(500, 300);
    phasePlot.show();

    // add approach plot
    fields = MyPlot::PlotFields("Z Amplitude Piezo Signal", true, "Time", "Voltage (V)", \
                                QPair<double, double>(0, 300), QPair<double, double>(0, 1), QColor("Red"),
                                false);
    approachPlot.SetPlot(fields, ui->approachWidget);
    ui->gridLayout_24->setSpacing(0);
    ui->gridLayout_24->addWidget(&approachPlot, 1, 0);
    approachPlot.resize(500, 100);
    approachPlot.setAutoScale(true);
    approachPlot.show();

    // add approach plot 2
    fields = MyPlot::PlotFields("PHASE SIGNAL", true, "Time", "something", \
                                QPair<double, double>(0, 300), QPair<double, double>(0, 1), QColor("Green"),
                                false);
    approachPlot2.SetPlot(fields, ui->approachWidget);
    ui->gridLayout_24->addWidget(&approachPlot2, 2, 0);
    approachPlot2.resize(500, 100);
    approachPlot2.setAutoScale(true);
    approachPlot2.show();

    // add signal plot 1
    fields = MyPlot::PlotFields("Z Offset", false, "Time", "Z Offset (V)", \
                                QPair<double, double>(0, 300), QPair<double, double>(0, 1), QColor("Red"),
                                false);
    signalPlot1.SetPlot(fields, ui->signalWidget);
    ui->gridLayout_10->setSpacing(0);
    ui->gridLayout_10->addWidget(&signalPlot1, 1, 0);
    signalPlot1.resize(500, 100);
    signalPlot1.show();

    // add signal plot 2
    fields = MyPlot::PlotFields("Error (V)", false, "Time", "Error", \
                                QPair<double, double>(0, 300), QPair<double, double>(0, 1), QColor("Red"),
                                false);
    signalPlot2.SetPlot(fields, ui->signalWidget);
    ui->gridLayout_10->addWidget(&signalPlot2, 2, 0);
    signalPlot2.resize(500, 100);
    signalPlot2.show();

    //force curve
    fields = MyPlot::PlotFields("Force Curve", true, "Z Offset (V)", "Z Amplitude", \
                                QPair<double, double>(0, 1000), QPair<double, double>(0, 10), QColor("Blue"),
                                false, true);
    forceCurve.SetPlot(fields, ui->forceWidget);
    ui->forcecurve_gridlayout->setSpacing(0);
    ui->forcecurve_gridlayout->addWidget(&forceCurve, 1, 0);
    forceCurve.setAutoScale(true);
    forceCurve.resize(500, 100);
    forceCurve.show();
}
void MainWindow::refreshPortsList()
{
    /*Populate the port combobox*/
    detectedSerialPortsList = QSerialPortInfo::availablePorts();
    //mutex.lock();
    ui->cboComPortSelection->clear();
    if (ui->cboComPortSelection) {
        for(const QSerialPortInfo &port_info : detectedSerialPortsList) {
            ui->cboComPortSelection->addItem(port_info.portName());
        }
        ui->cboComPortSelection->addItem("Refresh");
    }

//    if(ui->cboComPortSelection->itemText(0) != "Refresh")
//        commandQueue.push(new commandNode(setPort,(double)0));
    //mutex.unlock();
}

/*
 * Need to initialize the DAC limits and PGA values
 *
 */
void MainWindow::init_DAC_PGA()
{
    commandQueue.push(new commandNode(setDacMaxValues, DAC_BFRD1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_BFRD2, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_BR2, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_ZAMP, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_BR1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_BFRD3, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_ZOFFSET_FINE, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_ZOFFSET_COARSE, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_Y1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_Y2, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_X1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_X2, AFM_DAC_MAX_VOLTAGE));
    /* Initialize offset, amplitude, and bridge voltage with the value we have set in UI*/
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_DDS_AMPLITUDE, ui->spn_dds_amplitude->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_LEVELING, ui->spn_leveling->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZCOARSE, ui->spn_zcoarse->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZFINE, ui->spn_zfine->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_X1, ui->spn_freq_x1->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y1, ui->spn_freq_y1->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_X2, ui->spn_freq_x2->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y2, ui->spn_freq_y2->value()));
}

void MainWindow::approachTimerUp()
{
    if (approachTimer->isActive())
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
void MainWindow::dequeueReturnBuffer()
{
    currTab = ui->tabWidget->currentIndex();

    QVector<double> ampData;
    double ampVal;
    /*
     * This forces the buffer to be completely emptied
     * on each timer trigger
     */
    //QCoreApplication::processEvents();

    while (!returnQueue.empty()) {
        //updateStatusBar("Working...");
        QString fdata;
        _buffer = returnQueue.front();
        switch (_buffer->getReturnType()) {
        case DACBFRD1:
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            bfrd1 = _buffer->getFData();
            break;
        case DACBFRD2:
            bfrd2 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACBR2:
            br2 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACZAMP:
            zAmp = _buffer->getFData();
            break;
        case DACBR1:
            br1 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACBFRD3:
            bfrd3 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACZOFFSETFINE:
            zOffsetFine = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACY1:
            y1 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACZOFFSETCOARSE:
            zOffsetCoarse = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACY2:
            y2 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACX1:
            x1 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case DACX2:
            x2 = _buffer->getFData();
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case ADCZOFFSET:
            adcZ = _buffer->getFData();
            ui->adcValue->setText(QString::number(_buffer->getFData()));
            ui->label_autoappr_meas->setText(QString::number(_buffer->getFData()));
            if (autoapproach_state > 0) {
                autoappr_measurement = adcZ;
            }
            break;
        case ADCPHASE:
            bfrd3 = _buffer->getFData();
            break;
        case READSIGNALPHASEOFFSET:
            offset = _buffer->getdoffset();
            phase = _buffer->getdphase();
            adcZ = _buffer->getdsignal(); //ADC Z PZR FORCE AMPLITUDE
            ui->label_adczfine->setText(QString::number(offset));
            ui->label_appr_phase->setText(QString::number(phase));
            ui->adcValue->setText(QString::number(adcZ));
            ui->label_autoappr_meas->setText(QString::number(adcZ));
            if (autoapproach_state > 0) {
                autoappr_measurement = adcZ;
            }
            break;
        case AFMADCAMPLITUDEID:
            zAmp = _buffer->getFData();
            break;
        case AFMDACOFFSETID:
            zOffsetFine = _buffer->getFData();
            break;
        case DAC:
            fdata = QString::number(_buffer->getFData()); ui->dacValue->setText(fdata);
            break;
        case ADC:
            fdata = QString::number(_buffer->getFData());
            ui->adcValue->setText(fdata);
            break;
        case FREQSWEEP:
            freqRetVal = _buffer->getData();
            CreateFreqSweepGraph(_buffer->getAmplitude(), _buffer->getPhase(), _buffer->getBytesRead());
            emit SweepFinished();
            break;
        case FORCECURVE:
            ampData = _buffer->getAmplitude();
            for (int i = 0; i < ampData.size() - 1; i++) {
                ampVal = ampData.at(i);
                forceCurve.update(i, ampVal, false);
            }
            forceCurve.replot();
            break;
        case DEVICECALIBRATION:
            if (_buffer->getData() == AFM_SUCCESS)
                ui->label_13->setPixmap((QString)":/icons/icons/1413858979_ballgreen-24.png");
            else
                ui->label_13->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
            break;
        case SCANPARAMETERS:
            QApplication::restoreOverrideCursor();

            if (_buffer->getData() == AFM_SUCCESS) {
//                ui->label_13->setPixmap((QString)":/icons/icons/1413858979_ballgreen-24.png");
                msgBox.setText("Scan Parameters Set");
                msgBox.exec();
            } else {
                ui->label_13->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
            }
            break;
        case STARTSCAN_4ACT:
            //Callback to the state machine
            QTimer::singleShot(1, this, SLOT(scan_state_machine()));
            break;
        case SCANDATA:
            //Take the data out from _buffer and make it into something useful for state machine
           {
            if (_buffer->getData() == AFM_FAIL) {
                qDebug() << "afm bad scan data received";
                scan_state = SCAN_DISABLED;
                QTimer::singleShot(1, this, SLOT(scan_state_machine()));
                break;
            }

            int append_result = scan_result->append_data(_buffer->getzoffset(),
                                                         _buffer->getzamp(),
                                                         _buffer->getzphase());
            if(append_result == 0) {
                qDebug() << "Scan Data is in success!";
            } else if (append_result == 1) {
                qDebug() << "afm_data append_scan_data is full";
            } else {
                //We have a fault
                qDebug() << "afm_data append_scan_data failed";
                scan_state = SCAN_DISABLED;
            }
/*
            if (_buffer->getData() == AFM_SUCCESS) {
                QVector<double> zamp = _buffer->getzamp();
                int _size = zamp.size();
                for (int i = 0; i < _size; i++) {
                    scandata[row] = new double[_size];
                    for (int j = 0; j < _size; j++)
                        scandata[row][j] = zamp.at(row);
                    row++;
                }
                scanPlot.createDataset(scandata, _size, _size, 0, _size, 0, _size);
                scanPlot.updateGL();
            }
            */
            //  qDebug() << "Scan Data is in!";
            //Update the line graphs
             if (currTab == Approach) {
                adcZ =  _buffer->getzamp().at(0) * AFM_ADC_SCALING;
                //phase = _buffer->getzphase().at(0) * AFM_ADC_SCALING;
                phase = _buffer->getzoffset().at(0) * AFM_ADC_SCALING; //temp to show zoffset on phase graph
             }

            //Callback to the state machine
            QTimer::singleShot(1, this, SLOT(scan_state_machine()));
           }
        break;
        case PIDDISABLE:
            ui->label_pid_indicator->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
            break;
        case PIDENABLE:
            ui->label_pid_indicator->setPixmap((QString)":/icons/icons/1413858979_ballgreen-24.png");
            if(scan_state==2) {
                QTimer::singleShot(1, this, SLOT(scan_state_machine()));
            }
            break;
        case SETDACTABLE:
            if (_buffer->getData() == AFM_SUCCESS) {
                qDebug() << "SETDACTABLE success. Call again.";
                set_DAC_table_state_machine(1);
            } else {
                qDebug() << "SETDACTABLE fail. gg.";
            }
            break;
        case SIGGEN:
            if (_buffer->getData() == AFM_SUCCESS) {
                ui->label_scan_param_light->setPixmap((QString)":/icons/icons/1413858979_ballgreen-24.png");
                //msgBox.setText("Scan Parameters Set Success");
                //msgBox.exec();
            } else {
                ui->label_scan_param_light->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
                msgBox.setText("Scan Parameters Set Failed");
                msgBox.exec();
            }
            break;
        case AAPPR_STA:
            adcZ = _buffer->getdsignal();
            ui->lbl_autoappr_mcu_state->setText(QString::number(_buffer->getData()));
            ui->label_autoappr_meas->setText(QString::number(_buffer->getdsignal()));
            ui->label_33->setText(QString::number(_buffer->getData()));
            if((enum auto_approach_states_mcu)_buffer->getData() == APPR_MCU_DISABLED){
                isAutoApproach = false;
            } else if ((enum auto_approach_states_mcu)_buffer->getData() == SETPOINT_REACHED){
                commandQueue.push(new commandNode(pidSetP,ui->spnPidValueP->value()));
                commandQueue.push(new commandNode(pidSetI,ui->spnPidValueI->value()));
                commandQueue.push(new commandNode(pidSetD,ui->spnPidValueD->value()));
                commandQueue.push(new commandNode(pidSetPoint,ui->spnPidSetpoint->value()));
                commandQueue.push(new commandNode(pidEnable));//afm.pidEnable();
            }
            break;
        case AFMREBOOT:
            // Send the init stuff again
            updateStatusBar("AFM has rebooted. Re-initializing device. ");
            isAutoApproach = false;
            init_DAC_PGA();
            commandQueue.push(new commandNode(setDDSSettings, ui->currFreqVal->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_DDS_AMPLITUDE, ui->spn_dds_amplitude->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_LEVELING, ui->spn_leveling->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZCOARSE, ui->spn_zcoarse->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZFINE, ui->spn_zfine->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_X1, ui->spn_freq_x1->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y1, ui->spn_freq_y1->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_X2, ui->spn_freq_x2->value()));
            commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y2, ui->spn_freq_y2->value()));
            commandQueue.push(new commandNode(pidSetP,ui->spnPidValueP->value()));
            commandQueue.push(new commandNode(pidSetI,ui->spnPidValueI->value()));
            commandQueue.push(new commandNode(pidSetD,ui->spnPidValueD->value()));
            commandQueue.push(new commandNode(pidSetPoint,ui->spnPidSetpoint->value()));
               //commandQueue.push(new commandNode(pidEnable));//afm.pidEnable();
            break;
        } //end Switch

        if (currTab == Approach) {
            approachPlot.update(time, adcZ, true);
            approachPlot.setAxisAutoScale(QwtPlot::yLeft);
            approachPlot2.update(time, phase, true);
            approachPlot2.setAxisAutoScale(QwtPlot::yLeft);
            approachPlot.replot();
            approachPlot2.replot();
            //    ui->currOffsetValue->setValue(signal);
            //   ui->label_autoappr_meas->setText(QString::number(offset));
            time++;
        }
        if (currTab == 4) {
            signalPlot1.update(time, zOffsetFine, currTab == Signal ? true : false);
            signalPlot2.update(time, zAmp - ui->spnPidSetpoint->value(), currTab == Signal ? true : false);
            time++;
        }
        returnQueue.pop();
    }
}

void MainWindow::generalTimerUpdate()
{
}

void MainWindow::on_spnOffsetVoltage_valueChanged(double arg1)
{
//    mutex.lock();
//    commandQueue.push(new commandNode(memsSetOffset,(double)arg1));//afm.memsSetOffset(arg1);
//    mutex.unlock();
}

void MainWindow::on_spnBridgeVoltage_valueChanged(double arg1)
{
    commandQueue.push(new commandNode(memsSetBridgeVoltage, (double)arg1));//afm.memsSetBridgeVoltage(arg1);
}



void MainWindow::on_spnPidValueP_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetP, (double)arg1));//afm.pidSetP(arg1);
    mutex.unlock();
}

void MainWindow::on_spnPidValueI_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetI, (double)arg1));//afm.pidSetI(arg1);
    mutex.unlock();
}

void MainWindow::on_spnPidValueD_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetD, (double)arg1));//afm.pidSetD(arg1);
    mutex.unlock();
}

void MainWindow::on_spnPidSetpoint_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(pidSetPoint, (double)arg1));//afm.pidSetPoint(arg1);
    mutex.unlock();
}

void MainWindow::on_cboComPortSelection_currentIndexChanged(int index)
{
    if (index != -1) {
        if (ui->cboComPortSelection->itemText(index) == "Refresh" && index != 0)
            refreshPortsList();
        else
            commandQueue.push(new commandNode(setPort, (double)index));
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

void MainWindow::on_sld_stepmot_speed_valueChanged(int value){
    ui->lbl_stepmot_speed->setText(QString::number(value));
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSetSpeed, (double)value)); //int8 commandnode is not large enough, so use double.
    mutex.unlock();
}

void MainWindow::on_cbo_microstep_currentIndexChanged(int index){
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSetMicrostep, (qint8)index));
    mutex.unlock();
}

void MainWindow::on_btn_stepmot_cont_go_clicked(){
    mutex.lock();
    commandQueue.push(new commandNode(stepMotContGo));
    mutex.unlock();
}

void MainWindow::on_btn_stepmot_cont_stop_clicked(){
    mutex.lock();
    commandQueue.push(new commandNode(stepMotContStop));
    mutex.unlock();
}

void MainWindow::on_btn_stepmot_singlestep_clicked(){
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSingleStep));
    mutex.unlock();
}
void MainWindow::on_radio_stepmot_fwd_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSetDir, qint8(MOT_BACK)));//afm.stageSetDirBackward();
    mutex.unlock();
}
void MainWindow::on_radio_stepmot_back_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSetDir, qint8(MOT_FWD)));//afm.stageSetDirForward();
    mutex.unlock();
}
void MainWindow::on_btn_stepmot_sleep_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_SLEEP)));//afm.stageSetDirBackward();
    mutex.unlock();
}
void MainWindow::on_btn_stepmot_wake_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_WAKE)));//afm.stageSetDirForward();
    mutex.unlock();
}

void MainWindow::on_btn_autoappr_go_clicked()
{
    autoapproach_state = APPR_WAKEUP; //Initial state
    connect(task1_timer, SIGNAL(timeout()), this, SLOT(autoApproach_state_machine()));
    //Launch the autoApproach_state_machine
    QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
}


void MainWindow::on_btn_autoappr_stop_clicked(){
    qDebug() << "ABORT Inside AutoAppr State Machine i=" << autoapproach_state;
    autoapproach_state = APPR_DISABLED;
    mutex.lock();
    commandQueue.push(new commandNode(stepMotContStop));
    commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_SLEEP)));
    mutex.unlock();
    QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
}

/**
 * @brief MainWindow::autoApproach_state_machine is the core algorithm for
 *        auto approach. The autoapproach_state variable defines the state
 *        of operation.
 */

void MainWindow::autoApproach_state_machine(){
    //DEBUG ONLY!
    //autoappr_measurement = ui->spinbox_autoappr_meas_test->value();

    qDebug() << "AutoAppr State Machine i=" << autoapproach_state;
    switch(autoapproach_state) {
    case APPR_DISABLED: //Disabled state
        isAutoApproach = false;
        task1_timer->stop();
        ui->progbar_autoappr->setValue(0);
        ui->spnPidSetpoint_2->setEnabled(true);
        commandQueue.push(new commandNode(stepMotContStop));
        commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_SLEEP)));
        break;
    case APPR_WAKEUP: //Wake up and intialization.
        //Update UI
        isAutoApproach = true;
        //Grab current setpoint value
        autoappr_setpoint = ui->spnPidSetpoint_2->value();
        ui->spnPidSetpoint_2->setEnabled(false);
        ui->progbar_autoappr->setValue(1);
        mutex.lock();
        //Turn OFF PID
        commandQueue.push(new commandNode(pidDisable));
        //Stop and sleep the motor
        commandQueue.push(new commandNode(stepMotContStop));
        commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_SLEEP)));
        //Now wake it up
        commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_WAKE)));
        commandQueue.push(new commandNode(stepMotSetDir, qint8(MOT_FWD))); //Forward is down...
        commandQueue.push(new commandNode(stepMotSetSpeed, (double)26300));
        commandQueue.push(new commandNode(stepMotSetMicrostep, (qint8)1));
        mutex.unlock();
        autoapproach_state=FAST_RETR_GO;
        QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
        break;
    case FAST_RETR_GO: //Back-up a bit
        ui->progbar_autoappr->setValue(2);
        mutex.lock();
        commandQueue.push(new commandNode(stepMotContGo)); //int8 is not large enough, so use double.
        mutex.unlock();
        autoapproach_state=FAST_RETR_STOP;
        QTimer::singleShot(200, this, SLOT(autoApproach_state_machine()));
        break;
    case FAST_RETR_STOP: //Stop the retract
        ui->progbar_autoappr->setValue(3);
        mutex.lock();
        commandQueue.push(new commandNode(stepMotContStop));
        commandQueue.push(new commandNode(stepMotSetDir, qint8(MOT_BACK)));
        mutex.unlock();
        autoapproach_state=APPR_INIT_MEAS;
        QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
        break;
  case APPR_INIT_MEAS: //Get initial measurement
        //Measure Signal... ADC_Z_PZR_AMP
        //Clear existing first
        autoappr_measurement = -1;
        //Note that handler for ADCZOFFSET updates autoappr_measurement!
        commandQueue.push(new commandNode(readADC, (qint8)ADC_Z_PZR_AMP));
        autoapproach_state= PRE_FAST_APPR;
        QTimer::singleShot(600, this, SLOT(autoApproach_state_machine()));
        break;
    case PRE_FAST_APPR: //Continuous ON
        //Update UI
        ui->progbar_autoappr->setValue(4);
        if(autoappr_measurement > 0) {
            QString s = QString::number(autoappr_measurement);
            ui->label_autoappr_meas->setText(s);
        }

        // The callback for readADC ADCZOFFSET should update autoappr_measurement
        if(autoappr_measurement > 0) {
            if(autoappr_measurement <= autoappr_setpoint) {
                //Make sure that setpoint is OK.
                autoapproach_state = SETPOINT_REACHED;
                QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
                break;
            } else {
                //if signal received then save measurement_init and proceed.
                autoappr_measurement_init = autoappr_measurement;
                // VERY IMPORTANT We also double check that the target is less than 95% of the init to begin with.
                // If it is more than 95%, then we should skip straight to state 6.
                if(autoappr_setpoint <= (0.80*autoappr_measurement_init)) { //debug for now use 80%
                    mutex.lock();
                    commandQueue.push(new commandNode(stepMotContGo));
                    mutex.unlock();
                    autoapproach_state=FAST_APPR;
                    task1_timer->start(20);
                } else {
                    autoapproach_state = PRE_SLOW_APPR;
                    QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
                }
            }
        } else {
            //if signal not measured, then stop and throw err!
            autoapproach_state = APPR_DISABLED;
            QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
            qDebug() << "AutoAppr No Init Measurement Received autoappr_measurement=" << autoappr_measurement;
            qDebug() << "AutoAppr automatic abort. autoappr_measurement=" << autoappr_measurement << " autoapproach_fault_count="<<autoapproach_fault_count;
            updateStatusBar("Auto Approach aborted. Bad communication. ");
        }
        break;
    case FAST_APPR: //Abort available here.
        ui->progbar_autoappr->setValue(5);
        // Get measured signal. If measured signal expected has not been received, then uhhh
        // If measured signal is less than whatever, do whatever
        // if not yet at .95 init, etc...)

        // Update display
        if(autoappr_measurement > 0) {
            QString s = QString::number(autoappr_measurement);
            ui->label_autoappr_meas->setText(s);
        }

        // Actual logic
        // First check measurement validity
        if (autoappr_measurement == -1 && autoapproach_fault_count < MAX_AUTOAPPR_FAULT_COUNT) {
            qDebug() << "autoappr_measurement has not been updated yet!";
            autoapproach_fault_count++;
        } else if (autoapproach_fault_count >= MAX_AUTOAPPR_FAULT_COUNT) {
            autoapproach_state = APPR_DISABLED;
            qDebug() << "AutoAppr automatic abort. autoappr_measurement=" << autoappr_measurement << " autoapproach_fault_count="<<autoapproach_fault_count;
            updateStatusBar("Auto Approach aborted. Bad communication. ");
            break;
        } else {
            autoapproach_fault_count = 0;
        }
        // Now check measurement against target value.
        if((autoappr_measurement <= (0.95*autoappr_measurement_init)) && autoappr_measurement > 0) {
            task1_timer->stop();
            autoapproach_state=PRE_SLOW_APPR;
            QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
        } else if (autoappr_measurement != -1) {
            //Continue running the motor
            //Measure Signal... from ADC_Z_PZR_AMP
            //task1_timer will keep calling the state machine
            commandQueue.push(new commandNode(readADC, (qint8)ADC_Z_PZR_AMP));
        }
        // Reset measurement var
        autoappr_measurement = -1;
        break;
    case PRE_SLOW_APPR: //Reduce speed
        ui->progbar_autoappr->setValue(6);
        commandQueue.push(new commandNode(stepMotSetMicrostep, (qint8)3));
        commandQueue.push(new commandNode(stepMotSetSpeed, (double)20000));
        commandQueue.push(new commandNode(readADC, (qint8)ADC_Z_PZR_AMP));
        commandQueue.push(new commandNode(stepMotContGo));
        autoapproach_state=SLOW_APPR;
        task1_timer->start(20);
    case SLOW_APPR://Abort available here.
        ui->progbar_autoappr->setValue(7);
        // Update display
        if(autoappr_measurement > 0) {
            QString s = QString::number(autoappr_measurement);
            ui->label_autoappr_meas->setText(s);
        }
        //Loop like state #5
        // First check measurement validity
        if (autoappr_measurement == -1 && autoapproach_fault_count < MAX_AUTOAPPR_FAULT_COUNT) {
            qDebug() << "autoappr_measurement has not been updated yet!";
            autoapproach_fault_count++;
        } else if (autoapproach_fault_count >= MAX_AUTOAPPR_FAULT_COUNT) {
            autoapproach_state = APPR_DISABLED;
            qDebug() << "AutoAppr automatic abort. autoappr_measurement=" << autoappr_measurement << " autoapproach_fault_count="<<autoapproach_fault_count;
            updateStatusBar("Auto Approach aborted. Bad communication. ");
            break;
        } else {
            autoapproach_fault_count = 0;
        }
        // Check if measurement is at setpoint autoappr_setpoint
        if((autoappr_measurement <= autoappr_setpoint) && autoappr_measurement > 0) {
            task1_timer->stop();
            autoapproach_state=SETPOINT_REACHED;
            QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
        } else if (autoappr_measurement != -1) {
            //Continue running the motor
            //Measure Signal... from ADC_Z_PZR_AMP
            //task1_timer will keep calling the state machine
            commandQueue.push(new commandNode(readADC, (qint8)ADC_Z_PZR_AMP));
        }
        autoappr_measurement = -1;
        break;
    case SETPOINT_REACHED:
        ui->progbar_autoappr->setValue(8);
        commandQueue.push(new commandNode(stepMotContStop));
        commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_SLEEP)));
        //UPDATE UI
        //Turn on PID
        commandQueue.push(new commandNode(pidEnable));
        //Clean Up
        autoapproach_state = APPR_DISABLED;
        updateStatusBar("Auto Approach completed ");
        QTimer::singleShot(1, this, SLOT(autoApproach_state_machine()));
        break;
    }
}

void MainWindow::on_stepButton_clicked()
{
    mutex.lock();
    commandQueue.push(new commandNode(stageSetStep));//afm.stageSetStep();
    mutex.unlock();
}

void MainWindow::CreateFreqSweepGraph(QVector<double>   amplitudeData,
                                      QVector<double>   phaseData,
                                      int bytesRead)
{
    ui->freqProgressLabel->setText("TRUE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : Green; }");

    freqPlot.clearData();
    phasePlot.clearData();

    double freqVal;
    double ampVal;
    double phaseVal;
    double maxAmp=0;
    double maxAmpFreq=0;
    if (freqRetVal != AFM_SUCCESS) {
        QApplication::restoreOverrideCursor();
        QMessageBox msg;
        msg.setText(QString("Size of Freq Data: %1. Expected Size: %2").arg( \
                            QString::number(bytesRead), QString::number(ui->numFreqPoints->value() * 4)));
        msg.exec();
    } else {
        //qDebug() << "Size of X Data: " << frequencyData.size() << "Size of Y Data: " << amplitudeData.size();
        for (int i = 0; i < ui->numFreqPoints->value(); i++) {
            //qDebug() << "Freq: " << frequencyData[i] << " Amplitude: " << amplitudeData[i];
            quint16 step_size = ((quint16)ui->endFrequency->value()-(quint16)ui->startFrequency->value()) / (quint16)ui->numFreqPoints->value();
            freqVal = ui->startFrequency->value() + i * step_size;
            if(i < phaseData.size() && i < amplitudeData.size()) {
                phaseVal = phaseData.at(i);
                ampVal = amplitudeData.at(i);
                freqPlot.update(freqVal, ampVal, false); // add points to graph but don't replot
                phasePlot.update(freqVal, phaseVal, false);
                //Submit the current points to state machine for processing
                auto_freqsweep(ampVal, freqVal);
            } else {
                qDebug() << "MainWindow::CreateFreqSweepGraph Bad input array! Index out of bounds!";
                break;
            }
        }
        freqPlot.setAxisAutoScale(QwtPlot::yLeft);
        freqPlot.setAxisAutoScale(QwtPlot::xBottom);
        freqPlot.replot();
        phasePlot.setAxisAutoScale(QwtPlot::yLeft);
        phasePlot.setAxisAutoScale(QwtPlot::xBottom);
        phasePlot.replot(); // show the frequency sweep
    }

    //frequencyData.clear();
    phaseData.clear();
    amplitudeData.clear();
    ui->freqProgressLabel->setText("FALSE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : red; }");

    QApplication::restoreOverrideCursor();
    auto_freqsweep(-1, -1);
}

/**
 * @brief MainWindow::auto_freqsweep automatically scans the frequency range and selects the peak amplitude.
 *        Notifies user if it cannot find it.
 *        The frequency sweep graphing function should callback to auto_freqsweep.
 *        The complexity of this code is the need to recognize a cut-off (flat top) graph and bad graph.
 *        IMPORTANT!!! auto_freqsweep_amp_buffer must not be empty
 *
 * @param amp The amplitude from frequency sweep callback
 * @param freq The frequency at an amplitude from frequency sweep callback
 */

void MainWindow::auto_freqsweep(double amp, double freq){
    quint16 step_size;
    //Negative 1 is a special value which indicates that a particular sweep incoming data is now complete
    //If we are at the rough sweep stage, increment mode, or decrement mode, this code
    //will make sure the state machine ends up at where it needs to be
    if (amp == -1 && freq == -1) {
        if(auto_freqsweep_state == 2) {
            auto_freqsweep_state = 3;
        }
        else if (auto_freqsweep_state == 5 || auto_freqsweep_state == 4) {
            auto_freqsweep_state = 6;
        }
    }
    qDebug() << "auto_freqsweep state=" <<auto_freqsweep_state;
    switch(auto_freqsweep_state) {
    //State 0. disabled state. does nothing
    case 0:
        //This part is self-explanatory
        break;
    case 1:
        //Reset everything
        auto_freqsweep_maxamp_valid = false;
        auto_freqsweep_freq_at_maxamp = 0;
        auto_freqsweep_maxamp = 0;
        auto_freqsweep_decr_count = 0;
        auto_freqsweep_amp_buffer = {0,0,0,0,0};
        // Begin rough max sweep
        ui->endFrequency->setValue(15000); //TODO The 15kHz and 1Khz range can be changed
        ui->startFrequency->setValue(1000);
        ui->numFreqPoints->setValue(250);
        step_size = ((quint16)ui->endFrequency->value()-(quint16)ui->startFrequency->value()) / (quint16)ui->numFreqPoints->value();
        commandQueue.push(new commandNode(frequencySweep, (quint16)ui->numFreqPoints->value(), (quint16)ui->startFrequency->value(), (quint16)step_size));
        auto_freqsweep_state++;
        break;
    case 2:
        // Simple checking algorithm to obtain a range for the second, fine sweep
        if(amp > auto_freqsweep_maxamp) {
            auto_freqsweep_maxamp = amp;
            auto_freqsweep_freq_at_maxamp = freq;
        }
        break;
    case 3:
        // Start the fine second sweep
        ui->endFrequency->setValue(auto_freqsweep_freq_at_maxamp + 500);
        ui->startFrequency->setValue(auto_freqsweep_freq_at_maxamp - 500);
        ui->numFreqPoints->setValue(100);
        step_size = ((quint16)ui->endFrequency->value()-(quint16)ui->startFrequency->value()) / (quint16)ui->numFreqPoints->value();
        commandQueue.push(new commandNode(frequencySweep, (quint16)ui->numFreqPoints->value(), (quint16)ui->startFrequency->value(), (quint16)step_size));
        auto_freqsweep_state++;
        auto_freqsweep_maxamp = 0; //Clear the var for fine sweep
        break;
    case 4:
        // Collect and analyse data from the fine sweep
        // INCREMENT MODE
        // Put data into buffer
        if(auto_freqsweep_amp_buffer.size() > 4) { //limit size of buffer to 5
            auto_freqsweep_amp_buffer.pop_front();
        }
        auto_freqsweep_amp_buffer.push_back(amp);
        // Check if this is a new max and is at least 1.5v of amplitiude
        if(amp > auto_freqsweep_maxamp && amp > 1.5) {
            auto_freqsweep_maxamp = amp;
            auto_freqsweep_freq_at_maxamp = freq;
            // Set validity flag to false, pending validations
            auto_freqsweep_maxamp_valid = false;
        } else if(amp < auto_freqsweep_amp_buffer.at(auto_freqsweep_amp_buffer.size()-2)) {
            // The new value decrements, so we possibily have reached the peak
            // Ensure that all points in auto_freqsweep_amp_buffer thus far have positive derivaties
            // If it does, then we can move on to DECREMENT MODE, where we ensure that the values following the peak are indeed decresing
            bool has_negative_derivaties = false;
            for(int i=1; i<(auto_freqsweep_amp_buffer.size() - 1); i++) { //start at 1 to avoid assertion
                //Are the values decreasing? They shouldn't be.
                if(auto_freqsweep_amp_buffer.at(i) < auto_freqsweep_amp_buffer.at(i-1)) {
                    has_negative_derivaties = true;
                }
            }
            if(!has_negative_derivaties) {
                auto_freqsweep_state++;
            }
        }
        break;
    case 5:
        // DECREMENT MODE
        // Process the current data
        auto_freqsweep_decr_count++;
        auto_freqsweep_amp_buffer.pop_front();
        auto_freqsweep_amp_buffer.push_back(amp);

        if(amp > auto_freqsweep_amp_buffer.at(auto_freqsweep_amp_buffer.size()-2)) {
            // Nope it's bigger
            // Erase, Put data into buffer, then Go back to INCREMENT mode
            auto_freqsweep_decr_count = 0;
            auto_freqsweep_state--;
        }
        // Check on all the data received
        // At the fifth data point, check if all values have negative slopes
        if(auto_freqsweep_decr_count == auto_freqsweep_amp_buffer.size()) {
            bool has_positive_derivaties = false;
            for(int i=1; i<(auto_freqsweep_amp_buffer.size() - 1); i++) { //start at 1 to avoid assertion
                //Are the values increasing? They shouldn't be.
                if(auto_freqsweep_amp_buffer.at(i) > auto_freqsweep_amp_buffer.at(i-1)) {
                    has_positive_derivaties = true;
                }
            }
            if(!has_positive_derivaties) {
                auto_freqsweep_maxamp_valid = true;
            }
        }
        break;
    case 6:
        // Check if max_amp is greater than 1.5. This is it.
        if(auto_freqsweep_maxamp_valid) {
            ui->currFreqVal->setValue(auto_freqsweep_freq_at_maxamp);
            commandQueue.push(new commandNode(setDDSSettings, auto_freqsweep_freq_at_maxamp));
        } else {
            qDebug() << "No max found";
            msgBox.setText("Could not automatically locate the resonant frequency =(");
            msgBox.exec();
        }
        auto_freqsweep_state = 0;
        break;
    }
}

// Frequency sweep
void MainWindow::on_sweepButton_clicked()
{
    //QApplication::setOverrideCursor(Qt::WaitCursor);
    quint16 step_size = ((quint16)ui->endFrequency->value()-(quint16)ui->startFrequency->value()) / (quint16)ui->numFreqPoints->value();
    mutex.lock();
    commandQueue.push(new commandNode(frequencySweep, (quint16)ui->numFreqPoints->value(), (quint16)ui->startFrequency->value(), (quint16)step_size));
    mutex.unlock();
}

void MainWindow::on_useCurrFreqVal_clicked()
{
    ui->spnFrequencyVoltage->setValue(ui->currFreqVal->value());
}

void MainWindow::on_pushButton_6_clicked()
{
//    mutex.lock();
//    for(int i =0; i< 100; i++){
    row = 0;
    commandQueue.push(new commandNode(startScan));

    commandQueue.push(new commandNode(getScanData));
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
        commandNode *_node = new commandNode(writeDAC, ui->dacNumber->value(), valueToWrite);
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
    commandNode *_node = new commandNode(readDAC, (qint8)ui->dacNumber->value());
    commandQueue.push(_node);

    _node = new commandNode(readADC, (qint8)ui->adcNumber->value());
    commandQueue.push(_node);
}

void MainWindow::on_freqAutoScale_clicked()
{
    freqPlot.setAxisAutoScale(QwtPlot::yLeft);
    freqPlot.replot();
    phasePlot.setAxisAutoScale(QwtPlot::yLeft);
    phasePlot.replot();
}

void MainWindow::on_spnFrequencyVoltage_2_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(memsSetAmplitude, arg1));//afm.memsSetAmplitude(arg1);
    mutex.unlock();
}

void MainWindow::on_buttonAutoApproachMCU_clicked(bool checked)
{
    mutex.lock();
    if (!isAutoApproach) {
        commandQueue.push(new commandNode(afmAutoApproach, (double)ui->spnPidSetpoint->value()));
        isAutoApproach = true;
    } else {
        commandQueue.push(new commandNode(stageAbortContinuous));//afm.autoApproach();
        isAutoApproach = false;
    }
    mutex.unlock();
}



//todo fix me
void MainWindow::on_setMaxDACValuesButton_clicked()
{
    updateStatusBar("Setting DAC Values...");
    commandQueue.push(new commandNode(setDacMaxValues, DAC_Y1, (double)ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_Y2, (double)ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_X1, (double)ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_X2, (double)ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_ZOFFSET_COARSE, (double)ui->ZfineSpinBox->value()));
    commandQueue.push(new commandNode(setDacMaxValues, DAC_ZOFFSET_FINE, (double)ui->ZcoarseSpinBox->value()));

    ui->label_10->setVisible(true);
    ui->label_11->setVisible(true);
    ui->label_12->setVisible(true);
}



void MainWindow::on_calibrateButton_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    double _maxLat;

    //double _maxZ;

    _maxLat = ui->latSpinBox->value();
    //_maxZ = ui->ZcoarseSpinBox->value();

    if (_maxLat != 0)
        commandQueue.push(new commandNode(deviceCalibration, _maxLat));

    /*IF SCAN PARAMETERS HAVE BEEN SET
     *  how can we check this?*/
}

void MainWindow::updateStatusBar(QString _string)
{
    this->statusBar()->showMessage(_string);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{   
    if (index == 1)
        ui->toolBar->setEnabled(true);
    else
        ui->toolBar->setEnabled(false);
}

void MainWindow::pickPlotStyle(QAction *action)
{
    if (!action)
        return;

    if (action == ui->polygon)
        scanPlot.setPlotStyle(FILLED);
    else if (action == ui->filledmesh)
        scanPlot.setPlotStyle(FILLEDMESH);
    else if (action == ui->wireframe)
        scanPlot.setPlotStyle(WIREFRAME);
    else if (action == ui->hiddenline)
        scanPlot.setPlotStyle(HIDDENLINE);
    else if (action == ui->pointstyle)
        scanPlot.setPlotStyle(Qwt3D::POINTS);
    else
        scanPlot.setPlotStyle(NOPLOT);
    scanPlot.updateData();
    scanPlot.updateGL();
}

void MainWindow::setLeftGrid(bool b)
{
    setGrid(Qwt3D::LEFT, b);
}
void MainWindow::setRightGrid(bool b)
{
    setGrid(Qwt3D::RIGHT, b);
}
void MainWindow::setCeilGrid(bool b)
{
    setGrid(Qwt3D::CEIL, b);
}
void MainWindow::setFloorGrid(bool b)
{
    setGrid(Qwt3D::FLOOR, b);
}
void MainWindow::setFrontGrid(bool b)
{
    setGrid(Qwt3D::FRONT, b);
}
void MainWindow::setBackGrid(bool b)
{
    setGrid(Qwt3D::BACK, b);
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

    scanPlot.coordinates()->setGridLines(sum != Qwt3D::NOSIDEGRID, sum != Qwt3D::NOSIDEGRID, sum);
    scanPlot.updateGL();
}

void MainWindow::pickCoordSystem(QAction *action)
{
    if (!action)
        return;

    //activeCoordSystem = action;

    scanPlot.setTitle("QwtPlot3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");

    if (!scanPlot.hasData()) {
        double l = 0.6;
        scanPlot.createCoordinateSystem(Triple(-l, -l, -l), Triple(l, l, l));
        for (unsigned i = 0; i != scanPlot.coordinates()->axes.size(); ++i) {
            scanPlot.coordinates()->axes[i].setMajors(4);
            scanPlot.coordinates()->axes[i].setMinors(5);
        }
    }

    if (action == ui->Box || action == ui->Frame) {
        if (action == ui->Box)
            scanPlot.setCoordinateStyle(BOX);
        if (action == ui->Frame)
            scanPlot.setCoordinateStyle(FRAME);
        //grids->setEnabled(true);
    } else if (action == ui->None) {
        scanPlot.setTitle("QwtPlot3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");
        scanPlot.setCoordinateStyle(NOCOORD);
        //grids->setEnabled(false);
    }
}

void MainWindow::pickFloorStyle(QAction *action)
{
    if (!action)
        return;

    if (action == ui->floordata)
        scanPlot.setFloorStyle(FLOORDATA);
    else if (action == ui->flooriso)
        scanPlot.setFloorStyle(FLOORISO);
    else
        scanPlot.setFloorStyle(NOFLOOR);

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
    //commandQueue.push(new commandNode(stageSetPulseWidth,(qint8)));
    if (approachTimer->isActive()) {
        approachTimer->stop();
        approachTimer->start(5);
    } else {
        approachTimer->start(5);
    }
}

void MainWindow::on_continuousButton_released()
{
    if (approachTimer)
        approachTimer->stop();
}

void MainWindow::on_gwyddionButton_clicked()
{
    QProcess *process = new QProcess();
    QString program = "C:\\Program Files (x86)\\Gwyddion\\bin\\gwyddion.exe";

    process->startDetached(program, QStringList());
}

void MainWindow::afmWorkerError()
{
    //if(!msgBox.isEnabled()) {
    msgBox.setText("AFM Worker found an error and ran off with him");
    msgBox.exec();
    //}
}

void MainWindow::serialError()
{
    //if(!msgBox.isEnabled()) {
    msgBox.setText("There was an error communicating with the Serial Port.");
    msgBox.exec();
    //}
}

void MainWindow::setDDSFrequency(const QPointF& p)
{
    double frequency = p.x();

    ui->currFreqVal->setValue(frequency);
    commandQueue.push(new commandNode(setDDSSettings, frequency));
}

void MainWindow::on_spnBoxFineZRange_valueChanged(int arg1)
{
    commandQueue.push(new commandNode(memsSetFrequency, (double)arg1));
}

void MainWindow::on_spnBoxCoarseZ_valueChanged(double arg1)
{
    commandQueue.push(new commandNode(writeDAC, (double)DAC_ZOFFSET_COARSE, (double)arg1));
}

void MainWindow::on_spnBoxFineZ_valueChanged(double arg1)
{
    commandQueue.push(new commandNode(writeDAC, (double)DAC_ZOFFSET_FINE, (double)arg1));
}

void MainWindow::on_btnSetScanParameters_clicked()
{
    double numlines = ui->cmbScanNumLines->currentText().toDouble();
    double numpts = ui->cmbScanNumPoints->currentText().toDouble();

    commandQueue.push(new commandNode(scanParameters, ui->spnScanVmin->value(), ui->spnScanVmin2->value(), ui->spnScanVmax->value(), numpts, numlines));
}

void MainWindow::on_spnFrequencyVoltage_valueChanged(double arg1)
{
}

void MainWindow::updatePlot(double _signal, int _plot)
{
//    if (_plot == 1) {
//        approachPlot.update(time, _signal, currTab == Approach ? true : false);
//        time++;
//    }
}

void MainWindow::on_btnForceCurve_clicked()
{
    commandQueue.push(new commandNode(ForceCurve));
}

void MainWindow::on_btn_pid_on_clicked()
{
    qDebug() << "pid on clicked";
    //mutex.lock();
//    commandQueue.push(new commandNode(pidSetP,ui->spnPidValueP->value()));
//    commandQueue.push(new commandNode(pidSetI,ui->spnPidValueI->value()));
//    commandQueue.push(new commandNode(pidSetD,ui->spnPidValueD->value()));
//    commandQueue.push(new commandNode(pidSetPoint,ui->spnPidSetpoint->value()));
    commandQueue.push(new commandNode(pidEnable));//afm.pidEnable();
    //mutex.unlock();
}

void MainWindow::on_btn_pid_off_clicked()
{
    qDebug() << "pid off clicked";
    //mutex.lock();
    commandQueue.push(new commandNode(pidDisable));//afm.pidDisable();
    //mutex.unlock();
}

void MainWindow::on_btn_stepmot_user_up_2_pressed()
{
    qDebug() << "on_btn_stepmot_user_up_2_pressed";
}

void MainWindow::on_btn_stepmot_user_up_2_released()
{
    qDebug() << "on_btn_stepmot_user_up_2_released";
}

void MainWindow::on_sld_stepmot_user_spd_valueChanged(int value)
{
    ui->lbl_stepmot_user_spd->setText(QString::number(value));
}

void MainWindow::stepmot_user_control_callback(){
    stepmot_user_control(stepmot_callback_operation, false);
}

void MainWindow::stepmot_user_control(UserStepMotOp operation, bool isStep)
{
    // Stop autoapproach always
    autoapproach_state = APPR_DISABLED;

    if(operation==STOP) {
        //Stop and sleep motor at once
        mutex.lock();
        commandQueue.push(new commandNode(stepMotContStop));
        commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_SLEEP)));
        //Reset speed so we dont have any surprises
        commandQueue.push(new commandNode(stepMotSetSpeed, (double)UserSpd_to_Speed[0]));
        commandQueue.push(new commandNode(stepMotSetMicrostep, (qint8)UserSpd_to_Microsteps[0]));
        mutex.unlock();
        return;
    } else {
        // Using lookup table for computing the speed
        // Set Speed and Microsteps
        commandQueue.push(new commandNode(stepMotSetSpeed, (double)UserSpd_to_Speed[ui->sld_stepmot_user_spd->value()]));
        commandQueue.push(new commandNode(stepMotSetMicrostep, (qint8)UserSpd_to_Microsteps[ui->sld_stepmot_user_spd->value()]));
        //Set direction
        if(operation==APPR) {
            commandQueue.push(new commandNode(stepMotSetDir, qint8(MOT_FWD)));
        } else if (operation==RETR) {
            commandQueue.push(new commandNode(stepMotSetDir, qint8(MOT_BACK)));
        }
        //Wake motor
        commandQueue.push(new commandNode(stepMotSetState, qint8(MOT_WAKE)));
        if(isStep) {
            //Move a step only, and then callback. No need to sleep here.
            commandQueue.push(new commandNode(stepMotSingleStep));
            // Assign callback
            stepmot_callback_operation = operation;
            // single shot. 200ms is just a tad longer than an avg mouseclick (~120ms).
            QTimer::singleShot(200, this, SLOT(stepmot_user_control_callback()));
        } else {
            //Check if the buttons are still pressed?
            //Then Start in cont mode
            if(operation==APPR && ui->btn_stepmot_user_up->isDown()) {
                commandQueue.push(new commandNode(stepMotContGo));
            } else if (operation==RETR && ui->btn_stepmot_user_down->isDown()) {
                commandQueue.push(new commandNode(stepMotContGo));
            }
        }
    }
    return;
}

void MainWindow::on_btn_stepmot_user_up_pressed()
{
    stepmot_user_control(APPR, true);
}

void MainWindow::on_btn_stepmot_user_up_released()
{
    stepmot_user_control(STOP, true);
}

void MainWindow::on_btn_stepmot_user_down_pressed()
{
    stepmot_user_control(RETR, true);
}

void MainWindow::on_btn_stepmot_user_down_released()
{
    stepmot_user_control(STOP, true);
}

void MainWindow::on_btn_auto_freqsweep_clicked()
{
    auto_freqsweep_state = 1;
    auto_freqsweep(-5,-5);
}

void MainWindow::on_btn_setDACTable_clicked()
{
    set_DAC_table_state_machine(0);
}

void MainWindow::on_btn_siggen_clicked()
{
    quint8 ratioEnum = ui->cmb_scanRatio_old->value();
    double numlines = ui->cmbScanNumLines->currentText().toDouble();
    double numpts = ui->cmbScanNumPoints->currentText().toDouble();

    delete scan_result;
    scan_result = new afm_data(numpts, numlines, ratioEnum);

    commandQueue.push(new commandNode(SigGen, ratioEnum, numpts, numlines));
}

void MainWindow::on_btn_scan_start_clicked()
{
    commandQueue.push(new commandNode(startScan_4act));
    ui->label_scan_status->setText("Scanning...");
}

void MainWindow::on_btn_scan_next_clicked()
{
    commandQueue.push(new commandNode(scanStep_4act));
}

void MainWindow::on_btn_re_init_clicked()
{
    init_DAC_PGA();
}

/**
 * @fn MainWindow::send_DAC_table_state_machine
 * @brief Send the DAC table in blocks
 * @param type If type is 1, then this function is called from a callback, and it will continue next block of DAC table
 *             If type is 0, then this function is invoked by user or some other thing, and it will start over
 */

void MainWindow::set_DAC_table_state_machine(int type)
{
    if(type==0) {
        dac_table_current_block=0;
    }

    // Send the DACTable in batches of 256 points, each point is 2 bytes
    // so total 512 bytes per message

    int num_msg = 4096 / AFM_DACTABLE_BLK_SIZE;

    if(dac_table_current_block == num_msg) {
        //Stop and reset
        qDebug() << "dac_table_current_block at max value, msg #" << dac_table_current_block;
        //If we are in the appropriate scanning state, callback to the scan_state_machine
        if(scan_state == 3) {
            ui->progbar_scan->setValue((ui->progbar_scan->value())+1);
            QTimer::singleShot(1, this, SLOT(scan_state_machine()));
        }
    } else {
        commandQueue.push(new commandNode(setDACTable, qint8(dac_table_current_block)));
        qDebug() << "ROLL DAC Table msg #" << dac_table_current_block;
        dac_table_current_block++;
        //The dequeue receiver should call this function again
        //UI stuff
        if(scan_state == 3) {
            ui->progbar_scan->setValue((ui->progbar_scan->value())+1);
        }
    }

}

/**
 * @brief MainWindow::scan_state_machine This is the main controls for scanning. Note that callbacks for some of the states might reside in dequeuereturnbuffer
 */

void MainWindow::scan_state_machine(){
    qDebug() << "Scan State Machine i=" << scan_state;
    switch(scan_state) {
    case 0: //
        /* ENTRY: User button click or any other interrupt for scan
         * EXIT: N/A
         * Disabled state, safe to call at any time.
         * Stops the scan.
         */
        ui->progbar_scan->setValue(0);
        ui->label_scan_status->setText("Stopped");
        ui->label_scan_param_light->setPixmap((QString)":/icons/icons/1413858973_ballred-24.png");
        //enable UI elements
        //No need to inf
        break;
    case SCAN_INIT:
        /* ENTRY: User button click
         * EXIT: Command enable PID to uC
         * Initialize
         * Set PID params and turn on PID
         */

        ui->progbar_scan->setValue(3);
        ui->label_scan_status->setText("Setting PGA");
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_DDS_AMPLITUDE, ui->spn_dds_amplitude->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_LEVELING, ui->spn_leveling->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZCOARSE, ui->spn_zcoarse->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZFINE, ui->spn_zfine->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_X1, ui->spn_freq_x1->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y1, ui->spn_freq_y1->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_X2, ui->spn_freq_x2->value()));
        commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y2, ui->spn_freq_y2->value()));
        ui->label_scan_status->setText("Setting PID");
        commandQueue.push(new commandNode(pidSetP,ui->spnPidValueP->value()));
        commandQueue.push(new commandNode(pidSetI,ui->spnPidValueI->value()));
        commandQueue.push(new commandNode(pidSetD,ui->spnPidValueD->value()));
        commandQueue.push(new commandNode(pidSetPoint,ui->spnPidSetpoint->value()));
        commandQueue.push(new commandNode(pidEnable));//afm.pidEnable();
        scan_state=SET_DACTABLE;
        break;
    case SET_DACTABLE:
        /* ENTRY: PIDENABLE callback in dequeueReturnBuffer
         * EXIT: Begin command sequence for DAC Table
         * Send DAC Table
         */
        ui->progbar_scan->setValue(5);
        ui->label_scan_status->setText("Preparing AFM chip");
        set_DAC_table_state_machine(0);
        scan_state=SET_SIGGEN;
        break;
    case SET_SIGGEN:
    {
        /* ENTRY: DAC Table loading complete, via afm_callback
         * EXIT: Send command "Q" to enter scan mode in uC
         * SIGGEN and BEGIN_SCAN,  create new afm_data object
         */
        quint8 ratioEnum = ui->cmb_scanRatio_old->value();
        double numlines = ui->cmbScanNumLines->currentText().toDouble();
        double numpts = ui->cmbScanNumPoints->currentText().toDouble();
        commandQueue.push(new commandNode(SigGen, ratioEnum, numpts, numlines));
        commandQueue.push(new commandNode(startScan_4act));
        delete scan_result;
        scan_result = new afm_data(numpts, numlines, ratioEnum);
        ui->label_scan_status->setText("Scanning...");
        scan_state=SCAN_DATA_RECV;
        //DEBUG TEMP ONLY!!!!!!
        approachPlot.clearData();
        approachPlot2.clearData();
        approachPlot.replot();
        approachPlot.replot();
    }
    break;
    case SCAN_DATA_RECV:
    {
        /* ENTRY: Callback from AFM_START_SCAN_4ACT acknowledge (STARTSCAN_4ACT), and recursive call from SCANDATA in dequeueReturnBuffer
         * EXIT: When all data points are received, single-shot
         * Saves data, plot graph, keeps track of where we are, and requests the next data block
         */
        if(scan_result->is_data_full() == false && scan_result->has_error() == false) {
            commandQueue.push(new commandNode(scanStep_4act));
        } else if (scan_result->has_error() == true) {
            scan_state = SCAN_DISABLED;
            ui->label_scan_status->setText("Error while scanning");
            QTimer::singleShot(5000, this, SLOT(scan_state_machine()));
        } else {
            scan_state=SCAN_DONE;
            QTimer::singleShot(1, this, SLOT(scan_state_machine()));
        }
        //Update the UI
        // proof-of-concept only. will need to be tweaked.
        int scan_progress_pct = scan_result->get_scan_progress();
        ui->progbar_scan->setValue(scan_progress_pct);
    }
    break;
    case SCAN_DONE:
        /* ENTRY: When all data points are received
         * EXIT: Reset to disabled state
         * Clean-up activitie, if any.
         */
        //UPDATE UI
        //Clean Up
        scan_state = SCAN_DISABLED;
        QTimer::singleShot(1, this, SLOT(scan_state_machine()));
        break;
    }
}

void MainWindow::on_btn_scan_begin_clicked()
{
    scan_state = SCAN_INIT; //Initial state
    //Launch the scan_state_machine
    QTimer::singleShot(1, this, SLOT(scan_state_machine()));
}

void MainWindow::on_btn_scan_stop_clicked()
{
    qDebug() << "ABORT Inside Scan State Machine i=" << scan_state;
    scan_state = SCAN_DISABLED;
    QTimer::singleShot(1, this, SLOT(scan_state_machine()));
}

void MainWindow::on_pushButton_clicked()
{
    scan_result->print_all();
}

void MainWindow::on_btn_print_offset_clicked()
{
    scan_result->print_amp();
}

void MainWindow::on_btn_set_pga_clicked()
{
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_DDS_AMPLITUDE, ui->spn_dds_amplitude->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_LEVELING, ui->spn_leveling->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZCOARSE, ui->spn_zcoarse->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_ZFINE, ui->spn_zfine->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_X1, ui->spn_freq_x1->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y1, ui->spn_freq_y1->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_X2, ui->spn_freq_x2->value()));
    commandQueue.push(new commandNode(setPGA, (qint8)PGA_Y2, ui->spn_freq_y2->value()));
}

void MainWindow::on_spnPidSetpoint_2_valueChanged(double arg1)
{
    ui->spnPidSetpoint->setValue(arg1);
}

void MainWindow::on_btn_appr_plot_autoscale_clicked()
{
    approachPlot.setAutoScale(true);
    approachPlot2.setAutoScale(true);
    approachPlot.replot();
    approachPlot.replot();
}

void MainWindow::on_btn_appr_plot_clear_clicked()
{
    approachPlot.clearData();
    approachPlot2.clearData();
    approachPlot.replot();
    approachPlot.replot();
}

void MainWindow::on_btn_autoappr_mcu_start_clicked()
{
    commandQueue.push(new commandNode(aappr_begin, (double)ui->spnPidSetpoint_2->value()));
    isAutoApproach = true;
}

void MainWindow::on_btn_autoappr_mcu_stop_clicked()
{
    commandQueue.push(new commandNode(aappr_stop));
    isAutoApproach = false;
}

void MainWindow::on_btn_autoappr_mcu_start_2_clicked()
{
    commandQueue.push(new commandNode(aappr_begin, (double)ui->spnPidSetpoint_2->value()));
}

void MainWindow::on_pushButton_3_clicked()
{
     commandQueue.push(new commandNode(aappr_sta));
}

void MainWindow::on_btn_save_gxyzf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Gwyddion Simple XYZ (*.gxyzf);;Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
//            QTextStream stream(&file);
//            stream << ui->textEdit->toPlainText();
//            stream.flush();
            file.write(scan_result->save_gxyzf());
            file.close();
        }
    }
}

void MainWindow::on_btn_save_txt_1_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
//            QTextStream stream(&file);
//            stream << ui->textEdit->toPlainText();
//            stream.flush();
            file.write(scan_result->save_txt(1));
            file.close();
        }
    }
}

void MainWindow::on_btn_save_txt_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            file.write(scan_result->save_txt(2));
            file.close();
        }
    }
}

void MainWindow::on_spn_test_dac_coarse_z_valueChanged(double arg1)
{
    commandNode *_node = new commandNode(writeDAC, DAC_ZOFFSET_COARSE, arg1);
    commandQueue.push(_node);
}

void MainWindow::on_spn_test_dac_fine_z_valueChanged(double arg1)
{
    commandNode *_node = new commandNode(writeDAC, DAC_ZOFFSET_FINE, arg1);
    commandQueue.push(_node);
}
