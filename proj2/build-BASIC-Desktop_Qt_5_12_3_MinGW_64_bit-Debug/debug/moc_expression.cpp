/****************************************************************************
** Meta object code from reading C++ file 'expression.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BASIC/expression.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'expression.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_expression_t {
    QByteArrayData data[14];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_expression_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_expression_t qt_meta_stringdata_expression = {
    {
QT_MOC_LITERAL(0, 0, 10), // "expression"
QT_MOC_LITERAL(1, 11, 14), // "writeToConsole"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "msg"
QT_MOC_LITERAL(4, 31, 4), // "quit"
QT_MOC_LITERAL(5, 36, 3), // "run"
QT_MOC_LITERAL(6, 40, 14), // "QMap<int,node>"
QT_MOC_LITERAL(7, 55, 3), // "map"
QT_MOC_LITERAL(8, 59, 3), // "com"
QT_MOC_LITERAL(9, 63, 8), // "movement"
QT_MOC_LITERAL(10, 72, 13), // "getExpression"
QT_MOC_LITERAL(11, 86, 11), // "validfailed"
QT_MOC_LITERAL(12, 98, 13), // "setisInputing"
QT_MOC_LITERAL(13, 112, 2) // "is"

    },
    "expression\0writeToConsole\0\0msg\0quit\0"
    "run\0QMap<int,node>\0map\0com\0movement\0"
    "getExpression\0validfailed\0setisInputing\0"
    "is"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_expression[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       8,    2,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   61,    2, 0x0a /* Public */,
      11,    0,   64,    2, 0x0a /* Public */,
      12,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    0,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void expression::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<expression *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->writeToConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->quit(); break;
        case 2: _t->run((*reinterpret_cast< QMap<int,node>(*)>(_a[1]))); break;
        case 3: _t->com((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->getExpression((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->validfailed(); break;
        case 6: _t->setisInputing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (expression::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&expression::writeToConsole)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (expression::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&expression::quit)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (expression::*)(QMap<int,node> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&expression::run)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (expression::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&expression::com)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject expression::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_expression.data,
    qt_meta_data_expression,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *expression::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *expression::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_expression.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int expression::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void expression::writeToConsole(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void expression::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void expression::run(QMap<int,node> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void expression::com(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
