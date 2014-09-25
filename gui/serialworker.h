#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <afm.h>
#include <queue>
#include <commandNode.h>
#include <command.h>

using std::queue;



class serialworker : public QObject
{
    Q_OBJECT
    queue<commandNode*>& m_queue;
    nanoiAFM m_afm;
public:
    serialworker(QObject *parent, queue<commandNode*>& _queue, nanoiAFM& _afm) : m_queue(_queue),QObject(parent), m_afm(_afm){}
    void requestCommand(Command command);
    void requestCommand(Command command,qint8 dacID, double val);
    void abort();


private:
    //nanoiAFM* afm;
    Command _command;
    double _val;
    qint8 _dacID;
    bool _abort;
    QMutex mutex;
    QWaitCondition condition;
    float _returnBytes;
    void dowriteByte(char byte);
    void dowriteDAC(qint8 dacID, double val);
    int dosetRasterStep();
    int domemsSetOffset(double val);
    int domemsSetFrequency(double val);
    int domemsSetAmplitude(double val);
    int domemsSetBridgeVoltage(double val);
    int dopidEnable();
    int dopidDisable();
    int dopidSetP(float P);
    int dopidSetI(float I);
    int dopidSetD(float D);
    int dopidSetValues(qint8 P,qint8 I,qint8 D);
    int dopidSetPoint(float val);
    int dostageSetPulseWidth(qint8 val);
    void dostageSetDirForward();
    void dostageSetDirBackward();
    void dostageSetStep();
    void dostageSetContinuous();
    void dostageStepForward();
    void dostageStepBackward();
    void dostageMoveForward();
    void dostageMoveBackward();
    void dosetDDSSettings(quint16 numPoints, quint16 startFrequency, quint16 stepSize);
    int dofrequencySweep(quint16 numPoints, quint16 startFrequency, quint16 stepSize, QVector<double>& amplitude, QVector<double>& frequency, int& bytesRead);
    void dorasterStep(float val1, float val2);
    void doautoApproach();

signals:
    void valueChanged(const QString &value);
    void valueChanged(double value);
    void finished();

public slots:
    double doreadDAC();
    void mainLoop();
};

#endif // SERIALWORKER_H
