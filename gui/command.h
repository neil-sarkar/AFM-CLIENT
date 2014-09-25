#ifndef METHOD_H
#define METHOD_H

enum Command{
    writeDAC,
    readDAC,
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
    autoApproach
};

#endif // METHOD_H
