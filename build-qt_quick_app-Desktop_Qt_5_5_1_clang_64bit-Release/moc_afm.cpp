/****************************************************************************
** Meta object code from reading C++ file 'afm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/afm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'afm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AFM_t {
    QByteArrayData data[8];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AFM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AFM_t qt_meta_stringdata_AFM = {
    {
QT_MOC_LITERAL(0, 0, 3), // "AFM"
QT_MOC_LITERAL(1, 4, 17), // "command_generated"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "CommandNode*"
QT_MOC_LITERAL(4, 36, 13), // "dac_table_set"
QT_MOC_LITERAL(5, 50, 4), // "init"
QT_MOC_LITERAL(6, 55, 13), // "set_dac_table"
QT_MOC_LITERAL(7, 69, 24) // "cmd_generate_force_curve"

    },
    "AFM\0command_generated\0\0CommandNode*\0"
    "dac_table_set\0init\0set_dac_table\0"
    "cmd_generate_force_curve"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AFM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   45,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

       0        // eod
};

void AFM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AFM *_t = static_cast<AFM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->command_generated((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 1: _t->dac_table_set(); break;
        case 2: _t->init(); break;
        case 3: _t->set_dac_table(); break;
        case 4: _t->cmd_generate_force_curve(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            typedef void (AFM::*_t)(CommandNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::command_generated)) {
                *result = 0;
            }
        }
        {
            typedef void (AFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::dac_table_set)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AFM::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_AFM.data,
      qt_meta_data_AFM,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AFM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AFM::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AFM.stringdata0))
        return static_cast<void*>(const_cast< AFM*>(this));
    return AFMObject::qt_metacast(_clname);
}

int AFM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AFM::command_generated(CommandNode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AFM::dac_table_set()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
