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
    QByteArrayData data[15];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AFM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AFM_t qt_meta_stringdata_AFM = {
    {
QT_MOC_LITERAL(0, 0, 3), // "AFM"
QT_MOC_LITERAL(1, 4, 27), // "scanner_initialization_done"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 25), // "set_signal_generator_done"
QT_MOC_LITERAL(4, 59, 17), // "all_data_received"
QT_MOC_LITERAL(5, 77, 17), // "command_generated"
QT_MOC_LITERAL(6, 95, 12), // "CommandNode*"
QT_MOC_LITERAL(7, 108, 4), // "init"
QT_MOC_LITERAL(8, 113, 13), // "set_dac_table"
QT_MOC_LITERAL(9, 127, 24), // "start_scan_state_machine"
QT_MOC_LITERAL(10, 152, 24), // "scan_state_machine_setup"
QT_MOC_LITERAL(11, 177, 29), // "initialize_scan_state_machine"
QT_MOC_LITERAL(12, 207, 20), // "set_signal_generator"
QT_MOC_LITERAL(13, 228, 12), // "receive_data"
QT_MOC_LITERAL(14, 241, 22) // "end_scan_state_machine"

    },
    "AFM\0scanner_initialization_done\0\0"
    "set_signal_generator_done\0all_data_received\0"
    "command_generated\0CommandNode*\0init\0"
    "set_dac_table\0start_scan_state_machine\0"
    "scan_state_machine_setup\0"
    "initialize_scan_state_machine\0"
    "set_signal_generator\0receive_data\0"
    "end_scan_state_machine"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AFM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   80,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x0a /* Public */,
      10,    0,   83,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->scanner_initialization_done(); break;
        case 1: _t->set_signal_generator_done(); break;
        case 2: _t->all_data_received(); break;
        case 3: _t->command_generated((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 4: _t->init(); break;
        case 5: _t->set_dac_table(); break;
        case 6: _t->start_scan_state_machine(); break;
        case 7: _t->scan_state_machine_setup(); break;
        case 8: _t->initialize_scan_state_machine(); break;
        case 9: _t->set_signal_generator(); break;
        case 10: _t->receive_data(); break;
        case 11: _t->end_scan_state_machine(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
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
            typedef void (AFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::scanner_initialization_done)) {
                *result = 0;
            }
        }
        {
            typedef void (AFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::set_signal_generator_done)) {
                *result = 1;
            }
        }
        {
            typedef void (AFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::all_data_received)) {
                *result = 2;
            }
        }
        {
            typedef void (AFM::*_t)(CommandNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AFM::command_generated)) {
                *result = 3;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void AFM::scanner_initialization_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void AFM::set_signal_generator_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void AFM::all_data_received()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void AFM::command_generated(CommandNode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
