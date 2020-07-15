#include "adventureinterface.h"
#include<QMovie>
#include<QLabel>
#include<QDesktopWidget>
#include<QApplication>
#include<QPushButton>
#include<QPalette>
#include<QFont>
#include<QColor>




adventureInterface::adventureInterface(QWidget *parent) : QMainWindow(parent)
{
    QMovie* movie = new QMovie(":/动图/4.gif");
    QLabel* label = new QLabel(this);
    label->setScaledContents(true);
    QDesktopWidget* deskWgt = QApplication::desktop();
    QRect q = deskWgt->screenGeometry();
    label->setGeometry(0,-100,q.width(),q.height());
    label->setMovie(movie);
    movie->start();







    QFont font1("方正舒体",35);
    QColor color(255,140,140);
    button1 = new QPushButton(this);
    button1->setFlat(true);
    button1->setAutoFillBackground(true);
    button1->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);}");
    button1->setAttribute(Qt::WA_TranslucentBackground);
    button1->setGeometry(1300,500,400,300);
    button1->setText("开始游戏");
    QPalette pal1 = button1->palette();
    pal1.setColor(QPalette::ButtonText,color);
    button1->setPalette(pal1);
    button1->setFont(font1);




    button2 = new QPushButton(this);
    button2->setFlat(true);
    button2->setAutoFillBackground(true);
    button2->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);}");
    button2->setAttribute(Qt::WA_TranslucentBackground);
    button2->setGeometry(200,500,400,300);
    button2->setText("退回");
    QPalette pal2 = button2->palette();
    pal2.setColor(QPalette::ButtonText,color);
    button2->setPalette(pal2);
    button2->setFont(font1);




    this->setGeometry(QRect(2.0*q.width(),0,q.width(),q.height()));
}


