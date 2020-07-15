#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include"mybutton.h"
#include <QDialog>
#include<QTimer>
#include<QLabel>
#include<QString>
#include<QSoundEffect>

namespace Ui {
class scoreDialog;
}

class scoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit scoreDialog(QWidget *parent = 0);
    ~scoreDialog();
    QLabel *score;
    QLabel *textlabel;
    QTimer *Timer1,*Timer2,*Timer3, *timer,*timer_zp;
    int w=0;
    int x=400,y=250,h=50;
    int t=0;
    int s=0;
    QLabel *shininglabel;
    QLabel *usernameLabel;
    QLabel *zongpingLabel;
    void setBackgroundImage(QString path);

    QSoundEffect *dong,*clap,*ding,*com,*loading,*bgm2,*jntm;

    int perfect,great,good,pass,tryon,finalScore=200;

    void paintEvent(QPaintEvent * event);

    void onShakeWindow();

    QString zongping;
    QString songName;
    QString userName;
    QString pj;

    MyButton *nextsongBtn;

private slots:
    void paint();

    void hidelabel();

    void showzp();

    void nextsong();

    void recscore(QString,QString,int);


private:
    Ui::scoreDialog *ui;
};

#endif // SCOREDIALOG_H
