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

    /*Push event to get ports from the serialworker*/
    //commandQueue.push(new commandNode(getPorts,(double)0));
    refreshPortsList();

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
    connect(approachTimer, SIGNAL(timeout()), this, SLOT(approachTimerUp()));

    /*Intialize Graphs*/
    CreateGraphs();

    /* Initialize offset, amplitude, and bridge voltage with the value we have set in UI*/
    //on_spnFrequencyVoltage_2_valueChanged(ui->spnFrequencyVoltage_2->value());      // set amplitude
    //on_spnBridgeVoltage_valueChanged(ui->spnBridgeVoltage->value());                // set bridge voltage
    //on_spnOffsetVoltage_valueChanged(ui->spnOffsetVoltage->value()); // set offset

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
                               QPair<double, double>(3800, 4800), QPair<double, double>(0, 0.12), QColor("Red"),
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
                    QPair<double, double>(3800, 4800), QPair<double, double>(0, 0.12), QColor("Blue"),
                    false, true);

    phasePlot.SetPlot(fields, ui->freqWidget);
    ui->gridLayout_17->addWidget(&phasePlot, 2, 0);
    phasePlot.enableAxis(QwtPlot::xBottom);
    phasePlot.enableAxis(QwtPlot::yLeft);
    //phasePlot.resize(500, 300);
    phasePlot.show();

    // add approach plot
    fields = MyPlot::PlotFields("Bridge Signal", true, "Time", "Bridge Voltage (V)", \
                    QPair<double, double>(0, 300), QPair<double, double>(0, 1), QColor("Red"),
                    false);
    approachPlot.SetPlot(fields, ui->approachWidget);
    ui->gridLayout_24->setSpacing(0);
    ui->gridLayout_24->addWidget(&approachPlot, 1, 0);
    approachPlot.resize(500, 300);
    approachPlot.show();



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
 * Need to initialize the DAC limits
 *
 *
 *
 */
