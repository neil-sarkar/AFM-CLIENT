#include "afm_object.h"

AFMObject::AFMObject()
{

}

void AFMObject::init() {
    qDebug() << "AFMObject base class init called -- should overload this";
}

quint16 AFMObject::bytes_to_word(quint8 low, quint8 high) {
    return ((high << 8) | low);
}
