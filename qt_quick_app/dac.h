#ifndef DAC_H
#define DAC_H

#include <QObject>

class dac : public QObject
{
    Q_OBJECT
public:
    explicit dac(QObject *parent = 0);

signals:

public slots:
};

#endif // DAC_H