#ifndef _ADD_CLIENT_WIDGET_H_
#define _ADD_CLIENT_WIDGET_H_

#include <QDialog>

namespace Ui {
class addClientWidget;
}

class addClientWidget : public QDialog
{
    Q_OBJECT

public:
    explicit addClientWidget(QWidget *parent = nullptr);
    ~addClientWidget();

private:
    Ui::addClientWidget *ui;
};

#endif
