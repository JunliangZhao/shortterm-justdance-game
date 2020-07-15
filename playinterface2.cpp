#include "playinterface2.h"
#include "ui_playinterface2.h"
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QKeyEvent>
#include <gameover.h>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv/cv.h>
#include<opencv/cv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;


extern VideoCapture cap;
int deal=1;

int  Hsv_detehand(Mat src)
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
playinterface2::playinterface2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playinterface2)
{
    ui->setupUi(this);


    setWindowFlags (Qt::FramelessWindowHint);
    //加载所需图片与音频
    pl.load(":/xuemeiright.png");
    pr.load(":/xuemeileft.png");
    s->setSource(QUrl::fromLocalFile(":/imgs/magicalcastle.wav"));  //只能播放。.wav音频
    s->play();


    this->setWindowTitle(tr("magic castle,fantastic area"));
    this->setGeometry(0,0,1000,700);

    //设置背景黑色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    //添加QLabel控件
    QLabel *label1 = new QLabel(this);  //创建QLabel控件

    //添加Qpixmap对象，载入图片,将图片最大化
    QPixmap p;
    p.load(":/imgs/fantasticbackground.jpg");
    label1->setFixedSize(this->width(),this->height());
    label1->setPixmap(p.scaled(label1->size(),Qt::KeepAspectRatio,
                               Qt::SmoothTransformation));
    label1->show();
    label1->setGeometry(0,0,1350,700);

    pshock->load(":/imgs/jewel4.png");
    labelshock->setPixmap(*pshock);
    labelshock->setGeometry(100,100,100,100);
    labelshock->show();

    //创建两个说明label
    QLabel *labellife = new QLabel(this);
    labellife->setText("总积分");
    labellife->setGeometry(20,40,100,100);
    labellife->setFont(ui->label->font());

    QLabel *labelscore = new QLabel(this);
    QString a2 = "华文中宋";
    QFont *ft2=new QFont(a2,22);
    labelscore->setText("剩余时间");
    labelscore->setGeometry(20,80,140,100);
    labelscore->setFont(*ft2);

    //创建生命条label

    //随机生成陨石并坠落

    QTimer *timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),
            this,SLOT(slotTimeout()));
    connect(timer,SIGNAL(timeout()),
            this,SLOT(slotTimeout2()));
    connect(timer,SIGNAL(timeout()),
            this,SLOT(slotTimeout3()));
    connect(timer,SIGNAL(timeout()),
            this,SLOT(slotTimeout4()));
    connect(timer,SIGNAL(timeout()),
            this,SLOT(slotTimeout5()));
    timer->start(50);
    this->setGeometry(400,200,label1->width(),label1->height());
    timer2 = new QTimer(this);

    connect(timer2,SIGNAL(timeout()),
            this,SLOT(slotTimeoutscore()));
    connect(timer2,SIGNAL(timeout()),
            this,SLOT(yundong()));
    timer2->start(10);

    //生成小人
    labelpig->setParent(this);
    //添加Qpixmap对象，载入图片
    QPixmap p2;
    p2.load(":/imgs/pig.jpg");
    labelpig->setPixmap(p2);
    labelpig->show();
    labelpig->setGeometry(700,480,100,100);

    this->setGeometry(500,100,900,650);
    //用接口函数控制小人的位置

    //设置生命条、时长与历史记录
}

