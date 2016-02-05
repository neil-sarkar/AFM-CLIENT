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
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AFM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AFM_t qt_meta_stringdata_AFM = {
    {
QT_MOC_LITERAL(0, 0, 3), // "AFM"
QT_MOC_LITERAL(1, 4, 10), // "sweep_done"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 19), // "peak_detection_done"
QT_MOC_LITERAL(4, 36, 4), // "init"
QT_MOC_LITERAL(5, 41, 22), // "coarse_frequency_sweep"
QT_MOC_LITERAL(6, 64, 20), // "fine_frequency_sweep"
QT_MOC_LITERAL(7, 85, 19), // "start_state_machine"
QT_MOC_LITERAL(8, 105, 9) // "find_peak"

    },
    "AFM\0sweep_done\0\0peak_detection_done\0"
    "init\0coarse_frequency_sweep\0"
    "fine_frequency_sweep\0start_state_machine\0"
    "find_peak"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AFM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AFM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AFM *_t = static_cast<AFM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sweep_done(); break;
        case 1: _t->peak_detection_done(); break;
        case 2: _t->init(); break;
        case 3: _t->coarse_frequency_sweep(); break;
        case 4: _t->fine_frequency_sweep(); break;
        case 5: _t->start_state_machine(); break;
        case 6: _t->find_peak(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::sweep_done)) {
                *result = 0;
            }
        }
        {
            typedef void (AFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::peak_detection_done)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void AFM::sweep_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void AFM::peak_detection_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
