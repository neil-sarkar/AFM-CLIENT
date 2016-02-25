#ifndef DDS_H
#define DDS_H

#include <QObject>
#include <afm_object.h>
#include <qmath.h>

class DDS : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 start_frequency READ start_frequency WRITE set_start_frequency NOTIFY start_frequency_changed)
    Q_PROPERTY(quint16 step_size READ step_size WRITE set_step_size NOTIFY step_size_changed)
    Q_PROPERTY(quint32 end_frequency READ end_frequency WRITE set_end_frequency NOTIFY end_frequency_changed)
public:
    explicit DDS();
    void init();
    void set_start_frequency(quint32 start_frequency);
    void set_step_size(quint16 step_size);
    void set_end_frequency(quint32 end_frequency);
    quint32 start_frequency();
    quint16 step_size();
    quint32 end_frequency();
    quint16 num_steps();
    Q_INVOKABLE void cmd_set();
    void update_settings(QString, QVariant);
    void set_settings();

signals:
    void start_frequency_changed(int);
    void step_size_changed(int);
    void end_frequency_changed(int);

public slots:

private:
    quint32 m_start_frequency;
    quint16 m_step_size;
    quint32 m_end_frequency;
    const double SCALE_FACTOR = double (qPow(2.0, 28) / (5.0*qPow(10,6)));
    static const QString settings_group_name;
};

#endif // DDS_H
