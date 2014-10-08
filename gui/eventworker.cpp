#include "eventworker.h"
#include <QThread>
#include <afm.h>
#include <Qtimer>
#include <commandNode.h>

/* Moving all the timers into one thread.
 *
 * When timers trigger functions will push events to the commandQueue
 * for the serialworker to process.
 */
void eventworker::mainLoop()
{
    forever {

        if (_abort) {
            emit finished();
            //mutex.unlock();
            return;
        }
        ioTimer = startTimer(200); // for reading DAC/ADC

        generalTimer = new QTimer(this);
        connect(generalTimer, SIGNAL(timeout()), this, SLOT(generalTimerUpdate()));
        generalTimer->start(20); // every 20 ms, we update UI elements/other tasks, like continuous coarse step


    }
}

void eventworker::updateGraph()
{
    //this event should probably be in the mainwindow thread
}

void eventworker::generalTimerUpdate()
{
    //general timer update
    //what does this do?

//    int currTab = ui->tabWidget->currentIndex();
//        int id = e->timerId();


//        if( id == ioTimer ) {
//    #if AFM_MICRO_CONNECTED
//            if( continuousStep )
//                commandQueue.push(new commandNode(stageSetStep));//afm.stageSetStep();

//    //        adc5 = afm.readADC(AFM_ADC_AMPLTIDE_ID);
//    //        dac8 = afm.readDAC(AFM_DAC_OFFSET_ID);
//            commandQueue.push(new commandNode(readADC,0,0,(qint8)AFM_ADC_AMPLITUDE_ID));
//            commandQueue.push(new commandNode(readDAC,0,0,(qint8)AFM_DAC_OFFSET_ID));
//            mutex.lock();
//            returnBuffer<int>* _buffer;
//            if(!returnQueue.empty()){
//                _buffer = returnQueue.front();
//                adc5 = _buffer->getData();
//                returnQueue.pop();
//                _buffer = returnQueue.front();
//                dac8 = _buffer->getData();
//                returnQueue.pop();
//                mutex.unlock();
//            }
//            //adc5 = serialWorker->doreadADC(AFM_ADC_AMPLITUDE_ID);
//            //dac8 = serialWorker->doreadDAC(AFM_DAC_OFFSET_ID);

//            if( isAutoApproach ) {
//                approachPlot->update(time, adc5, currTab == Approach ? true: false);
//                ui->currOffsetValue->setValue(adc5);
//                time++;

//                commandQueue.push(new commandNode(stageSetStep));//afm.stageSetStep();

//                if ( adc5 <= 0.95*autoApproachComparison ) {
//                    on_buttonAutoApproachClient_clicked(false);
//                }
//            }

//    #else
//            adc5 = float(qrand())/RAND_MAX;
//            dac8 = float(qrand())/RAND_MAX;
//    #endif
//        }

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
    //emit finished();
}
