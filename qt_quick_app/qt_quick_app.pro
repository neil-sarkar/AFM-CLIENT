TEMPLATE = app

QT += qml quick
QT += serialport
CONFIG += c++11

SOURCES += main.cpp \
    receiver.cpp \
    serial_port.cpp \
    adc.cpp \
    dac.cpp \
    pid.cpp \
    motor.cpp \
    afm.cpp

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
    dac.h \
    pid.h \
    motor.h \
    afm.h

DISTFILES +=
