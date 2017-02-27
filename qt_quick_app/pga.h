#ifndef PGA_H
#define PGA_H

#include <QObject>
#include "command_node.h"
#include "afm_object.h"

class PGA : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(double m_value READ value WRITE set_value NOTIFY value_changed)
public:
    explicit PGA(qint8 id, double default_value);
    Q_INVOKABLE void set_value(double value);
    Q_INVOKABLE double value();
    void init();
    void set_settings();
    qint8 get_id();
    void transient_set_value(bool is_callback, const QString* master, int value);
    void restore_user_value();

    static const int X_1;
    static const int X_2;
    static const int Y_1;
    static const int Y_2;
    static const int Z_Fine;
    static const int DDS_Amplitude;
    static const int Z_Coarse;
    static const int Leveling;

signals:
    void value_changed(double);
    void pga_callback_received(const QString*);

public slots:

private:
    callback_return_type bind(void (PGA::*method)(QByteArray));
    typedef void (PGA::*callback_type)(QByteArray);

    qint8 m_id;
    double m_default_value;
    double m_value;
    const QString* m_caller;

    void cmd_set_value(double value, bool is_callback);
    void callback_value_set(QByteArray);
    qint8 value_to_pga(double value);
    static const QString settings_group_name;
};

#endif // PGA_H
