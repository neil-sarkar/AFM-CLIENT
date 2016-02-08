/****************************************************************************
** Meta object code from reading C++ file 'scanner.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/scanner.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Scanner_t {
    QByteArrayData data[10];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scanner_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scanner_t qt_meta_stringdata_Scanner = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Scanner"
QT_MOC_LITERAL(1, 8, 27), // "scanner_initialization_done"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 25), // "set_signal_generator_done"
QT_MOC_LITERAL(4, 63, 17), // "all_data_received"
QT_MOC_LITERAL(5, 81, 29), // "initialize_scan_state_machine"
QT_MOC_LITERAL(6, 111, 20), // "set_signal_generator"
QT_MOC_LITERAL(7, 132, 12), // "receive_data"
QT_MOC_LITERAL(8, 145, 22), // "end_scan_state_machine"
QT_MOC_LITERAL(9, 168, 19) // "start_state_machine"

    },
    "Scanner\0scanner_initialization_done\0"
    "\0set_signal_generator_done\0all_data_received\0"
    "initialize_scan_state_machine\0"
    "set_signal_generator\0receive_data\0"
    "end_scan_state_machine\0start_state_machine"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scanner[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
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

void Scanner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Scanner *_t = static_cast<Scanner *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scanner_initialization_done(); break;
        case 1: _t->set_signal_generator_done(); break;
        case 2: _t->all_data_received(); break;
        case 3: _t->initialize_scan_state_machine(); break;
        case 4: _t->set_signal_generator(); break;
        case 5: _t->receive_data(); break;
        case 6: _t->end_scan_state_machine(); break;
        case 7: _t->start_state_machine(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Scanner::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scanner::scanner_initialization_done)) {
                *result = 0;
            }
        }
        {
            typedef void (Scanner::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scanner::set_signal_generator_done)) {
                *result = 1;
            }
        }
        {
            typedef void (Scanner::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scanner::all_data_received)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Scanner::staticMetaObject = {
    { &AFMObject::staticMetaObject, qt_meta_stringdata_Scanner.data,
      qt_meta_data_Scanner,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Scanner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scanner::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Scanner.stringdata0))
        return static_cast<void*>(const_cast< Scanner*>(this));
    return AFMObject::qt_metacast(_clname);
}

int Scanner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AFMObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Scanner::scanner_initialization_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Scanner::set_signal_generator_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Scanner::all_data_received()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