void playinterface2::slotTimeout()
{
    //改变生命值
    //将背景重置为黑色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    //产生1000以内随机数
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1300);
    int n = (qrand()+15) % 1300;

    //创建陨石label
    static QLabel *label2=new QLabel(this);
    static int h=0;
    static int x=n;

    //设置label参数
    label2->show();
    QPixmap p;

    //陨石下落完重复下落
    if(h==760){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = (qrand()+15) % 1300;
        h=0;
        x=n;
    }


    //检测小猪是否撞上陨石

    if(labelpig->x()<(label2->x()+label2->width())
        &&(labelpig->x()+labelpig->width())>label2->x()
        &&labelpig->y()+15>(label2->y()+label2->height())
        &&labelpig->y()<(label2->y()+label2->height()))
    {
        s1++;
        login->setSource(QUrl::fromLocalFile(":/imgs/hit.wav"));
        login->play();
        pshock->load(":/imgs/lightblue.png");
        labelshock->setPixmap(*pshock);
        labelshock->setGeometry(labelpig->x(),labelpig->y()-20,
                                labelpig->width(),labelpig->height());
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&labelpig->y()+20<(label2->y()+label2->height()))
    {
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::red);
        this->setPalette(palette);
        life=life+50;
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = (qrand()+15) % 1300;
        h=0;
        x=n;
        label2->setGeometry(x,h,100,180);
    }
    else
    {
        label2->show();
        p.load(":/imgs/jewel1.png");
        label2->setPixmap(p);
        label2->adjustSize();


        h=h+10;
        label2->show();
        label2->setGeometry(x,h,100,180);
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&(labelpig->y()+label2->height()-15<label2->y()))    {
        pshock->load("");
        login->stop();
        labelshock->setPixmap(*pshock);
    }
}

void playinterface2::slotTimeout2()
{

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1300);
    int n = qrand() % 1300;


    static QLabel *label2=new QLabel(this);
    static int h=0;
    static int x=n+50;


    if(h==780){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = qrand() % 1300;
        h=0;
        x=n+50;
    }

    //设置label参数
    label2->show();
    QPixmap p;



    //检测学妹是否撞上陨石

    if(labelpig->x()<(label2->x()+label2->width())
        &&(labelpig->x()+labelpig->width())>label2->x()
        &&labelpig->y()+15>(label2->y()+label2->height())
        &&labelpig->y()<(label2->y()+label2->height()))
    {
        login->setSource(QUrl::fromLocalFile(":/imgs/hit.wav"));
        login->play();
        pshock->load(":/imgs/lightblue.png");
        labelshock->setPixmap(*pshock);
        s2++;
        labelshock->setGeometry(labelpig->x(),labelpig->y()-20,
                                labelpig->width(),labelpig->height());
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&labelpig->y()+20<(label2->y()+label2->height()))
    {
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::red);
        this->setPalette(palette);
        life=life+50;
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = qrand() % 1300;
        h=0;
        x=n+50;
        label2->setGeometry(x,h,50,180);
    }
    else
    {
        label2->show();
        p.load(":/imgs/jewel2.png");
        label2->setPixmap(p);
        label2->adjustSize();


        h=h+10;
        label2->show();
        label2->setGeometry(x,h,50,180);
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&(labelpig->y()+label2->height()-15<label2->y()))    {
        pshock->load("");
        login->stop();
        labelshock->setPixmap(*pshock);
    }
}

void playinterface2::slotTimeout3()
{

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1300);
    int n = (qrand()+30) % 1300;


    static QLabel *label2=new QLabel(this);
    static int h=0;
    static int x=n+100;


    if(h==720){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = (qrand()+30) % 1300;
        h=0;
        x=n+100;
    }

    //设置label参数
    label2->show();
    QPixmap p;

    //检测小猪是否撞上陨石
    if(labelpig->x()<(label2->x()+label2->width())
        &&(labelpig->x()+labelpig->width())>label2->x()
        &&labelpig->y()+15>(label2->y()+label2->height())
        &&labelpig->y()<(label2->y()+label2->height()))
    {
        login->setSource(QUrl::fromLocalFile(":/imgs/hit.wav"));
        login->play();
        pshock->load(":/imgs/lightblue.png");
        s3++;
        labelshock->setPixmap(*pshock);
        labelshock->setGeometry(labelpig->x(),labelpig->y()-20,
                                labelpig->width(),labelpig->height());
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&labelpig->y()+20<(label2->y()+label2->height()))
    {
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::red);
        this->setPalette(palette);
        life=life+50;
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = (qrand()+30) % 1300;
        h=0;
        x=n+100;
        label2->setGeometry(x,h,50,180);
    }
    else
    {
        label2->show();
        p.load(":/imgs/jewel3.png");
        label2->setPixmap(p);
        label2->adjustSize();


        h=h+10;
        label2->show();
        label2->setGeometry(x,h,50,180);
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&(labelpig->y()+label2->height()-15<label2->y()))    {
        pshock->load("");
        login->stop();
        labelshock->setPixmap(*pshock);
    }
}

