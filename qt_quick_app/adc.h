#ifndef ADC_H
#define ADC_H

#include <QObject>
#include "afm_object_interface.h"

class ADC : public AfmObject
{
    Q_OBJECT
    Q_INTERFACES(AfmObject)
public:
    explicit ADC(QObject *parent = 0);
    void read();

signals:

public slots:
};

#endif // ADC_H
