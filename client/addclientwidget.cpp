#include "addclientwidget.h"
#include "ui_addclientwidget.h"

addClientWidget::addClientWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addClientWidget)
{
    ui->setupUi(this);
}

addClientWidget::~addClientWidget()
{
    delete ui;
}
