#ifndef AFMOBJECT_H
#define AFMOBJECT_H

#include <QObject>
#include <QByteArray>

class AfmObject : public QObject
{
    Q_OBJECT
public:
    virtual void doSomething() = 0;
    virtual void doSomethingElse() = 0;

protected:
    QByteArray return_bytes;

signals:

public slots:
};

#define Interface_iid "test"
Q_DECLARE_INTERFACE(AfmObject, Interface_iid)
#endif // AFMOBJECT_H
