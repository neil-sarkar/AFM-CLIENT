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
    QByteArrayData data[9];
    char stringdata0[73];
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
QT_MOC_LITERAL(4, 30, 4), // "init"
QT_MOC_LITERAL(5, 35, 14), // "cmd_read_value"
QT_MOC_LITERAL(6, 50, 13), // "cmd_set_value"
QT_MOC_LITERAL(7, 64, 5), // "value"
QT_MOC_LITERAL(8, 70, 2) // "id"

    },
    "DAC\0value_changed\0\0id_changed\0init\0"
    "cmd_read_value\0cmd_set_value\0value\0"
    "id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DAC[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x02 /* Public */,
       5,    0,   42,    2, 0x02 /* Public */,
       6,    0,   43,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Double, 0x00495003,
       8, QMetaType::Int, 0x00495003,

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
        case 2: _t->init(); break;
        case 3: _t->cmd_read_value(); break;
        case 4: _t->cmd_set_value(); break;
        default: ;
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
    Q_UNUSED(_a);
}

const QMetaObject DAC::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_DAC.data,
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
    return AFMObject::qt_metacast(_clname);
}

int DAC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DAC::value_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DAC::id_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
