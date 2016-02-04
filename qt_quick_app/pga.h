#ifndef PGA_H
#define PGA_H

#include <QObject>
#include "command_node.h"
#include "afm_object.h"

class PGA : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE set_value NOTIFY value_changed)
public:
    explicit PGA(qint8 id);
    void set_value(double value);
    double value();
    void init();

    static const int X_1;
    static const int X_2;
    static const int Y_1;
    static const int Y_2;
    static const int Z_Fine;
    static const int DDS_Amplitude;
    static const int Z_Coarse;
    static const int Leveling;
    static int default_value(int id);


signals:
    void value_changed();

public slots:

private:
    qint8 m_id;
    double m_value;
    void cmd_set_value();
    qint8 value_to_pga();

};

#endif // PGA_H
