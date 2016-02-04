#ifndef ADC_H
#define ADC_H

#include <QObject>
#include "command_node.h"
#include "afm_object.h"

class ADC : public AFMObject
{
    Q_OBJECT
public:
    explicit ADC(qint8 id);
    void cmd_read();
    void init();

    // ADC channel (aka id) constants
    static const int X_1;
    static const int X_2;
    static const int Y_1;
    static const int Y_2;
    static const int Z;
    static const int Z_Piezoresistor_Amplitude;
    static const int Phase;
    static const double MAX_VOLTAGE;
    static const int RESOLUTION;
    static const double SCALE_FACTOR;
signals:

public slots:

private:
    qint8 m_id;

};

#endif // ADC_H
