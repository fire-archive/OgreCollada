/****************************************************************************
** Meta object code from reading C++ file 'OgreCOLLADAViewer.h'
**
** Created: Sun May 24 23:22:07 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/OgreCOLLADAViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OgreCOLLADAViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OgreCOLLADAViewer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      45,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OgreCOLLADAViewer[] = {
    "OgreCOLLADAViewer\0\0on_actionOpen_activated()\0"
    "on_actionQuit_activated()\0"
};

const QMetaObject OgreCOLLADAViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_OgreCOLLADAViewer,
      qt_meta_data_OgreCOLLADAViewer, 0 }
};

const QMetaObject *OgreCOLLADAViewer::metaObject() const
{
    return &staticMetaObject;
}

void *OgreCOLLADAViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OgreCOLLADAViewer))
        return static_cast<void*>(const_cast< OgreCOLLADAViewer*>(this));
    if (!strcmp(_clname, "Ui::MainWindow"))
        return static_cast< Ui::MainWindow*>(const_cast< OgreCOLLADAViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int OgreCOLLADAViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionOpen_activated(); break;
        case 1: on_actionQuit_activated(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
