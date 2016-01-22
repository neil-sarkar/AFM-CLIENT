#ifndef ADC_H
#define ADC_H

#include <QObject>

class adc : public QObject
{
    Q_OBJECT
public:
    explicit adc(QObject *parent = 0);

signals:

public slots:
};

#endif // ADC_H