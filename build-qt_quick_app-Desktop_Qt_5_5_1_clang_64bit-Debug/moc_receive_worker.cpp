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
    QByteArrayData data[8];
    char stringdata0[129];
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
QT_MOC_LITERAL(4, 55, 15), // "enqueue_command"
QT_MOC_LITERAL(5, 71, 12), // "CommandNode*"
QT_MOC_LITERAL(6, 84, 21), // "enqueue_response_byte"
QT_MOC_LITERAL(7, 106, 22) // "build_working_response"

    },
    "ReceiveWorker\0command_received\0\0"
    "response_byte_received\0enqueue_command\0"
    "CommandNode*\0enqueue_response_byte\0"
    "build_working_response"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReceiveWorker[] = {

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
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   41,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
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
        case 2: _t->enqueue_command((*reinterpret_cast< CommandNode*(*)>(_a[1]))); break;
        case 3: _t->enqueue_response_byte((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 4: _t->build_working_response(); break;
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
void ReceiveWorker::command_received()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ReceiveWorker::response_byte_received()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