void MainWindow::SetMaxDACValues()
{
    commandQueue.push(new commandNode(setDacValues, (double)DAC_BFRD1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_BFRD2, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_BR2, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_ZAMP, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_BR1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_BFRD3, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_ZOFFSET_FINE, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_Y1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_ZOFFSET_COARSE, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_Y2, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_X1, AFM_DAC_MAX_VOLTAGE));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_X2, AFM_DAC_MAX_VOLTAGE));
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
        _buffer = returnQueue.front();
        switch (_buffer->getReturnType()) {
        case DACBFRD1:
            ui->dacValue->setValue(_buffer->getFData());
            bfrd1 = _buffer->getFData();
            break;
        case DACBFRD2:
            bfrd2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACBR2:
            br2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACZAMP:
            zAmp = _buffer->getFData();
            break;
        case DACBR1:
            br1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACBFRD3:
            bfrd3 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACZOFFSETFINE:
            zOffsetFine = _buffer->getFData();
            break;
        case DACY1:
            y1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACZOFFSETCOARSE:
            zOffsetCoarse = _buffer->getFData();
            break;
        case DACY2:
            y2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACX1:
            x1 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case DACX2:
            x2 = _buffer->getFData();
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case ADCZOFFSET:
            bfrd3 = _buffer->getFData();
            if (useBridgeSignalAsSetpoint) {
                //ui->spnPidSetpoint->setValue(double(bfrd3));
                //ui->currPIDSetpoint->setValue(double(bfrd3));
            }
            break;
        case ADCPHASE:
            bfrd3 = _buffer->getFData();
            if (useBridgeSignalAsSetpoint) {
                //ui->spnPidSetpoint->setValue(double(bfrd3));
                //ui->currPIDSetpoint->setValue(double(bfrd3));
            }
            break;
        case READSIGNALPHASEOFFSET:
            offset = _buffer->getdoffset();
            phase = _buffer->getdphase();
            signal = _buffer->getdsignal();
            break;
        case AFMADCAMPLITUDEID:
            zAmp = _buffer->getFData();
            break;
        case AFMDACOFFSETID:
            zOffsetFine = _buffer->getFData();
            break;
        case DAC:
            ui->dacValue->setValue(_buffer->getFData());
            break;
        case ADC:
            ui->adcValue->setValue(_buffer->getFData());
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
        case SCANDATA:
            //update GRAPH

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

            break;
        }

        if (currTab == 3) {
//            approachPlot.update(time, signal, currTab == Approach ? true: false);
//            ui->currOffsetValue->setValue(signal);
//            time++;
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

void MainWindow::on_btnPidToggle_toggled(bool checked)
{
    if (checked) {
        //mutex.lock();
        commandQueue.push(new commandNode(pidEnable));//afm.pidEnable();
//        commandQueue.push(new commandNode(pidSetP,ui->spnPidValueP->value()));
//        commandQueue.push(new commandNode(pidSetI,ui->spnPidValueI->value()));
//        commandQueue.push(new commandNode(pidSetD,ui->spnPidValueD->value()));
//        commandQueue.push(new commandNode(pidSetPoint,ui->spnPidSetpoint->value()));
        //mutex.unlock();
    } else {
        //mutex.lock();
        commandQueue.push(new commandNode(pidDisable));//afm.pidDisable();
        //mutex.unlock();
    }
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

void MainWindow::on_sldAmplitudeVoltage_3_valueChanged(int value)
{
    ui->lblAmplitude->setText(QString::number(value));
    //mutex.lock();
    commandQueue.push(new commandNode(stageSetPulseWidth, (qint8)value));//afm.stageSetPulseWidth(value);
    //mutex.unlock();
}

void MainWindow::on_buttonCurrValuePidSetpoint_clicked(bool checked)
{
    useBridgeSignalAsSetpoint = checked;
}

// Button for autoapproach
// TODO: verify autoapproach
void MainWindow::on_buttonAutoApproachClient_clicked(bool checked)
{
    if (checked) {
        mutex.lock();
        autoApproachComparison = adc5; // comparison value before starting motor
        ui->comparisonValue->setValue(adc5);
        mutex.unlock();


        mutex.lock();
        commandQueue.push(new commandNode(stageSetPulseWidth, (qint8)19));
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
        commandQueue.push(new commandNode(stageSetPulseWidth, (qint8)ui->sldAmplitudeVoltage_3->value()));

        //afm.stageSetPulseWidth(ui->sldAmplitudeVoltage_3->value());
/*        ui->retreatButton->isChecked() == true ? afm.stageSetDirBackward() : \
 *                                               afm.stageSetDirForward();*/
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

void MainWindow::CreateFreqSweepGraph(QVector<double>	amplitudeData,
                      QVector<double>	phaseData,
                      int		bytesRead)
{
    ui->freqProgressLabel->setText("TRUE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : Green; }");

    freqPlot.clearData();
    phasePlot.clearData();

    double freqVal;
    double ampVal;
    double phaseVal;
    double scale = (25000000.0 / 16777216.0);
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
            freqVal = ((ui->startFrequency->value() + i * ui->stepSize->value()) * scale);
            phaseVal = phaseData.at(i);
            ampVal = amplitudeData.at(i);
            freqPlot.update(freqVal, ampVal, false); // add points to graph but don't replot
            phasePlot.update(freqVal, phaseVal, false);
        }
        phasePlot.replot();
        freqPlot.replot(); // show the frequency sweep
    }

    //frequencyData.clear();
    phaseData.clear();
    amplitudeData.clear();
    ui->freqProgressLabel->setText("FALSE");
    ui->freqProgressLabel->setStyleSheet("QLabel { color : red; }");

    QApplication::restoreOverrideCursor();
}

// Frequency sweep
void MainWindow::on_sweepButton_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    mutex.lock();
    commandQueue.push(new commandNode(frequencySweep, (quint16)ui->numFreqPoints->value(), (quint16)ui->startFrequency->value(), (quint16)ui->stepSize->value()));
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

void MainWindow::on_freqAutoScale_clicked(bool checked)
{
    freqPlot.setAutoScale(checked);
    phasePlot.setAutoScale(checked);
    ui->freqAutoScale->setChecked(checked);
}

void MainWindow::on_spnFrequencyVoltage_2_valueChanged(double arg1)
{
    mutex.lock();
    commandQueue.push(new commandNode(memsSetAmplitude, arg1));//afm.memsSetAmplitude(arg1);
    mutex.unlock();
}

void MainWindow::on_buttonSendSweep_clicked()
{
    //mutex.lock();
    commandQueue.push(new commandNode(setDDSSettings, (qint16)ui->numFreqPoints->value(), (qint16)ui->currFreqVal->value(), (qint16)ui->stepSize->value()));//afm.setDDSSettings(ui->numFreqPoints->value(), ui->currFreqVal->value(), ui->stepSize->value());
    // mutex.unlock();
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




void MainWindow::on_setMaxDACValuesButton_clicked()
{
    updateStatusBar("Setting DAC Values...");
    commandQueue.push(new commandNode(setDacValues, (double)DAC_Y1, ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_Y2, ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_X1, ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_X2, ui->latSpinBox->value()));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_ZOFFSET_COARSE, ui->ZfineSpinBox->value()));
    commandQueue.push(new commandNode(setDacValues, (double)DAC_ZOFFSET_FINE, ui->ZcoarseSpinBox->value()));

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
    msgBox.setText("AFM Worker left!");
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
    double scale = (25000000.0 / 16777216.0);
    commandQueue.push(new commandNode(setDDSSettings, frequency / scale));
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
    if (_plot == 1) {
        approachPlot.update(time, _signal, currTab == Approach ? true : false);
        ui->currOffsetValue->setValue(_signal);
        time++;
    }
}

void MainWindow::on_btnForceCurve_clicked()
{
    commandQueue.push(new commandNode(ForceCurve));
}
