#ifndef COMMANDNODE_H
#define COMMANDNODE_H

#include <QtGlobal>

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
    scanParameters,
    startScan
};

class commandNode
{


  public:

    /* Template constructors are hard.
     *
     *
     * Working on turning these constructors into templates*/

    /*int dosetRasterStep()
    int dopidEnable()
    int dopidDisable()
    void dostageSetDirForward()
    void dostageSetDirBackward()
    void dostageSetStep()
    void dostageSetContinuous()
    void dostageStepForward()
    void dostageStepBackward()
    void dostageMoveForward()
    void dostageMoveBackward()
    void doautoApproach()*/


    commandNode(Command commandName):
        m_commandName(commandName) {}


    /* readADC
     * readDAC*/
    /*void dowriteByte(char byte)*/
    //template <typename a_Type>
    commandNode(Command commandName,
                char val1):
        m_commandName(commandName),
        m_val1(val1) {}

    /*int domemsSetOffset(double val)
    int domemsSetFrequency(double val)
    int domemsSetAmplitude(double val)
    int domemsSetBridgeVoltage(double val)*/
    commandNode(Command commandName,
                double dval) :
        m_commandName(commandName),
        m_dval1(dval) {}

    /*
     * int dopidSetP(float P)
       int dopidSetI(float I)
       int dopidSetD(float D)
       int dopidSetPoint(float val)*/
    commandNode(Command commandName,
                float fval) :
        m_commandName(commandName),
        m_fval(fval) {}

    /*void dorasterStep(float val1, float val2)*/
    commandNode(Command commandName,
                float fval,
                float fval2) :
        m_commandName(commandName),
        m_fval(fval),
        m_fval2(fval2) {}

    /*int dostageSetPulseWidth(qint8 val)*/
    commandNode(Command commandName,
                qint8 qval) :
        m_commandName(commandName),
        m_qval(qval) {}

    /*void dowriteDAC(qint8 dacID, double val)*/
    commandNode(Command commandName,
                qint8 dacID,
                double dval) :
        m_commandName(commandName),
        m_qval(dacID),
        m_dval1(dval) {}

    /*int dopidSetValues(qint8 P,qint8 I,qint8 D)*/
    commandNode(Command commandName,
                qint8 P,
                qint8 I,
                qint8 D) :
        m_commandName(commandName),
        m_P(P),
        m_I(I),
        m_D(D) {}

    /*void dosetDDSSettings(quint16 numPoints, quint16 startFrequency, quint16 stepSize)*/
    commandNode(Command commandName,
                qint16 numPoints,
                qint16 startFrequency,
                qint16 stepSize) :
            m_commandName(commandName),
            m_numPoints(numPoints),
            m_startFrequency(startFrequency),
            m_stepSize(stepSize) {}

    /*int dofrequencySweep(quint16 numPoints, quint16 startFrequency, quint16 stepSize, QVector<double>& amplitude, QVector<double>& frequency, int& bytesRead)*/
    commandNode(Command commandName,
                quint16 numPoints,
                quint16 startFrequency,
                quint16 stepSize,
                QVector<double> amplitude,
                QVector<double> phase,
                QVector<double> frequency,
                int& bytesRead) :
            m_commandName(commandName),
            m_numPoints(numPoints),
            m_startFrequency(startFrequency),
            m_stepSize(stepSize),
            m_amplitude(amplitude),
            m_phase(phase),
            m_frequency(frequency),
            m_bytesRead(bytesRead) {}

    commandNode(Command commandName ,
                double vmin_line,
                double vmin_scan,
                double vmax,
                double numpts,
                double numlines)

          : m_commandName(commandName),
            m_vminLine(vmin_line),
            m_vminScan(vmin_scan),
            m_vmax(vmax),
            m_numpts(numpts),
            m_numLines(numlines){}

    ~commandNode() {}


    Command getcommandName() { return m_commandName; }
    char getval1() { return m_val1; }
    char getval2() { return m_val2; }
    char getval3() { return m_val3; }
    double getdval() { return m_dval1;}
    double getdval2(){ return m_dval2; }
    double getdval3(){ return m_dval3; }
    double getdval4(){ return m_dval4; }
    float getfval() { return m_fval;}
    float getfval2() {return m_fval2;}
    qint8 getP() { return m_P;}
    qint8 getI() { return m_I;}
    qint8 getD() { return m_D;}
    qint8 getqval() { return m_qval;}
    qint16 getnumPoints() { return m_numPoints;}
    qint16 getstartFrequency() { return m_startFrequency;}
    qint16 getstepSize() { return m_stepSize;}
    QVector<double> getamplitude() {return m_amplitude; }
    QVector<double> getfrequency() { return m_frequency; }
    QVector<double> getphase() { return m_phase;}
    int& getbytesRead() { return m_bytesRead;}
    double getvminLine(){ return m_vminLine;}
    double getvminScan(){ return m_vminScan;}
    double getvmax(){ return m_vmax;}
    double getnumpts(){return m_numpts;}
    double getnumLines(){return m_numLines;}

private:
    Command m_commandName;
    qint8 m_qval;
    char m_val1;
    char m_val2;
    char m_val3;
    double m_dval1;
    double m_dval2;
    double m_dval3;
    double m_dval4;
    float m_fval;
    float m_fval2;    
    qint8 m_P;
    qint8 m_I;
    qint8 m_D;
    qint16 m_numPoints;
    qint16 m_startFrequency;
    qint16 m_stepSize;
    QVector<double> m_amplitude;
    QVector<double> m_phase;
    QVector<double> m_frequency;    
    int m_bytesRead;
    double m_vminLine;
    double m_vminScan;
    double m_vmax;
    double m_numpts;
    double m_numLines;
};

#endif // COMMANDNODE_H
