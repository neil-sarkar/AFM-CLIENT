/****************************************************************************
** Meta object code from reading C++ file 'receive_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_quick_app/receive_worker.h"
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
struct qt_meta_stringdata_ReceiveWorker_t {
    QByteArrayData data[11];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReceiveWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReceiveWorker_t qt_meta_stringdata_ReceiveWorker = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ReceiveWorker"
QT_MOC_LITERAL(1, 14, 16), // "command_received"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 22), // "response_byte_received"
QT_MOC_LITERAL(4, 55, 26), // "mcu_reset_message_received"
QT_MOC_LITERAL(5, 82, 27), // "auto_approach_info_received"
QT_MOC_LITERAL(6, 110, 11), // "serial_read"
QT_MOC_LITERAL(7, 122, 15), // "enqueue_command"
QT_MOC_LITERAL(8, 138, 12), // "CommandNode*"
QT_MOC_LITERAL(9, 151, 21), // "enqueue_response_byte"
QT_MOC_LITERAL(10, 173, 22) // "build_working_response"

    },
    "ReceiveWorker\0command_received\0\0"
    "response_byte_received\0"
    "mcu_reset_message_received\0"
    "auto_approach_info_received\0serial_read\0"
    "enqueue_command\0CommandNode*\0"
    "enqueue_response_byte\0build_working_response"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReceiveWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::Char,    2,
    QMetaType::Void,

       0        // eod
};

void ReceiveWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ReceiveWorker *_t = static_cast<ReceiveWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->command_received(); break;
        case 1: _t->response_byte_received(); break;
        case 2: _t->mcu_reset_message_received(); break;
        case 3: _t->auto_approach_info_received((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->serial_read(); break;
        case 5: _t->enqueue_command((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 6: _t->enqueue_response_byte((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 7: _t->build_working_response(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::command_received)) {
                *result = 0;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::response_byte_received)) {
                *result = 1;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::mcu_reset_message_received)) {
                *result = 2;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::auto_approach_info_received)) {
                *result = 3;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::serial_read)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject ReceiveWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReceiveWorker.data,
      qt_meta_data_ReceiveWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ReceiveWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReceiveWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ReceiveWorker.stringdata0))
        return static_cast<void*>(const_cast< ReceiveWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int ReceiveWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ReceiveWorker::command_received()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ReceiveWorker::response_byte_received()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ReceiveWorker::mcu_reset_message_received()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ReceiveWorker::auto_approach_info_received(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ReceiveWorker::serial_read()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
