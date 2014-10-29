#-------------------------------------------------
#
# Project created by QtCreator 2014-03-06T19:01:57
#
#-------------------------------------------------

QT       += core gui
CONFIG   += serialport
CONFIG   += qwt


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT  += concurrent
QT  += serialport


LIBS += -lqwt

TARGET = nano-i
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    afm.cpp \
    plot.cpp \
    serialworker.cpp \
    eventworker.cpp \
    XYgenerator.cpp

HEADERS  += mainwindow.h \
    afm.h \
    plot.h \
    serialworker.h \
    commandNode.h \
    command.h \
    returnBuffer.h \
    eventworker.h \
    globals.h \
    returnTypes.h \
    XYgenerator.h

FORMS    += mainwindow.ui
INCLUDEPATH += $$PWD
INCLUDEPATH += C:\Users\Nick\Documents\armadillo-4.450.4\include
#INCLUDEPATH += C:\qwt-6.1.0\qwt-6.1.0\src
#include(C:\qwt-6.1.0\features\qwt.prf)
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -larmadillo
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -larmadillo
#else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -larmadillo

#INCLUDEPATH += $$PWD/../../../../../usr/include
#DEPENDPATH += $$PWD/../../../../../usr/include

#unix|win32: LIBS += -larmadillo
#QMAKE_LFLAGS += /INCREMENTAL:NO

win32:RC_ICONS += C:\Users\Nick\Documents\code\AFM-CLIENT\icons\icspi.ico
