#-------------------------------------------------
#
# Project created by QtCreator 2014-03-06T19:01:57
#
#-------------------------------------------------

QT       += core gui
QT       += serialport #QT 5 uses QT rather than CONFIG
CONFIG   += qwt

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT  += concurrent
QT  += serialport
QT  += opengl

TARGET = icspi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    afm.cpp \
    plot.cpp \
    eventworker.cpp \
    afm_worker.cpp \
    receive_worker.cpp \
    afm_data.cpp \
    send_worker.cpp

HEADERS  += mainwindow.h \
    afm.h \
    eventworker.h \
    globals.h \
    myplot.h \
    commandnode.h \
    returnbuffer.h \
    afm_worker.h \
    receive_worker.h \
    send_worker.h \
    icspi_products.h \
    afm_data.h \
    XYgenerator.cpp.disabled \
    XYgenerator.h.disabled \
    afm_state.h

FORMS    += mainwindow.ui
INCLUDEPATH += $$PWD

QWT_ROOT = C:/Qwt-6.1.2
INCLUDEPATH += $${QWT_ROOT}/include
DEPENDPATH += $${QWT_ROOT}/include
CONFIG( debug, debug|release ) {
        LIBS += -L$${QWT_ROOT}/lib -lqwtd
} else {
        LIBS += -L$${QWT_ROOT}/lib -lqwt
}
include ( $${QWT_ROOT}/features/qwt.prf )


INCLUDEPATH += $$PWD/../lib/qwtplot3d/include
DEPENDPATH += $$PWD/../lib/qwtplot3d/include
win32{
  !build_pass {
    win32-msvc | win32-msvc2002 {
      error(Unsupported Visual Studio version ( < 2003 ))
    }
  }

  win32-msvc2008 | win32-msvc2010 | win32-msvc2012 | win32-msvc2013 {
    QMAKE_CXXFLAGS += -MP
    QMAKE_CXXFLAGS += $$QMAKE_CFLAGS_STL
  }

    LIBS += -L$$PWD/../lib/qwtplot3d/lib -lqwtplot3d -lopengl32 -lglu32 -lgdi32
}

# Not used for now
#ARMA_ROOT = $$PWD/../lib/armadillo-5.500.2
#INCLUDEPATH += $${ARMA_ROOT}/include/armadillo_bits

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

#DISTFILES += \
#    mainwindow_gen2.qml
