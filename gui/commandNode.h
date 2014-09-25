#ifndef COMMANDNODE_H
#define COMMANDNODE_H
#include <command.h>
#include <QtGlobal>

class commandNode
{
    Command m_commandName;
    int m_sendByteSize;
    int m_recByteSize;
    char m_val1;
    char m_val2;
    char m_val3;
    qint8 m_dacID;
    double m_dval;
    float m_fval;
    float m_fval2;
    qint8 m_P;
    qint8 m_I;
    qint8 m_D;
    qint8 m_qval;
    qint16 m_numPoints;
    qint16 m_startFrequency;
    qint16 m_stepSize;
    QVector<double> m_amplitude;
    QVector<double> m_frequency;
    int m_bytesRead;
    float m_returnBytes;

  public:
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
    commandNode(Command commandName, int sendByteSize, int recByteSize)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize) {}

    commandNode(Command commandName, int sendByteSize, int recByteSize,qint8 dacID, float& returnBytes)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize),m_dacID(dacID), m_returnBytes(returnBytes) {}

    /*void dowriteByte(char byte)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, char val1)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_val1(val1) {}

    /*int domemsSetOffset(double val)
    int domemsSetFrequency(double val)
    int domemsSetAmplitude(double val)
    int domemsSetBridgeVoltage(double val)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, double dval)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_dval(dval) {}

    /*
     * int dopidSetP(float P)
       int dopidSetI(float I)
       int dopidSetD(float D)
       int dopidSetPoint(float val)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, float fval)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_fval(fval) {}

    /*void dorasterStep(float val1, float val2)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, float fval, float fval2)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_fval(fval), m_fval2(fval2) {}

    /*int dostageSetPulseWidth(qint8 val)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, qint8 qval)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_qval(qval) {}

    /*void dowriteDAC(qint8 dacID, double val)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, qint8 dacID, double dval)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_dacID(dacID),m_dval(dval) {}

    /*int dopidSetValues(qint8 P,qint8 I,qint8 D)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, qint8 P, qint8 I, qint8 D)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_P(P),m_I(I), m_D(D) {}

    /*void dosetDDSSettings(quint16 numPoints, quint16 startFrequency, quint16 stepSize)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, qint16 numPoints, qint16 startFrequency, qint16 stepSize)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_numPoints(numPoints),m_startFrequency(startFrequency), m_stepSize(stepSize) {}

    /*int dofrequencySweep(quint16 numPoints, quint16 startFrequency, quint16 stepSize, QVector<double>& amplitude, QVector<double>& frequency, int& bytesRead)*/
    commandNode(Command commandName, int sendByteSize, int recByteSize, quint16 numPoints, quint16 startFrequency, quint16 stepSize, QVector<double>& amplitude, QVector<double>& frequency, int& bytesRead)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize), m_numPoints(numPoints),m_startFrequency(startFrequency), m_stepSize(stepSize),m_amplitude(amplitude),m_frequency(frequency),m_bytesRead(bytesRead) {}
    ~commandNode() {}


    Command getcommandName() { return m_commandName; }
    int getsendByteSize() { return m_sendByteSize; }
    char getval1() { return m_val1; }
    char getval2() { return m_val2; }
    char getval3() { return m_val3; }
    qint8 getdacID() { return m_dacID;}
    double getdval() { return m_dval;}
    float getfval() { return m_fval;}
    float getfval2() {return m_fval2;}
    qint8 getP() { return m_P;}
    qint8 getI() { return m_I;}
    qint8 getD() { return m_D;}
    qint8 getqval() { return m_qval;}
    qint16 getnumPoints() { return m_numPoints;}
    qint16 getstartFrequency() { return m_startFrequency;}
    qint16 getstepSize() { return m_stepSize;}
    QVector<double>& getamplitude() {return m_amplitude; }
    QVector<double>& getfrequency() { return m_frequency; }
    int& getbytesRead() { return m_bytesRead;}
    float getreturnBytes() { return m_returnBytes; }
};

#endif // COMMANDNODE_H
