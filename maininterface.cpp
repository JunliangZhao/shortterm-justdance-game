#include "maininterface.h"
#include"mainwindow.h"
#include<QImage>
#include<QDesktopWidget>
#include<QApplication>
#include<QLabel>
#include<QMovie>
#include<QPalette>
#include<classicinterface.h>
#include<adventureinterface.h>
#include<QPropertyAnimation>
#include<QTimer>
#include<keeptime.h>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv/cv.h>
#include<opencv/cv.hpp>
#include <opencv2/core/core.hpp>
#include"justdance.h"
#include"classicgame.h"

using namespace std;
using namespace cv;

extern int flag1 ;
extern int flag2 ;

    Mat mainImg;
VideoCapture cap(0);

int  mainHsv_dete(Mat src)
{
    int m=0;
    Mat hsv_image;

    int h = 0;
    int s = 1;
    int v = 2;
    int a = 0;
    int b = 20;
    int c = 108;
    int d = 150;
    cvtColor(src, hsv_image, CV_BGR2HSV);




    int recor1 = 1000;
    int recor2 = 0;

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            uchar *p_src = hsv_image.ptr<uchar>(i, j);
            if (p_src[h] >= a && p_src[h] <= b && p_src[s] >= c && p_src[v] >= d)
            {
                if (j < recor1)
                {
                    recor1 = j;
                }

            }

        }
    }

    for (int i = 0; i < src.rows; i++)
    {
        for (int j =src.cols-1;j>=0;j--)
        {
            uchar *p_src = hsv_image.ptr<uchar>(i, j);
            if (p_src[h] >= a && p_src[h] <= b && p_src[s] >= c && p_src[v] >= d)
            {
                if (j > recor2)
                {
                    recor2 = j;
                }


            }

        }
    }
    if (recor1<100)
        {
            m = 1;
        }
        else if (src.cols-recor2<100)
        {
            m = -1;
        }
        else
        {
            m = 0;
        }




         return m;

}
mainInterface::mainInterface(QWidget *parent) : QMainWindow(parent)
{
    extern int signalflag;
    open=2;
    this->setAttribute(Qt::WA_DeleteOnClose,true);
//获取屏幕大小
    QDesktopWidget* deskWgt = QApplication::desktop();
    QRect q = deskWgt->screenGeometry();



//左动图设置
    QLabel* label1 = new QLabel(this);
    label1->setAttribute(Qt::WA_DeleteOnClose,true);
    label1->setScaledContents(true);
    label1->setGeometry(0,-100,q.width() / 2.0,q.height());
    QMovie* movie1 = new QMovie(":/动图/2.gif");
    label1->setMovie(movie1);
    movie1->start();




//右动图设置
    QLabel* label2 = new QLabel(this);
    label2->setAttribute(Qt::WA_DeleteOnClose,true);
    label2->setScaledContents(true);
    label2->setGeometry(q.width() / 2.0,-100,q.width() / 2.0,q.height());
    QMovie* movie2 = new QMovie(":/动图/1.gif");
    label2->setMovie(movie2);
    movie2->start();
    label2->show();




//经典模式按键
    QFont font1("方正苏新诗柳楷简体",35);
    QColor color(Qt::white);
    QLabel* label3 = new QLabel("经典模式",this);
    label3->setAttribute(Qt::WA_DeleteOnClose,true);
    QPalette pal =label3->palette();
    pal.setColor(QPalette::WindowText,color);
    label3->setPalette(pal);
    label3->setGeometry(300,100,300,200);
    label3->setFont(font1);
    label3->setAttribute(Qt::WA_TranslucentBackground);






//冒险模式按键
    QLabel* label4 = new QLabel("冒险模式",this);
    label4->setAttribute(Qt::WA_DeleteOnClose,true);
    QPalette pal2 = label4->palette();
    pal2.setColor(QPalette::WindowText,color);
    label4->setPalette(pal2);
    label4->setGeometry(1200,100,300,200);
    label4->setFont(font1);
    label4->setAttribute(Qt::WA_TranslucentBackground);


//图片加载
        button1 = new QPushButton(this);
        button1->setGeometry(300,400,300,200);
        QPixmap image;
        image.load(":/静图/QQ图片20190904165802.jpg");
        QPixmap image1 = image.scaled(button1->size());
        QSize p1(300,200);
        button1->setIcon(QIcon(image1));
        button1->setIconSize(p1);







    button2 = new QPushButton(this);
    button2->setGeometry(1200,400,300,200);
    QPixmap image2;
    image2.load(":/静图/20170822181145_d41d8cd98f00b204e9800998ecf8427e_9.jpg");
    button2->setIcon(QIcon(image2));
    button2->setIconSize(p1);


  //返回键的设置
    returnbutton = new QPushButton(this);
        returnbutton->setFlat(true);
        returnbutton->setAutoFillBackground(true);
        returnbutton->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);}");
        returnbutton->setAttribute(Qt::WA_TranslucentBackground);
        returnbutton->setGeometry(800,600,300,200);
        returnbutton->setFont(font1);
        returnbutton->setText("退回");
        QPalette pal3 = returnbutton->palette();
        pal3.setColor(QPalette::ButtonText,color);
        returnbutton->setPalette(pal3);

    this->setGeometry(QRect(-q.width(),0,q.width(),q.height()));


