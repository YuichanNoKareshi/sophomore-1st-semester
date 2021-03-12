/****************************************************************************
** Meta object code from reading C++ file 'WordListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QBoggle/WordListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WordListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WordListWidget_t {
    QByteArrayData data[15];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WordListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WordListWidget_t qt_meta_stringdata_WordListWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "WordListWidget"
QT_MOC_LITERAL(1, 15, 2), // "w1"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "word"
QT_MOC_LITERAL(4, 24, 8), // "isPolish"
QT_MOC_LITERAL(5, 33, 5), // "write"
QT_MOC_LITERAL(6, 39, 3), // "msg"
QT_MOC_LITERAL(7, 43, 9), // "megetword"
QT_MOC_LITERAL(8, 53, 15), // "computergetword"
QT_MOC_LITERAL(9, 69, 2), // "w2"
QT_MOC_LITERAL(10, 72, 6), // "polish"
QT_MOC_LITERAL(11, 79, 10), // "polishlett"
QT_MOC_LITERAL(12, 90, 8), // "QString*"
QT_MOC_LITERAL(13, 99, 4), // "lett"
QT_MOC_LITERAL(14, 104, 4) // "size"

    },
    "WordListWidget\0w1\0\0word\0isPolish\0write\0"
    "msg\0megetword\0computergetword\0w2\0"
    "polish\0polishlett\0QString*\0lett\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WordListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   61,    2, 0x0a /* Public */,
       8,    1,   64,    2, 0x0a /* Public */,
       9,    1,   67,    2, 0x0a /* Public */,
      10,    0,   70,    2, 0x0a /* Public */,
      11,    2,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,

       0        // eod
};

void WordListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WordListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->w1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->isPolish(); break;
        case 2: _t->write((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->megetword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->computergetword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->w2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->polish(); break;
        case 7: _t->polishlett((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WordListWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordListWidget::w1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WordListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordListWidget::isPolish)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WordListWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordListWidget::write)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WordListWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_WordListWidget.data,
    qt_meta_data_WordListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WordListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WordListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WordListWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WordListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void WordListWidget::w1(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WordListWidget::isPolish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WordListWidget::write(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