void playinterface2::slotTimeout4()
{

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1300);
    int n = (qrand()+40) % 1300;


    static QLabel *label2=new QLabel(this);
    static int h=0;
    static int x=n+140;


    if(h==700){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = (qrand()+40) % 1300;
        h=0;
        x=n+140;
    }

    //设置label参数
    label2->show();
    QPixmap p;


    //检测小猪是否撞上陨石
    if(labelpig->x()<(label2->x()+label2->width())
        &&(labelpig->x()+labelpig->width())>label2->x()
        &&labelpig->y()+15>(label2->y()+label2->height())
        &&labelpig->y()<(label2->y()+label2->height()))
    {
        login->setSource(QUrl::fromLocalFile(":/imgs/hit.wav"));
        login->play();
        pshock->load(":/imgs/lightblue.png");
        labelshock->setPixmap(*pshock);
        s4++;
        labelshock->setGeometry(labelpig->x(),labelpig->y()-20,
                                labelpig->width(),labelpig->height());
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&labelpig->y()+20<(label2->y()+label2->height()))
    {
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::red);
        this->setPalette(palette);
        life=life+50;
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = (qrand()+40) % 1300;
        h=0;
        x=n+140;
        label2->setGeometry(x,h,50,180);
    }
    else
    {
        label2->show();
        p.load(":/imgs/jewel4.png");
        label2->setPixmap(p);
        label2->adjustSize();


        h=h+10;
        label2->show();
        label2->setGeometry(x,h,50,180);
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&(labelpig->y()+label2->height()-15<label2->y()))    {
        pshock->load("");
        login->stop();
        labelshock->setPixmap(*pshock);
    }
}

void playinterface2::slotTimeout5()
{

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1300);
    int n = qrand() % 1300;


    static QLabel *label2=new QLabel(this);
    QPixmap p;
    static QLabel *label3=new QLabel(this);
    QPixmap p2;
    static int h=0;
    static int x=n+180;


    if(h==820){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1300);
        int n = qrand() % 1300;
        h=0;
        x=n+180;
    }

    //设置label参数

    //检测小猪是否撞上陨石
    if(labelpig->x()<(label2->x()+label2->width())
        &&(labelpig->x()+labelpig->width())>label2->x()
        &&labelpig->y()+15>(label2->y()+label2->height())
        &&labelpig->y()<(label2->y()+label2->height()))
    {
        login->setSource(QUrl::fromLocalFile(":/imgs/warning.wav"));
        login->play();
        pshock->load(":/imgs/jewel1.png");
        labelshock->setPixmap(*pshock);
        labelshock->setGeometry(labelpig->x(),labelpig->y()-20,
                                labelpig->width(),labelpig->height());
        s5++;
    }


    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&labelpig->y()+20<(label2->y()+label2->height()))
    {

        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::red);
        this->setPalette(palette);
        //life=life-5;
        label2->show();
        p.load("");
        label2->setPixmap(p);
        label2->adjustSize();

        h=h+10;
        label2->show();
        label2->setGeometry(x,h,50,180);

        t++;
        if(t%4==0)
        {
            p2.load(":/imgs/1.png");
        }
        if(t%4==1)
        {
            p2.load(":/imgs/2.png");
        }
        if(t%4==2)
        {
            p2.load(":/imgs/3.png");
        }
        if(t%4==3)
        {
            p2.load(":/imgs/4.png");
        }
        label3->setPixmap(p2);
        label3->setGeometry(labelpig->x(),labelpig->y()-20,
                                labelpig->width(),20);
        label3->setPixmap(p2.scaled(label3->size()));
        label3->show();
        deal=0;
    }
    else
    {
        deal=1;
        label2->show();
        p.load(":/imgs/stone2.png");
        label2->setPixmap(p);
        label2->adjustSize();

        h=h+10;
        label2->show();
        label2->setGeometry(x,h,50,180);
        p2.load("");
        label3->setPixmap(p2);
    }

    if(labelpig->x()<(label2->x()+label2->width())
            &&(labelpig->x()+labelpig->width())>label2->x()
            &&(labelpig->y()+label2->height()>label2->y())
            &&(labelpig->y()+label2->height()-15<label2->y()))    {
        pshock->load("");
        login->stop();
        labelshock->setPixmap(*pshock);
    }

}

