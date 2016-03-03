#ifndef FORCECURVEGENERATOR_H
#define FORCECURVEGENERATOR_H

#include "afm_object.h"

class ForceCurveGenerator : public AFMObject
{
    Q_OBJECT
public:
    ForceCurveGenerator();
    Q_INVOKABLE void cmd_generate_force_curve();
    void init();

signals:
    void new_approaching_amplitude_data(QVariantList);
    void new_approaching_phase_data(QVariantList);
    void new_retracting_amplitude_data(QVariantList);
    void new_retracting_phase_data(QVariantList);

private:
    void callback_generate_force_curve(QByteArray return_bytes);
    typedef void (ForceCurveGenerator::*callback_type)(QByteArray);
    callback_return_type bind(callback_type method);
};

#endif // FORCECURVEGENERATOR_H
