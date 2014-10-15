#include "eventworker.h"
#include <QThread>
#include <afm.h>
#include <Qtimer>
#include <commandNode.h>
#include <mainwindow.h>
#include <globals.h>



/* Moving all the timers into one thread.
 *
 * When timers trigger functions will push events to the commandQueue
 * for the serialworker to process.
 */
void eventworker::mainLoop()
{


    //forever {

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


    //}
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

    if(_mainwindow != nullptr){
    //if( id == ioTimer ) {
#if AFM_MICRO_CONNECTED
        mutex.lock();
        if( _mainwindow->getContinuousStep() )
            m_queue.push(new commandNode(stageSetStep));//afm.stageSetStep();
        mutex.unlock();
//        adc5 = afm.readADC(AFM_ADC_AMPLTIDE_ID);
//        dac8 = afm.readDAC(AFM_DAC_OFFSET_ID);
        mutex.lock();
        m_queue.push(new commandNode(readADC,(qint8)AFM_ADC_AMPLITUDE_ID));
        mutex.unlock();
//        returnBuffer<int>* _buffer;
//        mutex.lock();
//        if(!return_queue.empty()){
//            _buffer = return_queue.front();
//            if(_buffer->getFunction() == "ADC"){
//                return_queue.pop();
//                _buffer = return_queue.front();
//                _mainwindow->setADC5(_buffer->getData());
//                return_queue.pop();
//            }
//        }
//        mutex.unlock();
        mutex.lock();
        m_queue.push(new commandNode(readDAC,(qint8)AFM_DAC_OFFSET_ID));
        mutex.unlock();
//        mutex.lock();
//        if(!return_queue.empty()){
//            _buffer = return_queue.front();
//            if(_buffer->getFunction() == "DAC"){
//                return_queue.pop();
//                _buffer = return_queue.front();
//                _mainwindow->setDAC8(_buffer->getData());
//                return_queue.pop();
//            }

//        }
//        mutex.unlock();
        //adc5 = serialWorker->doreadADC(AFM_ADC_AMPLITUDE_ID);
        //dac8 = serialWorker->doreadDAC(AFM_DAC_OFFSET_ID);

        mutex.lock();
        if( _mainwindow->getAutoApproach() ) {
            //approachPlot->update(time, adc5, currTab == Approach ? true: false);
            //MainWindow::ui->currOffsetValue->setValue(adc5);
            //time++;

            m_queue.push(new commandNode(stageSetStep));//afm.stageSetStep();

            if ( _mainwindow->getADC5() <= 0.95*_mainwindow->getAutoApproachComparison() ) {
                //on_buttonAutoApproachClient_clicked(false);
            }
        }
        mutex.unlock();

#else
        mutex.lock();
        _mainwindow->setADC5(float(qrand())/RAND_MAX);
        _mainwindow->setDAC8(float(qrand())/RAND_MAX);
        mutex.lock();
#endif
    }
    //}

}

//void MainWindow::timerEvent(QTimerEvent *e) {
//
//}
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
