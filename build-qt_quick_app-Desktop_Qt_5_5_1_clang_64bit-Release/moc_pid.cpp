/****************************************************************************
** Meta object code from reading C++ file 'pid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/pid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PID_t {
    QByteArrayData data[15];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PID_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PID_t qt_meta_stringdata_PID = {
    {
QT_MOC_LITERAL(0, 0, 3), // "PID"
QT_MOC_LITERAL(1, 4, 20), // "proportional_changed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "integral_changed"
QT_MOC_LITERAL(4, 43, 18), // "derivative_changed"
QT_MOC_LITERAL(5, 62, 16), // "setpoint_changed"
QT_MOC_LITERAL(6, 79, 15), // "enabled_changed"
QT_MOC_LITERAL(7, 95, 11), // "set_enabled"
QT_MOC_LITERAL(8, 107, 1), // "e"
QT_MOC_LITERAL(9, 109, 12), // "set_disabled"
QT_MOC_LITERAL(10, 122, 12), // "proportional"
QT_MOC_LITERAL(11, 135, 8), // "integral"
QT_MOC_LITERAL(12, 144, 10), // "derivative"
QT_MOC_LITERAL(13, 155, 8), // "setpoint"
QT_MOC_LITERAL(14, 164, 7) // "enabled"

    },
    "PID\0proportional_changed\0\0integral_changed\0"
    "derivative_changed\0setpoint_changed\0"
    "enabled_changed\0set_enabled\0e\0"
    "set_disabled\0proportional\0integral\0"
    "derivative\0setpoint\0enabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PID[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       5,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   59,    2, 0x02 /* Public */,
       7,    0,   62,    2, 0x22 /* Public | MethodCloned */,
       9,    0,   63,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::Float, 0x00495003,
      11, QMetaType::Float, 0x00495003,
      12, QMetaType::Float, 0x00495003,
      13, QMetaType::Float, 0x00495003,
      14, QMetaType::Bool, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void PID::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PID *_t = static_cast<PID *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->proportional_changed(); break;
        case 1: _t->integral_changed(); break;
        case 2: _t->derivative_changed(); break;
        case 3: _t->setpoint_changed(); break;
        case 4: _t->enabled_changed(); break;
        case 5: _t->set_enabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->set_enabled(); break;
        case 7: _t->set_disabled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PID::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::proportional_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (PID::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::integral_changed)) {
                *result = 1;
            }
        }
        {
            typedef void (PID::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::derivative_changed)) {
                *result = 2;
            }
        }
        {
            typedef void (PID::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::setpoint_changed)) {
                *result = 3;
            }
        }
        {
            typedef void (PID::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::enabled_changed)) {
                *result = 4;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        PID *_t = static_cast<PID *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->proportional(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->integral(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->derivative(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->setpoint(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->enabled(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        PID *_t = static_cast<PID *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_proportional(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->set_integral(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->set_derivative(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->set_setpoint(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->set_enabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject PID::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_PID.data,
      qt_meta_data_PID,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PID::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PID::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PID.stringdata0))
        return static_cast<void*>(const_cast< PID*>(this));
    return AFMObject::qt_metacast(_clname);
}

int PID::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AFMObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PID::proportional_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PID::integral_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PID::derivative_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PID::setpoint_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PID::enabled_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
