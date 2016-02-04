/****************************************************************************
** Meta object code from reading C++ file 'serial_port.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/serial_port.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serial_port.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SerialPort_t {
    QByteArrayData data[16];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPort_t qt_meta_stringdata_SerialPort = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SerialPort"
QT_MOC_LITERAL(1, 11, 9), // "connected"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "disconnected"
QT_MOC_LITERAL(4, 35, 12), // "message_sent"
QT_MOC_LITERAL(5, 48, 12), // "CommandNode*"
QT_MOC_LITERAL(6, 61, 13), // "byte_received"
QT_MOC_LITERAL(7, 75, 13), // "on_ready_read"
QT_MOC_LITERAL(8, 89, 14), // "scan_for_ports"
QT_MOC_LITERAL(9, 104, 15), // "check_connected"
QT_MOC_LITERAL(10, 120, 10), // "write_byte"
QT_MOC_LITERAL(11, 131, 4), // "byte"
QT_MOC_LITERAL(12, 136, 15), // "execute_command"
QT_MOC_LITERAL(13, 152, 9), // "reset_mcu"
QT_MOC_LITERAL(14, 162, 18), // "initialize_reading"
QT_MOC_LITERAL(15, 181, 5) // "close"

    },
    "SerialPort\0connected\0\0disconnected\0"
    "message_sent\0CommandNode*\0byte_received\0"
    "on_ready_read\0scan_for_ports\0"
    "check_connected\0write_byte\0byte\0"
    "execute_command\0reset_mcu\0initialize_reading\0"
    "close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPort[] = {

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
       4,    1,   76,    2, 0x06 /* Public */,
       6,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   82,    2, 0x0a /* Public */,
       8,    0,   83,    2, 0x0a /* Public */,
       9,    0,   84,    2, 0x0a /* Public */,
      10,    1,   85,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      15,    0,   93,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Char,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Char,   11,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

       0        // eod
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialPort *_t = static_cast<SerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->message_sent((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 3: _t->byte_received((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 4: _t->on_ready_read(); break;
        case 5: _t->scan_for_ports(); break;
        case 6: _t->check_connected(); break;
        case 7: { int _r = _t->write_byte((*reinterpret_cast< char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->execute_command((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 9: _t->reset_mcu(); break;
        case 10: _t->initialize_reading(); break;
        case 11: _t->close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CommandNode* >(); break;
            }
            break;
        case 8:
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
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::connected)) {
                *result = 0;
            }
        }
        {
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::disconnected)) {
                *result = 1;
            }
        }
        {
            typedef void (SerialPort::*_t)(CommandNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::message_sent)) {
                *result = 2;
            }
        }
        {
            typedef void (SerialPort::*_t)(char );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::byte_received)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject SerialPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SerialPort.data,
      qt_meta_data_SerialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort.stringdata0))
        return static_cast<void*>(const_cast< SerialPort*>(this));
    return QObject::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void SerialPort::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SerialPort::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void SerialPort::message_sent(CommandNode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SerialPort::byte_received(char _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
