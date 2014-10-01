#include "eventworker.h"
#include <QThread>
#include <afm.h>
#include <Qtimer>

/* Moving all the timers into one thread.
 *
 * When timers trigger functions will push events to the commandQueue
 * for the serialworker to process.
 */
void eventworker::mainLoop()
{
    generalTimer = new QTimer(this);
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(generalTimerUpdate()));
    generalTimer->start(20); // every 20 ms, we update UI elements/other tasks, like continuous coarse step

    graphTimer = new QTimer(this);
    connect(graphTimer, SIGNAL(timeout()), this, SLOT(updateGraph()));
    graphTimer->start(20);
}

void eventworker::updateGraph()
{

}

void eventworker::generalTimerUpdate()
{

}
