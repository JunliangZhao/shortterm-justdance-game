#ifndef JUSTDANCE_H
#define JUSTDANCE_H

#include"mybutton.h"
#include"jinglebell.h"
#include"kk.h"
#include <QMainWindow>
#include<QFile>
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QFont>
#include<QLabel>
#include<QSoundEffect>
#include<QMovie>




namespace Ui {
class justdance;
}

class justdance : public QMainWindow
{
    Q_OBJECT

public:
    explicit justdance(QWidget *parent = 0);
    ~justdance();

    int dx=0;

    QMovie *movie,*movie2;
    QLabel *gifLab1,*gifLab2;

    QSoundEffect *music=new QSoundEffect(this);
    QSoundEffect *bgm;
    QSoundEffect *dingdong;
    jinglebell *jingle;
    kk *k24;


    QLabel *dancepic;

    QTime *currentTime;

    QStringList strlist,strlist2,strlist3;

    QString str,str2;

    QTimer *t, *Timer;

    QTime *lycTime;

    int count=0;

    QFile *file;

    QFont f;

    QString forename=":/";

    MyButton *selectbtn,*StartButton,*exitbtn,*qiegeBtn;

    QString *selectedSong;

    void setBackgroundImage(QString path);


signals:

    void sendscore(QString,QString,int);


private slots:
    void settime();

    void paint();

    void on_exitbtn_clicked();

    void on_selectbtn_clicked();

    void acceptSongName(QString);

    void on_StartButton_clicked();


    void qiege();





private:
    Ui::justdance *ui;
};

#endif // MAINWINDOW_H
