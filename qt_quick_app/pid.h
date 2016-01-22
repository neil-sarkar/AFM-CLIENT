#ifndef PID_H
#define PID_H

#include <QObject>

class pid : public QObject
{
    Q_OBJECT
public:
    explicit pid(QObject *parent = 0);

signals:

public slots:
};

#endif // PID_H