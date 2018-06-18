/****************************************************************************
** Meta object code from reading C++ file 'SpeechDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SpeechDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpeechDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpeechDlg_t {
    QByteArrayData data[10];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpeechDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpeechDlg_t qt_meta_stringdata_SpeechDlg = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SpeechDlg"
QT_MOC_LITERAL(1, 10, 15), // "slotRecordStart"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "slotRecordStop"
QT_MOC_LITERAL(4, 42, 15), // "slotRecordError"
QT_MOC_LITERAL(5, 58, 5), // "error"
QT_MOC_LITERAL(6, 64, 17), // "slotYaKitComplete"
QT_MOC_LITERAL(7, 82, 3), // "err"
QT_MOC_LITERAL(8, 86, 14), // "slotYaKitError"
QT_MOC_LITERAL(9, 101, 18) // "slotSend2Recognize"

    },
    "SpeechDlg\0slotRecordStart\0\0slotRecordStop\0"
    "slotRecordError\0error\0slotYaKitComplete\0"
    "err\0slotYaKitError\0slotSend2Recognize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpeechDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       8,    1,   52,    2, 0x08 /* Private */,
       9,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

       0        // eod
};

void SpeechDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpeechDlg *_t = static_cast<SpeechDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotRecordStart(); break;
        case 1: _t->slotRecordStop(); break;
        case 2: _t->slotRecordError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotYaKitComplete((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slotYaKitError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slotSend2Recognize(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpeechDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SpeechDlg.data,
      qt_meta_data_SpeechDlg,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SpeechDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpeechDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpeechDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SpeechDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
