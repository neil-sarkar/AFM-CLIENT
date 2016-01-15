/****************************************************************************
** Meta object code from reading C++ file 'afm_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/afm_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'afm_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_afm_worker_t {
    QByteArrayData data[21];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_afm_worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_afm_worker_t qt_meta_stringdata_afm_worker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "afm_worker"
QT_MOC_LITERAL(1, 11, 17), // "process_uart_resp"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "new_uart_resp"
QT_MOC_LITERAL(4, 44, 15), // "push_recv_queue"
QT_MOC_LITERAL(5, 60, 10), // "message_id"
QT_MOC_LITERAL(6, 71, 11), // "message_tag"
QT_MOC_LITERAL(7, 83, 16), // "writeByte_result"
QT_MOC_LITERAL(8, 100, 8), // "finished"
QT_MOC_LITERAL(9, 109, 16), // "init_serial_port"
QT_MOC_LITERAL(10, 126, 16), // "open_serial_port"
QT_MOC_LITERAL(11, 143, 14), // "serialPortName"
QT_MOC_LITERAL(12, 158, 9), // "baud_rate"
QT_MOC_LITERAL(13, 168, 17), // "close_serial_port"
QT_MOC_LITERAL(14, 186, 19), // "serial_port_is_open"
QT_MOC_LITERAL(15, 206, 18), // "clearPayloadBuffer"
QT_MOC_LITERAL(16, 225, 14), // "addPayloadByte"
QT_MOC_LITERAL(17, 240, 4), // "byte"
QT_MOC_LITERAL(18, 245, 8), // "writeMsg"
QT_MOC_LITERAL(19, 254, 6), // "msg_id"
QT_MOC_LITERAL(20, 261, 11) // "onReadyRead"

    },
    "afm_worker\0process_uart_resp\0\0"
    "new_uart_resp\0push_recv_queue\0message_id\0"
    "message_tag\0writeByte_result\0finished\0"
    "init_serial_port\0open_serial_port\0"
    "serialPortName\0baud_rate\0close_serial_port\0"
    "serial_port_is_open\0clearPayloadBuffer\0"
    "addPayloadByte\0byte\0writeMsg\0msg_id\0"
    "onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_afm_worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    3,   72,    2, 0x06 /* Public */,
       8,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   80,    2, 0x0a /* Public */,
      10,    2,   81,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,
      15,    0,   88,    2, 0x0a /* Public */,
      16,    1,   89,    2, 0x0a /* Public */,
      18,    1,   92,    2, 0x0a /* Public */,
      20,    0,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::Int,    5,    6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char,   17,
    QMetaType::Void, QMetaType::UChar,   19,
    QMetaType::Void,

       0        // eod
};

void afm_worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        afm_worker *_t = static_cast<afm_worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->process_uart_resp((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->push_recv_queue((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->finished(); break;
        case 3: _t->init_serial_port(); break;
        case 4: { bool _r = _t->open_serial_port((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->close_serial_port(); break;
        case 6: { bool _r = _t->serial_port_is_open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->clearPayloadBuffer(); break;
        case 8: _t->addPayloadByte((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 9: _t->writeMsg((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 10: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (afm_worker::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&afm_worker::process_uart_resp)) {
                *result = 0;
            }
        }
        {
            typedef void (afm_worker::*_t)(unsigned char , unsigned char , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&afm_worker::push_recv_queue)) {
                *result = 1;
            }
        }
        {
            typedef void (afm_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&afm_worker::finished)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject afm_worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_afm_worker.data,
      qt_meta_data_afm_worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *afm_worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *afm_worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_afm_worker.stringdata0))
        return static_cast<void*>(const_cast< afm_worker*>(this));
    return QObject::qt_metacast(_clname);
}

int afm_worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void afm_worker::process_uart_resp(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void afm_worker::push_recv_queue(unsigned char _t1, unsigned char _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void afm_worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
