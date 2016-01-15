/****************************************************************************
** Meta object code from reading C++ file 'send_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/send_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'send_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_send_worker_t {
    QByteArrayData data[11];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_send_worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_send_worker_t qt_meta_stringdata_send_worker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "send_worker"
QT_MOC_LITERAL(1, 12, 16), // "open_serial_port"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "serialPortName"
QT_MOC_LITERAL(4, 45, 9), // "baud_rate"
QT_MOC_LITERAL(5, 55, 17), // "close_serial_port"
QT_MOC_LITERAL(6, 73, 8), // "finished"
QT_MOC_LITERAL(7, 82, 15), // "updateStatusBar"
QT_MOC_LITERAL(8, 98, 7), // "_string"
QT_MOC_LITERAL(9, 106, 8), // "mainLoop"
QT_MOC_LITERAL(10, 115, 11) // "queue_check"

    },
    "send_worker\0open_serial_port\0\0"
    "serialPortName\0baud_rate\0close_serial_port\0"
    "finished\0updateStatusBar\0_string\0"
    "mainLoop\0queue_check"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_send_worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    0,   49,    2, 0x06 /* Public */,
       6,    0,   50,    2, 0x06 /* Public */,
       7,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   54,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void send_worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        send_worker *_t = static_cast<send_worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->open_serial_port((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->close_serial_port(); break;
        case 2: _t->finished(); break;
        case 3: _t->updateStatusBar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->mainLoop(); break;
        case 5: _t->queue_check(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef bool (send_worker::*_t)(QString , qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&send_worker::open_serial_port)) {
                *result = 0;
            }
        }
        {
            typedef void (send_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&send_worker::close_serial_port)) {
                *result = 1;
            }
        }
        {
            typedef void (send_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&send_worker::finished)) {
                *result = 2;
            }
        }
        {
            typedef void (send_worker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&send_worker::updateStatusBar)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject send_worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_send_worker.data,
      qt_meta_data_send_worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *send_worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *send_worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_send_worker.stringdata0))
        return static_cast<void*>(const_cast< send_worker*>(this));
    return QObject::qt_metacast(_clname);
}

int send_worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
bool send_worker::open_serial_port(QString _t1, qint32 _t2)
{
    bool _t0 = bool();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void send_worker::close_serial_port()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void send_worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void send_worker::updateStatusBar(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
