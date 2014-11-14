#include <eventworker.h>
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
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(updateGraph()));
    generalTimer->start(500); // need to get refresh rate from mainwindow
}

void eventworker::updateGraph()
{
    //this event should probably be in the mainwindow thread
    if (_abort) {
        emit finished();
        //mutex.unlock();
        return;
    }
    MainWindow* _mainwindow = (MainWindow *) QApplication::activeWindow();

    if(_mainwindow != NULL){
        if(_mainwindow->getCurrTab() == 3){
            mutex.lock();
            m_queue.push(new commandNode(readADC,(qint8)ADC_Z_AMP));
            mutex.unlock();
        }
        else if( _mainwindow->getCurrTab() == 4 ) {
            mutex.lock();
            m_queue.push(new commandNode(readDAC,(qint8)DAC_ZAMP));
            m_queue.push(new commandNode(readDAC,(qint8)DAC_ZOFFSET_FINE));
            mutex.unlock();
        }
    }

}

void eventworker::generalTimerUpdate()
{
    //general timer update
    //what does this do?

    //int currTab = MainWindow::ui->tabWidget->currentIndex();
    //int id = e->timerId();

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
