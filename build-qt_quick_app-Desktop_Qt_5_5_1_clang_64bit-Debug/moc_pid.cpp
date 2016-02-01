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
    QByteArrayData data[13];
    char stringdata0[159];
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
QT_MOC_LITERAL(5, 62, 17), // "set_point_changed"
QT_MOC_LITERAL(6, 80, 17), // "command_generated"
QT_MOC_LITERAL(7, 98, 12), // "CommandNode*"
QT_MOC_LITERAL(8, 111, 4), // "node"
QT_MOC_LITERAL(9, 116, 12), // "proportional"
QT_MOC_LITERAL(10, 129, 8), // "integral"
QT_MOC_LITERAL(11, 138, 10), // "derivative"
QT_MOC_LITERAL(12, 149, 9) // "set_point"

    },
    "PID\0proportional_changed\0\0integral_changed\0"
    "derivative_changed\0set_point_changed\0"
    "command_generated\0CommandNode*\0node\0"
    "proportional\0integral\0derivative\0"
    "set_point"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PID[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       4,   46, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

 // properties: name, type, flags
       9, QMetaType::Float, 0x00495003,
      10, QMetaType::Float, 0x00495003,
      11, QMetaType::Float, 0x00495003,
      12, QMetaType::Float, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

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
        case 3: _t->set_point_changed(); break;
        case 4: _t->command_generated((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CommandNode* >(); break;
            }
            break;
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
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::set_point_changed)) {
                *result = 3;
            }
        }
        {
            typedef void (PID::*_t)(CommandNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::command_generated)) {
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
        case 3: *reinterpret_cast< float*>(_v) = _t->set_point(); break;
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
        case 3: _t->set_set_point(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject PID::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PID.data,
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
    return QObject::qt_metacast(_clname);
}

int PID::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
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
void PID::set_point_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PID::command_generated(CommandNode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
