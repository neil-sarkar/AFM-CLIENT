#-------------------------------------------------
#
# Project created by QtCreator 2014-03-06T19:01:57
#
#-------------------------------------------------

QT       += core gui
CONFIG   += serialport
CONFIG   += qwt
#MOC_DIR  += C:/qwtplot3d-0.3.1-322-src/qwtplot3d-0.3.1-322-src/src/tmp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT  += concurrent
QT  += serialport
QT  += opengl

TARGET = nano-i
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    afm.cpp \
    plot.cpp \
    serialworker.cpp \
    eventworker.cpp \
    XYgenerator.cpp \
    receiver.cpp

HEADERS  += mainwindow.h \
    afm.h \
    serialworker.h \
    eventworker.h \
    globals.h \
    XYgenerator.h \
    myplot.h \
    receiver.h \
    commandnode.h \
    returnbuffer.h

FORMS    += mainwindow.ui
INCLUDEPATH += $$PWD
INCLUDEPATH += C:/Users/Nick/Documents/armadillo-4.450.4/include
INCLUDEPATH += C:/qwtplot3d-0.3.1-322-src/qwtplot3d-0.3.1-322-src/include
#INCLUDEPATH += C:/Users/Nick/Documents/code/gwyddion-2.39/libgwyddion

LIBS += -LC:/qwtplot3d-0.3.1-322-src/qwtplot3d-0.3.1-322-src/lib -lqwtplot3d -lopengl32 -lglu32 -lgdi32
#LIBS += "-LC:/Program Files (x86)/Gwyddion/lib -ldependency"

#CONFIG( debug, debug|release ) {
#        LIBS += -LC:/qwt-6.1.1/lib -lqwtd
#} else {
#        LIBS += -LC:/qwt-6.1.1/lib -lqwt
#}
#win32:LIBS += C:/qwt-6.1.1/lib/libqwt.a
#win32:LIBS += C:/Users/Nick/Documents/armadillo-4.450.4/include
#INCLUDEPATH += C:\qwt-6.1.0\qwt-6.1.0\src
#include(C:\qwt-6.1.0\features\qwt.prf)
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -larmadillo
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -larmadillo
#else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -larmadillo

#INCLUDEPATH += $$PWD/../../../../../usr/include
#DEPENDPATH += $$PWD/../../../../../usr/include

#unix|win32: LIBS += -larmadillo
#QMAKE_LFLAGS += /INCREMENTAL:NO

#win32:RC_ICONS += C:\Users\Nick\Documents\code\AFM-CLIENT\icons\icspi.ico

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../qwt-6.1.1/lib/ -lqwt
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../qwt-6.1.1/lib/ -lqwtd
#else:unix: LIBS += -L$$PWD/../../../../../../qwt-6.1.1/lib/ -lqwt

#INCLUDEPATH += $$PWD/../../../../../../qwt-6.1.1/include
#DEPENDPATH += $$PWD/../../../../../../qwt-6.1.1/include

RESOURCES += \
    resources.qrc
