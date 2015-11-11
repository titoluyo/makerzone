/****************************************************************************
** Meta object code from reading C++ file 'objectgl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/objectgl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectgl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ObjectOpenGL_t {
    QByteArrayData data[16];
    char stringdata[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ObjectOpenGL_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ObjectOpenGL_t qt_meta_stringdata_ObjectOpenGL = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 16),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 5),
QT_MOC_LITERAL(4, 37, 16),
QT_MOC_LITERAL(5, 54, 16),
QT_MOC_LITERAL(6, 71, 9),
QT_MOC_LITERAL(7, 81, 8),
QT_MOC_LITERAL(8, 90, 8),
QT_MOC_LITERAL(9, 99, 9),
QT_MOC_LITERAL(10, 109, 7),
QT_MOC_LITERAL(11, 117, 10),
QT_MOC_LITERAL(12, 128, 13),
QT_MOC_LITERAL(13, 142, 12),
QT_MOC_LITERAL(14, 155, 12),
QT_MOC_LITERAL(15, 168, 12)
    },
    "ObjectOpenGL\0xRotationChanged\0\0angle\0"
    "yRotationChanged\0zRotationChanged\0"
    "FrontView\0RearView\0LeftView\0RightView\0"
    "TopView\0BottomView\0IsometricView\0"
    "SetXRotation\0SetYRotation\0SetZRotation\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjectOpenGL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       4,    1,   82,    2, 0x06,
       5,    1,   85,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,   88,    2, 0x0a,
       7,    0,   89,    2, 0x0a,
       8,    0,   90,    2, 0x0a,
       9,    0,   91,    2, 0x0a,
      10,    0,   92,    2, 0x0a,
      11,    0,   93,    2, 0x0a,
      12,    0,   94,    2, 0x0a,
      13,    1,   95,    2, 0x0a,
      14,    1,   98,    2, 0x0a,
      15,    1,  101,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ObjectOpenGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ObjectOpenGL *_t = static_cast<ObjectOpenGL *>(_o);
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->FrontView(); break;
        case 4: _t->RearView(); break;
        case 5: _t->LeftView(); break;
        case 6: _t->RightView(); break;
        case 7: _t->TopView(); break;
        case 8: _t->BottomView(); break;
        case 9: _t->IsometricView(); break;
        case 10: _t->SetXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->SetYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->SetZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ObjectOpenGL::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObjectOpenGL::xRotationChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (ObjectOpenGL::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObjectOpenGL::yRotationChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (ObjectOpenGL::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObjectOpenGL::zRotationChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ObjectOpenGL::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ObjectOpenGL.data,
      qt_meta_data_ObjectOpenGL,  qt_static_metacall, 0, 0}
};


const QMetaObject *ObjectOpenGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjectOpenGL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectOpenGL.stringdata))
        return static_cast<void*>(const_cast< ObjectOpenGL*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ObjectOpenGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ObjectOpenGL::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ObjectOpenGL::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ObjectOpenGL::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
