/****************************************************************************
** Meta object code from reading C++ file 'VoiceRecordDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VoiceRecordDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VoiceRecordDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VoiceRecordDlg_t {
    QByteArrayData data[16];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VoiceRecordDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VoiceRecordDlg_t qt_meta_stringdata_VoiceRecordDlg = {
    {
QT_MOC_LITERAL(0, 0, 14), // "VoiceRecordDlg"
QT_MOC_LITERAL(1, 15, 20), // "slotChangeAudioLevel"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "QAudioBuffer"
QT_MOC_LITERAL(4, 50, 3), // "buf"
QT_MOC_LITERAL(5, 54, 16), // "slotStateChanged"
QT_MOC_LITERAL(6, 71, 21), // "QMediaRecorder::State"
QT_MOC_LITERAL(7, 93, 5), // "state"
QT_MOC_LITERAL(8, 99, 25), // "slotRecorderStatusChanged"
QT_MOC_LITERAL(9, 125, 22), // "QMediaRecorder::Status"
QT_MOC_LITERAL(10, 148, 6), // "status"
QT_MOC_LITERAL(11, 155, 23), // "slotDisplayErrorMessage"
QT_MOC_LITERAL(12, 179, 18), // "slotSent2Recognize"
QT_MOC_LITERAL(13, 198, 12), // "slotGetReply"
QT_MOC_LITERAL(14, 211, 14), // "QNetworkReply*"
QT_MOC_LITERAL(15, 226, 3) // "ans"

    },
    "VoiceRecordDlg\0slotChangeAudioLevel\0"
    "\0QAudioBuffer\0buf\0slotStateChanged\0"
    "QMediaRecorder::State\0state\0"
    "slotRecorderStatusChanged\0"
    "QMediaRecorder::Status\0status\0"
    "slotDisplayErrorMessage\0slotSent2Recognize\0"
    "slotGetReply\0QNetworkReply*\0ans"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VoiceRecordDlg[] = {

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
       1,    1,   44,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       8,    1,   50,    2, 0x08 /* Private */,
      11,    0,   53,    2, 0x08 /* Private */,
      12,    0,   54,    2, 0x08 /* Private */,
      13,    1,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void VoiceRecordDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VoiceRecordDlg *_t = static_cast<VoiceRecordDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotChangeAudioLevel((*reinterpret_cast< const QAudioBuffer(*)>(_a[1]))); break;
        case 1: _t->slotStateChanged((*reinterpret_cast< QMediaRecorder::State(*)>(_a[1]))); break;
        case 2: _t->slotRecorderStatusChanged((*reinterpret_cast< QMediaRecorder::Status(*)>(_a[1]))); break;
        case 3: _t->slotDisplayErrorMessage(); break;
        case 4: _t->slotSent2Recognize(); break;
        case 5: _t->slotGetReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VoiceRecordDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_VoiceRecordDlg.data,
      qt_meta_data_VoiceRecordDlg,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VoiceRecordDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VoiceRecordDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VoiceRecordDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int VoiceRecordDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
