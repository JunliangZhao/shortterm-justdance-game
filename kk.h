#ifndef KK_H
#define KK_H

#include <QMainWindow>
#include<QLabel>
#include<QMovie>

#define NUM 13
namespace Ui {
class kk;
}

class kk : public QMainWindow
{
    Q_OBJECT

public:
    explicit kk(QWidget *parent = 0);
    ~kk();
    QLabel *bklabel;
    QMovie *movie;
    QLabel *flashlabel;
    QLabel *movelabel;
    QLabel *temp;



    int num=0;


private:
    Ui::kk *ui;
private slots:
    void change();
    void  flash();
    void labelmove();
   void goal();
   void printperson();

};

#endif // MAINWINDOW_H
