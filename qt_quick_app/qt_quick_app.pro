TEMPLATE = app

QT += qml quick
QT += serialport
QT += concurrent
QT += network webkitwidgets widgets
QT += script
CONFIG += c++11

DESTDIR = $$PWD

SOURCES += main.cpp \
    receiver.cpp \
    serial_port.cpp \
    adc.cpp \
    motor.cpp \
    afm.cpp \
    dac.cpp \
    send_worker.cpp \
    receive_worker.cpp \
    pga.cpp \
    pid.cpp \
    builder.cpp \
    afm_object.cpp \
    constants.cpp \
    command_node.cpp \
    dds.cpp \
    sweeper.cpp \
    approacher.cpp \
    scanner.cpp \
    scan_data.cpp \
    mainwindow.cpp

RESOURCES += qml.qrc \
    assets.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    receiver.h \
    serial_port.h \
    serial_port_constants.h \
    adc.h \
    motor.h \
    afm.h \
    dac.h \
    command_node.h \
    motor_constants.h \
    send_worker.h \
    thread_safe_queue.h \
    receive_worker.h \
    pga.h \
    pid.h \
    builder.h \
    afm_object.h \
    constants.h \
    dds.h \
    sweeper.h \
    approacher.h \
    scanner.h \
    scan_data.h \
    data_point.h \
    mainwindow.h

DISTFILES += \
    test.html \
    sweep.html \
    styles.css
