#ifndef NEWSCOREDIALOG_H
#define NEWSCOREDIALOG_H

#include <QDialog>
#include<QLabel>

namespace Ui {
class NewscoreDialog;
}

class NewscoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewscoreDialog(QWidget *parent = 0);
    ~NewscoreDialog();
      QLabel *printlabel;
private slots:
      void recevice(int);

private:
    Ui::NewscoreDialog *ui;

};

#endif // NEWSCOREDIALOG_H
