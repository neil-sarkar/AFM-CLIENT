/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_All;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionMinimize;
    QAction *actionMaximize;
    QAction *openFile;
    QAction *openMeshFile;
    QAction *animation;
    QAction *Exit;
    QAction *Box;
    QAction *Frame;
    QAction *None;
    QAction *front;
    QAction *back;
    QAction *right;
    QAction *left;
    QAction *ceil;
    QAction *floor;
    QAction *pointstyle;
    QAction *wireframe;
    QAction *hiddenline;
    QAction *polygon;
    QAction *filledmesh;
    QAction *nodata;
    QAction *floordata;
    QAction *flooriso;
    QAction *floornone;
    QAction *normals;
    QWidget *centralWidget;
    QFrame *sidebarFrame;
    QHBoxLayout *horizontalLayout_30;
    QWidget *widget_3;
    QGridLayout *_2;
    QPushButton *btn_scan_begin;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_4;
    QSpinBox *refreshSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblComPortSelection;
    QComboBox *cboComPortSelection;
    QPushButton *btnSetScanParameters;
    QGroupBox *grpScanControl;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *lblScanVmaxV;
    QDoubleSpinBox *spnScanVmax;
    QHBoxLayout *horizontalLayout_12;
    QLabel *lblVminV;
    QDoubleSpinBox *spnScanVmin;
    QHBoxLayout *horizontalLayout_13;
    QLabel *lblScanVmin2;
    QDoubleSpinBox *spnScanVmin2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *lblScanNumLines;
    QComboBox *cmbScanNumLines;
    QHBoxLayout *horizontalLayout_15;
    QLabel *lblScanNumPoints;
    QComboBox *cmbScanNumPoints;
    QHBoxLayout *horizontalLayout_16;
    QLabel *lblScanDelay;
    QSpinBox *spnScanDelay;
    QLabel *label_scan_param_light;
    QLabel *label_40;
    QPushButton *btn_scan_stop;
    QProgressBar *progbar_scan;
    QLabel *label_scan_status;
    QTabWidget *tabWidget;
    QWidget *controlTab;
    QGridLayout *gridLayout_28;
    QHBoxLayout *horizontalLayout_33;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *grpMemsControl;
    QLabel *label_17;
    QGroupBox *grpPIDControl;
    QGridLayout *gridLayout_4;
    QLabel *lblPidValueP;
    QDoubleSpinBox *spnPidValueP;
    QDoubleSpinBox *spnPidValueI;
    QLabel *lblPidValueI;
    QLabel *lblPidValueD;
    QDoubleSpinBox *spnPidValueD;
    QPushButton *btn_pid_off;
    QDoubleSpinBox *spnPidSetpoint;
    QPushButton *btn_pid_on;
    QLabel *lblPidSetPoint;
    QLabel *label_pid_indicator;
    QGroupBox *grpPIDControl_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_13;
    QPushButton *calibrateButton;
    QLabel *label_30;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_19;
    QLabel *label_38;
    QLabel *label_36;
    QSpinBox *spn_freq_y1;
    QLabel *lblAmplitudeVoltage_2;
    QLabel *label_37;
    QLabel *label_35;
    QDoubleSpinBox *spn_leveling;
    QSpinBox *spn_freq_x1;
    QDoubleSpinBox *spnBridgeVoltage;
    QDoubleSpinBox *spnFrequencyVoltage;
    QDoubleSpinBox *spn_dds_amplitude;
    QLabel *fineZRangeLabel;
    QLabel *coarseZLabel;
    QLabel *lblFrequencyVoltage;
    QLabel *lblAmplitudeVoltage;
    QLabel *lblBridgeVoltage;
    QDoubleSpinBox *spn_zfine;
    QLabel *lblOffsetVoltage;
    QSpinBox *spnBoxFineZRange;
    QDoubleSpinBox *spn_zcoarse;
    QSpinBox *spn_freq_x2;
    QLabel *label_39;
    QSpinBox *spn_freq_y2;
    QPushButton *btn_set_pga;
    QGroupBox *grpPIDControl_3;
    QPushButton *btn_re_init;
    QWidget *scanTab;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_15;
    QGridLayout *gridLayout_9;
    QPushButton *btn_scan_start;
    QPushButton *btn_setDACTable;
    QLabel *label_34;
    QSpinBox *cmb_scanRatio_old;
    QPushButton *btn_scan_next;
    QPushButton *pushButton;
    QPushButton *btn_siggen;
    QPushButton *btn_print_offset;
    QPushButton *btn_save_gxyzf;
    QPushButton *btn_save_txt_1;
    QPushButton *btn_save_txt_2;
    QComboBox *cmb_scanRatio;
    QGridLayout *gridLayout_8;
    QTabWidget *tabScan;
    QWidget *tabScanForward;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_41;
    QGridLayout *gridLayout_11;
    QPushButton *gwyddionButton;
    QWidget *tabScanReverse;
    QWidget *graph_2d_scan;
    QWidget *tabFreqSweep;
    QGridLayout *gridLayout_18;
    QWidget *freqWidget;
    QGridLayout *gridLayout_23;
    QGridLayout *gridLayout_17;
    QHBoxLayout *horizontalLayout_31;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_2;
    QGridLayout *gridLayout_16;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_38;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_14;
    QCheckBox *checkBox;
    QVBoxLayout *verticalLayout_9;
    QPushButton *sweepButton;
    QPushButton *freqAutoScale;
    QPushButton *useCurrFreqVal;
    QPushButton *btn_auto_freqsweep;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_20;
    QSpinBox *numFreqPoints;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_19;
    QLabel *freqProgressLabel;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_23;
    QSpacerItem *horizontalSpacer_12;
    QSpinBox *startFrequency;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_22;
    QSpacerItem *horizontalSpacer_7;
    QSpinBox *endFrequency;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_14;
    QDoubleSpinBox *currFreqVal;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tabApproach;
    QGridLayout *gridLayout_25;
    QWidget *approachWidget;
    QGridLayout *gridLayout_29;
    QGridLayout *gridLayout_24;
    QHBoxLayout *horizontalLayout_34;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_13;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_32;
    QDoubleSpinBox *spn_test_dac_coarse_z;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_35;
    QDoubleSpinBox *spn_test_dac_fine_z;
    QLabel *label_24;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_25;
    QDoubleSpinBox *currOffsetValue;
    QGridLayout *gridLayout_5;
    QProgressBar *progbar_autoappr;
    QPushButton *btn_autoappr_go;
    QPushButton *btn_autoappr_stop;
    QLabel *label_appr_phase_2;
    QLabel *label_adczfine;
    QLabel *label_autoappr_meas;
    QLabel *label_29;
    QLabel *label_appr_phase;
    QLabel *label_41;
    QLabel *label_28;
    QDoubleSpinBox *spnPidSetpoint_2;
    QLabel *label_32;
    QLabel *lbl_autoappr_mcu_state;
    QPushButton *btn_autoappr_mcu_start;
    QPushButton *btn_autoappr_mcu_stop;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_24;
    QPushButton *btn_appr_plot_autoscale;
    QPushButton *btn_appr_plot_clear;
    QPushButton *buttonCurrValuePidSetpoint;
    QHBoxLayout *horizontalLayout_43;
    QHBoxLayout *horizontalLayout_44;
    QGridLayout *gridLayout_13;
    QPushButton *btn_stepmot_user_up;
    QLabel *label_31;
    QSlider *sld_stepmot_user_spd;
    QLabel *lbl_stepmot_user_spd;
    QPushButton *btn_stepmot_user_down;
    QSpacerItem *horizontalSpacer_3;
    QWidget *tabSignal;
    QGridLayout *gridLayout_26;
    QWidget *signalWidget;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_20;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QWidget *testTab;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *dacNumber;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_2;
    QSpinBox *adcNumber;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_3;
    QLabel *dacValue;
    QLabel *label_5;
    QLabel *adcValue;
    QPushButton *buttonReadIO;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_22;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_6;
    QDoubleSpinBox *valToWrite;
    QPushButton *buttonWriteToDAC;
    QVBoxLayout *verticalLayout;
    QLabel *label_15;
    QFrame *line;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_10;
    QDoubleSpinBox *latSpinBox;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_9;
    QDoubleSpinBox *ZcoarseSpinBox;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_8;
    QDoubleSpinBox *ZfineSpinBox;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_39;
    QPushButton *setMaxDACValuesButton;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_46;
    QRadioButton *radio_stepmot_fwd;
    QRadioButton *radio_stepmot_back;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_26;
    QComboBox *cbo_microstep;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_27;
    QLabel *lbl_stepmot_speed;
    QSlider *sld_stepmot_speed;
    QHBoxLayout *horizontalLayout_48;
    QPushButton *btn_stepmot_sleep;
    QPushButton *btn_stepmot_wake;
    QHBoxLayout *horizontalLayout_42;
    QPushButton *btn_stepmot_cont_go;
    QPushButton *btn_stepmot_cont_stop;
    QPushButton *btn_stepmot_singlestep;
    QPushButton *btnForceCurve;
    QWidget *gridLayoutWidget;
    QGridLayout *forcecurve_gridlayout;
    QWidget *forceWidget;
    QPushButton *pushButton_3;
    QPushButton *btn_autoappr_mcu_start_2;
    QLabel *label_33;
    QWidget *tabLog;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuWindow;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(910, 679);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/icspi.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_All = new QAction(MainWindow);
        actionSave_All->setObjectName(QStringLiteral("actionSave_All"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionMinimize = new QAction(MainWindow);
        actionMinimize->setObjectName(QStringLiteral("actionMinimize"));
        actionMaximize = new QAction(MainWindow);
        actionMaximize->setObjectName(QStringLiteral("actionMaximize"));
        openFile = new QAction(MainWindow);
        openFile->setObjectName(QStringLiteral("openFile"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/toolbar/icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFile->setIcon(icon1);
        openMeshFile = new QAction(MainWindow);
        openMeshFile->setObjectName(QStringLiteral("openMeshFile"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/toolbar/icons/filecell.png"), QSize(), QIcon::Normal, QIcon::Off);
        openMeshFile->setIcon(icon2);
        animation = new QAction(MainWindow);
        animation->setObjectName(QStringLiteral("animation"));
        animation->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/toolbar/icons/movie.png"), QSize(), QIcon::Normal, QIcon::Off);
        animation->setIcon(icon3);
        Exit = new QAction(MainWindow);
        Exit->setObjectName(QStringLiteral("Exit"));
        Box = new QAction(MainWindow);
        Box->setObjectName(QStringLiteral("Box"));
        Box->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/toolbar/icons/box.png"), QSize(), QIcon::Normal, QIcon::Off);
        Box->setIcon(icon4);
        Frame = new QAction(MainWindow);
        Frame->setObjectName(QStringLiteral("Frame"));
        Frame->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/toolbar/icons/frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        Frame->setIcon(icon5);
        None = new QAction(MainWindow);
        None->setObjectName(QStringLiteral("None"));
        None->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/toolbar/icons/none.png"), QSize(), QIcon::Normal, QIcon::Off);
        None->setIcon(icon6);
        front = new QAction(MainWindow);
        front->setObjectName(QStringLiteral("front"));
        front->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/toolbar/icons/gridfr.png"), QSize(), QIcon::Normal, QIcon::Off);
        front->setIcon(icon7);
        back = new QAction(MainWindow);
        back->setObjectName(QStringLiteral("back"));
        back->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/toolbar/icons/gridb.png"), QSize(), QIcon::Normal, QIcon::Off);
        back->setIcon(icon8);
        right = new QAction(MainWindow);
        right->setObjectName(QStringLiteral("right"));
        right->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/toolbar/icons/gridr.png"), QSize(), QIcon::Normal, QIcon::Off);
        right->setIcon(icon9);
        left = new QAction(MainWindow);
        left->setObjectName(QStringLiteral("left"));
        left->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/toolbar/icons/gridl.png"), QSize(), QIcon::Normal, QIcon::Off);
        left->setIcon(icon10);
        ceil = new QAction(MainWindow);
        ceil->setObjectName(QStringLiteral("ceil"));
        ceil->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/toolbar/icons/gridc.png"), QSize(), QIcon::Normal, QIcon::Off);
        ceil->setIcon(icon11);
        floor = new QAction(MainWindow);
        floor->setObjectName(QStringLiteral("floor"));
        floor->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/toolbar/icons/gridf.png"), QSize(), QIcon::Normal, QIcon::Off);
        floor->setIcon(icon12);
        pointstyle = new QAction(MainWindow);
        pointstyle->setObjectName(QStringLiteral("pointstyle"));
        pointstyle->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/toolbar/icons/scattered.png"), QSize(), QIcon::Normal, QIcon::Off);
        pointstyle->setIcon(icon13);
        wireframe = new QAction(MainWindow);
        wireframe->setObjectName(QStringLiteral("wireframe"));
        wireframe->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/toolbar/icons/wireframe.png"), QSize(), QIcon::Normal, QIcon::Off);
        wireframe->setIcon(icon14);
        hiddenline = new QAction(MainWindow);
        hiddenline->setObjectName(QStringLiteral("hiddenline"));
        hiddenline->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/toolbar/icons/hiddenline.png"), QSize(), QIcon::Normal, QIcon::Off);
        hiddenline->setIcon(icon15);
        polygon = new QAction(MainWindow);
        polygon->setObjectName(QStringLiteral("polygon"));
        polygon->setCheckable(true);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/toolbar/icons/polygon.png"), QSize(), QIcon::Normal, QIcon::Off);
        polygon->setIcon(icon16);
        filledmesh = new QAction(MainWindow);
        filledmesh->setObjectName(QStringLiteral("filledmesh"));
        filledmesh->setCheckable(true);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/toolbar/icons/filledmesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        filledmesh->setIcon(icon17);
        nodata = new QAction(MainWindow);
        nodata->setObjectName(QStringLiteral("nodata"));
        nodata->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/toolbar/icons/nodata.png"), QSize(), QIcon::Normal, QIcon::Off);
        nodata->setIcon(icon18);
        floordata = new QAction(MainWindow);
        floordata->setObjectName(QStringLiteral("floordata"));
        floordata->setCheckable(true);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/toolbar/icons/floordata.png"), QSize(), QIcon::Normal, QIcon::Off);
        floordata->setIcon(icon19);
        flooriso = new QAction(MainWindow);
        flooriso->setObjectName(QStringLiteral("flooriso"));
        flooriso->setCheckable(true);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/toolbar/icons/flooriso.png"), QSize(), QIcon::Normal, QIcon::Off);
        flooriso->setIcon(icon20);
        floornone = new QAction(MainWindow);
        floornone->setObjectName(QStringLiteral("floornone"));
        floornone->setCheckable(true);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/toolbar/icons/floorempty.png"), QSize(), QIcon::Normal, QIcon::Off);
        floornone->setIcon(icon21);
        normals = new QAction(MainWindow);
        normals->setObjectName(QStringLiteral("normals"));
        normals->setCheckable(true);
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/toolbar/icons/normals.png"), QSize(), QIcon::Normal, QIcon::Off);
        normals->setIcon(icon22);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        sidebarFrame = new QFrame(centralWidget);
        sidebarFrame->setObjectName(QStringLiteral("sidebarFrame"));
        sidebarFrame->setGeometry(QRect(0, 0, 200, 528));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sidebarFrame->sizePolicy().hasHeightForWidth());
        sidebarFrame->setSizePolicy(sizePolicy1);
        sidebarFrame->setMinimumSize(QSize(200, 528));
        sidebarFrame->setStyleSheet(QLatin1String("#sidebarFrame {\n"
"/*background: #7f8c8d;*/\n"
"background: #9E9E9E;\n"
"border: none;\n"
"border-right: 1px solid black;\n"
"border-bottom: 1px solid black;\n"
"\n"
"}"));
        sidebarFrame->setFrameShape(QFrame::StyledPanel);
        sidebarFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_30 = new QHBoxLayout(sidebarFrame);
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        widget_3 = new QWidget(sidebarFrame);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);
        _2 = new QGridLayout(widget_3);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QStringLiteral("_2"));
        btn_scan_begin = new QPushButton(widget_3);
        btn_scan_begin->setObjectName(QStringLiteral("btn_scan_begin"));
        btn_scan_begin->setStyleSheet(QStringLiteral(""));

        _2->addWidget(btn_scan_begin, 3, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetFixedSize);

        gridLayout_3->addLayout(verticalLayout_5, 4, 0, 1, 1);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_23->addWidget(label_4);

        refreshSpinBox = new QSpinBox(widget_3);
        refreshSpinBox->setObjectName(QStringLiteral("refreshSpinBox"));
        refreshSpinBox->setMaximum(10000);
        refreshSpinBox->setValue(100);

        horizontalLayout_23->addWidget(refreshSpinBox);


        gridLayout_3->addLayout(horizontalLayout_23, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lblComPortSelection = new QLabel(widget_3);
        lblComPortSelection->setObjectName(QStringLiteral("lblComPortSelection"));
        sizePolicy2.setHeightForWidth(lblComPortSelection->sizePolicy().hasHeightForWidth());
        lblComPortSelection->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(lblComPortSelection);

        cboComPortSelection = new QComboBox(widget_3);
        cboComPortSelection->setObjectName(QStringLiteral("cboComPortSelection"));
        cboComPortSelection->setEnabled(true);
        cboComPortSelection->setStyleSheet(QLatin1String("    QComboBox  {\n"
"        border: 1px solid gray;\n"
"        border-radius: 3px;\n"
"        padding: 1px 18px 1px 3px;\n"
"        min-width: 6em;\n"
"    }\n"
"     \n"
"    QComboBox:editable  {\n"
"        background: white;\n"
"    }\n"
"     \n"
"    QComboBox:!editable, QComboBox::drop-down:editable  {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    }\n"
"     \n"
"    /* QComboBox gets the \"on\" state when the popup is open */\n"
"    QComboBox:!editable:on, QComboBox::drop-down:editable:on  {\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                    stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,\n"
"                                    stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n"
"    }\n"
"     \n"
"    QComboBox:on  { /* shift the text when the popup opens */\n"
"        paddin"
                        "g-top: 3px;\n"
"        padding-left: 4px;\n"
"    }\n"
"     \n"
"    QComboBox::drop-down  {\n"
"        subcontrol-origin: padding;\n"
"        subcontrol-position: top right;\n"
"        width: 15px;\n"
"     \n"
"        border-left-width: 1px;\n"
"        border-left-color: darkgray;\n"
"        border-left-style: solid; /* just a single line */\n"
"        border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"        border-bottom-right-radius: 3px;\n"
"    }\n"
"     \n"
"    QComboBox::down-arrow  {\n"
"        image: url(C:/Qt/Tools/QtCreator/bin/qml/QtQuick/Controls/Styles/Base/images/arrow-down.png);\n"
"    }\n"
"     \n"
"    QComboBox::down-arrow:on  { /* shift the arrow when popup is open */\n"
"        top: 1px;\n"
"        left: 1px;\n"
"    }\n"
""));
        cboComPortSelection->setEditable(false);

        horizontalLayout_6->addWidget(cboComPortSelection);


        gridLayout_3->addLayout(horizontalLayout_6, 1, 0, 1, 1);


        _2->addLayout(gridLayout_3, 1, 0, 1, 1);

        btnSetScanParameters = new QPushButton(widget_3);
        btnSetScanParameters->setObjectName(QStringLiteral("btnSetScanParameters"));

        _2->addWidget(btnSetScanParameters, 9, 0, 1, 1);

        grpScanControl = new QGroupBox(widget_3);
        grpScanControl->setObjectName(QStringLiteral("grpScanControl"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(grpScanControl->sizePolicy().hasHeightForWidth());
        grpScanControl->setSizePolicy(sizePolicy3);
        grpScanControl->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"		font-size: 17px;\n"
"    }\n"
""));
        gridLayout_6 = new QGridLayout(grpScanControl);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        lblScanVmaxV = new QLabel(grpScanControl);
        lblScanVmaxV->setObjectName(QStringLiteral("lblScanVmaxV"));

        horizontalLayout_11->addWidget(lblScanVmaxV);

        spnScanVmax = new QDoubleSpinBox(grpScanControl);
        spnScanVmax->setObjectName(QStringLiteral("spnScanVmax"));
        spnScanVmax->setSingleStep(0.01);
        spnScanVmax->setValue(3);

        horizontalLayout_11->addWidget(spnScanVmax);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        lblVminV = new QLabel(grpScanControl);
        lblVminV->setObjectName(QStringLiteral("lblVminV"));

        horizontalLayout_12->addWidget(lblVminV);

        spnScanVmin = new QDoubleSpinBox(grpScanControl);
        spnScanVmin->setObjectName(QStringLiteral("spnScanVmin"));
        spnScanVmin->setSingleStep(0.01);
        spnScanVmin->setValue(0.5);

        horizontalLayout_12->addWidget(spnScanVmin);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        lblScanVmin2 = new QLabel(grpScanControl);
        lblScanVmin2->setObjectName(QStringLiteral("lblScanVmin2"));

        horizontalLayout_13->addWidget(lblScanVmin2);

        spnScanVmin2 = new QDoubleSpinBox(grpScanControl);
        spnScanVmin2->setObjectName(QStringLiteral("spnScanVmin2"));
        spnScanVmin2->setSingleStep(0.01);
        spnScanVmin2->setValue(0.2);

        horizontalLayout_13->addWidget(spnScanVmin2);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        lblScanNumLines = new QLabel(grpScanControl);
        lblScanNumLines->setObjectName(QStringLiteral("lblScanNumLines"));

        horizontalLayout_14->addWidget(lblScanNumLines);

        cmbScanNumLines = new QComboBox(grpScanControl);
        cmbScanNumLines->setObjectName(QStringLiteral("cmbScanNumLines"));

        horizontalLayout_14->addWidget(cmbScanNumLines);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        lblScanNumPoints = new QLabel(grpScanControl);
        lblScanNumPoints->setObjectName(QStringLiteral("lblScanNumPoints"));

        horizontalLayout_15->addWidget(lblScanNumPoints);

        cmbScanNumPoints = new QComboBox(grpScanControl);
        cmbScanNumPoints->setObjectName(QStringLiteral("cmbScanNumPoints"));

        horizontalLayout_15->addWidget(cmbScanNumPoints);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        lblScanDelay = new QLabel(grpScanControl);
        lblScanDelay->setObjectName(QStringLiteral("lblScanDelay"));

        horizontalLayout_16->addWidget(lblScanDelay);

        spnScanDelay = new QSpinBox(grpScanControl);
        spnScanDelay->setObjectName(QStringLiteral("spnScanDelay"));
        spnScanDelay->setValue(10);

        horizontalLayout_16->addWidget(spnScanDelay);


        verticalLayout_4->addLayout(horizontalLayout_16);

        label_scan_param_light = new QLabel(grpScanControl);
        label_scan_param_light->setObjectName(QStringLiteral("label_scan_param_light"));
        label_scan_param_light->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/1413858973_ballred-24.png")));

        verticalLayout_4->addWidget(label_scan_param_light);

        label_40 = new QLabel(grpScanControl);
        label_40->setObjectName(QStringLiteral("label_40"));

        verticalLayout_4->addWidget(label_40);


        gridLayout_6->addLayout(verticalLayout_4, 0, 0, 1, 1);


        _2->addWidget(grpScanControl, 8, 0, 1, 1);

        btn_scan_stop = new QPushButton(widget_3);
        btn_scan_stop->setObjectName(QStringLiteral("btn_scan_stop"));

        _2->addWidget(btn_scan_stop, 4, 0, 1, 1);

        progbar_scan = new QProgressBar(widget_3);
        progbar_scan->setObjectName(QStringLiteral("progbar_scan"));
        progbar_scan->setValue(0);

        _2->addWidget(progbar_scan, 6, 0, 1, 1);

        label_scan_status = new QLabel(widget_3);
        label_scan_status->setObjectName(QStringLiteral("label_scan_status"));

        _2->addWidget(label_scan_status, 5, 0, 1, 1);


        horizontalLayout_30->addWidget(widget_3);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(206, 0, 701, 601));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy4);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane { /* The tab widget frame */\n"
"     border: 2px solid gray;\n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
" }\n"
"\n"
" QTabWidget::tab-bar {\n"
"     left: 5px; /* move to the right by 5px */\n"
" }\n"
"\n"
" /* Style the tab using the tab sub-control. Note that\n"
"     it reads QTabBar _not_ QTabWidget */\n"
" QTabBar::tab {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"     border-left: 2px solid gray;\n"
" border-right: 2px solid gray;\n"
" border-top: 2px solid gray;\n"
"     border-bottom-color: gray; /* same as the pane color */\n"
"     border-top-left-radius: 4px;\n"
"     border-top-right-radius: 4px;\n"
"     min-width: 8ex;\n"
"     padding: 2px;\n"
""
                        " }\n"
"\n"
" QTabBar::tab:selected, QTabBar::tab:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                 stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
" }\n"
"\n"
" QTabBar::tab:selected {\n"
"     border-color: #9B9B9B;\n"
"     border-bottom-color: #C2C7CB; /* same as pane color */\n"
" }\n"
"\n"
" QTabBar::tab:!selected {\n"
"     margin-top: 2px; /* make non-selected tabs look smaller */\n"
" }"));
        controlTab = new QWidget();
        controlTab->setObjectName(QStringLiteral("controlTab"));
        gridLayout_28 = new QGridLayout(controlTab);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QStringLiteral("gridLayout_28"));
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        grpMemsControl = new QGroupBox(controlTab);
        grpMemsControl->setObjectName(QStringLiteral("grpMemsControl"));
        sizePolicy3.setHeightForWidth(grpMemsControl->sizePolicy().hasHeightForWidth());
        grpMemsControl->setSizePolicy(sizePolicy3);
        grpMemsControl->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 , stop: 1 #FFFFFF);\n"
