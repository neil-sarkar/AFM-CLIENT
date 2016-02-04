/****************************************************************************
** Meta object code from reading C++ file 'dds.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/dds.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dds.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DDS_t {
    QByteArrayData data[8];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DDS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DDS_t qt_meta_stringdata_DDS = {
    {
QT_MOC_LITERAL(0, 0, 3), // "DDS"
QT_MOC_LITERAL(1, 4, 23), // "start_frequency_changed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "step_size_changed"
QT_MOC_LITERAL(4, 47, 18), // "num_points_changed"
QT_MOC_LITERAL(5, 66, 15), // "start_frequency"
QT_MOC_LITERAL(6, 82, 9), // "step_size"
QT_MOC_LITERAL(7, 92, 10) // "num_points"

    },
    "DDS\0start_frequency_changed\0\0"
    "step_size_changed\0num_points_changed\0"
    "start_frequency\0step_size\0num_points"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DDS[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::UInt, 0x00495003,
       6, QMetaType::UShort, 0x00495003,
       7, QMetaType::UShort, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void DDS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DDS *_t = static_cast<DDS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start_frequency_changed(); break;
        case 1: _t->step_size_changed(); break;
        case 2: _t->num_points_changed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DDS::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DDS::start_frequency_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (DDS::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DDS::step_size_changed)) {
                *result = 1;
            }
        }
        {
            typedef void (DDS::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DDS::num_points_changed)) {
                *result = 2;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        DDS *_t = static_cast<DDS *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->start_frequency(); break;
        case 1: *reinterpret_cast< quint16*>(_v) = _t->step_size(); break;
        case 2: *reinterpret_cast< quint16*>(_v) = _t->num_points(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        DDS *_t = static_cast<DDS *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_start_frequency(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->set_step_size(*reinterpret_cast< quint16*>(_v)); break;
        case 2: _t->set_num_points(*reinterpret_cast< quint16*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject DDS::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_DDS.data,
      qt_meta_data_DDS,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DDS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DDS::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DDS.stringdata0))
        return static_cast<void*>(const_cast< DDS*>(this));
    return AFMObject::qt_metacast(_clname);
}

int DDS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AFMObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DDS::start_frequency_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DDS::step_size_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DDS::num_points_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
