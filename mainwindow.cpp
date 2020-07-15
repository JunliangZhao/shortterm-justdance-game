#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mybutton.h"
#include<logindialog.h>
#include<registdialog.h>
#include<QPushButton>
#include<QLabel>
#include<QMovie>
#include<QApplication>
#include<QGridLayout>
#include<QSoundEffect>
#include<QDesktopWidget>
#include<QDialog>
#include<QFontDialog>
#include<QPropertyAnimation>
#include<QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose,true);
//    extern int flag1;
//    extern int flag2;

showFullScreen();

//背景图片的设置
    this->setAutoFillBackground(true);
    QImage image;
    image.load(":/静图/QQ图片20190904165244.jpg");
    QPalette pal = this->palette();
    QDesktopWidget* deskWgt = QApplication::desktop();
    deskWgt->setAttribute(Qt::WA_DeleteOnClose,true);
    QRect q = deskWgt->screenGeometry();
    QSize p(q.width(),q.height());
    pal.setBrush(QPalette::Window,QBrush(image.scaled(p,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(pal);



//登录按钮
    MyButton* button = new MyButton(this);
    button->setText("登录");
    button->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'方正苏新诗柳楷简体';"
                "font-size:40px;"
                "background-color:rgb(125,55,75);"
                "color:rgb(238,238,238);"
                );



//注册按钮

    MyButton* button2 = new MyButton(this);
    button2->setAttribute(Qt::WA_DeleteOnClose,true);
    button2->setText("注册");
    button2->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'方正苏新诗柳楷简体';"
                "font-size:40px;"
                "background-color:rgb(125,55,75);"
                "color:rgb(238,238,238);"
                );



    QSoundEffect *login=new QSoundEffect(this);
    login->setSource(QUrl::fromLocalFile(":/音频/Taylor Swift - Call It What You Want.wav"));
    //void QSoundEffect::setSource(const QUrl &url)
    //主机上线音效
    MyButton* button3 = new MyButton(this);
    button3->setText("播放音乐");
    connect(button3,&QPushButton::clicked,login,&login->play);
    button3->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'方正苏新诗柳楷简体';"
                "font-size:40px;"
                "background-color:rgb(125,55,75);"
                "color:rgb(238,238,238);"
                );



//暂停音乐
    MyButton* button4 = new MyButton(this);
    button4->setText("暂停音乐");
    connect(button4,&QPushButton::clicked,login,&login->stop);
    button4->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'方正苏新诗柳楷简体';"
                "font-size:40px;"
                "background-color:rgb(125,55,75);"
                "color:rgb(238,238,238);"
                );


//退出游戏

    MyButton* button5 = new MyButton(this);
    button5->setText("退出");
    button5->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'方正苏新诗柳楷简体';"
                "font-size:40px;"
                "background-color:rgb(125,55,75);"
                "color:rgb(238,238,238);"
                );



//动图的设置
    QMovie* movie = new QMovie(":/动图/aa586e8fab3e4c91a396edbf8064dd31.gif");
    QLabel* label = new QLabel(this);
    label->resize(300,200);
    label->setMovie(movie);
    movie->start();
    label->show();


//按钮的设置

    button->setGeometry(400,400,250,50);
    button2->setGeometry(400,500,250,50);
    button3->setGeometry(400,600,250,50);
    button4->setGeometry(400,700,250,50);
    button5->setGeometry(400,800,250,50);
    label->setGeometry(790,500,1300,300);



    setGeometry(QRect(0,0,q.width(),q.height()));



//登录按钮的槽函数
    connect(button,&QPushButton::clicked,this,[=](){
        //切换动画
          loginDialog* dialog1= new loginDialog(this);
          dialog1->setWindowOpacity(0);
          dialog1->show();
          QPropertyAnimation* animation = new QPropertyAnimation(dialog1,"windowOpacity");
          animation->setDuration(1500);
          animation->setStartValue(0);
          animation->setEndValue(1);
          animation->start();





        //登录对话框登录按钮的槽函数

          connect(dialog1->button,&QPushButton::clicked,this,[=](){
              if(dialog1->flag)
              {
                  //设置淡入效果
                    dialog1->setWindowOpacity(1);
                    QPropertyAnimation* animation = new QPropertyAnimation(dialog1,"windowOpacity");
                    animation->setDuration(1500);
                    animation->setStartValue(1);
                    animation->setEndValue(0);
                    animation->start();

                    dialog1->mainInterface =new mainInterface();
                    dialog1->mainInterface->show();








                //主界面与游戏界面的切换动画
                     QPropertyAnimation* animation2 = new QPropertyAnimation(this,"geometry");
                     animation2->setDuration(3000);
                     animation2->setStartValue(QRect(0,0,q.width(),q.height()));
                     animation2->setEndValue(QRect(q.width(),0,q.width(),q.height()));
                     animation2->start();






                    QPropertyAnimation* animation3 = new QPropertyAnimation(dialog1->mainInterface,"geometry");
                    animation3->setDuration(3000);
                    animation3->setStartValue(QRect(-q.width(),0,q.width(),q.height()));
                    animation3->setEndValue(QRect(0,0,q.width(),q.height()));
                    animation3->start();
                    this->close();
                    delete this;



               }
          });


    });


//注册按钮的槽函数
   connect(button2,&QPushButton::clicked,this,[=](){
       //注册按钮的淡入效果
           registDialog* dialog2 = new registDialog(this);
           dialog2->setWindowOpacity(0);
           dialog2->show();
           QPropertyAnimation* animation = new QPropertyAnimation(dialog2,"windowOpacity");

           animation->setDuration(1500);
           animation->setStartValue(0);
           animation->setEndValue(1);
           animation->start();
    });


//退出按钮的槽函数
   connect(button5,&QPushButton::clicked,this,[=](){
       this->close();
       delete this;
   });

   button->show();
   button2->show();
   button3->show();
   button4->show();
   button5->show();
}





MainWindow::~MainWindow()
{
    delete ui;
}
