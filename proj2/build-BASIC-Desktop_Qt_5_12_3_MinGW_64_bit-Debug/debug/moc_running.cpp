/****************************************************************************
** Meta object code from reading C++ file 'running.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BASIC/running.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'running.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_running_t {
    QByteArrayData data[15];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_running_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_running_t qt_meta_stringdata_running = {
    {
QT_MOC_LITERAL(0, 0, 7), // "running"
QT_MOC_LITERAL(1, 8, 11), // "validfailed"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "writeToConsole"
QT_MOC_LITERAL(4, 36, 3), // "msg"
QT_MOC_LITERAL(5, 40, 16), // "setExpisInputing"
QT_MOC_LITERAL(6, 57, 2), // "is"
QT_MOC_LITERAL(7, 60, 3), // "run"
QT_MOC_LITERAL(8, 64, 14), // "QMap<int,node>"
QT_MOC_LITERAL(9, 79, 4), // "mapp"
QT_MOC_LITERAL(10, 84, 8), // "getInput"
QT_MOC_LITERAL(11, 93, 4), // "word"
QT_MOC_LITERAL(12, 98, 3), // "com"
QT_MOC_LITERAL(13, 102, 1), // "c"
QT_MOC_LITERAL(14, 104, 8) // "movement"

    },
    "running\0validfailed\0\0writeToConsole\0"
    "msg\0setExpisInputing\0is\0run\0QMap<int,node>\0"
    "mapp\0getInput\0word\0com\0c\0movement"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_running[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   51,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      12,    2,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   14,

       0        // eod
};

void running::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<running *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->validfailed(); break;
        case 1: _t->writeToConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setExpisInputing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->run((*reinterpret_cast< QMap<int,node>(*)>(_a[1]))); break;
        case 4: _t->getInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->com((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (running::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&running::validfailed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (running::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&running::writeToConsole)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (running::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&running::setExpisInputing)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject running::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_running.data,
    qt_meta_data_running,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *running::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *running::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_running.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int running::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void running::validfailed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void running::writeToConsole(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void running::setExpisInputing(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
