#include "afm_object.h"

AFMObject::AFMObject()
{

}

void AFMObject::init() {
    qDebug() << "AFMObject base class init called -- should overload this";
}

template <class T>
std::function<void(QByteArray paylaod)> AFMObject::bind(AFMObject* object, void (T::*method)(QByteArray)) {
    return std::bind(object, method);
}
