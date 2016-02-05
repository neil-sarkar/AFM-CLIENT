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
    QByteArrayData data[4];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Approacher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Approacher_t qt_meta_stringdata_Approacher = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Approacher"
QT_MOC_LITERAL(1, 11, 23), // "cmd_start_auto_approach"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 22) // "cmd_stop_auto_approach"

    },
    "Approacher\0cmd_start_auto_approach\0\0"
    "cmd_stop_auto_approach"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Approacher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x02 /* Public */,
       3,    0,   25,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Approacher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Approacher *_t = static_cast<Approacher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cmd_start_auto_approach(); break;
        case 1: _t->cmd_stop_auto_approach(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
