/****************************************************************************
** Meta object code from reading C++ file 'replacedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mynotpad/replacedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'replacedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_replacedialog_t {
    QByteArrayData data[9];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_replacedialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_replacedialog_t qt_meta_stringdata_replacedialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "replacedialog"
QT_MOC_LITERAL(1, 14, 20), // "signal_replaceAllStr"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 23), // "signal_replaceCurOneStr"
QT_MOC_LITERAL(4, 60, 21), // "signal_findReplaceStr"
QT_MOC_LITERAL(5, 82, 15), // "slot_choose_str"
QT_MOC_LITERAL(6, 98, 22), // "slot_find_button_state"
QT_MOC_LITERAL(7, 121, 29), // "slot_replace_one_button_state"
QT_MOC_LITERAL(8, 151, 29) // "slot_repalce_all_button_state"

    },
    "replacedialog\0signal_replaceAllStr\0\0"
    "signal_replaceCurOneStr\0signal_findReplaceStr\0"
    "slot_choose_str\0slot_find_button_state\0"
    "slot_replace_one_button_state\0"
    "slot_repalce_all_button_state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_replacedialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       3,    2,   56,    2, 0x06 /* Public */,
       4,    2,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   66,    2, 0x0a /* Public */,
       6,    0,   67,    2, 0x0a /* Public */,
       7,    0,   68,    2, 0x0a /* Public */,
       8,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void replacedialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        replacedialog *_t = static_cast<replacedialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_replaceAllStr((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->signal_replaceCurOneStr((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->signal_findReplaceStr((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->slot_choose_str(); break;
        case 4: _t->slot_find_button_state(); break;
        case 5: _t->slot_replace_one_button_state(); break;
        case 6: _t->slot_repalce_all_button_state(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (replacedialog::*_t)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&replacedialog::signal_replaceAllStr)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (replacedialog::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&replacedialog::signal_replaceCurOneStr)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (replacedialog::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&replacedialog::signal_findReplaceStr)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject replacedialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_replacedialog.data,
      qt_meta_data_replacedialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *replacedialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *replacedialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_replacedialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int replacedialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void replacedialog::signal_replaceAllStr(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void replacedialog::signal_replaceCurOneStr(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void replacedialog::signal_findReplaceStr(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
