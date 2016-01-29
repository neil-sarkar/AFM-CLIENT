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

private:
    qint8 id;
    static constexpr double MAX_VOLTAGE = 2.5;
    static constexpr int RESOLUTION = 4095;
    static constexpr double SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;
};

#endif // ADC_H
