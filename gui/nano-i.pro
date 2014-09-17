#-------------------------------------------------
#
# Project created by QtCreator 2014-03-06T19:01:57
#
#-------------------------------------------------

QT       += core gui
CONFIG   += serialport
CONFIG   += qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nano-i
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    afm.cpp \
    plot.cpp \
    XYGenerator.cpp

HEADERS  += mainwindow.h \
    afm.h \
    plot.h \
    XYGenerator.h

FORMS    += mainwindow.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -larmadillo
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -larmadillo
#else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -larmadillo

#INCLUDEPATH += $$PWD/../../../../../usr/include
#DEPENDPATH += $$PWD/../../../../../usr/include

unix|win32: LIBS += -larmadillo
