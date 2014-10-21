/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_37;
    QFrame *sidebarFrame;
    QHBoxLayout *horizontalLayout_30;
    QWidget *widget_3;
    QGridLayout *_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_4;
    QSpinBox *refreshSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblComPortSelection;
    QComboBox *cboComPortSelection;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_13;
    QPushButton *pushButton_6;
    QTabWidget *tabWidget;
    QWidget *controlTab;
    QGridLayout *gridLayout_28;
    QHBoxLayout *horizontalLayout_33;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *grpPIDControl;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblPidValueP;
    QDoubleSpinBox *spnPidValueP;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblPidValueI;
    QDoubleSpinBox *spnPidValueI;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lblPidValueD;
    QDoubleSpinBox *spnPidValueD;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lblPidSetPoint;
    QDoubleSpinBox *spnPidSetpoint;
    QPushButton *btnPidToggle;
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
    QSpinBox *spnScanNumLines;
    QHBoxLayout *horizontalLayout_15;
    QLabel *lblScanNumPoints;
    QSpinBox *spnScanNumPoints;
    QHBoxLayout *horizontalLayout_16;
    QLabel *lblScanDelay;
    QSpinBox *spnScanDelay;
    QGroupBox *grpMemsControl;
    QGridLayout *gridLayout_20;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_7;
    QLabel *lblOffsetVoltage;
    QLabel *lblBridgeVoltage;
    QLabel *lblFrequencyVoltage;
    QLabel *lblAmplitudeVoltage;
    QVBoxLayout *verticalLayout_14;
    QDoubleSpinBox *spnOffsetVoltage;
    QDoubleSpinBox *spnBridgeVoltage;
    QDoubleSpinBox *spnFrequencyVoltage;
    QDoubleSpinBox *spnFrequencyVoltage_2;
    QLabel *label_17;
    QVBoxLayout *verticalLayout;
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
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_7;
    QWidget *scanTab;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_8;
    QTabWidget *tabScan;
    QWidget *tabScanForward;
    QWidget *tabScanReverse;
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
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_20;
    QSpinBox *numFreqPoints;
    QVBoxLayout *verticalLayout_9;
    QPushButton *sweepButton;
    QPushButton *freqAutoScale;
    QPushButton *buttonSendSweep;
    QPushButton *useCurrFreqVal;
    QCheckBox *checkBox;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_19;
    QLabel *freqProgressLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_23;
    QSpinBox *startFrequency;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_22;
    QSpinBox *stepSize;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_18;
    QDoubleSpinBox *currFreqVal;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tabApproach;
    QGridLayout *gridLayout_25;
    QWidget *approachWidget;
    QGridLayout *gridLayout_29;
    QGridLayout *gridLayout_24;
    QHBoxLayout *horizontalLayout_34;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_22;
    QPushButton *buttonCurrValuePidSetpoint;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_21;
    QDoubleSpinBox *currPIDSetpoint;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_24;
    QDoubleSpinBox *comparisonValue;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_25;
    QDoubleSpinBox *currOffsetValue;
    QPushButton *buttonAutoApproachMCU;
    QPushButton *buttonAutoApproachClient;
    QPushButton *writeCharacter;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *verticalLayout_6;
    QSlider *sldAmplitudeVoltage_3;
    QHBoxLayout *horizontalLayout_24;
    QLabel *lblMemsAmplitudeMinVal_3;
    QSpacerItem *horizontalSpacer;
    QLabel *lblAmplitude;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lblMemsAmplitudeMaxVal_3;
    QHBoxLayout *horizontalLayout_43;
    QPushButton *stepButton;
    QPushButton *continuousButton;
    QHBoxLayout *horizontalLayout_44;
    QRadioButton *retreatButton;
    QRadioButton *approachButton;
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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *dacNumber;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_2;
    QSpinBox *adcNumber;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_6;
    QDoubleSpinBox *valToWrite;
    QPushButton *buttonWriteToDAC;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_3;
    QDoubleSpinBox *dacValue;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_5;
    QDoubleSpinBox *adcValue;
    QSpacerItem *verticalSpacer_4;
    QPushButton *buttonReadIO;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuWindow;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(910, 569);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        horizontalLayout_37 = new QHBoxLayout(centralWidget);
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
        horizontalLayout_37->setContentsMargins(0, 0, -1, 0);
        sidebarFrame = new QFrame(centralWidget);
        sidebarFrame->setObjectName(QStringLiteral("sidebarFrame"));
        sidebarFrame->setMinimumSize(QSize(200, 528));
        sidebarFrame->setStyleSheet(QLatin1String("#sidebarFrame {\n"
"background: #9E9E9E;\n"
"border: none;\n"
"border-right: 1px solid black;\n"
"}"));
        sidebarFrame->setFrameShape(QFrame::StyledPanel);
        sidebarFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_30 = new QHBoxLayout(sidebarFrame);
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        widget_3 = new QWidget(sidebarFrame);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        _2 = new QGridLayout(widget_3);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QStringLiteral("_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetFixedSize);

        gridLayout_3->addLayout(verticalLayout_5, 5, 0, 1, 1);

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
        sizePolicy1.setHeightForWidth(lblComPortSelection->sizePolicy().hasHeightForWidth());
        lblComPortSelection->setSizePolicy(sizePolicy1);

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

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QStringLiteral("horizontalLayout_40"));
        label_14 = new QLabel(widget_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_40->addWidget(label_14);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_11);

        label_13 = new QLabel(widget_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setPixmap(QPixmap(QString::fromUtf8("../icons/1413858973_ballred-24.png")));

        horizontalLayout_40->addWidget(label_13);


        gridLayout_3->addLayout(horizontalLayout_40, 3, 0, 1, 1);


        _2->addLayout(gridLayout_3, 0, 0, 1, 1);

        pushButton_6 = new QPushButton(widget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setStyleSheet(QStringLiteral(""));

        _2->addWidget(pushButton_6, 1, 0, 1, 1);


        horizontalLayout_30->addWidget(widget_3);


        horizontalLayout_37->addWidget(sidebarFrame);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane { /* The tab widget frame */\n"
"     border: 2px solid gray;\n"
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
" }\n"
"\n"
" QTabBar::tab:selected, QTabBar::tab:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"      "
                        "                           stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
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
        grpPIDControl = new QGroupBox(controlTab);
        grpPIDControl->setObjectName(QStringLiteral("grpPIDControl"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(grpPIDControl->sizePolicy().hasHeightForWidth());
        grpPIDControl->setSizePolicy(sizePolicy3);
        grpPIDControl->setStyleSheet(QLatin1String("    QGroupBox  {\n"
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
        gridLayout_4 = new QGridLayout(grpPIDControl);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblPidValueP = new QLabel(grpPIDControl);
        lblPidValueP->setObjectName(QStringLiteral("lblPidValueP"));

        horizontalLayout_4->addWidget(lblPidValueP);

        spnPidValueP = new QDoubleSpinBox(grpPIDControl);
        spnPidValueP->setObjectName(QStringLiteral("spnPidValueP"));
        spnPidValueP->setSingleStep(0.01);

        horizontalLayout_4->addWidget(spnPidValueP);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lblPidValueI = new QLabel(grpPIDControl);
        lblPidValueI->setObjectName(QStringLiteral("lblPidValueI"));

        horizontalLayout_5->addWidget(lblPidValueI);

        spnPidValueI = new QDoubleSpinBox(grpPIDControl);
        spnPidValueI->setObjectName(QStringLiteral("spnPidValueI"));
        spnPidValueI->setSingleStep(0.01);

        horizontalLayout_5->addWidget(spnPidValueI);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        lblPidValueD = new QLabel(grpPIDControl);
        lblPidValueD->setObjectName(QStringLiteral("lblPidValueD"));

        horizontalLayout_9->addWidget(lblPidValueD);

        spnPidValueD = new QDoubleSpinBox(grpPIDControl);
        spnPidValueD->setObjectName(QStringLiteral("spnPidValueD"));
        spnPidValueD->setSingleStep(0.01);

        horizontalLayout_9->addWidget(spnPidValueD);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        lblPidSetPoint = new QLabel(grpPIDControl);
        lblPidSetPoint->setObjectName(QStringLiteral("lblPidSetPoint"));

        horizontalLayout_10->addWidget(lblPidSetPoint);

        spnPidSetpoint = new QDoubleSpinBox(grpPIDControl);
        spnPidSetpoint->setObjectName(QStringLiteral("spnPidSetpoint"));
        spnPidSetpoint->setSingleStep(0.01);

        horizontalLayout_10->addWidget(spnPidSetpoint);


        verticalLayout_3->addLayout(horizontalLayout_10);

        btnPidToggle = new QPushButton(grpPIDControl);
        btnPidToggle->setObjectName(QStringLiteral("btnPidToggle"));
        btnPidToggle->setEnabled(true);
        btnPidToggle->setStyleSheet(QStringLiteral(""));
        btnPidToggle->setCheckable(true);
        btnPidToggle->setChecked(false);

        verticalLayout_3->addWidget(btnPidToggle);


        gridLayout_5->addLayout(verticalLayout_3, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_5, 0, 0, 1, 1);


        verticalLayout_13->addWidget(grpPIDControl);

        grpScanControl = new QGroupBox(controlTab);
        grpScanControl->setObjectName(QStringLiteral("grpScanControl"));
        sizePolicy3.setHeightForWidth(grpScanControl->sizePolicy().hasHeightForWidth());
        grpScanControl->setSizePolicy(sizePolicy3);
        grpScanControl->setStyleSheet(QLatin1String("    QGroupBox  {\n"
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

        horizontalLayout_13->addWidget(spnScanVmin2);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        lblScanNumLines = new QLabel(grpScanControl);
        lblScanNumLines->setObjectName(QStringLiteral("lblScanNumLines"));

        horizontalLayout_14->addWidget(lblScanNumLines);

        spnScanNumLines = new QSpinBox(grpScanControl);
        spnScanNumLines->setObjectName(QStringLiteral("spnScanNumLines"));

        horizontalLayout_14->addWidget(spnScanNumLines);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        lblScanNumPoints = new QLabel(grpScanControl);
        lblScanNumPoints->setObjectName(QStringLiteral("lblScanNumPoints"));

        horizontalLayout_15->addWidget(lblScanNumPoints);

        spnScanNumPoints = new QSpinBox(grpScanControl);
        spnScanNumPoints->setObjectName(QStringLiteral("spnScanNumPoints"));

        horizontalLayout_15->addWidget(spnScanNumPoints);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        lblScanDelay = new QLabel(grpScanControl);
        lblScanDelay->setObjectName(QStringLiteral("lblScanDelay"));

        horizontalLayout_16->addWidget(lblScanDelay);

        spnScanDelay = new QSpinBox(grpScanControl);
        spnScanDelay->setObjectName(QStringLiteral("spnScanDelay"));

        horizontalLayout_16->addWidget(spnScanDelay);


        verticalLayout_4->addLayout(horizontalLayout_16);


        gridLayout_6->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout_13->addWidget(grpScanControl);


        horizontalLayout_33->addLayout(verticalLayout_13);

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
"                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"    }\n"
""));
        gridLayout_20 = new QGridLayout(grpMemsControl);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QStringLiteral("gridLayout_20"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        lblOffsetVoltage = new QLabel(grpMemsControl);
        lblOffsetVoltage->setObjectName(QStringLiteral("lblOffsetVoltage"));

        verticalLayout_7->addWidget(lblOffsetVoltage);

        lblBridgeVoltage = new QLabel(grpMemsControl);
        lblBridgeVoltage->setObjectName(QStringLiteral("lblBridgeVoltage"));

        verticalLayout_7->addWidget(lblBridgeVoltage);

        lblFrequencyVoltage = new QLabel(grpMemsControl);
        lblFrequencyVoltage->setObjectName(QStringLiteral("lblFrequencyVoltage"));

        verticalLayout_7->addWidget(lblFrequencyVoltage);

        lblAmplitudeVoltage = new QLabel(grpMemsControl);
        lblAmplitudeVoltage->setObjectName(QStringLiteral("lblAmplitudeVoltage"));
        lblAmplitudeVoltage->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lblAmplitudeVoltage->sizePolicy().hasHeightForWidth());
        lblAmplitudeVoltage->setSizePolicy(sizePolicy4);

        verticalLayout_7->addWidget(lblAmplitudeVoltage);


        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        spnOffsetVoltage = new QDoubleSpinBox(grpMemsControl);
        spnOffsetVoltage->setObjectName(QStringLiteral("spnOffsetVoltage"));
        spnOffsetVoltage->setDecimals(4);
        spnOffsetVoltage->setSingleStep(0.01);
        spnOffsetVoltage->setValue(0.045);

        verticalLayout_14->addWidget(spnOffsetVoltage);

        spnBridgeVoltage = new QDoubleSpinBox(grpMemsControl);
        spnBridgeVoltage->setObjectName(QStringLiteral("spnBridgeVoltage"));
        spnBridgeVoltage->setDecimals(4);
        spnBridgeVoltage->setSingleStep(0.01);
        spnBridgeVoltage->setValue(2);

        verticalLayout_14->addWidget(spnBridgeVoltage);

        spnFrequencyVoltage = new QDoubleSpinBox(grpMemsControl);
        spnFrequencyVoltage->setObjectName(QStringLiteral("spnFrequencyVoltage"));
        spnFrequencyVoltage->setDecimals(4);
        spnFrequencyVoltage->setSingleStep(0.01);

        verticalLayout_14->addWidget(spnFrequencyVoltage);

        spnFrequencyVoltage_2 = new QDoubleSpinBox(grpMemsControl);
        spnFrequencyVoltage_2->setObjectName(QStringLiteral("spnFrequencyVoltage_2"));
        spnFrequencyVoltage_2->setDecimals(4);
        spnFrequencyVoltage_2->setMaximum(3);
        spnFrequencyVoltage_2->setSingleStep(0.1);
        spnFrequencyVoltage_2->setValue(2.4);

        verticalLayout_14->addWidget(spnFrequencyVoltage_2);


        horizontalLayout->addLayout(verticalLayout_14);


        gridLayout_20->addLayout(horizontalLayout, 0, 0, 1, 1);

        label_17 = new QLabel(grpMemsControl);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_20->addWidget(label_17, 7, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        label_7 = new QLabel(grpMemsControl);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_29->addWidget(label_7);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_10);

        latSpinBox = new QDoubleSpinBox(grpMemsControl);
        latSpinBox->setObjectName(QStringLiteral("latSpinBox"));
        sizePolicy1.setHeightForWidth(latSpinBox->sizePolicy().hasHeightForWidth());
        latSpinBox->setSizePolicy(sizePolicy1);
        latSpinBox->setMaximum(3.3);
        latSpinBox->setSingleStep(0.1);

        horizontalLayout_29->addWidget(latSpinBox);

        label_10 = new QLabel(grpMemsControl);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setStyleSheet(QStringLiteral(""));
        label_10->setPixmap(QPixmap(QString::fromUtf8("../icons/1413837188_checkmark-24.png")));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_29->addWidget(label_10);


        gridLayout_7->addLayout(horizontalLayout_29, 3, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(grpMemsControl);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_7->addWidget(label_8);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        ZcoarseSpinBox = new QDoubleSpinBox(grpMemsControl);
        ZcoarseSpinBox->setObjectName(QStringLiteral("ZcoarseSpinBox"));
        sizePolicy1.setHeightForWidth(ZcoarseSpinBox->sizePolicy().hasHeightForWidth());
        ZcoarseSpinBox->setSizePolicy(sizePolicy1);
        ZcoarseSpinBox->setMaximum(3.3);
        ZcoarseSpinBox->setSingleStep(0.1);

        horizontalLayout_7->addWidget(ZcoarseSpinBox);

        label_12 = new QLabel(grpMemsControl);
        label_12->setObjectName(QStringLiteral("label_12"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy5);
        label_12->setPixmap(QPixmap(QString::fromUtf8("../icons/1413837188_checkmark-24.png")));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_12);


        gridLayout_7->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(grpMemsControl);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        ZfineSpinBox = new QDoubleSpinBox(grpMemsControl);
        ZfineSpinBox->setObjectName(QStringLiteral("ZfineSpinBox"));
        sizePolicy1.setHeightForWidth(ZfineSpinBox->sizePolicy().hasHeightForWidth());
        ZfineSpinBox->setSizePolicy(sizePolicy1);
        ZfineSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ZfineSpinBox->setMaximum(3.3);
        ZfineSpinBox->setSingleStep(0.1);

        horizontalLayout_2->addWidget(ZfineSpinBox);

        label_11 = new QLabel(grpMemsControl);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setPixmap(QPixmap(QString::fromUtf8("../icons/1413837188_checkmark-24.png")));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_11);


        gridLayout_7->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
        setMaxDACValuesButton = new QPushButton(grpMemsControl);
        setMaxDACValuesButton->setObjectName(QStringLiteral("setMaxDACValuesButton"));
        sizePolicy1.setHeightForWidth(setMaxDACValuesButton->sizePolicy().hasHeightForWidth());
        setMaxDACValuesButton->setSizePolicy(sizePolicy1);

        horizontalLayout_39->addWidget(setMaxDACValuesButton);


        gridLayout_7->addLayout(horizontalLayout_39, 4, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_7);


        gridLayout_20->addLayout(verticalLayout, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_20->addItem(verticalSpacer_3, 6, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_20->addItem(verticalSpacer_2, 1, 0, 1, 1);


        horizontalLayout_33->addWidget(grpMemsControl);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_7);


        gridLayout_28->addLayout(horizontalLayout_33, 0, 0, 1, 1);

        tabWidget->addTab(controlTab, QString());
        scanTab = new QWidget();
        scanTab->setObjectName(QStringLiteral("scanTab"));
        gridLayout_9 = new QGridLayout(scanTab);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        tabScan = new QTabWidget(scanTab);
        tabScan->setObjectName(QStringLiteral("tabScan"));
        tabScanForward = new QWidget();
        tabScanForward->setObjectName(QStringLiteral("tabScanForward"));
        tabScan->addTab(tabScanForward, QString());
        tabScanReverse = new QWidget();
        tabScanReverse->setObjectName(QStringLiteral("tabScanReverse"));
        tabScan->addTab(tabScanReverse, QString());

        gridLayout_8->addWidget(tabScan, 0, 0, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 0, 0, 1, 1);

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
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        gridLayout_16 = new QGridLayout(widget_2);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
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

        buttonSendSweep = new QPushButton(groupBox_2);
        buttonSendSweep->setObjectName(QStringLiteral("buttonSendSweep"));
        buttonSendSweep->setStyleSheet(QStringLiteral(""));

        verticalLayout_9->addWidget(buttonSendSweep);

        useCurrFreqVal = new QPushButton(groupBox_2);
        useCurrFreqVal->setObjectName(QStringLiteral("useCurrFreqVal"));
        useCurrFreqVal->setStyleSheet(QStringLiteral(""));

        verticalLayout_9->addWidget(useCurrFreqVal);


        gridLayout_14->addLayout(verticalLayout_9, 0, 0, 1, 1);

        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        gridLayout_14->addWidget(checkBox, 2, 0, 1, 1);

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

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_28->addWidget(label_23);

        startFrequency = new QSpinBox(groupBox_2);
        startFrequency->setObjectName(QStringLiteral("startFrequency"));
        startFrequency->setReadOnly(false);
        startFrequency->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        startFrequency->setMaximum(10000);
        startFrequency->setSingleStep(100);
        startFrequency->setValue(3800);

        horizontalLayout_28->addWidget(startFrequency);


        verticalLayout_8->addLayout(horizontalLayout_28);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_27->addWidget(label_22);

        stepSize = new QSpinBox(groupBox_2);
        stepSize->setObjectName(QStringLiteral("stepSize"));
        stepSize->setReadOnly(false);
        stepSize->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        stepSize->setMaximum(1000);
        stepSize->setSingleStep(5);
        stepSize->setValue(5);

        horizontalLayout_27->addWidget(stepSize);


        verticalLayout_8->addLayout(horizontalLayout_27);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_8->addWidget(label_18);

        currFreqVal = new QDoubleSpinBox(groupBox_2);
        currFreqVal->setObjectName(QStringLiteral("currFreqVal"));
        currFreqVal->setReadOnly(false);
        currFreqVal->setButtonSymbols(QAbstractSpinBox::NoButtons);
        currFreqVal->setMaximum(10000);

        horizontalLayout_8->addWidget(currFreqVal);


        verticalLayout_8->addLayout(horizontalLayout_8);


        gridLayout_14->addLayout(verticalLayout_8, 0, 1, 1, 1);


        gridLayout_15->addLayout(gridLayout_14, 0, 0, 1, 1);


        horizontalLayout_38->addLayout(gridLayout_15);


        gridLayout_16->addWidget(groupBox_2, 0, 0, 1, 1);


        horizontalLayout_31->addWidget(widget_2);

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

        groupBox = new QGroupBox(approachWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
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
        pushButton_22 = new QPushButton(groupBox);
        pushButton_22->setObjectName(QStringLiteral("pushButton_22"));
        pushButton_22->setStyleSheet(QStringLiteral(""));
        pushButton_22->setCheckable(true);

        verticalLayout_2->addWidget(pushButton_22);

        buttonCurrValuePidSetpoint = new QPushButton(groupBox);
        buttonCurrValuePidSetpoint->setObjectName(QStringLiteral("buttonCurrValuePidSetpoint"));
        buttonCurrValuePidSetpoint->setStyleSheet(QStringLiteral(""));
        buttonCurrValuePidSetpoint->setCheckable(true);

        verticalLayout_2->addWidget(buttonCurrValuePidSetpoint);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_32->addWidget(label_21);

        currPIDSetpoint = new QDoubleSpinBox(groupBox);
        currPIDSetpoint->setObjectName(QStringLiteral("currPIDSetpoint"));
        currPIDSetpoint->setReadOnly(true);
        currPIDSetpoint->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_32->addWidget(currPIDSetpoint);


        verticalLayout_2->addLayout(horizontalLayout_32);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_35->addWidget(label_24);

        comparisonValue = new QDoubleSpinBox(groupBox);
        comparisonValue->setObjectName(QStringLiteral("comparisonValue"));
        comparisonValue->setReadOnly(true);
        comparisonValue->setButtonSymbols(QAbstractSpinBox::NoButtons);
        comparisonValue->setDecimals(4);

        horizontalLayout_35->addWidget(comparisonValue);


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

        buttonAutoApproachMCU = new QPushButton(groupBox);
        buttonAutoApproachMCU->setObjectName(QStringLiteral("buttonAutoApproachMCU"));
        buttonAutoApproachMCU->setStyleSheet(QStringLiteral(""));
        buttonAutoApproachMCU->setCheckable(false);

        verticalLayout_2->addWidget(buttonAutoApproachMCU);

        buttonAutoApproachClient = new QPushButton(groupBox);
        buttonAutoApproachClient->setObjectName(QStringLiteral("buttonAutoApproachClient"));
        buttonAutoApproachClient->setStyleSheet(QStringLiteral(""));
        buttonAutoApproachClient->setCheckable(true);

        verticalLayout_2->addWidget(buttonAutoApproachClient);

        writeCharacter = new QPushButton(groupBox);
        writeCharacter->setObjectName(QStringLiteral("writeCharacter"));
        writeCharacter->setStyleSheet(QStringLiteral(""));
        writeCharacter->setCheckable(true);

        verticalLayout_2->addWidget(writeCharacter);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        sldAmplitudeVoltage_3 = new QSlider(groupBox);
        sldAmplitudeVoltage_3->setObjectName(QStringLiteral("sldAmplitudeVoltage_3"));
        sldAmplitudeVoltage_3->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"border: 1px solid #bbb;\n"
"background: white;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,\n"
"    stop: 0 #66e, stop: 1 #bbf);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #bbf, stop: 1 #55f);\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: #fff;\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #eee, stop:1 #ccc);\n"
"border: 1px solid #777;\n"
"width: 13px;\n"
"margin-top: -2px;\n"
"margin-bottom: -2px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #fff, stop:1 #ddd);\n"
"border: 1px solid #444;\n"
"border-radius: 4px;\n"
"}\n"
""
                        "\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #bbb;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}"));
        sldAmplitudeVoltage_3->setMinimum(0);
        sldAmplitudeVoltage_3->setMaximum(19);
        sldAmplitudeVoltage_3->setSingleStep(1);
        sldAmplitudeVoltage_3->setValue(0);
        sldAmplitudeVoltage_3->setOrientation(Qt::Horizontal);
        sldAmplitudeVoltage_3->setTickPosition(QSlider::TicksBelow);

        verticalLayout_6->addWidget(sldAmplitudeVoltage_3);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        lblMemsAmplitudeMinVal_3 = new QLabel(groupBox);
        lblMemsAmplitudeMinVal_3->setObjectName(QStringLiteral("lblMemsAmplitudeMinVal_3"));
        sizePolicy4.setHeightForWidth(lblMemsAmplitudeMinVal_3->sizePolicy().hasHeightForWidth());
        lblMemsAmplitudeMinVal_3->setSizePolicy(sizePolicy4);

        horizontalLayout_24->addWidget(lblMemsAmplitudeMinVal_3);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer);

        lblAmplitude = new QLabel(groupBox);
        lblAmplitude->setObjectName(QStringLiteral("lblAmplitude"));
        sizePolicy5.setHeightForWidth(lblAmplitude->sizePolicy().hasHeightForWidth());
        lblAmplitude->setSizePolicy(sizePolicy5);
        lblAmplitude->setMinimumSize(QSize(15, 0));

        horizontalLayout_24->addWidget(lblAmplitude);

        horizontalSpacer_4 = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_4);

        lblMemsAmplitudeMaxVal_3 = new QLabel(groupBox);
        lblMemsAmplitudeMaxVal_3->setObjectName(QStringLiteral("lblMemsAmplitudeMaxVal_3"));
        sizePolicy4.setHeightForWidth(lblMemsAmplitudeMaxVal_3->sizePolicy().hasHeightForWidth());
        lblMemsAmplitudeMaxVal_3->setSizePolicy(sizePolicy4);

        horizontalLayout_24->addWidget(lblMemsAmplitudeMaxVal_3);


        verticalLayout_6->addLayout(horizontalLayout_24);


        verticalLayout_21->addLayout(verticalLayout_6);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));
        stepButton = new QPushButton(groupBox);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout_43->addWidget(stepButton);

        continuousButton = new QPushButton(groupBox);
        continuousButton->setObjectName(QStringLiteral("continuousButton"));
        continuousButton->setStyleSheet(QStringLiteral(""));
        continuousButton->setCheckable(true);

        horizontalLayout_43->addWidget(continuousButton);


        verticalLayout_21->addLayout(horizontalLayout_43);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));
        retreatButton = new QRadioButton(groupBox);
        retreatButton->setObjectName(QStringLiteral("retreatButton"));
        retreatButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout_44->addWidget(retreatButton);

        approachButton = new QRadioButton(groupBox);
        approachButton->setObjectName(QStringLiteral("approachButton"));

        horizontalLayout_44->addWidget(approachButton);


        verticalLayout_21->addLayout(horizontalLayout_44);


        gridLayout->addLayout(verticalLayout_21, 0, 0, 1, 1);


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
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setStyleSheet(QStringLiteral(""));
        pushButton_5->setCheckable(true);

        horizontalLayout_20->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(signalWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setStyleSheet(QStringLiteral(""));
        pushButton_4->setCheckable(true);

        horizontalLayout_20->addWidget(pushButton_4);


        gridLayout_10->addLayout(horizontalLayout_20, 0, 0, 1, 1);


        gridLayout_12->addLayout(gridLayout_10, 0, 0, 1, 1);


        gridLayout_26->addWidget(signalWidget, 0, 0, 1, 1);

        tabWidget->addTab(tabSignal, QString());
        testTab = new QWidget();
        testTab->setObjectName(QStringLiteral("testTab"));
        layoutWidget = new QWidget(testTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 80, 307, 123));
        horizontalLayout_26 = new QHBoxLayout(layoutWidget);
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
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        dacNumber = new QSpinBox(layoutWidget);
        dacNumber->setObjectName(QStringLiteral("dacNumber"));

        horizontalLayout_3->addWidget(dacNumber);


        verticalLayout_10->addLayout(horizontalLayout_3);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_19->addWidget(label_2);

        adcNumber = new QSpinBox(layoutWidget);
        adcNumber->setObjectName(QStringLiteral("adcNumber"));

        horizontalLayout_19->addWidget(adcNumber);


        verticalLayout_10->addLayout(horizontalLayout_19);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_25->addWidget(label_6);

        valToWrite = new QDoubleSpinBox(layoutWidget);
        valToWrite->setObjectName(QStringLiteral("valToWrite"));
        valToWrite->setMaximum(2.5);
        valToWrite->setSingleStep(0.25);

        horizontalLayout_25->addWidget(valToWrite);


        verticalLayout_10->addLayout(horizontalLayout_25);

        buttonWriteToDAC = new QPushButton(layoutWidget);
        buttonWriteToDAC->setObjectName(QStringLiteral("buttonWriteToDAC"));
        buttonWriteToDAC->setStyleSheet(QStringLiteral(""));

        verticalLayout_10->addWidget(buttonWriteToDAC);


        horizontalLayout_26->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_21->addWidget(label_3);

        dacValue = new QDoubleSpinBox(layoutWidget);
        dacValue->setObjectName(QStringLiteral("dacValue"));

        horizontalLayout_21->addWidget(dacValue);


        verticalLayout_11->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_22->addWidget(label_5);

        adcValue = new QDoubleSpinBox(layoutWidget);
        adcValue->setObjectName(QStringLiteral("adcValue"));

        horizontalLayout_22->addWidget(adcValue);


        verticalLayout_11->addLayout(horizontalLayout_22);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_4);

        buttonReadIO = new QPushButton(layoutWidget);
        buttonReadIO->setObjectName(QStringLiteral("buttonReadIO"));
        buttonReadIO->setStyleSheet(QStringLiteral(""));

        verticalLayout_11->addWidget(buttonReadIO);


        horizontalLayout_26->addLayout(verticalLayout_11);

        tabWidget->addTab(testTab, QString());

        horizontalLayout_37->addWidget(tabWidget);

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
        MainWindow->setStatusBar(statusBar);

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

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);
        tabScan->setCurrentIndex(0);


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
        label_4->setText(QApplication::translate("MainWindow", "Plot Refresh (ms):", 0));
        lblComPortSelection->setText(QApplication::translate("MainWindow", "COM:", 0));
        cboComPortSelection->setCurrentText(QString());
        label_14->setText(QApplication::translate("MainWindow", "Calibrated:", 0));
        label_13->setText(QString());
        pushButton_6->setText(QApplication::translate("MainWindow", "SCAN", 0));
        grpPIDControl->setTitle(QApplication::translate("MainWindow", "PID Control", 0));
        lblPidValueP->setText(QApplication::translate("MainWindow", "P:", 0));
        lblPidValueI->setText(QApplication::translate("MainWindow", "I:", 0));
        lblPidValueD->setText(QApplication::translate("MainWindow", "D:", 0));
        lblPidSetPoint->setText(QApplication::translate("MainWindow", "Setpoint:", 0));
        btnPidToggle->setText(QApplication::translate("MainWindow", "PID", 0));
        grpScanControl->setTitle(QApplication::translate("MainWindow", "Scan Control", 0));
        lblScanVmaxV->setText(QApplication::translate("MainWindow", "Vmax (V):", 0));
        lblVminV->setText(QApplication::translate("MainWindow", "Vmin (V):", 0));
        lblScanVmin2->setText(QApplication::translate("MainWindow", "Vmin2 (V):", 0));
        lblScanNumLines->setText(QApplication::translate("MainWindow", "Num Lines:", 0));
        lblScanNumPoints->setText(QApplication::translate("MainWindow", "Num Points:", 0));
        lblScanDelay->setText(QApplication::translate("MainWindow", "Wait Time (ms):", 0));
        grpMemsControl->setTitle(QApplication::translate("MainWindow", "MEMS Control", 0));
        lblOffsetVoltage->setText(QApplication::translate("MainWindow", "Offset (V):", 0));
        lblBridgeVoltage->setText(QApplication::translate("MainWindow", "Bridge Voltage (V):", 0));
        lblFrequencyVoltage->setText(QApplication::translate("MainWindow", "Frequency (V):", 0));
        lblAmplitudeVoltage->setText(QApplication::translate("MainWindow", "Amplitude (V):", 0));
        label_17->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Vmax Lat:", 0));
        label_10->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Vmax Z Coarse:", 0));
        label_12->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Vmax ZFine:", 0));
        label_11->setText(QString());
        setMaxDACValuesButton->setText(QApplication::translate("MainWindow", "Set Values", 0));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "Control Setup", 0));
        tabScan->setTabText(tabScan->indexOf(tabScanForward), QApplication::translate("MainWindow", "Forward", 0));
        tabScan->setTabText(tabScan->indexOf(tabScanReverse), QApplication::translate("MainWindow", "Reverse", 0));
        tabWidget->setTabText(tabWidget->indexOf(scanTab), QApplication::translate("MainWindow", "Scan", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        label_20->setText(QApplication::translate("MainWindow", "Number of Points:", 0));
        sweepButton->setText(QApplication::translate("MainWindow", "Sweep", 0));
        freqAutoScale->setText(QApplication::translate("MainWindow", "Auto Scale", 0));
        buttonSendSweep->setText(QApplication::translate("MainWindow", "Send Sweep Data", 0));
        useCurrFreqVal->setText(QApplication::translate("MainWindow", "Use Current Freq Value", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Show Marker", 0));
        label_19->setText(QApplication::translate("MainWindow", "In Progress:", 0));
        freqProgressLabel->setText(QApplication::translate("MainWindow", "FALSE", 0));
        label_23->setText(QApplication::translate("MainWindow", "Start Frequency (Hz):", 0));
        label_22->setText(QApplication::translate("MainWindow", "Step Size (Hz):", 0));
        label_18->setText(QApplication::translate("MainWindow", "Current Freq Value:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabFreqSweep), QApplication::translate("MainWindow", "Frequency Sweep", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Coarse Approach", 0));
        pushButton_22->setText(QApplication::translate("MainWindow", "Auto Scale", 0));
        buttonCurrValuePidSetpoint->setText(QApplication::translate("MainWindow", "Current Value as PID Setpoint", 0));
        label_21->setText(QApplication::translate("MainWindow", "Curr PID Setpoint:", 0));
        label_24->setText(QApplication::translate("MainWindow", "Comparison Value:", 0));
        label_25->setText(QApplication::translate("MainWindow", "Current Value:", 0));
        buttonAutoApproachMCU->setText(QApplication::translate("MainWindow", "Auto Approach MCU", 0));
        buttonAutoApproachClient->setText(QApplication::translate("MainWindow", "Auto Approach Client", 0));
        writeCharacter->setText(QApplication::translate("MainWindow", "Write Character", 0));
        lblMemsAmplitudeMinVal_3->setText(QApplication::translate("MainWindow", "S", 0));
        lblAmplitude->setText(QApplication::translate("MainWindow", "0", 0));
        lblMemsAmplitudeMaxVal_3->setText(QApplication::translate("MainWindow", "F", 0));
        stepButton->setText(QApplication::translate("MainWindow", "Step", 0));
        continuousButton->setText(QApplication::translate("MainWindow", "Cont", 0));
        retreatButton->setText(QApplication::translate("MainWindow", "Retr", 0));
        approachButton->setText(QApplication::translate("MainWindow", "Appr", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabApproach), QApplication::translate("MainWindow", "Approach", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Autoscale Offset", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Autoscale Error", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabSignal), QApplication::translate("MainWindow", "Signal", 0));
        label->setText(QApplication::translate("MainWindow", "DAC #", 0));
        label_2->setText(QApplication::translate("MainWindow", "ADC #", 0));
        label_6->setText(QApplication::translate("MainWindow", "Value to Write", 0));
        buttonWriteToDAC->setText(QApplication::translate("MainWindow", "Write to DAC", 0));
        label_3->setText(QApplication::translate("MainWindow", "DAC Value", 0));
        label_5->setText(QApplication::translate("MainWindow", "ADC Value", 0));
        buttonReadIO->setText(QApplication::translate("MainWindow", "Read from DAC/ADC", 0));
        tabWidget->setTabText(tabWidget->indexOf(testTab), QApplication::translate("MainWindow", "Test", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
