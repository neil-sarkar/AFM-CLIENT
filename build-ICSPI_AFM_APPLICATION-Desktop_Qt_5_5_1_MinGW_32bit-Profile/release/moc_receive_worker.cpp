/****************************************************************************
** Meta object code from reading C++ file 'receive_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/receive_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receive_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_receive_worker_t {
    QByteArrayData data[16];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_receive_worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_receive_worker_t qt_meta_stringdata_receive_worker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "receive_worker"
QT_MOC_LITERAL(1, 15, 8), // "finished"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "serialError"
QT_MOC_LITERAL(4, 37, 19), // "serial_port_is_open"
QT_MOC_LITERAL(5, 57, 10), // "getNextMsg"
QT_MOC_LITERAL(6, 68, 22), // "afm_worker_onReadyRead"
QT_MOC_LITERAL(7, 91, 12), // "afm_callback"
QT_MOC_LITERAL(8, 104, 18), // "callback_operation"
QT_MOC_LITERAL(9, 123, 8), // "mainLoop"
QT_MOC_LITERAL(10, 132, 17), // "process_uart_resp"
QT_MOC_LITERAL(11, 150, 13), // "new_uart_resp"
QT_MOC_LITERAL(12, 164, 15), // "push_recv_queue"
QT_MOC_LITERAL(13, 180, 10), // "message_id"
QT_MOC_LITERAL(14, 191, 11), // "message_tag"
QT_MOC_LITERAL(15, 203, 16) // "writeByte_result"

    },
    "receive_worker\0finished\0\0serialError\0"
    "serial_port_is_open\0getNextMsg\0"
    "afm_worker_onReadyRead\0afm_callback\0"
    "callback_operation\0mainLoop\0"
    "process_uart_resp\0new_uart_resp\0"
    "push_recv_queue\0message_id\0message_tag\0"
    "writeByte_result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_receive_worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
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

 // slots: name, argc, parameters, tag, flags
       9,    0,   67,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      12,    3,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   11,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::Int,   13,   14,   15,

       0        // eod
};

void receive_worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        receive_worker *_t = static_cast<receive_worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->serialError(); break;
        case 2: { bool _r = _t->serial_port_is_open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->getNextMsg(); break;
        case 4: _t->afm_worker_onReadyRead(); break;
        case 5: _t->afm_callback((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->mainLoop(); break;
        case 7: _t->process_uart_resp((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->push_recv_queue((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (receive_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&receive_worker::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (receive_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&receive_worker::serialError)) {
                *result = 1;
            }
        }
        {
            typedef bool (receive_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&receive_worker::serial_port_is_open)) {
                *result = 2;
            }
        }
        {
            typedef void (receive_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&receive_worker::getNextMsg)) {
                *result = 3;
            }
        }
        {
            typedef void (receive_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&receive_worker::afm_worker_onReadyRead)) {
                *result = 4;
            }
        }
        {
            typedef void (receive_worker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&receive_worker::afm_callback)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject receive_worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_receive_worker.data,
      qt_meta_data_receive_worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *receive_worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *receive_worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_receive_worker.stringdata0))
        return static_cast<void*>(const_cast< receive_worker*>(this));
    return QObject::qt_metacast(_clname);
}

int receive_worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void receive_worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void receive_worker::serialError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
bool receive_worker::serial_port_is_open()
{
    bool _t0 = bool();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
void receive_worker::getNextMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void receive_worker::afm_worker_onReadyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void receive_worker::afm_callback(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
