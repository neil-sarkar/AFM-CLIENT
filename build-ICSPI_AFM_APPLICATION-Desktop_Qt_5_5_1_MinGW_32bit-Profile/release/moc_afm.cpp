/****************************************************************************
** Meta object code from reading C++ file 'afm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/afm.h"
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
struct qt_meta_stringdata_icspiAFM_t {
    QByteArrayData data[7];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_icspiAFM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_icspiAFM_t qt_meta_stringdata_icspiAFM = {
    {
QT_MOC_LITERAL(0, 0, 8), // "icspiAFM"
QT_MOC_LITERAL(1, 9, 18), // "clearPayloadBuffer"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "addPayloadByte"
QT_MOC_LITERAL(4, 44, 4), // "byte"
QT_MOC_LITERAL(5, 49, 8), // "writeMsg"
QT_MOC_LITERAL(6, 58, 6) // "msg_id"

    },
    "icspiAFM\0clearPayloadBuffer\0\0"
    "addPayloadByte\0byte\0writeMsg\0msg_id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_icspiAFM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,
       5,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Int, QMetaType::Char,    4,
    QMetaType::Int, QMetaType::UChar,    6,

       0        // eod
};

void icspiAFM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        icspiAFM *_t = static_cast<icspiAFM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearPayloadBuffer(); break;
        case 1: { int _r = _t->addPayloadByte((*reinterpret_cast< char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->writeMsg((*reinterpret_cast< unsigned char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (icspiAFM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&icspiAFM::clearPayloadBuffer)) {
                *result = 0;
            }
        }
        {
            typedef int (icspiAFM::*_t)(char );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&icspiAFM::addPayloadByte)) {
                *result = 1;
            }
        }
        {
            typedef int (icspiAFM::*_t)(unsigned char );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&icspiAFM::writeMsg)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject icspiAFM::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_icspiAFM.data,
      qt_meta_data_icspiAFM,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *icspiAFM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *icspiAFM::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_icspiAFM.stringdata0))
        return static_cast<void*>(const_cast< icspiAFM*>(this));
    return QObject::qt_metacast(_clname);
}

int icspiAFM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void icspiAFM::clearPayloadBuffer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
int icspiAFM::addPayloadByte(char _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
int icspiAFM::writeMsg(unsigned char _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
