/****************************************************************************
** Meta object code from reading C++ file 'Recorder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Recorder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Recorder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Recorder_t {
    QByteArrayData data[14];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Recorder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Recorder_t qt_meta_stringdata_Recorder = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Recorder"
QT_MOC_LITERAL(1, 9, 16), // "sigRecordStarted"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "sigRecordStoped"
QT_MOC_LITERAL(4, 43, 15), // "sigRecordPaused"
QT_MOC_LITERAL(5, 59, 14), // "sigRecordError"
QT_MOC_LITERAL(6, 74, 5), // "error"
QT_MOC_LITERAL(7, 80, 16), // "slotBufferProbed"
QT_MOC_LITERAL(8, 97, 12), // "QAudioBuffer"
QT_MOC_LITERAL(9, 110, 3), // "buf"
QT_MOC_LITERAL(10, 114, 24), // "slotRecorderStateChanged"
QT_MOC_LITERAL(11, 139, 21), // "QMediaRecorder::State"
QT_MOC_LITERAL(12, 161, 5), // "state"
QT_MOC_LITERAL(13, 167, 18) // "slotDRecorderError"

    },
    "Recorder\0sigRecordStarted\0\0sigRecordStoped\0"
    "sigRecordPaused\0sigRecordError\0error\0"
    "slotBufferProbed\0QAudioBuffer\0buf\0"
    "slotRecorderStateChanged\0QMediaRecorder::State\0"
    "state\0slotDRecorderError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Recorder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   55,    2, 0x08 /* Private */,
      10,    1,   58,    2, 0x08 /* Private */,
      13,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void Recorder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Recorder *_t = static_cast<Recorder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigRecordStarted(); break;
        case 1: _t->sigRecordStoped(); break;
        case 2: _t->sigRecordPaused(); break;
        case 3: _t->sigRecordError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slotBufferProbed((*reinterpret_cast< const QAudioBuffer(*)>(_a[1]))); break;
        case 5: _t->slotRecorderStateChanged((*reinterpret_cast< QMediaRecorder::State(*)>(_a[1]))); break;
        case 6: _t->slotDRecorderError(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Recorder::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Recorder::sigRecordStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Recorder::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Recorder::sigRecordStoped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Recorder::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Recorder::sigRecordPaused)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Recorder::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Recorder::sigRecordError)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Recorder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Recorder.data,
      qt_meta_data_Recorder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Recorder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Recorder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Recorder.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Recorder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Recorder::sigRecordStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Recorder::sigRecordStoped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Recorder::sigRecordPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Recorder::sigRecordError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
