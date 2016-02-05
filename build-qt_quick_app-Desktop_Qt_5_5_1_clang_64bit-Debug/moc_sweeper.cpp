/****************************************************************************
** Meta object code from reading C++ file 'sweeper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/sweeper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sweeper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Sweeper_t {
    QByteArrayData data[12];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Sweeper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Sweeper_t qt_meta_stringdata_Sweeper = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Sweeper"
QT_MOC_LITERAL(1, 8, 19), // "initialization_done"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "sweep_done"
QT_MOC_LITERAL(4, 40, 19), // "peak_detection_done"
QT_MOC_LITERAL(5, 60, 21), // "peak_detection_failed"
QT_MOC_LITERAL(6, 82, 16), // "machine_finished"
QT_MOC_LITERAL(7, 99, 20), // "set_stable_frequency"
QT_MOC_LITERAL(8, 120, 15), // "frequency_sweep"
QT_MOC_LITERAL(9, 136, 9), // "find_peak"
QT_MOC_LITERAL(10, 146, 18), // "initialize_machine"
QT_MOC_LITERAL(11, 165, 19) // "start_state_machine"

    },
    "Sweeper\0initialization_done\0\0sweep_done\0"
    "peak_detection_done\0peak_detection_failed\0"
    "machine_finished\0set_stable_frequency\0"
    "frequency_sweep\0find_peak\0initialize_machine\0"
    "start_state_machine"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Sweeper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    0,   73,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

       0        // eod
};

void Sweeper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Sweeper *_t = static_cast<Sweeper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initialization_done(); break;
        case 1: _t->sweep_done(); break;
        case 2: _t->peak_detection_done(); break;
        case 3: _t->peak_detection_failed(); break;
        case 4: _t->machine_finished(); break;
        case 5: _t->set_stable_frequency(); break;
        case 6: _t->frequency_sweep(); break;
        case 7: { int _r = _t->find_peak();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->initialize_machine(); break;
        case 9: _t->start_state_machine(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Sweeper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sweeper::initialization_done)) {
                *result = 0;
            }
        }
        {
            typedef void (Sweeper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sweeper::sweep_done)) {
                *result = 1;
            }
        }
        {
            typedef void (Sweeper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sweeper::peak_detection_done)) {
                *result = 2;
            }
        }
        {
            typedef void (Sweeper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sweeper::peak_detection_failed)) {
                *result = 3;
            }
        }
        {
            typedef void (Sweeper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sweeper::machine_finished)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Sweeper::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_Sweeper.data,
      qt_meta_data_Sweeper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Sweeper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Sweeper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Sweeper.stringdata0))
        return static_cast<void*>(const_cast< Sweeper*>(this));
    return AFMObject::qt_metacast(_clname);
}

int Sweeper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AFMObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Sweeper::initialization_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Sweeper::sweep_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Sweeper::peak_detection_done()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Sweeper::peak_detection_failed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Sweeper::machine_finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