void playinterface2::slotTimeoutscore()
{

    //绘制时间条
    static QLabel *labelstrip = new QLabel(this);
    labelstrip->setGeometry(150,110,score/5,40);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(0,255,0,150));
    labelstrip->setAutoFillBackground(true);
    labelstrip->setPalette(palette);
    labelstrip->show();



    //绘制分数条
    static QLabel *labelscore = new QLabel(this);
    QLinearGradient linearGrad(QPointF(50,120), QPointF(751,221));
    linearGrad.setColorAt(0, Qt::red);
    linearGrad.setColorAt(0.3, Qt::yellow);

    linearGrad.setColorAt(0.6, Qt::green);
    linearGrad.setColorAt(0.8,Qt::blue);
    linearGrad.setColorAt(1,Qt::magenta);

    QBrush brush(linearGrad);
    QPalette palette2;
    palette2.setBrush(QPalette::Background, brush);
    labelscore->setAutoFillBackground(true);
    labelscore->setPalette(palette2);
    labelscore->setGeometry(150,70,life,40);
    labelscore->show();

    //绘制分数条
    static QLabel *labellife2 = new QLabel(this);
    QString a=QString::number(life);
    a=QString::number(life);
    labellife2->setText(a);
    labellife2->show();
    if(life<60)
    {
        labellife2->setGeometry(150,40,100,100);
    }
    else if(life<700)
    {
        labellife2->setGeometry(90+life,40,100,100);
    }
    else
    {
        labellife2->setGeometry(790,40,100,100);
    }
    labellife2->setFont(ui->label->font());
    labellife2->show();

    //计时，绘制时间条
    score--;
    static QLabel *labelscore2 = new QLabel(this);
    QString b=QString::number(score);
    b=QString::number(score);
    labelscore2->setText(b);
    labelscore2->show();
    if(score>400)
    {
        labelscore2->setGeometry(70+score/5,80,100,100);
    }
    else
    {
        labelscore2->setGeometry(150,80,100,100);
    }
    labelscore2->setFont(ui->label->font());

    if(score==0)
    {
        extern QString user;
        if(s1!=0&&s2!=0&&s3!=0&&s4!=0&&life>500)
        {
            user="魔仙女王";
        }
        else if(s1!=0&&s2!=0&&s3!=0&&s4!=0&&life>300)
        {
            user="幻影魔仙";
        }

        else if(s1!=0&&s2!=0&&s3!=0&&s4!=0&&life>100)
        {
            user="魔法精灵";
        }

        else if(s1!=0&&s2!=0&&s3!=0&&s4!=0)
        {
            user="见习小魔仙";
        }
        else
        {

        }

        s->stop();
        this->close();
        login->stop();
        timer2->stop();
        gameover *p=new gameover;
        p->show();
    }
}

playinterface2::~playinterface2()
{
    delete ui;
}

//键入改变小猪位置
void playinterface2::yundong()
{
   int x=labelpig->x();
   int m=0;
   Mat img;

   cap.read(img);
   if(deal)
   {
   m=Hsv_detehand(img);
   }

    if(m==1)
    {
        labelpig->setPixmap(pl);
        cout<<"right"<<endl;
        if(x<800)
        {
            x=x+5;
        }

        labelpig->setGeometry(x,labelpig->y(),labelpig->width(),labelpig->height());
    }
    if(m==-1)
    {
        labelpig->setPixmap(pr);
        cout<<"left"<<endl;
        if(x>0)
        {
        x=x-5;
        }
        labelpig->setGeometry(x,labelpig->y(),labelpig->width(),labelpig->height());
    }
}


