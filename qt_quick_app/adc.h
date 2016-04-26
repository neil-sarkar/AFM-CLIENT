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
    static bool is_actuator_connected(double voltage);

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
    static const double SCALE_FACTOR; // calculated from MAX_VOLTAGE and RESOLUTION

     // if you were to call get resistances, what range of values would be acceptable for us to consider the actuator working
    static const int Min_Resistance;
    static const int Max_Resistance;

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
    static double voltage_resistance_equation(double);
};

#endif // ADC_H
