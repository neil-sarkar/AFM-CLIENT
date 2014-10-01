#ifndef METHOD_H
#define METHOD_H

#include <QEventLoop>
#include <iostream>
#include <QThread>

enum Command{
    writeDAC,
    readDAC,
    readADC,
    writeByte,
    setRasterStep,
    memsSetOffset,
    memsSetFrequency,
    memsSetAmplitude,
    memsSetBridgeVoltage,
    pidEnable,
    pidDisable,
    pidSetP,
    pidSetI,
    pidSetD,
    pidSetValues,
    pidSetPoint,
    stageSetPulseWidth,
    stageSetDirForward,
    stageSetDirBackward,
    stageSetStep,
    stageSetContinuous,
    stageStepForward,
    stageStepBackward,
    stageMoveForward,
    stageMoveBackward,
    setDDSSettings,
    frequencySweep,
    afmAutoApproach,
    setPorts,
    mainWindowTimerEvent
};



#endif // METHOD_H
