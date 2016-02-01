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
    QByteArrayData data[18];
    char stringdata0[210];
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
QT_MOC_LITERAL(6, 80, 15), // "enabled_changed"
QT_MOC_LITERAL(7, 96, 17), // "command_generated"
QT_MOC_LITERAL(8, 114, 12), // "CommandNode*"
QT_MOC_LITERAL(9, 127, 4), // "node"
QT_MOC_LITERAL(10, 132, 11), // "set_enabled"
QT_MOC_LITERAL(11, 144, 1), // "e"
QT_MOC_LITERAL(12, 146, 12), // "set_disabled"
QT_MOC_LITERAL(13, 159, 12), // "proportional"
QT_MOC_LITERAL(14, 172, 8), // "integral"
QT_MOC_LITERAL(15, 181, 10), // "derivative"
QT_MOC_LITERAL(16, 192, 9), // "set_point"
QT_MOC_LITERAL(17, 202, 7) // "enabled"

    },
    "PID\0proportional_changed\0\0integral_changed\0"
    "derivative_changed\0set_point_changed\0"
    "enabled_changed\0command_generated\0"
    "CommandNode*\0node\0set_enabled\0e\0"
    "set_disabled\0proportional\0integral\0"
    "derivative\0set_point\0enabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PID[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       5,   72, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    0,   63,    2, 0x06 /* Public */,
       7,    1,   64,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      10,    1,   67,    2, 0x02 /* Public */,
      10,    0,   70,    2, 0x22 /* Public | MethodCloned */,
      12,    0,   71,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

 // methods: parameters
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      13, QMetaType::Float, 0x00495003,
      14, QMetaType::Float, 0x00495003,
      15, QMetaType::Float, 0x00495003,
      16, QMetaType::Float, 0x00495003,
      17, QMetaType::Bool, 0x00495003,

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
        case 3: _t->set_point_changed(); break;
        case 4: _t->enabled_changed(); break;
        case 5: _t->command_generated((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 6: _t->set_enabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->set_enabled(); break;
        case 8: _t->set_disabled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            typedef void (PID::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::enabled_changed)) {
                *result = 4;
            }
        }
        {
            typedef void (PID::*_t)(CommandNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PID::command_generated)) {
                *result = 5;
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
        case 3: _t->set_set_point(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->set_enabled(*reinterpret_cast< bool*>(_v)); break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
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
void PID::set_point_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PID::enabled_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void PID::command_generated(CommandNode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