"    }\n"
""));
        label_17 = new QLabel(grpMemsControl);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(11, 495, 16, 16));
        grpPIDControl = new QGroupBox(grpMemsControl);
        grpPIDControl->setObjectName(QStringLiteral("grpPIDControl"));
        grpPIDControl->setGeometry(QRect(20, 60, 161, 146));
        sizePolicy3.setHeightForWidth(grpPIDControl->sizePolicy().hasHeightForWidth());
        grpPIDControl->setSizePolicy(sizePolicy3);
        grpPIDControl->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        gridLayout_4 = new QGridLayout(grpPIDControl);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        lblPidValueP = new QLabel(grpPIDControl);
        lblPidValueP->setObjectName(QStringLiteral("lblPidValueP"));

        gridLayout_4->addWidget(lblPidValueP, 0, 0, 1, 1);

        spnPidValueP = new QDoubleSpinBox(grpPIDControl);
        spnPidValueP->setObjectName(QStringLiteral("spnPidValueP"));
        spnPidValueP->setMinimum(-100);
        spnPidValueP->setMaximum(100);
        spnPidValueP->setSingleStep(0.1);
        spnPidValueP->setValue(0.1);

        gridLayout_4->addWidget(spnPidValueP, 0, 1, 2, 2);

        spnPidValueI = new QDoubleSpinBox(grpPIDControl);
        spnPidValueI->setObjectName(QStringLiteral("spnPidValueI"));
        spnPidValueI->setMinimum(-1e+06);
        spnPidValueI->setMaximum(10000);
        spnPidValueI->setSingleStep(0.5);
        spnPidValueI->setValue(10);

        gridLayout_4->addWidget(spnPidValueI, 2, 1, 1, 2);

        lblPidValueI = new QLabel(grpPIDControl);
        lblPidValueI->setObjectName(QStringLiteral("lblPidValueI"));

        gridLayout_4->addWidget(lblPidValueI, 1, 0, 2, 1);

        lblPidValueD = new QLabel(grpPIDControl);
        lblPidValueD->setObjectName(QStringLiteral("lblPidValueD"));

        gridLayout_4->addWidget(lblPidValueD, 3, 0, 1, 1);

        spnPidValueD = new QDoubleSpinBox(grpPIDControl);
        spnPidValueD->setObjectName(QStringLiteral("spnPidValueD"));
        spnPidValueD->setMaximum(10000);
        spnPidValueD->setSingleStep(1);

        gridLayout_4->addWidget(spnPidValueD, 3, 1, 1, 2);

        btn_pid_off = new QPushButton(grpPIDControl);
        btn_pid_off->setObjectName(QStringLiteral("btn_pid_off"));

        gridLayout_4->addWidget(btn_pid_off, 5, 1, 1, 1);

        spnPidSetpoint = new QDoubleSpinBox(grpPIDControl);
        spnPidSetpoint->setObjectName(QStringLiteral("spnPidSetpoint"));
        spnPidSetpoint->setMinimum(0);
        spnPidSetpoint->setMaximum(10000);
        spnPidSetpoint->setSingleStep(0.01);
        spnPidSetpoint->setValue(1);

        gridLayout_4->addWidget(spnPidSetpoint, 4, 1, 1, 2);

        btn_pid_on = new QPushButton(grpPIDControl);
        btn_pid_on->setObjectName(QStringLiteral("btn_pid_on"));

        gridLayout_4->addWidget(btn_pid_on, 5, 0, 1, 1);

        lblPidSetPoint = new QLabel(grpPIDControl);
        lblPidSetPoint->setObjectName(QStringLiteral("lblPidSetPoint"));

        gridLayout_4->addWidget(lblPidSetPoint, 4, 0, 1, 1);

        label_pid_indicator = new QLabel(grpPIDControl);
        label_pid_indicator->setObjectName(QStringLiteral("label_pid_indicator"));
        label_pid_indicator->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/1413858973_ballred-24.png")));

        gridLayout_4->addWidget(label_pid_indicator, 5, 2, 1, 1);

        grpPIDControl_2 = new QGroupBox(grpMemsControl);
        grpPIDControl_2->setObjectName(QStringLiteral("grpPIDControl_2"));
        grpPIDControl_2->setGeometry(QRect(200, 60, 161, 146));
        sizePolicy3.setHeightForWidth(grpPIDControl_2->sizePolicy().hasHeightForWidth());
        grpPIDControl_2->setSizePolicy(sizePolicy3);
        grpPIDControl_2->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        layoutWidget_2 = new QWidget(grpPIDControl_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 40, 131, 26));
        horizontalLayout_40 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_40->setObjectName(QStringLiteral("horizontalLayout_40"));
        horizontalLayout_40->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_40->addWidget(label_14);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_11);

        label_13 = new QLabel(layoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/1413858973_ballred-24.png")));

        horizontalLayout_40->addWidget(label_13);

        calibrateButton = new QPushButton(grpPIDControl_2);
        calibrateButton->setObjectName(QStringLiteral("calibrateButton"));
        calibrateButton->setGeometry(QRect(30, 70, 111, 23));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(calibrateButton->sizePolicy().hasHeightForWidth());
        calibrateButton->setSizePolicy(sizePolicy5);
        calibrateButton->setMinimumSize(QSize(0, 0));
        calibrateButton->setStyleSheet(QStringLiteral(""));
        label_30 = new QLabel(grpPIDControl_2);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(50, 20, 81, 16));
        groupBox_3 = new QGroupBox(grpMemsControl);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 220, 281, 321));
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        groupBox_3->setMinimumSize(QSize(251, 244));
        groupBox_3->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 241, 298));
        gridLayout_19 = new QGridLayout(layoutWidget);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        gridLayout_19->setContentsMargins(0, 0, 0, 0);
        label_38 = new QLabel(layoutWidget);
        label_38->setObjectName(QStringLiteral("label_38"));

        gridLayout_19->addWidget(label_38, 15, 0, 1, 1);

        label_36 = new QLabel(layoutWidget);
        label_36->setObjectName(QStringLiteral("label_36"));

        gridLayout_19->addWidget(label_36, 13, 0, 1, 1);

        spn_freq_y1 = new QSpinBox(layoutWidget);
        spn_freq_y1->setObjectName(QStringLiteral("spn_freq_y1"));
        spn_freq_y1->setMaximum(100);
        spn_freq_y1->setValue(100);

        gridLayout_19->addWidget(spn_freq_y1, 14, 1, 1, 1);

        lblAmplitudeVoltage_2 = new QLabel(layoutWidget);
        lblAmplitudeVoltage_2->setObjectName(QStringLiteral("lblAmplitudeVoltage_2"));
        lblAmplitudeVoltage_2->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(lblAmplitudeVoltage_2->sizePolicy().hasHeightForWidth());
        lblAmplitudeVoltage_2->setSizePolicy(sizePolicy6);

        gridLayout_19->addWidget(lblAmplitudeVoltage_2, 11, 0, 1, 1);

        label_37 = new QLabel(layoutWidget);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_19->addWidget(label_37, 13, 1, 1, 1);

        label_35 = new QLabel(layoutWidget);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout_19->addWidget(label_35, 12, 0, 1, 1);

        spn_leveling = new QDoubleSpinBox(layoutWidget);
        spn_leveling->setObjectName(QStringLiteral("spn_leveling"));
        spn_leveling->setDecimals(0);
        spn_leveling->setMaximum(100);
        spn_leveling->setSingleStep(1);
        spn_leveling->setValue(0);

        gridLayout_19->addWidget(spn_leveling, 11, 1, 1, 1);

        spn_freq_x1 = new QSpinBox(layoutWidget);
        spn_freq_x1->setObjectName(QStringLiteral("spn_freq_x1"));
        spn_freq_x1->setMaximum(100);
        spn_freq_x1->setValue(100);

        gridLayout_19->addWidget(spn_freq_x1, 14, 0, 1, 1);

        spnBridgeVoltage = new QDoubleSpinBox(layoutWidget);
        spnBridgeVoltage->setObjectName(QStringLiteral("spnBridgeVoltage"));
        spnBridgeVoltage->setDecimals(4);
        spnBridgeVoltage->setSingleStep(0.01);
        spnBridgeVoltage->setValue(2);

        gridLayout_19->addWidget(spnBridgeVoltage, 6, 1, 1, 1);

        spnFrequencyVoltage = new QDoubleSpinBox(layoutWidget);
        spnFrequencyVoltage->setObjectName(QStringLiteral("spnFrequencyVoltage"));
        spnFrequencyVoltage->setDecimals(4);
        spnFrequencyVoltage->setSingleStep(0.01);

        gridLayout_19->addWidget(spnFrequencyVoltage, 8, 1, 1, 1);

        spn_dds_amplitude = new QDoubleSpinBox(layoutWidget);
        spn_dds_amplitude->setObjectName(QStringLiteral("spn_dds_amplitude"));
        spn_dds_amplitude->setDecimals(0);
        spn_dds_amplitude->setMaximum(100);
        spn_dds_amplitude->setSingleStep(1);
        spn_dds_amplitude->setValue(60);

        gridLayout_19->addWidget(spn_dds_amplitude, 10, 1, 1, 1);

        fineZRangeLabel = new QLabel(layoutWidget);
        fineZRangeLabel->setObjectName(QStringLiteral("fineZRangeLabel"));

        gridLayout_19->addWidget(fineZRangeLabel, 4, 0, 1, 1);

        coarseZLabel = new QLabel(layoutWidget);
        coarseZLabel->setObjectName(QStringLiteral("coarseZLabel"));

        gridLayout_19->addWidget(coarseZLabel, 0, 0, 1, 1);

        lblFrequencyVoltage = new QLabel(layoutWidget);
        lblFrequencyVoltage->setObjectName(QStringLiteral("lblFrequencyVoltage"));

        gridLayout_19->addWidget(lblFrequencyVoltage, 8, 0, 1, 1);

        lblAmplitudeVoltage = new QLabel(layoutWidget);
        lblAmplitudeVoltage->setObjectName(QStringLiteral("lblAmplitudeVoltage"));
        lblAmplitudeVoltage->setEnabled(true);
        sizePolicy6.setHeightForWidth(lblAmplitudeVoltage->sizePolicy().hasHeightForWidth());
        lblAmplitudeVoltage->setSizePolicy(sizePolicy6);

        gridLayout_19->addWidget(lblAmplitudeVoltage, 10, 0, 1, 1);

        lblBridgeVoltage = new QLabel(layoutWidget);
        lblBridgeVoltage->setObjectName(QStringLiteral("lblBridgeVoltage"));

        gridLayout_19->addWidget(lblBridgeVoltage, 6, 0, 1, 1);

        spn_zfine = new QDoubleSpinBox(layoutWidget);
        spn_zfine->setObjectName(QStringLiteral("spn_zfine"));
        spn_zfine->setDecimals(4);
        spn_zfine->setMaximum(100);
        spn_zfine->setSingleStep(1);
        spn_zfine->setValue(10);

        gridLayout_19->addWidget(spn_zfine, 2, 1, 1, 1);

        lblOffsetVoltage = new QLabel(layoutWidget);
        lblOffsetVoltage->setObjectName(QStringLiteral("lblOffsetVoltage"));

        gridLayout_19->addWidget(lblOffsetVoltage, 2, 0, 1, 1);

        spnBoxFineZRange = new QSpinBox(layoutWidget);
        spnBoxFineZRange->setObjectName(QStringLiteral("spnBoxFineZRange"));
        spnBoxFineZRange->setMaximum(100);
        spnBoxFineZRange->setValue(1);

        gridLayout_19->addWidget(spnBoxFineZRange, 4, 1, 1, 1);

        spn_zcoarse = new QDoubleSpinBox(layoutWidget);
        spn_zcoarse->setObjectName(QStringLiteral("spn_zcoarse"));
        spn_zcoarse->setMaximum(100);
        spn_zcoarse->setValue(100);

        gridLayout_19->addWidget(spn_zcoarse, 0, 1, 1, 1);

        spn_freq_x2 = new QSpinBox(layoutWidget);
        spn_freq_x2->setObjectName(QStringLiteral("spn_freq_x2"));
        spn_freq_x2->setMaximum(100);
        spn_freq_x2->setValue(100);

        gridLayout_19->addWidget(spn_freq_x2, 16, 0, 1, 1);

        label_39 = new QLabel(layoutWidget);
        label_39->setObjectName(QStringLiteral("label_39"));

        gridLayout_19->addWidget(label_39, 15, 1, 1, 1);

        spn_freq_y2 = new QSpinBox(layoutWidget);
        spn_freq_y2->setObjectName(QStringLiteral("spn_freq_y2"));
        spn_freq_y2->setMaximum(100);
        spn_freq_y2->setValue(100);

        gridLayout_19->addWidget(spn_freq_y2, 16, 1, 1, 1);

        btn_set_pga = new QPushButton(layoutWidget);
        btn_set_pga->setObjectName(QStringLiteral("btn_set_pga"));

        gridLayout_19->addWidget(btn_set_pga, 17, 0, 1, 2);

        grpPIDControl_3 = new QGroupBox(grpMemsControl);
        grpPIDControl_3->setObjectName(QStringLiteral("grpPIDControl_3"));
        grpPIDControl_3->setGeometry(QRect(390, 50, 261, 351));
        sizePolicy3.setHeightForWidth(grpPIDControl_3->sizePolicy().hasHeightForWidth());
        grpPIDControl_3->setSizePolicy(sizePolicy3);
        grpPIDControl_3->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        btn_re_init = new QPushButton(grpPIDControl_3);
        btn_re_init->setObjectName(QStringLiteral("btn_re_init"));
        btn_re_init->setGeometry(QRect(40, 40, 167, 23));

        verticalLayout_13->addWidget(grpMemsControl);


        horizontalLayout_33->addLayout(verticalLayout_13);


        gridLayout_28->addLayout(horizontalLayout_33, 0, 0, 1, 1);

        tabWidget->addTab(controlTab, QString());
        scanTab = new QWidget();
        scanTab->setObjectName(QStringLiteral("scanTab"));
        layoutWidget1 = new QWidget(scanTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(9, 18, 681, 521));
        verticalLayout_15 = new QVBoxLayout(layoutWidget1);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        btn_scan_start = new QPushButton(layoutWidget1);
        btn_scan_start->setObjectName(QStringLiteral("btn_scan_start"));

        gridLayout_9->addWidget(btn_scan_start, 2, 3, 1, 1);

        btn_setDACTable = new QPushButton(layoutWidget1);
        btn_setDACTable->setObjectName(QStringLiteral("btn_setDACTable"));

        gridLayout_9->addWidget(btn_setDACTable, 1, 1, 1, 1);

        label_34 = new QLabel(layoutWidget1);
        label_34->setObjectName(QStringLiteral("label_34"));

        gridLayout_9->addWidget(label_34, 1, 0, 1, 1);

        cmb_scanRatio_old = new QSpinBox(layoutWidget1);
        cmb_scanRatio_old->setObjectName(QStringLiteral("cmb_scanRatio_old"));
        cmb_scanRatio_old->setMaximum(8);
        cmb_scanRatio_old->setValue(2);

        gridLayout_9->addWidget(cmb_scanRatio_old, 2, 0, 1, 1);

        btn_scan_next = new QPushButton(layoutWidget1);
        btn_scan_next->setObjectName(QStringLiteral("btn_scan_next"));

        gridLayout_9->addWidget(btn_scan_next, 2, 5, 1, 1);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_9->addWidget(pushButton, 1, 3, 1, 1);

        btn_siggen = new QPushButton(layoutWidget1);
        btn_siggen->setObjectName(QStringLiteral("btn_siggen"));

        gridLayout_9->addWidget(btn_siggen, 2, 1, 1, 1);

        btn_print_offset = new QPushButton(layoutWidget1);
        btn_print_offset->setObjectName(QStringLiteral("btn_print_offset"));

        gridLayout_9->addWidget(btn_print_offset, 1, 4, 1, 1);

        btn_save_gxyzf = new QPushButton(layoutWidget1);
        btn_save_gxyzf->setObjectName(QStringLiteral("btn_save_gxyzf"));

        gridLayout_9->addWidget(btn_save_gxyzf, 3, 5, 1, 1);

        btn_save_txt_1 = new QPushButton(layoutWidget1);
        btn_save_txt_1->setObjectName(QStringLiteral("btn_save_txt_1"));

        gridLayout_9->addWidget(btn_save_txt_1, 3, 3, 1, 1);

        btn_save_txt_2 = new QPushButton(layoutWidget1);
        btn_save_txt_2->setObjectName(QStringLiteral("btn_save_txt_2"));

        gridLayout_9->addWidget(btn_save_txt_2, 3, 4, 1, 1);

        cmb_scanRatio = new QComboBox(layoutWidget1);
        cmb_scanRatio->setObjectName(QStringLiteral("cmb_scanRatio"));

        gridLayout_9->addWidget(cmb_scanRatio, 3, 0, 1, 1);


        verticalLayout_15->addLayout(gridLayout_9);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        tabScan = new QTabWidget(layoutWidget1);
        tabScan->setObjectName(QStringLiteral("tabScan"));
        tabScanForward = new QWidget();
        tabScanForward->setObjectName(QStringLiteral("tabScanForward"));
        frame = new QFrame(tabScanForward);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(9, 38, 631, 381));
        sizePolicy4.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy4);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_41 = new QHBoxLayout(frame);
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_41->setObjectName(QStringLiteral("horizontalLayout_41"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(0);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));

        horizontalLayout_41->addLayout(gridLayout_11);

        gwyddionButton = new QPushButton(tabScanForward);
        gwyddionButton->setObjectName(QStringLiteral("gwyddionButton"));
        gwyddionButton->setGeometry(QRect(39, 9, 84, 23));
        sizePolicy2.setHeightForWidth(gwyddionButton->sizePolicy().hasHeightForWidth());
        gwyddionButton->setSizePolicy(sizePolicy2);
        gwyddionButton->setLayoutDirection(Qt::RightToLeft);
        tabScan->addTab(tabScanForward, QString());
        tabScanReverse = new QWidget();
        tabScanReverse->setObjectName(QStringLiteral("tabScanReverse"));
        graph_2d_scan = new QWidget(tabScanReverse);
        graph_2d_scan->setObjectName(QStringLiteral("graph_2d_scan"));
        graph_2d_scan->setGeometry(QRect(10, 10, 659, 391));
        sizePolicy1.setHeightForWidth(graph_2d_scan->sizePolicy().hasHeightForWidth());
        graph_2d_scan->setSizePolicy(sizePolicy1);
        tabScan->addTab(tabScanReverse, QString());

        gridLayout_8->addWidget(tabScan, 0, 0, 1, 1);


        verticalLayout_15->addLayout(gridLayout_8);

        tabWidget->addTab(scanTab, QString());
        tabFreqSweep = new QWidget();
        tabFreqSweep->setObjectName(QStringLiteral("tabFreqSweep"));
        gridLayout_18 = new QGridLayout(tabFreqSweep);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        freqWidget = new QWidget(tabFreqSweep);
        freqWidget->setObjectName(QStringLiteral("freqWidget"));
        freqWidget->setMinimumSize(QSize(0, 0));
        freqWidget->setMaximumSize(QSize(910, 600));
        gridLayout_23 = new QGridLayout(freqWidget);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        gridLayout_17 = new QGridLayout();
        gridLayout_17->setSpacing(6);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_5);

        widget_2 = new QWidget(freqWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        gridLayout_16 = new QGridLayout(widget_2);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));

        horizontalLayout_31->addWidget(widget_2);

        groupBox_2 = new QGroupBox(freqWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        horizontalLayout_38 = new QHBoxLayout(groupBox_2);
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_38->setObjectName(QStringLiteral("horizontalLayout_38"));
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(6);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setSpacing(6);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        gridLayout_14->addWidget(checkBox, 2, 0, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        sweepButton = new QPushButton(groupBox_2);
        sweepButton->setObjectName(QStringLiteral("sweepButton"));
        sweepButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_9->addWidget(sweepButton);

        freqAutoScale = new QPushButton(groupBox_2);
        freqAutoScale->setObjectName(QStringLiteral("freqAutoScale"));
        freqAutoScale->setStyleSheet(QStringLiteral(""));
        freqAutoScale->setCheckable(true);

        verticalLayout_9->addWidget(freqAutoScale);

        useCurrFreqVal = new QPushButton(groupBox_2);
        useCurrFreqVal->setObjectName(QStringLiteral("useCurrFreqVal"));
        useCurrFreqVal->setStyleSheet(QStringLiteral(""));

        verticalLayout_9->addWidget(useCurrFreqVal);

        btn_auto_freqsweep = new QPushButton(groupBox_2);
        btn_auto_freqsweep->setObjectName(QStringLiteral("btn_auto_freqsweep"));

        verticalLayout_9->addWidget(btn_auto_freqsweep);


        gridLayout_14->addLayout(verticalLayout_9, 0, 0, 1, 1);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_18->addWidget(label_20);

        numFreqPoints = new QSpinBox(groupBox_2);
        numFreqPoints->setObjectName(QStringLiteral("numFreqPoints"));
        numFreqPoints->setMaximum(1000);
        numFreqPoints->setValue(200);

        horizontalLayout_18->addWidget(numFreqPoints);


        gridLayout_14->addLayout(horizontalLayout_18, 1, 0, 1, 2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_17->addWidget(label_19);

        freqProgressLabel = new QLabel(groupBox_2);
        freqProgressLabel->setObjectName(QStringLiteral("freqProgressLabel"));
        freqProgressLabel->setStyleSheet(QLatin1String("\n"
"QLabel {  color : red; };"));

        horizontalLayout_17->addWidget(freqProgressLabel);


        verticalLayout_8->addLayout(horizontalLayout_17);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_28->addWidget(label_23);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_12);

        startFrequency = new QSpinBox(groupBox_2);
        startFrequency->setObjectName(QStringLiteral("startFrequency"));
        startFrequency->setReadOnly(false);
        startFrequency->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        startFrequency->setMaximum(20000);
        startFrequency->setSingleStep(100);
        startFrequency->setValue(3000);

        horizontalLayout_28->addWidget(startFrequency);


        verticalLayout_8->addLayout(horizontalLayout_28);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_27->addWidget(label_22);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_7);

        endFrequency = new QSpinBox(groupBox_2);
        endFrequency->setObjectName(QStringLiteral("endFrequency"));
        endFrequency->setReadOnly(false);
        endFrequency->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        endFrequency->setMaximum(20000);
        endFrequency->setSingleStep(100);
        endFrequency->setValue(8000);

        horizontalLayout_27->addWidget(endFrequency);


        verticalLayout_8->addLayout(horizontalLayout_27);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_8->addWidget(label_18);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);

        currFreqVal = new QDoubleSpinBox(groupBox_2);
        currFreqVal->setObjectName(QStringLiteral("currFreqVal"));
        currFreqVal->setReadOnly(false);
        currFreqVal->setButtonSymbols(QAbstractSpinBox::NoButtons);
        currFreqVal->setDecimals(0);
        currFreqVal->setMaximum(150000);

        horizontalLayout_8->addWidget(currFreqVal);


        verticalLayout_8->addLayout(horizontalLayout_8);


        gridLayout_14->addLayout(verticalLayout_8, 0, 1, 1, 1);


        gridLayout_15->addLayout(gridLayout_14, 0, 0, 1, 1);


        horizontalLayout_38->addLayout(gridLayout_15);


        horizontalLayout_31->addWidget(groupBox_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_6);


        gridLayout_17->addLayout(horizontalLayout_31, 0, 0, 1, 1);


        gridLayout_23->addLayout(gridLayout_17, 0, 0, 1, 1);


        gridLayout_18->addWidget(freqWidget, 0, 0, 1, 1);

        tabWidget->addTab(tabFreqSweep, QString());
        tabApproach = new QWidget();
        tabApproach->setObjectName(QStringLiteral("tabApproach"));
        gridLayout_25 = new QGridLayout(tabApproach);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QStringLiteral("gridLayout_25"));
        approachWidget = new QWidget(tabApproach);
        approachWidget->setObjectName(QStringLiteral("approachWidget"));
        gridLayout_29 = new QGridLayout(approachWidget);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QStringLiteral("gridLayout_29"));
        gridLayout_24 = new QGridLayout();
        gridLayout_24->setSpacing(6);
        gridLayout_24->setObjectName(QStringLiteral("gridLayout_24"));
        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setObjectName(QStringLiteral("horizontalLayout_34"));
        horizontalSpacer_2 = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_2);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_13);

        groupBox = new QGroupBox(approachWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setStyleSheet(QLatin1String("    QGroupBox  {\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"        border: 2px solid gray;\n"
"        border-radius: 5px;\n"
"        margin-top: 1ex; /* leave space at the top for the title */\n"
"    }\n"
"     \n"
"    QGroupBox::title  {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top center; /* position at the top center */\n"
"        padding: 0 3px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        spn_test_dac_coarse_z = new QDoubleSpinBox(groupBox);
        spn_test_dac_coarse_z->setObjectName(QStringLiteral("spn_test_dac_coarse_z"));
        spn_test_dac_coarse_z->setSingleStep(0.01);

        horizontalLayout_32->addWidget(spn_test_dac_coarse_z);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_32->addWidget(label_21);


        verticalLayout_2->addLayout(horizontalLayout_32);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
        spn_test_dac_fine_z = new QDoubleSpinBox(groupBox);
        spn_test_dac_fine_z->setObjectName(QStringLiteral("spn_test_dac_fine_z"));
        spn_test_dac_fine_z->setSingleStep(0.01);

        horizontalLayout_35->addWidget(spn_test_dac_fine_z);

        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_35->addWidget(label_24);


        verticalLayout_2->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_36->addWidget(label_25);

        currOffsetValue = new QDoubleSpinBox(groupBox);
        currOffsetValue->setObjectName(QStringLiteral("currOffsetValue"));
        currOffsetValue->setReadOnly(true);
        currOffsetValue->setButtonSymbols(QAbstractSpinBox::NoButtons);
        currOffsetValue->setDecimals(4);

        horizontalLayout_36->addWidget(currOffsetValue);


        verticalLayout_2->addLayout(horizontalLayout_36);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        progbar_autoappr = new QProgressBar(groupBox);
        progbar_autoappr->setObjectName(QStringLiteral("progbar_autoappr"));
        progbar_autoappr->setMaximum(8);
        progbar_autoappr->setValue(8);

        gridLayout_5->addWidget(progbar_autoappr, 0, 0, 1, 6);

        btn_autoappr_go = new QPushButton(groupBox);
        btn_autoappr_go->setObjectName(QStringLiteral("btn_autoappr_go"));
        btn_autoappr_go->setEnabled(false);

        gridLayout_5->addWidget(btn_autoappr_go, 3, 0, 1, 3);

        btn_autoappr_stop = new QPushButton(groupBox);
        btn_autoappr_stop->setObjectName(QStringLiteral("btn_autoappr_stop"));
        btn_autoappr_stop->setEnabled(false);

        gridLayout_5->addWidget(btn_autoappr_stop, 3, 3, 1, 3);

        label_appr_phase_2 = new QLabel(groupBox);
        label_appr_phase_2->setObjectName(QStringLiteral("label_appr_phase_2"));

        gridLayout_5->addWidget(label_appr_phase_2, 0, 6, 1, 1);

        label_adczfine = new QLabel(groupBox);
        label_adczfine->setObjectName(QStringLiteral("label_adczfine"));

        gridLayout_5->addWidget(label_adczfine, 0, 7, 1, 1);

        label_autoappr_meas = new QLabel(groupBox);
        label_autoappr_meas->setObjectName(QStringLiteral("label_autoappr_meas"));

        gridLayout_5->addWidget(label_autoappr_meas, 1, 7, 1, 1);

        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout_5->addWidget(label_29, 1, 6, 1, 1);

        label_appr_phase = new QLabel(groupBox);
        label_appr_phase->setObjectName(QStringLiteral("label_appr_phase"));

        gridLayout_5->addWidget(label_appr_phase, 3, 7, 1, 1);

        label_41 = new QLabel(groupBox);
        label_41->setObjectName(QStringLiteral("label_41"));

        gridLayout_5->addWidget(label_41, 3, 6, 1, 1);

        label_28 = new QLabel(groupBox);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_5->addWidget(label_28, 1, 0, 1, 1);

        spnPidSetpoint_2 = new QDoubleSpinBox(groupBox);
        spnPidSetpoint_2->setObjectName(QStringLiteral("spnPidSetpoint_2"));
        spnPidSetpoint_2->setMinimum(0.01);
        spnPidSetpoint_2->setMaximum(10000);
        spnPidSetpoint_2->setSingleStep(0.01);
        spnPidSetpoint_2->setValue(1);

        gridLayout_5->addWidget(spnPidSetpoint_2, 1, 1, 1, 1);

        label_32 = new QLabel(groupBox);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_5->addWidget(label_32, 1, 4, 1, 1);

        lbl_autoappr_mcu_state = new QLabel(groupBox);
        lbl_autoappr_mcu_state->setObjectName(QStringLiteral("lbl_autoappr_mcu_state"));

        gridLayout_5->addWidget(lbl_autoappr_mcu_state, 1, 5, 1, 1);

        btn_autoappr_mcu_start = new QPushButton(groupBox);
        btn_autoappr_mcu_start->setObjectName(QStringLiteral("btn_autoappr_mcu_start"));

        gridLayout_5->addWidget(btn_autoappr_mcu_start, 1, 2, 1, 1);

        btn_autoappr_mcu_stop = new QPushButton(groupBox);
        btn_autoappr_mcu_stop->setObjectName(QStringLiteral("btn_autoappr_mcu_stop"));

        gridLayout_5->addWidget(btn_autoappr_mcu_stop, 1, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout_5, 1, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));

        verticalLayout_6->addLayout(horizontalLayout_24);


        verticalLayout_21->addLayout(verticalLayout_6);

        btn_appr_plot_autoscale = new QPushButton(groupBox);
        btn_appr_plot_autoscale->setObjectName(QStringLiteral("btn_appr_plot_autoscale"));
        btn_appr_plot_autoscale->setStyleSheet(QStringLiteral(""));
        btn_appr_plot_autoscale->setCheckable(true);

        verticalLayout_21->addWidget(btn_appr_plot_autoscale);

        btn_appr_plot_clear = new QPushButton(groupBox);
        btn_appr_plot_clear->setObjectName(QStringLiteral("btn_appr_plot_clear"));

        verticalLayout_21->addWidget(btn_appr_plot_clear);

        buttonCurrValuePidSetpoint = new QPushButton(groupBox);
        buttonCurrValuePidSetpoint->setObjectName(QStringLiteral("buttonCurrValuePidSetpoint"));
        buttonCurrValuePidSetpoint->setStyleSheet(QStringLiteral(""));
        buttonCurrValuePidSetpoint->setCheckable(true);

        verticalLayout_21->addWidget(buttonCurrValuePidSetpoint);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));

        verticalLayout_21->addLayout(horizontalLayout_43);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));

        verticalLayout_21->addLayout(horizontalLayout_44);


        gridLayout->addLayout(verticalLayout_21, 0, 1, 1, 1);

        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(6);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        btn_stepmot_user_up = new QPushButton(groupBox);
        btn_stepmot_user_up->setObjectName(QStringLiteral("btn_stepmot_user_up"));
        btn_stepmot_user_up->setAutoFillBackground(false);
        btn_stepmot_user_up->setStyleSheet(QStringLiteral(""));

        gridLayout_13->addWidget(btn_stepmot_user_up, 2, 1, 1, 2);

        label_31 = new QLabel(groupBox);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_13->addWidget(label_31, 0, 0, 1, 2);

        sld_stepmot_user_spd = new QSlider(groupBox);
        sld_stepmot_user_spd->setObjectName(QStringLiteral("sld_stepmot_user_spd"));
        sld_stepmot_user_spd->setMinimum(1);
        sld_stepmot_user_spd->setMaximum(4);
        sld_stepmot_user_spd->setOrientation(Qt::Horizontal);

        gridLayout_13->addWidget(sld_stepmot_user_spd, 1, 0, 1, 3);

        lbl_stepmot_user_spd = new QLabel(groupBox);
        lbl_stepmot_user_spd->setObjectName(QStringLiteral("lbl_stepmot_user_spd"));

        gridLayout_13->addWidget(lbl_stepmot_user_spd, 0, 2, 1, 1);

        btn_stepmot_user_down = new QPushButton(groupBox);
        btn_stepmot_user_down->setObjectName(QStringLiteral("btn_stepmot_user_down"));
        btn_stepmot_user_down->setAutoFillBackground(false);
        btn_stepmot_user_down->setStyleSheet(QStringLiteral(""));

        gridLayout_13->addWidget(btn_stepmot_user_down, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_13, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        horizontalLayout_34->addWidget(groupBox);

        horizontalSpacer_3 = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_3);


        gridLayout_24->addLayout(horizontalLayout_34, 0, 0, 1, 1);


        gridLayout_29->addLayout(gridLayout_24, 0, 0, 1, 1);


        gridLayout_25->addWidget(approachWidget, 0, 0, 1, 1);

        tabWidget->addTab(tabApproach, QString());
        tabSignal = new QWidget();
        tabSignal->setObjectName(QStringLiteral("tabSignal"));
        gridLayout_26 = new QGridLayout(tabSignal);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QStringLiteral("gridLayout_26"));
        signalWidget = new QWidget(tabSignal);
        signalWidget->setObjectName(QStringLiteral("signalWidget"));
        gridLayout_12 = new QGridLayout(signalWidget);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        pushButton_5 = new QPushButton(signalWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        sizePolicy2.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy2);
        pushButton_5->setStyleSheet(QStringLiteral(""));
        pushButton_5->setCheckable(true);

        horizontalLayout_20->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(signalWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy2.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy2);
        pushButton_4->setStyleSheet(QStringLiteral(""));
        pushButton_4->setCheckable(true);

        horizontalLayout_20->addWidget(pushButton_4);


        gridLayout_10->addLayout(horizontalLayout_20, 0, 0, 1, 1);


        gridLayout_12->addLayout(gridLayout_10, 0, 0, 1, 1);


        gridLayout_26->addWidget(signalWidget, 0, 0, 1, 1);

        tabWidget->addTab(tabSignal, QString());
        testTab = new QWidget();
        testTab->setObjectName(QStringLiteral("testTab"));
        layoutWidget2 = new QWidget(testTab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 10, 561, 239));
        horizontalLayout_26 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        dacNumber = new QSpinBox(layoutWidget2);
        dacNumber->setObjectName(QStringLiteral("dacNumber"));

        horizontalLayout_3->addWidget(dacNumber);


        verticalLayout_10->addLayout(horizontalLayout_3);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_19->addWidget(label_2);

        adcNumber = new QSpinBox(layoutWidget2);
        adcNumber->setObjectName(QStringLiteral("adcNumber"));

        horizontalLayout_19->addWidget(adcNumber);


        verticalLayout_10->addLayout(horizontalLayout_19);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_7->addWidget(label_3);

        dacValue = new QLabel(layoutWidget2);
        dacValue->setObjectName(QStringLiteral("dacValue"));

        verticalLayout_7->addWidget(dacValue);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_7->addWidget(label_5);

        adcValue = new QLabel(layoutWidget2);
        adcValue->setObjectName(QStringLiteral("adcValue"));

        verticalLayout_7->addWidget(adcValue);

        buttonReadIO = new QPushButton(layoutWidget2);
        buttonReadIO->setObjectName(QStringLiteral("buttonReadIO"));
        buttonReadIO->setStyleSheet(QStringLiteral(""));

        verticalLayout_7->addWidget(buttonReadIO);


        verticalLayout_10->addLayout(verticalLayout_7);


        horizontalLayout_26->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_14->addWidget(label_6);

        valToWrite = new QDoubleSpinBox(layoutWidget2);
        valToWrite->setObjectName(QStringLiteral("valToWrite"));
        valToWrite->setMaximum(2.5);
        valToWrite->setSingleStep(0.25);

        verticalLayout_14->addWidget(valToWrite);

        buttonWriteToDAC = new QPushButton(layoutWidget2);
        buttonWriteToDAC->setObjectName(QStringLiteral("buttonWriteToDAC"));
        buttonWriteToDAC->setStyleSheet(QStringLiteral(""));

        verticalLayout_14->addWidget(buttonWriteToDAC);


        horizontalLayout_22->addLayout(verticalLayout_14);


        verticalLayout_11->addLayout(horizontalLayout_22);


        horizontalLayout_26->addLayout(verticalLayout_11);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout->addWidget(label_15);

        line = new QFrame(layoutWidget2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_29->addWidget(label_7);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_10);

        latSpinBox = new QDoubleSpinBox(layoutWidget2);
        latSpinBox->setObjectName(QStringLiteral("latSpinBox"));
        sizePolicy2.setHeightForWidth(latSpinBox->sizePolicy().hasHeightForWidth());
        latSpinBox->setSizePolicy(sizePolicy2);
        latSpinBox->setMaximum(3.3);
        latSpinBox->setSingleStep(0.1);
        latSpinBox->setValue(3.3);

        horizontalLayout_29->addWidget(latSpinBox);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMaximumSize(QSize(24, 20));
        label_10->setStyleSheet(QStringLiteral(""));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/1413837188_checkmark-24.png")));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_29->addWidget(label_10);


        gridLayout_7->addLayout(horizontalLayout_29, 3, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_7->addWidget(label_8);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        ZcoarseSpinBox = new QDoubleSpinBox(layoutWidget2);
        ZcoarseSpinBox->setObjectName(QStringLiteral("ZcoarseSpinBox"));
        sizePolicy2.setHeightForWidth(ZcoarseSpinBox->sizePolicy().hasHeightForWidth());
        ZcoarseSpinBox->setSizePolicy(sizePolicy2);
        ZcoarseSpinBox->setMaximum(3.3);
        ZcoarseSpinBox->setSingleStep(0.1);
        ZcoarseSpinBox->setValue(2);

        horizontalLayout_7->addWidget(ZcoarseSpinBox);

        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy7);
        label_12->setMaximumSize(QSize(24, 20));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/1413837188_checkmark-24.png")));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_12);


        gridLayout_7->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        ZfineSpinBox = new QDoubleSpinBox(layoutWidget2);
        ZfineSpinBox->setObjectName(QStringLiteral("ZfineSpinBox"));
        sizePolicy2.setHeightForWidth(ZfineSpinBox->sizePolicy().hasHeightForWidth());
        ZfineSpinBox->setSizePolicy(sizePolicy2);
        ZfineSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ZfineSpinBox->setMaximum(3.3);
        ZfineSpinBox->setSingleStep(0.1);
        ZfineSpinBox->setValue(3.3);

        horizontalLayout_2->addWidget(ZfineSpinBox);

        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(24, 20));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/1413837188_checkmark-24.png")));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_11);


        gridLayout_7->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
        setMaxDACValuesButton = new QPushButton(layoutWidget2);
        setMaxDACValuesButton->setObjectName(QStringLiteral("setMaxDACValuesButton"));
        setMaxDACValuesButton->setEnabled(true);
        sizePolicy2.setHeightForWidth(setMaxDACValuesButton->sizePolicy().hasHeightForWidth());
        setMaxDACValuesButton->setSizePolicy(sizePolicy2);

        horizontalLayout_39->addWidget(setMaxDACValuesButton);


        gridLayout_7->addLayout(horizontalLayout_39, 4, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_7);


        horizontalLayout_26->addLayout(verticalLayout);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_16 = new QLabel(layoutWidget2);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_12->addWidget(label_16);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QStringLiteral("horizontalLayout_46"));
        radio_stepmot_fwd = new QRadioButton(layoutWidget2);
        radio_stepmot_fwd->setObjectName(QStringLiteral("radio_stepmot_fwd"));
        radio_stepmot_fwd->setStyleSheet(QStringLiteral(""));

        horizontalLayout_46->addWidget(radio_stepmot_fwd);

        radio_stepmot_back = new QRadioButton(layoutWidget2);
        radio_stepmot_back->setObjectName(QStringLiteral("radio_stepmot_back"));

        horizontalLayout_46->addWidget(radio_stepmot_back);


        verticalLayout_12->addLayout(horizontalLayout_46);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QStringLiteral("horizontalLayout_45"));
        label_26 = new QLabel(layoutWidget2);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_45->addWidget(label_26);

        cbo_microstep = new QComboBox(layoutWidget2);
        cbo_microstep->setObjectName(QStringLiteral("cbo_microstep"));
        cbo_microstep->setEnabled(true);
        cbo_microstep->setStyleSheet(QLatin1String("    QComboBox  {\n"
"        border: 1px solid gray;\n"
"        border-radius: 3px;\n"
"        padding: 1px 18px 1px 3px;\n"
"        min-width: 6em;\n"
"    }\n"
"     \n"
"    QComboBox:editable  {\n"
"        background: white;\n"
"    }\n"
"     \n"
"    QComboBox:!editable, QComboBox::drop-down:editable  {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    }\n"
"     \n"
"    /* QComboBox gets the \"on\" state when the popup is open */\n"
"    QComboBox:!editable:on, QComboBox::drop-down:editable:on  {\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                    stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,\n"
"                                    stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n"
"    }\n"
"     \n"
"    QComboBox:on  { /* shift the text when the popup opens */\n"
"        paddin"
                        "g-top: 3px;\n"
"        padding-left: 4px;\n"
"    }\n"
"     \n"
"    QComboBox::drop-down  {\n"
"        subcontrol-origin: padding;\n"
"        subcontrol-position: top right;\n"
"        width: 15px;\n"
"     \n"
"        border-left-width: 1px;\n"
"        border-left-color: darkgray;\n"
"        border-left-style: solid; /* just a single line */\n"
"        border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"        border-bottom-right-radius: 3px;\n"
"    }\n"
"     \n"
"    QComboBox::down-arrow  {\n"
"        image: url(C:/Qt/Tools/QtCreator/bin/qml/QtQuick/Controls/Styles/Base/images/arrow-down.png);\n"
"    }\n"
"     \n"
"    QComboBox::down-arrow:on  { /* shift the arrow when popup is open */\n"
"        top: 1px;\n"
"        left: 1px;\n"
"    }\n"
""));
        cbo_microstep->setEditable(false);

        horizontalLayout_45->addWidget(cbo_microstep);


        verticalLayout_12->addLayout(horizontalLayout_45);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QStringLiteral("horizontalLayout_47"));
        label_27 = new QLabel(layoutWidget2);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_47->addWidget(label_27);

        lbl_stepmot_speed = new QLabel(layoutWidget2);
        lbl_stepmot_speed->setObjectName(QStringLiteral("lbl_stepmot_speed"));

        horizontalLayout_47->addWidget(lbl_stepmot_speed);


        verticalLayout_12->addLayout(horizontalLayout_47);

        sld_stepmot_speed = new QSlider(layoutWidget2);
        sld_stepmot_speed->setObjectName(QStringLiteral("sld_stepmot_speed"));
        sld_stepmot_speed->setMaximum(26300);
        sld_stepmot_speed->setOrientation(Qt::Horizontal);

        verticalLayout_12->addWidget(sld_stepmot_speed);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName(QStringLiteral("horizontalLayout_48"));
        btn_stepmot_sleep = new QPushButton(layoutWidget2);
        btn_stepmot_sleep->setObjectName(QStringLiteral("btn_stepmot_sleep"));

        horizontalLayout_48->addWidget(btn_stepmot_sleep);

        btn_stepmot_wake = new QPushButton(layoutWidget2);
        btn_stepmot_wake->setObjectName(QStringLiteral("btn_stepmot_wake"));

        horizontalLayout_48->addWidget(btn_stepmot_wake);


        verticalLayout_12->addLayout(horizontalLayout_48);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName(QStringLiteral("horizontalLayout_42"));
        btn_stepmot_cont_go = new QPushButton(layoutWidget2);
        btn_stepmot_cont_go->setObjectName(QStringLiteral("btn_stepmot_cont_go"));

        horizontalLayout_42->addWidget(btn_stepmot_cont_go);

        btn_stepmot_cont_stop = new QPushButton(layoutWidget2);
        btn_stepmot_cont_stop->setObjectName(QStringLiteral("btn_stepmot_cont_stop"));

        horizontalLayout_42->addWidget(btn_stepmot_cont_stop);


        verticalLayout_12->addLayout(horizontalLayout_42);

        btn_stepmot_singlestep = new QPushButton(layoutWidget2);
        btn_stepmot_singlestep->setObjectName(QStringLiteral("btn_stepmot_singlestep"));
        btn_stepmot_singlestep->setStyleSheet(QStringLiteral(""));

        verticalLayout_12->addWidget(btn_stepmot_singlestep);


        horizontalLayout_26->addLayout(verticalLayout_12);

        btnForceCurve = new QPushButton(testTab);
        btnForceCurve->setObjectName(QStringLiteral("btnForceCurve"));
        btnForceCurve->setGeometry(QRect(20, 340, 75, 23));
        gridLayoutWidget = new QWidget(testTab);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 370, 661, 151));
        forcecurve_gridlayout = new QGridLayout(gridLayoutWidget);
        forcecurve_gridlayout->setSpacing(6);
        forcecurve_gridlayout->setContentsMargins(11, 11, 11, 11);
        forcecurve_gridlayout->setObjectName(QStringLiteral("forcecurve_gridlayout"));
        forcecurve_gridlayout->setContentsMargins(0, 0, 0, 0);
        forceWidget = new QWidget(gridLayoutWidget);
        forceWidget->setObjectName(QStringLiteral("forceWidget"));
        sizePolicy1.setHeightForWidth(forceWidget->sizePolicy().hasHeightForWidth());
        forceWidget->setSizePolicy(sizePolicy1);

        forcecurve_gridlayout->addWidget(forceWidget, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(testTab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(300, 290, 75, 23));
        btn_autoappr_mcu_start_2 = new QPushButton(testTab);
        btn_autoappr_mcu_start_2->setObjectName(QStringLiteral("btn_autoappr_mcu_start_2"));
        btn_autoappr_mcu_start_2->setGeometry(QRect(200, 290, 75, 23));
        label_33 = new QLabel(testTab);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(390, 290, 47, 13));
        tabWidget->addTab(testTab, QString());
        tabLog = new QWidget();
        tabLog->setObjectName(QStringLiteral("tabLog"));
        tabWidget->addTab(tabLog, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 910, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setEnabled(false);
        toolBar->setMinimumSize(QSize(0, 20));
        toolBar->setLayoutDirection(Qt::LeftToRight);
        toolBar->setStyleSheet(QStringLiteral("border-bottom: 1px solid black;"));
        toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_All);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionCut);
        menuWindow->addAction(actionMinimize);
        menuWindow->addAction(actionMaximize);
        toolBar->addAction(openFile);
        toolBar->addAction(openMeshFile);
        toolBar->addAction(animation);
        toolBar->addAction(Box);
        toolBar->addAction(Frame);
        toolBar->addAction(None);
        toolBar->addAction(left);
        toolBar->addAction(ceil);
        toolBar->addAction(back);
        toolBar->addAction(front);
        toolBar->addAction(right);
        toolBar->addAction(floor);
        toolBar->addAction(pointstyle);
        toolBar->addAction(wireframe);
        toolBar->addAction(hiddenline);
        toolBar->addAction(polygon);
        toolBar->addAction(filledmesh);
        toolBar->addAction(nodata);
        toolBar->addAction(floordata);
        toolBar->addAction(flooriso);
        toolBar->addAction(floornone);
        toolBar->addAction(normals);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);
        cmb_scanRatio->setCurrentIndex(0);
        tabScan->setCurrentIndex(1);
        cbo_microstep->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave_All->setText(QApplication::translate("MainWindow", "Save All", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0));
        actionMinimize->setText(QApplication::translate("MainWindow", "Minimize", 0));
        actionMaximize->setText(QApplication::translate("MainWindow", "Maximize", 0));
        openFile->setText(QApplication::translate("MainWindow", "Open File", 0));
        openFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        openMeshFile->setText(QApplication::translate("MainWindow", "Open FEM File", 0));
        animation->setText(QApplication::translate("MainWindow", "Animation", 0));
        Exit->setText(QApplication::translate("MainWindow", "Exit", 0));
        Exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        Box->setText(QApplication::translate("MainWindow", "Box", 0));
        Frame->setText(QApplication::translate("MainWindow", "Frame", 0));
        None->setText(QApplication::translate("MainWindow", "None", 0));
        front->setText(QApplication::translate("MainWindow", "front", 0));
        back->setText(QApplication::translate("MainWindow", "back", 0));
        right->setText(QApplication::translate("MainWindow", "right", 0));
        left->setText(QApplication::translate("MainWindow", "left", 0));
        ceil->setText(QApplication::translate("MainWindow", "ceil", 0));
        floor->setText(QApplication::translate("MainWindow", "floor", 0));
        pointstyle->setText(QApplication::translate("MainWindow", "pointstyle", 0));
        wireframe->setText(QApplication::translate("MainWindow", "wireframe", 0));
        hiddenline->setText(QApplication::translate("MainWindow", "hiddenline", 0));
        polygon->setText(QApplication::translate("MainWindow", "polygon", 0));
        filledmesh->setText(QApplication::translate("MainWindow", "filledmesh", 0));
        nodata->setText(QApplication::translate("MainWindow", "nodata", 0));
        floordata->setText(QApplication::translate("MainWindow", "floordata", 0));
        flooriso->setText(QApplication::translate("MainWindow", "flooriso", 0));
        floornone->setText(QApplication::translate("MainWindow", "floornone", 0));
        normals->setText(QApplication::translate("MainWindow", "normals", 0));
        btn_scan_begin->setText(QApplication::translate("MainWindow", "Scan", 0));
        label_4->setText(QApplication::translate("MainWindow", "Plot Refresh (ms):", 0));
        lblComPortSelection->setText(QApplication::translate("MainWindow", "COM:", 0));
        cboComPortSelection->setCurrentText(QString());
        btnSetScanParameters->setText(QApplication::translate("MainWindow", "Set Scan Parameters", 0));
        grpScanControl->setTitle(QApplication::translate("MainWindow", "Scan Control", 0));
        lblScanVmaxV->setText(QApplication::translate("MainWindow", "Vmax (V):", 0));
        lblVminV->setText(QApplication::translate("MainWindow", "Vmin (V):", 0));
        lblScanVmin2->setText(QApplication::translate("MainWindow", "Vmin2 (V):", 0));
        lblScanNumLines->setText(QApplication::translate("MainWindow", "Num Lines:", 0));
        cmbScanNumLines->clear();
        cmbScanNumLines->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "16", 0)
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
         << QApplication::translate("MainWindow", "1024", 0)
        );
        cmbScanNumLines->setCurrentText(QApplication::translate("MainWindow", "1", 0));
        lblScanNumPoints->setText(QApplication::translate("MainWindow", "Num Points:", 0));
        cmbScanNumPoints->clear();
        cmbScanNumPoints->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "16", 0)
         << QApplication::translate("MainWindow", "32", 0)
         << QApplication::translate("MainWindow", "64", 0)
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
         << QApplication::translate("MainWindow", "1028", 0)
        );
        cmbScanNumPoints->setCurrentText(QApplication::translate("MainWindow", "1", 0));
        lblScanDelay->setText(QApplication::translate("MainWindow", "Wait Time (ms):", 0));
        label_scan_param_light->setText(QString());
        label_40->setText(QApplication::translate("MainWindow", "Parameter Status", 0));
        btn_scan_stop->setText(QApplication::translate("MainWindow", "Don't Scan", 0));
        label_scan_status->setText(QString());
        grpMemsControl->setTitle(QApplication::translate("MainWindow", "MEMS Control", 0));
        label_17->setText(QString());
        grpPIDControl->setTitle(QApplication::translate("MainWindow", "PID Control", 0));
        lblPidValueP->setText(QApplication::translate("MainWindow", "P:", 0));
        lblPidValueI->setText(QApplication::translate("MainWindow", "I:", 0));
        lblPidValueD->setText(QApplication::translate("MainWindow", "D:", 0));
        btn_pid_off->setText(QApplication::translate("MainWindow", "OFF", 0));
        btn_pid_on->setText(QApplication::translate("MainWindow", "ON", 0));
        lblPidSetPoint->setText(QApplication::translate("MainWindow", "Setpoint:", 0));
        label_pid_indicator->setText(QString());
        grpPIDControl_2->setTitle(QApplication::translate("MainWindow", "Calibration", 0));
        label_14->setText(QApplication::translate("MainWindow", "Calibrated:", 0));
        label_13->setText(QString());
        calibrateButton->setText(QApplication::translate("MainWindow", "Calibrate", 0));
        label_30->setText(QApplication::translate("MainWindow", "2ACT ONLY", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Programmable Gain Amplifier PGA", 0));
        label_38->setText(QApplication::translate("MainWindow", "x2", 0));
        label_36->setText(QApplication::translate("MainWindow", "x1", 0));
        lblAmplitudeVoltage_2->setText(QApplication::translate("MainWindow", "Leveling", 0));
        label_37->setText(QApplication::translate("MainWindow", "y1", 0));
        label_35->setText(QApplication::translate("MainWindow", "4ACT Frequency (%):", 0));
        fineZRangeLabel->setText(QApplication::translate("MainWindow", "Fine Z Range (%)", 0));
        coarseZLabel->setText(QApplication::translate("MainWindow", "Coarse Z (%)", 0));
        lblFrequencyVoltage->setText(QApplication::translate("MainWindow", "2ACT Frequency (V):", 0));
        lblAmplitudeVoltage->setText(QApplication::translate("MainWindow", "DDS Amplitude (%):", 0));
        lblBridgeVoltage->setText(QApplication::translate("MainWindow", "Bridge Voltage (V):", 0));
        lblOffsetVoltage->setText(QApplication::translate("MainWindow", "Fine Z (%)", 0));
        label_39->setText(QApplication::translate("MainWindow", "y2", 0));
        btn_set_pga->setText(QApplication::translate("MainWindow", "Set", 0));
        grpPIDControl_3->setTitle(QApplication::translate("MainWindow", "Platform Controls", 0));
        btn_re_init->setText(QApplication::translate("MainWindow", "Re-Initialize AFM: DAC and PGA", 0));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "Control Setup", 0));
        btn_scan_start->setText(QApplication::translate("MainWindow", "Enter Scan Mode", 0));
        btn_setDACTable->setText(QApplication::translate("MainWindow", "DAC Table because Keil", 0));
        label_34->setText(QApplication::translate("MainWindow", "Ratio ENUM", 0));
        btn_scan_next->setText(QApplication::translate("MainWindow", "Next Points", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Print afm_data", 0));
        btn_siggen->setText(QApplication::translate("MainWindow", "SigGen", 0));
        btn_print_offset->setText(QApplication::translate("MainWindow", "Print amp for gwyddion", 0));
        btn_save_gxyzf->setText(QApplication::translate("MainWindow", "Save gwyddion xyzf", 0));
        btn_save_txt_1->setText(QApplication::translate("MainWindow", "Save fwd offset text", 0));
        btn_save_txt_2->setText(QApplication::translate("MainWindow", "Save rev offset text", 0));
        cmb_scanRatio->clear();
        cmb_scanRatio->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0:1", 0)
         << QApplication::translate("MainWindow", "1:1", 0)
         << QApplication::translate("MainWindow", "3:1", 0)
         << QApplication::translate("MainWindow", "7:1", 0)
        );
        gwyddionButton->setText(QApplication::translate("MainWindow", "Open Gwyddion", 0));
        tabScan->setTabText(tabScan->indexOf(tabScanForward), QApplication::translate("MainWindow", "Forward", 0));
        tabScan->setTabText(tabScan->indexOf(tabScanReverse), QApplication::translate("MainWindow", "Reverse", 0));
        tabWidget->setTabText(tabWidget->indexOf(scanTab), QApplication::translate("MainWindow", "Scan", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Show Marker", 0));
        sweepButton->setText(QApplication::translate("MainWindow", "Sweep", 0));
        freqAutoScale->setText(QApplication::translate("MainWindow", "Auto Scale Graph Y", 0));
        useCurrFreqVal->setText(QApplication::translate("MainWindow", "Use Current Freq Value", 0));
        btn_auto_freqsweep->setText(QApplication::translate("MainWindow", "Auto Find Freq Max", 0));
        label_20->setText(QApplication::translate("MainWindow", "Resolution (number of points):", 0));
        label_19->setText(QApplication::translate("MainWindow", "In Progress:", 0));
        freqProgressLabel->setText(QApplication::translate("MainWindow", "FALSE", 0));
        label_23->setText(QApplication::translate("MainWindow", "Start Frequency (Hz):", 0));
        label_22->setText(QApplication::translate("MainWindow", "End Frequency (Hz):", 0));
        label_18->setText(QApplication::translate("MainWindow", "Current Freq Value:", 0));
        currFreqVal->setSuffix(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabFreqSweep), QApplication::translate("MainWindow", "Frequency Sweep", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Coarse Approach", 0));
        label_21->setText(QApplication::translate("MainWindow", "Set DAC Coarse Z", 0));
        label_24->setText(QApplication::translate("MainWindow", "Set DAC Fine Z", 0));
        label_25->setText(QApplication::translate("MainWindow", "Current Signal:", 0));
        progbar_autoappr->setFormat(QApplication::translate("MainWindow", "Step %v", 0));
        btn_autoappr_go->setText(QApplication::translate("MainWindow", "Qt AutoApproach Go", 0));
        btn_autoappr_stop->setText(QApplication::translate("MainWindow", "Qt AutoApproach STOP", 0));
        label_appr_phase_2->setText(QApplication::translate("MainWindow", "DAC Z FINE OFFSET", 0));
        label_adczfine->setText(QApplication::translate("MainWindow", "NO SIGNAL", 0));
        label_autoappr_meas->setText(QApplication::translate("MainWindow", "NO SIGNAL", 0));
        label_29->setText(QApplication::translate("MainWindow", "ADC PZR Z-AMP", 0));
        label_appr_phase->setText(QApplication::translate("MainWindow", "NO SIGNAL", 0));
        label_41->setText(QApplication::translate("MainWindow", "PZR PHASE", 0));
        label_28->setText(QApplication::translate("MainWindow", "Setpoint: ", 0));
        label_32->setText(QApplication::translate("MainWindow", "MCU State", 0));
        lbl_autoappr_mcu_state->setText(QApplication::translate("MainWindow", "NO SIGNAL", 0));
        btn_autoappr_mcu_start->setText(QApplication::translate("MainWindow", "MCU GO", 0));
        btn_autoappr_mcu_stop->setText(QApplication::translate("MainWindow", "MCU STOP", 0));
        btn_appr_plot_autoscale->setText(QApplication::translate("MainWindow", "Auto Scale", 0));
        btn_appr_plot_clear->setText(QApplication::translate("MainWindow", "Clear Data", 0));
        buttonCurrValuePidSetpoint->setText(QApplication::translate("MainWindow", "Current Value as PID Setpoint", 0));
        btn_stepmot_user_up->setText(QApplication::translate("MainWindow", "Retract", 0));
        label_31->setText(QApplication::translate("MainWindow", "Speed", 0));
        lbl_stepmot_user_spd->setText(QApplication::translate("MainWindow", "1", 0));
        btn_stepmot_user_down->setText(QApplication::translate("MainWindow", "Approach", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabApproach), QApplication::translate("MainWindow", "Approach", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Autoscale Offset", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Autoscale Error", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabSignal), QApplication::translate("MainWindow", "Signal", 0));
        label->setText(QApplication::translate("MainWindow", "DAC #", 0));
        label_2->setText(QApplication::translate("MainWindow", "ADC #", 0));
        label_3->setText(QApplication::translate("MainWindow", "DAC Value", 0));
        dacValue->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_5->setText(QApplication::translate("MainWindow", "ADC Value", 0));
        adcValue->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        buttonReadIO->setText(QApplication::translate("MainWindow", "Read from DAC/ADC", 0));
        label_6->setText(QApplication::translate("MainWindow", "Value to Write", 0));
        buttonWriteToDAC->setText(QApplication::translate("MainWindow", "Write to DAC", 0));
        label_15->setText(QApplication::translate("MainWindow", "Set Max DAC values", 0));
        label_7->setText(QApplication::translate("MainWindow", "Vmax Lat:", 0));
        label_10->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Vmax Z Coarse:", 0));
        label_12->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Vmax ZFine:", 0));
        label_11->setText(QString());
        setMaxDACValuesButton->setText(QApplication::translate("MainWindow", "Set DAC Max Values", 0));
        label_16->setText(QApplication::translate("MainWindow", "Stepper Motor Controls", 0));
        radio_stepmot_fwd->setText(QApplication::translate("MainWindow", "Fwd", 0));
        radio_stepmot_back->setText(QApplication::translate("MainWindow", "Back", 0));
        label_26->setText(QApplication::translate("MainWindow", "Microstep 1/th", 0));
        cbo_microstep->setCurrentText(QString());
        label_27->setText(QApplication::translate("MainWindow", "Speed", 0));
        lbl_stepmot_speed->setText(QApplication::translate("MainWindow", "0", 0));
        btn_stepmot_sleep->setText(QApplication::translate("MainWindow", "Sleep", 0));
        btn_stepmot_wake->setText(QApplication::translate("MainWindow", "Wake", 0));
        btn_stepmot_cont_go->setText(QApplication::translate("MainWindow", "GO", 0));
        btn_stepmot_cont_stop->setText(QApplication::translate("MainWindow", "STOP", 0));
        btn_stepmot_singlestep->setText(QApplication::translate("MainWindow", "STEP", 0));
        btnForceCurve->setText(QApplication::translate("MainWindow", "Force Curve", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "MCU STA", 0));
        btn_autoappr_mcu_start_2->setText(QApplication::translate("MainWindow", "MCU GO", 0));
        label_33->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(testTab), QApplication::translate("MainWindow", "Test", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabLog), QApplication::translate("MainWindow", "Log", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
