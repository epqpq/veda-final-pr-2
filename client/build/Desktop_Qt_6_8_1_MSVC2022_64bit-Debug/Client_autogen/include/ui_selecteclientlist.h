/********************************************************************************
** Form generated from reading UI file 'selecteclientlist.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTECLIENTLIST_H
#define UI_SELECTECLIENTLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_SelecteClientList
{
public:
    QListWidget *clientListWidget;

    void setupUi(QDialog *SelecteClientList)
    {
        if (SelecteClientList->objectName().isEmpty())
            SelecteClientList->setObjectName("SelecteClientList");
        SelecteClientList->resize(400, 300);
        clientListWidget = new QListWidget(SelecteClientList);
        clientListWidget->setObjectName("clientListWidget");
        clientListWidget->setGeometry(QRect(0, 0, 400, 300));
        clientListWidget->setStyleSheet(QString::fromUtf8("\n"
"     QListWidget {\n"
"         background-color: #000000;\n"
"         font: 14px 'Segoe UI';\n"
"         color: #FFFFFF;\n"
"         padding: 5px;\n"
"     }\n"
"     QListWidget::item {\n"
"         padding: 10px;\n"
"         border-bottom: 1px solid #333333;\n"
"         color: #FFFFFF;\n"
"     }\n"
"     QListWidget::item:hover {\n"
"         background-color: #444444;\n"
"     }\n"
"     QListWidget::item:selected {\n"
"         background-color: #6C63FF;\n"
"         color: white;\n"
"     }\n"
"    "));

        retranslateUi(SelecteClientList);

        QMetaObject::connectSlotsByName(SelecteClientList);
    } // setupUi

    void retranslateUi(QDialog *SelecteClientList)
    {
        SelecteClientList->setWindowTitle(QCoreApplication::translate("SelecteClientList", "Select Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelecteClientList: public Ui_SelecteClientList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTECLIENTLIST_H
