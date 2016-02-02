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

signals:

public slots:

private:
    qint8 m_id;
    static constexpr double MAX_VOLTAGE = 2.5;
    static constexpr int RESOLUTION = 4095;
    static constexpr double SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;
    static constexpr unsigned char READ_COMMAND = 0x63;
};

#endif // ADC_H
