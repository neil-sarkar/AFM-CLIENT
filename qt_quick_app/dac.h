#ifndef DAC_H
#define DAC_H

#include <QObject>
#include <QtGlobal>
#include "command_node.h"
#include "afm_object.h"

class DAC : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE set_value NOTIFY value_changed)
    Q_PROPERTY(int id READ id WRITE set_id NOTIFY id_changed)

public:
    explicit DAC(qint8 id);
    void set_value(double value, bool cmd = true);
    void set_id(qint8 id); // Convenience function for tests - once initialized, the id should not change.
    double value();
    qint8 id();
    Q_INVOKABLE void init();
    Q_INVOKABLE void cmd_read_value();
    Q_INVOKABLE void cmd_set_value();


    static const int Buffered_1;
    static const int Buffered_2;
    static const int Board_2;
    static const int Z_Amplitude;
    static const int Board_1;
    static const int Buffered_3;
    static const int Z_Offset_Fine;
    static const int Y_1;
    static const int Z_Offset_Coarse;
    static const int Y_2;
    static const int X_1;
    static const int X_2;

signals:
    void value_changed(double);
    void id_changed();

public slots:


private:
    qint8 m_id;
    double m_value;
    static const quint16 RESOLUTION;
    static const double MAX_VOLTAGE;
    static const double SCALE_FACTOR;
    void callback_read_value(QByteArray);
    callback_return_type bind(void (DAC::*method)(QByteArray));
    typedef void (DAC::*callback_type)(QByteArray);

};

#endif // DAC_H
