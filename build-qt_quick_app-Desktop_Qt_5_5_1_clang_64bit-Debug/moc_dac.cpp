/****************************************************************************
** Meta object code from reading C++ file 'dac.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/dac.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dac.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DAC_t {
    QByteArrayData data[12];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DAC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DAC_t qt_meta_stringdata_DAC = {
    {
QT_MOC_LITERAL(0, 0, 3), // "DAC"
QT_MOC_LITERAL(1, 4, 13), // "value_changed"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 10), // "id_changed"
QT_MOC_LITERAL(4, 30, 17), // "command_generated"
QT_MOC_LITERAL(5, 48, 12), // "CommandNode*"
QT_MOC_LITERAL(6, 61, 1), // "c"
QT_MOC_LITERAL(7, 63, 4), // "init"
QT_MOC_LITERAL(8, 68, 4), // "read"
QT_MOC_LITERAL(9, 73, 5), // "write"
QT_MOC_LITERAL(10, 79, 5), // "value"
QT_MOC_LITERAL(11, 85, 2) // "id"

    },
    "DAC\0value_changed\0\0id_changed\0"
    "command_generated\0CommandNode*\0c\0init\0"
    "read\0write\0value\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DAC[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    1,   46,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   49,    2, 0x02 /* Public */,
       8,    0,   50,    2, 0x02 /* Public */,
       9,    0,   51,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::Double, 0x00495003,
      11, QMetaType::Int, 0x00495003,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void DAC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DAC *_t = static_cast<DAC *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->value_changed(); break;
        case 1: _t->id_changed(); break;
        case 2: _t->command_generated((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 3: _t->init(); break;
        case 4: _t->read(); break;
        case 5: _t->write(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
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
            typedef void (DAC::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DAC::value_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (DAC::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DAC::id_changed)) {
                *result = 1;
            }
        }
        {
            typedef void (DAC::*_t)(CommandNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DAC::command_generated)) {
                *result = 2;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        DAC *_t = static_cast<DAC *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->value(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->id(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        DAC *_t = static_cast<DAC *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_value(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->set_id(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject DAC::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DAC.data,
      qt_meta_data_DAC,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DAC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DAC::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DAC.stringdata0))
        return static_cast<void*>(const_cast< DAC*>(this));
    return QObject::qt_metacast(_clname);
}

int DAC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
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
void DAC::value_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DAC::id_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DAC::command_generated(CommandNode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
