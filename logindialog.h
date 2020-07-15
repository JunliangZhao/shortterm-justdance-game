#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QPushButton>
#include<maininterface.h>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
     QPushButton* button;
     QPushButton* headPortrait ;
     mainInterface* mainInterface;
     int flag = 0;
     int flag2 = 0;

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
