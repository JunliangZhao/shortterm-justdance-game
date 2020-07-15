#ifndef CHANGEHEADDIALOG_H
#define CHANGEHEADDIALOG_H

#include <QDialog>
#include<QPushButton>

namespace Ui {
class changeHeadDialog;
}

class changeHeadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeHeadDialog(QWidget *parent = 0);
    ~changeHeadDialog();
    QPushButton* leftbutton;
    QPushButton* rightbutton;
    QPushButton* bottombutton;
private:
    Ui::changeHeadDialog *ui;
};

#endif // CHANGEHEADDIALOG_H
