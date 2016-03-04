#include "afm_object.h"

AFMObject::AFMObject()
{

}

void AFMObject::init() {
    qDebug() << "AFMObject base class init called -- should overload this";
}

void AFMObject::set_settings() {
    qDebug() << "AFMObject base class set_settings called -- should overload this";
}

quint16 AFMObject::bytes_to_word(quint8 low, quint8 high) {
    return ((high << 8) | low);
}

void AFMObject::update_settings(QString settings_group_name, QString settings_key, QVariant settings_value) {
    settings.beginGroup(settings_group_name);
    settings.setValue(settings_key, settings_value);
    settings.endGroup();
}
