#ifndef FORCECURVEGENERATOR_H
#define FORCECURVEGENERATOR_H

#include "afm_object.h"

class ForceCurveGenerator : public AFMObject
{
    Q_OBJECT
public:
    ForceCurveGenerator();
    Q_INVOKABLE void cmd_generate_force_curve();
    void save_raw_data(QString save_folder);
    void init();

signals:
    void new_approaching_amplitude_data(QVariantList);
    void new_approaching_phase_data(QVariantList);
    void new_retracting_amplitude_data(QVariantList);
    void new_retracting_phase_data(QVariantList);

private:
    QVariantList m_approaching_amplitude, m_approaching_phase, m_retracting_amplitude, m_retracting_phase;
    void callback_generate_force_curve(QByteArray return_bytes);
    typedef void (ForceCurveGenerator::*callback_type)(QByteArray);
    callback_return_type bind(callback_type method);
    void clear_buffers();
    const int Initial_Z;
    const int Step_Size;
};

#endif // FORCECURVEGENERATOR_H
