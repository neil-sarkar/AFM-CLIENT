#include <eventworker.h>

/************************************************************
 *
 * EventWorker: Pushes two events to the queue every 100ms
 *                  -First event is a read to the Amplitude DAC
 *                  -Second event is a read to the Offset ADC
 *
 ************************************************************/

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
    //TODO: This thread needs to update the graphs to ensure no delay
    //when doing a continuous approach in the Main Thread
    if (_abort) {
        delete generalTimer;
        emit finished();
        //mutex.unlock();
        return;
    }
    _mainwindow = (MainWindow *) QApplication::activeWindow();

    if(_mainwindow){
        if(_mainwindow->getCurrTab() == 3 && !_mainwindow->getAutoApproach()){
            //m_queue.push(new commandNode(readADC,(qint8)ADC_PHASE));

            m_queue.push(new commandNode(readSignalPhaseOffset));
            if(!graph_queue.empty()){
                _node = graph_queue.front();
                if(_node->getReturnType() == READSIGNALPHASEOFFSET)
                    emit updatePlot(_node->getdsignal(),1);
                graph_queue.pop();
            }

        }
//        if( _mainwindow->getCurrTab() == 4 ) {
//            mutex.lock();
//            m_queue.push(new commandNode(readDAC,(qint8)DAC_ZAMP));
//            m_queue.push(new commandNode(readDAC,(qint8)DAC_ZOFFSET_FINE));
//            mutex.unlock();
//        }
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
