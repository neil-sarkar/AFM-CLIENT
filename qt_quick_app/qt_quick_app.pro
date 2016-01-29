TEMPLATE = app

QT += qml quick
QT += serialport
CONFIG += c++11

SOURCES += main.cpp \
    receiver.cpp \
    serial_port.cpp \
    adc.cpp \
    pid.cpp \
    motor.cpp \
    afm.cpp \
    pga.cpp \
    dac.cpp \
    send_worker.cpp \
    receive_worker.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    receiver.h \
    serial_port.h \
    serial_port_constants.h \
    adc.h \
    pid.h \
    motor.h \
    afm.h \
    pga.h \
    dac.h \
    afm_object_interface.h \
    command_node.h \
    motor_constants.h \
    send_worker.h \
    thread_safe_queue.h \
    receive_worker.h

DISTFILES +=
