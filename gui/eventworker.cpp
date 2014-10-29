#include "eventworker.h"
#include <QThread>
#include <afm.h>
#include <Qtimer>
#include <commandNode.h>
#include <mainwindow.h>
#include <globals.h>



/* EventWorker:
 *          Pushes two events to the queue every 100ms
 *              -First event is a read to the Amplitude DAC
 *              -Second event is a read to the Offset ADC
 */
void eventworker::mainLoop()
{
    _abort = false;
    if (_abort) {
        emit finished();
        //mutex.unlock();
        return;
    }
    //ioTimer = startTimer(200); // for reading DAC/ADC

    generalTimer = new QTimer(this);
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(generalTimerUpdate()));
    generalTimer->start(100); // need to get refresh rate from mainwindow
}

void eventworker::updateGraph()
{
    //this event should probably be in the mainwindow thread
}

void eventworker::generalTimerUpdate()
{
    //general timer update
    //what does this do?

    //int currTab = MainWindow::ui->tabWidget->currentIndex();
    //int id = e->timerId();
    if (_abort) {
        emit finished();
        //mutex.unlock();
        return;
    }
    MainWindow* _mainwindow = (MainWindow *) QApplication::activeWindow();
    int id = 1;

    if(_mainwindow != NULL){
    if( _mainwindow->getCurrTab() == 4 ) {
#if AFM_MICRO_CONNECTED
//        mutex.lock();
//        if( _mainwindow->getContinuousStep() )
//            m_queue.push(new commandNode(stageSetStep));//afm.stageSetStep();
//        mutex.unlock();
//        adc5 = afm.readADC(AFM_ADC_AMPLTIDE_ID);
//        dac8 = afm.readDAC(AFM_DAC_OFFSET_ID);
        mutex.lock();
        m_queue.push(new commandNode(readDAC,(qint8)DAC_ZAMP));
        m_queue.push(new commandNode(readDAC,(qint8)DAC_ZOFFSET_FINE));
        mutex.unlock();

#else
        mutex.lock();
        _mainwindow->setADC5(float(qrand())/RAND_MAX);
        _mainwindow->setDAC8(float(qrand())/RAND_MAX);
        mutex.lock();
#endif
    }
    }

}

void eventworker::abort()
{
    //QMutexLocker locker(&mutex);
    //mutex.unlock();
    _abort = true;
    //condition.wakeOne();
}
eventworker::~eventworker()
{
    emit finished();
}
