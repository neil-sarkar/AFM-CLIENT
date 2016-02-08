/****************************************************************************
** Meta object code from reading C++ file 'motor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/motor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Motor_t {
    QByteArrayData data[11];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Motor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Motor_t qt_meta_stringdata_Motor = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Motor"
QT_MOC_LITERAL(1, 6, 13), // "speed_changed"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 17), // "direction_changed"
QT_MOC_LITERAL(4, 39, 13), // "state_changed"
QT_MOC_LITERAL(5, 53, 15), // "cmd_single_step"
QT_MOC_LITERAL(6, 69, 14), // "run_continuous"
QT_MOC_LITERAL(7, 84, 19), // "cmd_stop_continuous"
QT_MOC_LITERAL(8, 104, 5), // "speed"
QT_MOC_LITERAL(9, 110, 9), // "direction"
QT_MOC_LITERAL(10, 120, 5) // "state"

    },
    "Motor\0speed_changed\0\0direction_changed\0"
    "state_changed\0cmd_single_step\0"
    "run_continuous\0cmd_stop_continuous\0"
    "speed\0direction\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Motor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       3,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x02 /* Public */,
       6,    0,   48,    2, 0x02 /* Public */,
       7,    0,   49,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Int, 0x00495003,
       9, QMetaType::Int, 0x00495003,
      10, QMetaType::Int, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void Motor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Motor *_t = static_cast<Motor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->speed_changed(); break;
        case 1: _t->direction_changed(); break;
        case 2: _t->state_changed(); break;
        case 3: _t->cmd_single_step(); break;
        case 4: _t->run_continuous(); break;
        case 5: _t->cmd_stop_continuous(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Motor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Motor::speed_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (Motor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Motor::direction_changed)) {
                *result = 1;
            }
        }
        {
            typedef void (Motor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Motor::state_changed)) {
                *result = 2;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Motor *_t = static_cast<Motor *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->speed(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->direction(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->state(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Motor *_t = static_cast<Motor *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_speed(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->set_direction(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->set_state(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject Motor::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_Motor.data,
      qt_meta_data_Motor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Motor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Motor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Motor.stringdata0))
        return static_cast<void*>(const_cast< Motor*>(this));
    return AFMObject::qt_metacast(_clname);
}

int Motor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AFMObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
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
void Motor::speed_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Motor::direction_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Motor::state_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
