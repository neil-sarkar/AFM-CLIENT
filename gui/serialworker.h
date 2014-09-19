#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

class serialworker : public QObject
{
    Q_OBJECT

public:
    explicit serialworker(QObject *parent = 0);
    enum Method{
        writeByte,
        readByte
    };
    void requestMethod(Method method);
    void abort();

private:
    Method _method;
    bool _abort;
    bool _interrupt;
    QMutex mutex;
    QWaitCondition condition;
    void dowriteByte(char byte);
    void doreadByte();

signals:
    void valueChanged(const QString &value);
    void finished();

public slots:
    void mainLoop();
};

#endif // SERIALWORKER_H