//返回键的槽函数
      connect(returnbutton,&QPushButton::clicked,this,[=](){
          MainWindow *temp=new MainWindow;

          temp->show();
          this->close();
          //如果该窗口被创建，则返回键被点击时该窗口关闭
          if(flag1==1)
          {
              this->face1->close();
              flag1=0;
              delete this->face1;
          }
          if(flag2==1)
          {
              this->face2->close();
              flag2=0;
              delete this->face2;
          }


      });




//经典模式按钮槽函数
    connect(button1,&QPushButton::clicked,this,[=](){
        open=1;

        if(flag1 == 0)
        {
            this->face1 = new classicInterface();
            face1->show();
            flag1 = 1;
        }




//经典页面的返回键的槽函数
        connect(this->face1->button2,&QPushButton::clicked,this,[=](){
                   open=2;

            if(signalflag)
            {
                //页面切换的动画
                QPropertyAnimation* animation3 = new QPropertyAnimation(this->face1,"geometry");
                animation3->setDuration(3000);
                animation3->setStartValue(QRect(0,0,q.width(),q.height()));
                animation3->setEndValue(QRect(-q.width(),0,q.width(),q.height()));
                animation3->start();



                QPropertyAnimation* animation4 = new QPropertyAnimation(this,"geometry");
                animation4->setDuration(3000);
                animation4->setStartValue(QRect(q.width(),0,q.width(),q.height()));
                animation4->setEndValue(QRect(0,0,q.width(),q.height()));
                animation4->start();
            }
            else
            {
                ;
            }



             keeptime time;
             time.timestart();
        });



        if(signalflag)
        {
            QPropertyAnimation* animation1 = new QPropertyAnimation(this,"geometry");
            animation1->setDuration(3000);
            animation1->setStartValue(QRect(0,0,q.width(),q.height()));
            animation1->setEndValue(QRect(q.width(),0,q.width(),q.height()));
            animation1->start();





            QPropertyAnimation* animation2 = new QPropertyAnimation(this->face1,"geometry");
            animation2->setDuration(3000);
            animation2->setStartValue(QRect(-q.width(),0,q.width(),q.height()));
            animation2->setEndValue(QRect(0,0,q.width(),q.height()));
            animation2->start();

        }
        else
        {
            ;
        }



        keeptime time;
        time.timestart();

    });



//冒险模式按钮的槽函数
    connect(button2,&QPushButton::clicked,this,[=](){
          open=3;

        if(flag2 == 0)
        {
            this->face2 = new adventureInterface();
            face2->show();
            flag2 = 1;
        }

        if(signalflag)
        {


            QPropertyAnimation* animation1 = new QPropertyAnimation(this,"geometry");
            animation1->setDuration(3000);
            animation1->setStartValue(QRect(0,0,q.width(),q.height()));
            animation1->setEndValue(QRect(-q.width(),0,q.width(),q.height()));
            animation1->start();





            QPropertyAnimation* animation2 = new QPropertyAnimation(this->face2,"geometry");
            animation2->setDuration(3000);
            animation2->setStartValue(QRect(q.width(),0,q.width(),q.height()));
            animation2->setEndValue(QRect(0,0,q.width(),q.height()));
            animation2->start();
        }
        else
        {
            ;
        }


        keeptime time;
        time.timestart();


//冒险模式的退回键的槽函数
        connect(this->face2->button2,&QPushButton::clicked,this,[=](){
               open=2;

            if(signalflag)
            {
                QPropertyAnimation* animation3 = new QPropertyAnimation(this->face2,"geometry");
                animation3->setDuration(3000);
                animation3->setStartValue(QRect(0,0,q.width(),q.height()));
                animation3->setEndValue(QRect(q.width(),0,q.width(),q.height()));
                animation3->start();



                QPropertyAnimation* animation4 = new QPropertyAnimation(this,"geometry");
                animation4->setDuration(3000);
                animation4->setStartValue(QRect(-q.width(),0,q.width(),q.height()));
                animation4->setEndValue(QRect(0,0,q.width(),q.height()));
                animation4->start();
            }
            else
            {
                ;
            }



            keeptime time;
            time.timestart();
    });
 });
   maketime=new QTimer(this);
    connect(maketime,SIGNAL(timeout()),this,SLOT(make()));
    maketime->start(50);
}





mainInterface::~mainInterface()
{
    delete button1;
    delete button2;
    delete returnbutton;
    delete maketime;

}

void mainInterface::make()
{
     extern int signalflag;

    cap.read(mainImg);
    int m=0;
    m=mainHsv_dete(mainImg);
    if(m==1 && open==2 && signalflag)
     {
        this->button2->clicked(true);


    }
    else if(m==-1 && open==2 && signalflag)
    {
        this->button1->clicked(true);

    }
    else if(m==1 && open==1 && signalflag)
    {
        this->face1->button2->clicked(true);


    }
    else if(m==-1 && open==3 && signalflag)
    {
        this->face2->button2->clicked(true);


    }
    else if(m==1 &&open==3 && signalflag)
    {
        open=0;
         justdance *temp=new justdance;
         temp->show();
        this->close();
        if(flag1 == 1)
        {
            this->face1->close();

            flag1=0;

        }
        if(flag2 == 1)
        {

            this->face2->close();

            flag2=0;


        }






    }
    else if(m==-1 && open==1 &&signalflag)
    {
        open=0;
        classicgame *temp=new classicgame;
        temp->show();

        if(flag1 == 1)
        {
            this->face1->close();
            flag1=0;


        }
        if(flag2 == 1)
        {

            this->face2->close();

            flag2=0;


        }
         this->close();




    }
    else
    {

    }





}

