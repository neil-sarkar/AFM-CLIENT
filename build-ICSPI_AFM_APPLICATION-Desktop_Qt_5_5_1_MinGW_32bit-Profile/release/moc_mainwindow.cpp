/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[118];
    char stringdata0[2757];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "finished"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 13), // "SweepFinished"
QT_MOC_LITERAL(4, 35, 15), // "updateStatusBar"
QT_MOC_LITERAL(5, 51, 7), // "_string"
QT_MOC_LITERAL(6, 59, 13), // "pickPlotStyle"
QT_MOC_LITERAL(7, 73, 8), // "QAction*"
QT_MOC_LITERAL(8, 82, 11), // "setLeftGrid"
QT_MOC_LITERAL(9, 94, 1), // "b"
QT_MOC_LITERAL(10, 96, 12), // "setRightGrid"
QT_MOC_LITERAL(11, 109, 11), // "setCeilGrid"
QT_MOC_LITERAL(12, 121, 12), // "setFloorGrid"
QT_MOC_LITERAL(13, 134, 12), // "setFrontGrid"
QT_MOC_LITERAL(14, 147, 11), // "setBackGrid"
QT_MOC_LITERAL(15, 159, 7), // "setGrid"
QT_MOC_LITERAL(16, 167, 11), // "Qwt3D::SIDE"
QT_MOC_LITERAL(17, 179, 15), // "pickCoordSystem"
QT_MOC_LITERAL(18, 195, 14), // "pickFloorStyle"
QT_MOC_LITERAL(19, 210, 11), // "showNormals"
QT_MOC_LITERAL(20, 222, 3), // "val"
QT_MOC_LITERAL(21, 226, 11), // "serialError"
QT_MOC_LITERAL(22, 238, 14), // "afmWorkerError"
QT_MOC_LITERAL(23, 253, 15), // "setDDSFrequency"
QT_MOC_LITERAL(24, 269, 1), // "p"
QT_MOC_LITERAL(25, 271, 10), // "updatePlot"
QT_MOC_LITERAL(26, 282, 7), // "_signal"
QT_MOC_LITERAL(27, 290, 5), // "_plot"
QT_MOC_LITERAL(28, 296, 14), // "MainWindowLoop"
QT_MOC_LITERAL(29, 311, 19), // "dequeueReturnBuffer"
QT_MOC_LITERAL(30, 331, 18), // "generalTimerUpdate"
QT_MOC_LITERAL(31, 350, 15), // "approachTimerUp"
QT_MOC_LITERAL(32, 366, 14), // "finishedThread"
QT_MOC_LITERAL(33, 381, 26), // "autoApproach_state_machine"
QT_MOC_LITERAL(34, 408, 29), // "stepmot_user_control_callback"
QT_MOC_LITERAL(35, 438, 18), // "scan_state_machine"
QT_MOC_LITERAL(36, 457, 33), // "on_sld_stepmot_speed_valueCha..."
QT_MOC_LITERAL(37, 491, 5), // "value"
QT_MOC_LITERAL(38, 497, 36), // "on_cbo_microstep_currentIndex..."
QT_MOC_LITERAL(39, 534, 5), // "index"
QT_MOC_LITERAL(40, 540, 30), // "on_btn_stepmot_cont_go_clicked"
QT_MOC_LITERAL(41, 571, 32), // "on_btn_stepmot_cont_stop_clicked"
QT_MOC_LITERAL(42, 604, 33), // "on_btn_stepmot_singlestep_cli..."
QT_MOC_LITERAL(43, 638, 28), // "on_radio_stepmot_fwd_clicked"
QT_MOC_LITERAL(44, 667, 29), // "on_radio_stepmot_back_clicked"
QT_MOC_LITERAL(45, 697, 28), // "on_btn_stepmot_sleep_clicked"
QT_MOC_LITERAL(46, 726, 27), // "on_btn_stepmot_wake_clicked"
QT_MOC_LITERAL(47, 754, 26), // "on_btn_autoappr_go_clicked"
QT_MOC_LITERAL(48, 781, 28), // "on_btn_autoappr_stop_clicked"
QT_MOC_LITERAL(49, 810, 24), // "on_retreatButton_clicked"
QT_MOC_LITERAL(50, 835, 21), // "on_stepButton_clicked"
QT_MOC_LITERAL(51, 857, 32), // "on_spnOffsetVoltage_valueChanged"
QT_MOC_LITERAL(52, 890, 4), // "arg1"
QT_MOC_LITERAL(53, 895, 32), // "on_spnBridgeVoltage_valueChanged"
QT_MOC_LITERAL(54, 928, 28), // "on_spnPidValueP_valueChanged"
QT_MOC_LITERAL(55, 957, 28), // "on_spnPidValueI_valueChanged"
QT_MOC_LITERAL(56, 986, 28), // "on_spnPidValueD_valueChanged"
QT_MOC_LITERAL(57, 1015, 30), // "on_spnPidSetpoint_valueChanged"
QT_MOC_LITERAL(58, 1046, 42), // "on_cboComPortSelection_curren..."
QT_MOC_LITERAL(59, 1089, 30), // "on_refreshSpinBox_valueChanged"
QT_MOC_LITERAL(60, 1120, 24), // "on_pushButton_22_clicked"
QT_MOC_LITERAL(61, 1145, 7), // "checked"
QT_MOC_LITERAL(62, 1153, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(63, 1177, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(64, 1201, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(65, 1221, 22), // "on_sweepButton_clicked"
QT_MOC_LITERAL(66, 1244, 25), // "on_useCurrFreqVal_clicked"
QT_MOC_LITERAL(67, 1270, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(68, 1294, 27), // "on_buttonWriteToDAC_clicked"
QT_MOC_LITERAL(69, 1322, 23), // "on_buttonReadIO_clicked"
QT_MOC_LITERAL(70, 1346, 24), // "on_freqAutoScale_clicked"
QT_MOC_LITERAL(71, 1371, 37), // "on_spnFrequencyVoltage_2_valu..."
QT_MOC_LITERAL(72, 1409, 32), // "on_buttonAutoApproachMCU_clicked"
QT_MOC_LITERAL(73, 1442, 25), // "on_approachButton_clicked"
QT_MOC_LITERAL(74, 1468, 32), // "on_setMaxDACValuesButton_clicked"
QT_MOC_LITERAL(75, 1501, 26), // "on_calibrateButton_clicked"
QT_MOC_LITERAL(76, 1528, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(77, 1556, 27), // "on_continuousButton_pressed"
QT_MOC_LITERAL(78, 1584, 28), // "on_continuousButton_released"
QT_MOC_LITERAL(79, 1613, 25), // "on_gwyddionButton_clicked"
QT_MOC_LITERAL(80, 1639, 32), // "on_spnBoxFineZRange_valueChanged"
QT_MOC_LITERAL(81, 1672, 29), // "on_spnBoxCoarseZ_valueChanged"
QT_MOC_LITERAL(82, 1702, 27), // "on_spnBoxFineZ_valueChanged"
QT_MOC_LITERAL(83, 1730, 31), // "on_btnSetScanParameters_clicked"
QT_MOC_LITERAL(84, 1762, 35), // "on_spnFrequencyVoltage_valueC..."
QT_MOC_LITERAL(85, 1798, 24), // "on_btnForceCurve_clicked"
QT_MOC_LITERAL(86, 1823, 21), // "on_btn_pid_on_clicked"
QT_MOC_LITERAL(87, 1845, 22), // "on_btn_pid_off_clicked"
QT_MOC_LITERAL(88, 1868, 32), // "on_btn_stepmot_user_up_2_pressed"
QT_MOC_LITERAL(89, 1901, 33), // "on_btn_stepmot_user_up_2_rele..."
QT_MOC_LITERAL(90, 1935, 36), // "on_sld_stepmot_user_spd_value..."
QT_MOC_LITERAL(91, 1972, 30), // "on_btn_stepmot_user_up_pressed"
QT_MOC_LITERAL(92, 2003, 31), // "on_btn_stepmot_user_up_released"
QT_MOC_LITERAL(93, 2035, 32), // "on_btn_stepmot_user_down_pressed"
QT_MOC_LITERAL(94, 2068, 33), // "on_btn_stepmot_user_down_rele..."
QT_MOC_LITERAL(95, 2102, 29), // "on_btn_auto_freqsweep_clicked"
QT_MOC_LITERAL(96, 2132, 26), // "on_btn_setDACTable_clicked"
QT_MOC_LITERAL(97, 2159, 21), // "on_btn_siggen_clicked"
QT_MOC_LITERAL(98, 2181, 25), // "on_btn_scan_start_clicked"
QT_MOC_LITERAL(99, 2207, 24), // "on_btn_scan_next_clicked"
QT_MOC_LITERAL(100, 2232, 22), // "on_btn_re_init_clicked"
QT_MOC_LITERAL(101, 2255, 25), // "on_btn_scan_begin_clicked"
QT_MOC_LITERAL(102, 2281, 24), // "on_btn_scan_stop_clicked"
QT_MOC_LITERAL(103, 2306, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(104, 2328, 27), // "on_btn_print_offset_clicked"
QT_MOC_LITERAL(105, 2356, 22), // "on_btn_set_pga_clicked"
QT_MOC_LITERAL(106, 2379, 32), // "on_spnPidSetpoint_2_valueChanged"
QT_MOC_LITERAL(107, 2412, 34), // "on_btn_appr_plot_autoscale_cl..."
QT_MOC_LITERAL(108, 2447, 30), // "on_btn_appr_plot_clear_clicked"
QT_MOC_LITERAL(109, 2478, 33), // "on_btn_autoappr_mcu_start_cli..."
QT_MOC_LITERAL(110, 2512, 32), // "on_btn_autoappr_mcu_stop_clicked"
QT_MOC_LITERAL(111, 2545, 35), // "on_btn_autoappr_mcu_start_2_c..."
QT_MOC_LITERAL(112, 2581, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(113, 2605, 25), // "on_btn_save_gxyzf_clicked"
QT_MOC_LITERAL(114, 2631, 25), // "on_btn_save_txt_1_clicked"
QT_MOC_LITERAL(115, 2657, 25), // "on_btn_save_txt_2_clicked"
QT_MOC_LITERAL(116, 2683, 37), // "on_spn_test_dac_coarse_z_valu..."
QT_MOC_LITERAL(117, 2721, 35) // "on_spn_test_dac_fine_z_valueC..."

    },
    "MainWindow\0finished\0\0SweepFinished\0"
    "updateStatusBar\0_string\0pickPlotStyle\0"
    "QAction*\0setLeftGrid\0b\0setRightGrid\0"
    "setCeilGrid\0setFloorGrid\0setFrontGrid\0"
    "setBackGrid\0setGrid\0Qwt3D::SIDE\0"
    "pickCoordSystem\0pickFloorStyle\0"
    "showNormals\0val\0serialError\0afmWorkerError\0"
    "setDDSFrequency\0p\0updatePlot\0_signal\0"
    "_plot\0MainWindowLoop\0dequeueReturnBuffer\0"
    "generalTimerUpdate\0approachTimerUp\0"
    "finishedThread\0autoApproach_state_machine\0"
    "stepmot_user_control_callback\0"
    "scan_state_machine\0on_sld_stepmot_speed_valueChanged\0"
    "value\0on_cbo_microstep_currentIndexChanged\0"
    "index\0on_btn_stepmot_cont_go_clicked\0"
    "on_btn_stepmot_cont_stop_clicked\0"
    "on_btn_stepmot_singlestep_clicked\0"
    "on_radio_stepmot_fwd_clicked\0"
    "on_radio_stepmot_back_clicked\0"
    "on_btn_stepmot_sleep_clicked\0"
    "on_btn_stepmot_wake_clicked\0"
    "on_btn_autoappr_go_clicked\0"
    "on_btn_autoappr_stop_clicked\0"
    "on_retreatButton_clicked\0on_stepButton_clicked\0"
    "on_spnOffsetVoltage_valueChanged\0arg1\0"
    "on_spnBridgeVoltage_valueChanged\0"
    "on_spnPidValueP_valueChanged\0"
    "on_spnPidValueI_valueChanged\0"
    "on_spnPidValueD_valueChanged\0"
    "on_spnPidSetpoint_valueChanged\0"
    "on_cboComPortSelection_currentIndexChanged\0"
    "on_refreshSpinBox_valueChanged\0"
    "on_pushButton_22_clicked\0checked\0"
    "on_pushButton_4_clicked\0on_pushButton_5_clicked\0"
    "on_checkBox_clicked\0on_sweepButton_clicked\0"
    "on_useCurrFreqVal_clicked\0"
    "on_pushButton_6_clicked\0"
    "on_buttonWriteToDAC_clicked\0"
    "on_buttonReadIO_clicked\0"
    "on_freqAutoScale_clicked\0"
    "on_spnFrequencyVoltage_2_valueChanged\0"
    "on_buttonAutoApproachMCU_clicked\0"
    "on_approachButton_clicked\0"
    "on_setMaxDACValuesButton_clicked\0"
    "on_calibrateButton_clicked\0"
    "on_tabWidget_currentChanged\0"
    "on_continuousButton_pressed\0"
    "on_continuousButton_released\0"
    "on_gwyddionButton_clicked\0"
    "on_spnBoxFineZRange_valueChanged\0"
    "on_spnBoxCoarseZ_valueChanged\0"
    "on_spnBoxFineZ_valueChanged\0"
    "on_btnSetScanParameters_clicked\0"
    "on_spnFrequencyVoltage_valueChanged\0"
    "on_btnForceCurve_clicked\0on_btn_pid_on_clicked\0"
    "on_btn_pid_off_clicked\0"
    "on_btn_stepmot_user_up_2_pressed\0"
    "on_btn_stepmot_user_up_2_released\0"
    "on_sld_stepmot_user_spd_valueChanged\0"
    "on_btn_stepmot_user_up_pressed\0"
    "on_btn_stepmot_user_up_released\0"
    "on_btn_stepmot_user_down_pressed\0"
    "on_btn_stepmot_user_down_released\0"
    "on_btn_auto_freqsweep_clicked\0"
    "on_btn_setDACTable_clicked\0"
    "on_btn_siggen_clicked\0on_btn_scan_start_clicked\0"
    "on_btn_scan_next_clicked\0"
    "on_btn_re_init_clicked\0on_btn_scan_begin_clicked\0"
    "on_btn_scan_stop_clicked\0on_pushButton_clicked\0"
    "on_btn_print_offset_clicked\0"
    "on_btn_set_pga_clicked\0"
    "on_spnPidSetpoint_2_valueChanged\0"
    "on_btn_appr_plot_autoscale_clicked\0"
    "on_btn_appr_plot_clear_clicked\0"
    "on_btn_autoappr_mcu_start_clicked\0"
    "on_btn_autoappr_mcu_stop_clicked\0"
    "on_btn_autoappr_mcu_start_2_clicked\0"
    "on_pushButton_3_clicked\0"
    "on_btn_save_gxyzf_clicked\0"
    "on_btn_save_txt_1_clicked\0"
    "on_btn_save_txt_2_clicked\0"
    "on_spn_test_dac_coarse_z_valueChanged\0"
    "on_spn_test_dac_fine_z_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     104,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  534,    2, 0x06 /* Public */,
       3,    0,  535,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  536,    2, 0x0a /* Public */,
       6,    1,  539,    2, 0x0a /* Public */,
       8,    1,  542,    2, 0x0a /* Public */,
      10,    1,  545,    2, 0x0a /* Public */,
      11,    1,  548,    2, 0x0a /* Public */,
      12,    1,  551,    2, 0x0a /* Public */,
      13,    1,  554,    2, 0x0a /* Public */,
      14,    1,  557,    2, 0x0a /* Public */,
      15,    2,  560,    2, 0x0a /* Public */,
      17,    1,  565,    2, 0x0a /* Public */,
      18,    1,  568,    2, 0x0a /* Public */,
      19,    1,  571,    2, 0x0a /* Public */,
      21,    0,  574,    2, 0x0a /* Public */,
      22,    0,  575,    2, 0x0a /* Public */,
      23,    1,  576,    2, 0x0a /* Public */,
      25,    2,  579,    2, 0x0a /* Public */,
      28,    0,  584,    2, 0x08 /* Private */,
      29,    0,  585,    2, 0x08 /* Private */,
      30,    0,  586,    2, 0x08 /* Private */,
      31,    0,  587,    2, 0x08 /* Private */,
      32,    0,  588,    2, 0x08 /* Private */,
      33,    0,  589,    2, 0x08 /* Private */,
      34,    0,  590,    2, 0x08 /* Private */,
      35,    0,  591,    2, 0x08 /* Private */,
      36,    1,  592,    2, 0x08 /* Private */,
      38,    1,  595,    2, 0x08 /* Private */,
      40,    0,  598,    2, 0x08 /* Private */,
      41,    0,  599,    2, 0x08 /* Private */,
      42,    0,  600,    2, 0x08 /* Private */,
      43,    0,  601,    2, 0x08 /* Private */,
      44,    0,  602,    2, 0x08 /* Private */,
      45,    0,  603,    2, 0x08 /* Private */,
      46,    0,  604,    2, 0x08 /* Private */,
      47,    0,  605,    2, 0x08 /* Private */,
      48,    0,  606,    2, 0x08 /* Private */,
      49,    0,  607,    2, 0x08 /* Private */,
      50,    0,  608,    2, 0x08 /* Private */,
      51,    1,  609,    2, 0x08 /* Private */,
      53,    1,  612,    2, 0x08 /* Private */,
      54,    1,  615,    2, 0x08 /* Private */,
      55,    1,  618,    2, 0x08 /* Private */,
      56,    1,  621,    2, 0x08 /* Private */,
      57,    1,  624,    2, 0x08 /* Private */,
      58,    1,  627,    2, 0x08 /* Private */,
      59,    1,  630,    2, 0x08 /* Private */,
      60,    1,  633,    2, 0x08 /* Private */,
      62,    1,  636,    2, 0x08 /* Private */,
      63,    1,  639,    2, 0x08 /* Private */,
      64,    1,  642,    2, 0x08 /* Private */,
      65,    0,  645,    2, 0x08 /* Private */,
      66,    0,  646,    2, 0x08 /* Private */,
      67,    0,  647,    2, 0x08 /* Private */,
      68,    0,  648,    2, 0x08 /* Private */,
      69,    0,  649,    2, 0x08 /* Private */,
      70,    0,  650,    2, 0x08 /* Private */,
      71,    1,  651,    2, 0x08 /* Private */,
      72,    1,  654,    2, 0x08 /* Private */,
      73,    0,  657,    2, 0x08 /* Private */,
      74,    0,  658,    2, 0x08 /* Private */,
      75,    0,  659,    2, 0x08 /* Private */,
      76,    1,  660,    2, 0x08 /* Private */,
      77,    0,  663,    2, 0x08 /* Private */,
      78,    0,  664,    2, 0x08 /* Private */,
      79,    0,  665,    2, 0x08 /* Private */,
      80,    1,  666,    2, 0x08 /* Private */,
      81,    1,  669,    2, 0x08 /* Private */,
      82,    1,  672,    2, 0x08 /* Private */,
      83,    0,  675,    2, 0x08 /* Private */,
      84,    1,  676,    2, 0x08 /* Private */,
      85,    0,  679,    2, 0x08 /* Private */,
      86,    0,  680,    2, 0x08 /* Private */,
      87,    0,  681,    2, 0x08 /* Private */,
      88,    0,  682,    2, 0x08 /* Private */,
      89,    0,  683,    2, 0x08 /* Private */,
      90,    1,  684,    2, 0x08 /* Private */,
      91,    0,  687,    2, 0x08 /* Private */,
      92,    0,  688,    2, 0x08 /* Private */,
      93,    0,  689,    2, 0x08 /* Private */,
      94,    0,  690,    2, 0x08 /* Private */,
      95,    0,  691,    2, 0x08 /* Private */,
      96,    0,  692,    2, 0x08 /* Private */,
      97,    0,  693,    2, 0x08 /* Private */,
      98,    0,  694,    2, 0x08 /* Private */,
      99,    0,  695,    2, 0x08 /* Private */,
     100,    0,  696,    2, 0x08 /* Private */,
     101,    0,  697,    2, 0x08 /* Private */,
     102,    0,  698,    2, 0x08 /* Private */,
     103,    0,  699,    2, 0x08 /* Private */,
     104,    0,  700,    2, 0x08 /* Private */,
     105,    0,  701,    2, 0x08 /* Private */,
     106,    1,  702,    2, 0x08 /* Private */,
     107,    0,  705,    2, 0x08 /* Private */,
     108,    0,  706,    2, 0x08 /* Private */,
     109,    0,  707,    2, 0x08 /* Private */,
     110,    0,  708,    2, 0x08 /* Private */,
     111,    0,  709,    2, 0x08 /* Private */,
     112,    0,  710,    2, 0x08 /* Private */,
     113,    0,  711,    2, 0x08 /* Private */,
     114,    0,  712,    2, 0x08 /* Private */,
     115,    0,  713,    2, 0x08 /* Private */,
     116,    1,  714,    2, 0x08 /* Private */,
     117,    1,  717,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Bool,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF,   24,
    QMetaType::Void, QMetaType::Double, QMetaType::Int,   26,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   52,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   52,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->SweepFinished(); break;
        case 2: _t->updateStatusBar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->pickPlotStyle((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->setLeftGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setRightGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setCeilGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setFloorGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setFrontGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setBackGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setGrid((*reinterpret_cast< Qwt3D::SIDE(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->pickCoordSystem((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 12: _t->pickFloorStyle((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 13: _t->showNormals((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->serialError(); break;
        case 15: _t->afmWorkerError(); break;
        case 16: _t->setDDSFrequency((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 17: _t->updatePlot((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->MainWindowLoop(); break;
        case 19: _t->dequeueReturnBuffer(); break;
        case 20: _t->generalTimerUpdate(); break;
        case 21: _t->approachTimerUp(); break;
        case 22: _t->finishedThread(); break;
        case 23: _t->autoApproach_state_machine(); break;
        case 24: _t->stepmot_user_control_callback(); break;
        case 25: _t->scan_state_machine(); break;
        case 26: _t->on_sld_stepmot_speed_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_cbo_microstep_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_btn_stepmot_cont_go_clicked(); break;
        case 29: _t->on_btn_stepmot_cont_stop_clicked(); break;
        case 30: _t->on_btn_stepmot_singlestep_clicked(); break;
        case 31: _t->on_radio_stepmot_fwd_clicked(); break;
        case 32: _t->on_radio_stepmot_back_clicked(); break;
        case 33: _t->on_btn_stepmot_sleep_clicked(); break;
        case 34: _t->on_btn_stepmot_wake_clicked(); break;
        case 35: _t->on_btn_autoappr_go_clicked(); break;
        case 36: _t->on_btn_autoappr_stop_clicked(); break;
        case 37: _t->on_retreatButton_clicked(); break;
        case 38: _t->on_stepButton_clicked(); break;
        case 39: _t->on_spnOffsetVoltage_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 40: _t->on_spnBridgeVoltage_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 41: _t->on_spnPidValueP_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 42: _t->on_spnPidValueI_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 43: _t->on_spnPidValueD_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 44: _t->on_spnPidSetpoint_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 45: _t->on_cboComPortSelection_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: _t->on_refreshSpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: _t->on_pushButton_22_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->on_pushButton_4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: _t->on_pushButton_5_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 51: _t->on_sweepButton_clicked(); break;
        case 52: _t->on_useCurrFreqVal_clicked(); break;
        case 53: _t->on_pushButton_6_clicked(); break;
        case 54: _t->on_buttonWriteToDAC_clicked(); break;
        case 55: _t->on_buttonReadIO_clicked(); break;
        case 56: _t->on_freqAutoScale_clicked(); break;
        case 57: _t->on_spnFrequencyVoltage_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 58: _t->on_buttonAutoApproachMCU_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->on_approachButton_clicked(); break;
        case 60: _t->on_setMaxDACValuesButton_clicked(); break;
        case 61: _t->on_calibrateButton_clicked(); break;
        case 62: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->on_continuousButton_pressed(); break;
        case 64: _t->on_continuousButton_released(); break;
        case 65: _t->on_gwyddionButton_clicked(); break;
        case 66: _t->on_spnBoxFineZRange_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->on_spnBoxCoarseZ_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 68: _t->on_spnBoxFineZ_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 69: _t->on_btnSetScanParameters_clicked(); break;
        case 70: _t->on_spnFrequencyVoltage_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 71: _t->on_btnForceCurve_clicked(); break;
        case 72: _t->on_btn_pid_on_clicked(); break;
        case 73: _t->on_btn_pid_off_clicked(); break;
        case 74: _t->on_btn_stepmot_user_up_2_pressed(); break;
        case 75: _t->on_btn_stepmot_user_up_2_released(); break;
        case 76: _t->on_sld_stepmot_user_spd_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->on_btn_stepmot_user_up_pressed(); break;
        case 78: _t->on_btn_stepmot_user_up_released(); break;
        case 79: _t->on_btn_stepmot_user_down_pressed(); break;
        case 80: _t->on_btn_stepmot_user_down_released(); break;
        case 81: _t->on_btn_auto_freqsweep_clicked(); break;
        case 82: _t->on_btn_setDACTable_clicked(); break;
        case 83: _t->on_btn_siggen_clicked(); break;
        case 84: _t->on_btn_scan_start_clicked(); break;
        case 85: _t->on_btn_scan_next_clicked(); break;
        case 86: _t->on_btn_re_init_clicked(); break;
        case 87: _t->on_btn_scan_begin_clicked(); break;
        case 88: _t->on_btn_scan_stop_clicked(); break;
        case 89: _t->on_pushButton_clicked(); break;
        case 90: _t->on_btn_print_offset_clicked(); break;
        case 91: _t->on_btn_set_pga_clicked(); break;
        case 92: _t->on_spnPidSetpoint_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 93: _t->on_btn_appr_plot_autoscale_clicked(); break;
        case 94: _t->on_btn_appr_plot_clear_clicked(); break;
        case 95: _t->on_btn_autoappr_mcu_start_clicked(); break;
        case 96: _t->on_btn_autoappr_mcu_stop_clicked(); break;
        case 97: _t->on_btn_autoappr_mcu_start_2_clicked(); break;
        case 98: _t->on_pushButton_3_clicked(); break;
        case 99: _t->on_btn_save_gxyzf_clicked(); break;
        case 100: _t->on_btn_save_txt_1_clicked(); break;
        case 101: _t->on_btn_save_txt_2_clicked(); break;
        case 102: _t->on_spn_test_dac_coarse_z_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 103: _t->on_spn_test_dac_fine_z_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SweepFinished)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 104)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 104;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 104)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 104;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::SweepFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
