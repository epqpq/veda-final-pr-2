/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "selectMenu",
    "",
    "QTreeWidgetItem*",
    "item",
    "column",
    "registerClient",
    "deleteClient",
    "connectClient",
    "addClient",
    "QString&",
    "ip",
    "id",
    "selectClient",
    "mode",
    "addClientTab",
    "Client*",
    "client",
    "openClientWidget",
    "closeClientWidget",
    "enlargeClientWidget",
    "selectedClient",
    "setFilePath",
    "playVideo",
    "speedUpVideo",
    "speedDownVideo",
    "handleClientDisconnected",
    "clientID"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  104,    2, 0x08,    1 /* Private */,
       6,    0,  109,    2, 0x08,    4 /* Private */,
       7,    0,  110,    2, 0x08,    5 /* Private */,
       8,    0,  111,    2, 0x08,    6 /* Private */,
       9,    2,  112,    2, 0x08,    7 /* Private */,
      13,    1,  117,    2, 0x08,   10 /* Private */,
      15,    1,  120,    2, 0x08,   12 /* Private */,
      18,    0,  123,    2, 0x08,   14 /* Private */,
      19,    0,  124,    2, 0x08,   15 /* Private */,
      20,    1,  125,    2, 0x08,   16 /* Private */,
      22,    0,  128,    2, 0x08,   18 /* Private */,
      23,    0,  129,    2, 0x08,   19 /* Private */,
      24,    0,  130,    2, 0x08,   20 /* Private */,
      25,    0,  131,    2, 0x08,   21 /* Private */,
      26,    1,  132,    2, 0x08,   22 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 10, 0x80000000 | 10,   11,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'selectMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'registerClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addClient'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        // method 'selectClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'addClientTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Client *, std::false_type>,
        // method 'openClientWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeClientWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enlargeClientWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Client *, std::false_type>,
        // method 'setFilePath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'speedUpVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'speedDownVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleClientDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectMenu((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->registerClient(); break;
        case 2: _t->deleteClient(); break;
        case 3: _t->connectClient(); break;
        case 4: { bool _r = _t->addClient((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->selectClient((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->addClientTab((*reinterpret_cast< std::add_pointer_t<Client*>>(_a[1]))); break;
        case 7: _t->openClientWidget(); break;
        case 8: _t->closeClientWidget(); break;
        case 9: _t->enlargeClientWidget((*reinterpret_cast< std::add_pointer_t<Client*>>(_a[1]))); break;
        case 10: _t->setFilePath(); break;
        case 11: _t->playVideo(); break;
        case 12: _t->speedUpVideo(); break;
        case 13: _t->speedDownVideo(); break;
        case 14: _t->handleClientDisconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Client* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Client* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
