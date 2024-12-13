#ifndef _SELECTE_CLIENT_LIST_H_
#define _SELECTE_CLIENT_LIST_H_

#include <QDialog>
#include <QListWidget>

namespace Ui {
class SelecteClientList;
}

class SelecteClientList : public QDialog
{
    Q_OBJECT

public:
    explicit SelecteClientList(QWidget *parent = nullptr);
    ~SelecteClientList();
private:
    Ui::SelecteClientList *ui;
};

#endif
