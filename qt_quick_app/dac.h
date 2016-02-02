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
    void set_value(double value);
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
    void value_changed();
    void id_changed();

public slots:


private:
    qint8 m_id;
    double m_value;
    static constexpr int RESOLUTION = 4095;
    static constexpr double MAX_VOLTAGE = 3.3;

};

#endif // DAC_H
