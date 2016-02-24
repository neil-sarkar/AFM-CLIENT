#ifndef ADC_H
#define ADC_H

#include <QObject>
#include "command_node.h"
#include "afm_object.h"

class ADC : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value NOTIFY value_changed)
public:
    explicit ADC(qint8 id);
    void init();
    Q_INVOKABLE double value();
    Q_INVOKABLE void read();
    void update_value(double value);

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
    void value_changed(double);
    void new_resistance_value(double);

public slots:

private:
    qint8 m_id;
    double m_value;
    void callback_read(QByteArray );
    callback_return_type bind(void (ADC::*method)(QByteArray));
    typedef void (ADC::*callback_type)(QByteArray);
    void cmd_read();
    double voltage_resistance_equation(double);
};

#endif // ADC_H
