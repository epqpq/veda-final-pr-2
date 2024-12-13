#include "selecteclientlist.h"
#include "ui_selecteclientlist.h"

SelecteClientList::SelecteClientList(QWidget *parent)
    : QDialog(parent), ui(new Ui::SelecteClientList)
{
    ui->setupUi(this);
}

SelecteClientList::~SelecteClientList()
{
    delete ui;
}
