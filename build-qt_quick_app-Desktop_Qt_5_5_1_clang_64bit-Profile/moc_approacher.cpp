/****************************************************************************
** Meta object code from reading C++ file 'approacher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/approacher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'approacher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Approacher_t {
    QByteArrayData data[10];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Approacher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Approacher_t qt_meta_stringdata_Approacher = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Approacher"
QT_MOC_LITERAL(1, 11, 16), // "setpoint_changed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "state_changed"
QT_MOC_LITERAL(4, 43, 33), // "handle_auto_approach_info_mes..."
QT_MOC_LITERAL(5, 77, 16), // "working_response"
QT_MOC_LITERAL(6, 94, 23), // "cmd_start_auto_approach"
QT_MOC_LITERAL(7, 118, 22), // "cmd_stop_auto_approach"
QT_MOC_LITERAL(8, 141, 8), // "setpoint"
QT_MOC_LITERAL(9, 150, 5) // "state"

    },
    "Approacher\0setpoint_changed\0\0state_changed\0"
    "handle_auto_approach_info_message\0"
    "working_response\0cmd_start_auto_approach\0"
    "cmd_stop_auto_approach\0setpoint\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Approacher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   46, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   41,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   44,    2, 0x02 /* Public */,
       7,    0,   45,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    5,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Double, 0x00495003,
       9, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void Approacher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Approacher *_t = static_cast<Approacher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setpoint_changed(); break;
        case 1: _t->state_changed(); break;
        case 2: _t->handle_auto_approach_info_message((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->cmd_start_auto_approach(); break;
        case 4: _t->cmd_stop_auto_approach(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Approacher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Approacher::setpoint_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (Approacher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Approacher::state_changed)) {
                *result = 1;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Approacher *_t = static_cast<Approacher *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->setpoint(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->state(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Approacher *_t = static_cast<Approacher *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_setpoint(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Approacher::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_Approacher.data,
      qt_meta_data_Approacher,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Approacher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Approacher::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Approacher.stringdata0))
        return static_cast<void*>(const_cast< Approacher*>(this));
    return AFMObject::qt_metacast(_clname);
}

int Approacher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AFMObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Approacher::setpoint_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Approacher::state_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
