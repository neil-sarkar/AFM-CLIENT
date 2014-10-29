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
    stageAbortContinuous,
    stageStepForward,
    stageStepBackward,
    stageMoveForward,
    stageMoveBackward,
    setDDSSettings,
    frequencySweep,
    afmAutoApproach,
    getPorts,
    setPort,
    mainWindowTimerEvent,
    setDacValues,
    deviceCalibration,
    scanParameters
};



#endif // METHOD_H
