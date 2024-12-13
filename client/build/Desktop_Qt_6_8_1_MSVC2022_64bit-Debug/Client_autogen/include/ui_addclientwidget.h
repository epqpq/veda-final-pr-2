/********************************************************************************
** Form generated from reading UI file 'addclientwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCLIENTWIDGET_H
#define UI_ADDCLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addClientWidget
{
public:
    QLineEdit *idLine;
    QLabel *cctvID;
    QLabel *cctvIP;
    QLineEdit *ipLine;
    QPushButton *registerClientBtn;

    void setupUi(QDialog *addClientWidget)
    {
        if (addClientWidget->objectName().isEmpty())
            addClientWidget->setObjectName("addClientWidget");
        addClientWidget->resize(400, 237);
        idLine = new QLineEdit(addClientWidget);
        idLine->setObjectName("idLine");
        idLine->setGeometry(QRect(120, 40, 261, 24));
        cctvID = new QLabel(addClientWidget);
        cctvID->setObjectName("cctvID");
        cctvID->setGeometry(QRect(30, 40, 81, 16));
        cctvIP = new QLabel(addClientWidget);
        cctvIP->setObjectName("cctvIP");
        cctvIP->setGeometry(QRect(30, 80, 81, 16));
        ipLine = new QLineEdit(addClientWidget);
        ipLine->setObjectName("ipLine");
        ipLine->setGeometry(QRect(120, 80, 261, 24));
        registerClientBtn = new QPushButton(addClientWidget);
        registerClientBtn->setObjectName("registerClientBtn");
        registerClientBtn->setGeometry(QRect(300, 190, 80, 24));

        retranslateUi(addClientWidget);

        QMetaObject::connectSlotsByName(addClientWidget);
    } // setupUi

    void retranslateUi(QDialog *addClientWidget)
    {
        addClientWidget->setWindowTitle(QCoreApplication::translate("addClientWidget", "Dialog", nullptr));
        cctvID->setText(QCoreApplication::translate("addClientWidget", "ID", nullptr));
        cctvIP->setText(QCoreApplication::translate("addClientWidget", "IP", nullptr));
        registerClientBtn->setText(QCoreApplication::translate("addClientWidget", "\353\223\261\353\241\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addClientWidget: public Ui_addClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCLIENTWIDGET_H
