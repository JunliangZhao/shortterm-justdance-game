#include "jinglebell.h"
#include "ui_jinglebell.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include<opencv/highgui.h>
#include <string>
#include<QLabel>
#include<QTimer>
#include<QImage>
#include<QDebug>
#include<QPixmap>
#include<QVector>
#include<QMovie>
#include<fstream>
#include<QFont>
#include<QDesktopWidget>
#include<iostream>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QSoundEffect>

using namespace std;
using namespace cv;
extern int fenshu;
extern  VideoCapture cap;
Mat jinglebellImg;
double ja0[3]={1,1,1};

int jflashnum=0;
int jmoveloca=0;

int jscore=0;


int jdeal1=0;
int jdeal2=1;



int jnum1=0;

int jshuju=0;
int jnum=0;
int jinglebelllocation[23]={-650,-770,-360,-800,-150,-530,-770,-720,-410,-760,-500,-560,-690,-870,-730,-610,-500,-620,-830,-600,-500,-620};




Mat  jinglebellHsv_dete(Mat src)
{
    Mat hsv_image;

    int h = 0;
    int s = 1;
    int v = 2;
    int a = 0;
    int b = 20;
    int c = 48;
    int d =50;
    cvtColor(src, hsv_image, CV_BGR2HSV);
    Mat output_mask = Mat::zeros(src.size(), CV_8UC1);

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            uchar *p_mask = output_mask.ptr<uchar>(i, j);
            uchar *p_src = hsv_image.ptr<uchar>(i, j);
            if (p_src[h] >= a && p_src[h] <= b && p_src[s] >= c && p_src[v] >= d)
            {


                src.at<Vec3b>(i, j)[0] = 0;
                src.at<Vec3b>(i, j)[1] = 0;
                src.at<Vec3b>(i, j)[2] = 0;

                p_mask[0] = 1;
            }
            else p_mask[0] = 0;
        }
    }

    int recor1=1000;
    int recor2=0;

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
        for (int j = src.cols-1;j>=0; j--)
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


    for (int i = 0; i < src.rows; i++)
    {
        for (int j = recor1;j<recor2; j++)
        {
            uchar *p_mask = output_mask.ptr<uchar>(i, j);
            p_mask[0] = 1;
        }
    }
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            uchar *p_mask = output_mask.ptr<uchar>(i, j);
            p_mask[0] = 0;
        }
    }
    for (int i = src.rows - 1; i > src.rows - 75; i--)
    {
        for (int j = 0; j < src.cols; j++)
        {
            uchar *p_mask = output_mask.ptr<uchar>(i, j);
            p_mask[0] = 0;
        }
    }
    Mat dete(src.size(), CV_8UC3, Scalar(255,255,255));
    src.copyTo(dete, output_mask);


    return dete;
}
void jinglebelljudge(Mat  templateImg)
{

    cap.read(jinglebellImg);
    jinglebellImg=jinglebellHsv_dete(jinglebellImg);


    cvtColor(jinglebellImg,jinglebellImg, CV_BGR2GRAY);
    medianBlur(jinglebellImg, jinglebellImg, 5);
    //Canny
    bitwise_not(jinglebellImg, jinglebellImg);
    threshold(jinglebellImg, jinglebellImg, 150, 255,CV_THRESH_BINARY);
    vector<vector<Point>> contours1;
    findContours(jinglebellImg, contours1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (auto it = contours1.begin(); it != contours1.end();)
    {
        if (contourArea(*it) < 300.0)
        {

            it = contours1.erase(it);
        }
        else
        {

            it++;
        }
    }
    //drawContours(copyImg1, contours1, -1, Scalar(0, 255, 0), 2, 8);

    cv::resize(templateImg, templateImg,Size(),0.2,0.2);
    // Mat copyImg2 = templateImg.clone();
    cvtColor(templateImg, templateImg, CV_BGR2GRAY);
    threshold(templateImg, templateImg, 100, 255, CV_THRESH_BINARY);

    vector<vector<Point>> contours2;
    findContours(templateImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(copyImg2, contours2, -1, Scalar(0, 255, 0), 2, 8);


    double a2=1.0;
    double a1 = 1.0;
    for (unsigned int i = 0; i < contours1.size(); i++)
    {
        a1 = matchShapes(contours1[i], contours2[0], CV_CONTOURS_MATCH_I1, 0.0);
        if (a1 <a2)
        {
            a2 = a1;
        }


    }

    ja0[2]=ja0[1];
    ja0[1]=ja0[0];
    ja0[0]=a2;
    jshuju++;


    // cout << "simalar" << a2<<endl;


}

jinglebell::jinglebell(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jinglebell)
{
     this->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->setupUi(this);
    QPushButton *exitbtn =  new QPushButton(this);
    QPushButton *qiegeBtn = new QPushButton(this);
    exitbtn->setGeometry(50,50,150,50);
    qiegeBtn->setGeometry(50,120,150,50);
    exitbtn->setFlat(true);
    qiegeBtn->setFlat(true);
    connect(exitbtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(qiegeBtn,SIGNAL(clicked(bool)),this,SLOT(close()));



    QRect rec = QApplication::desktop()->screenGeometry();
    this->setFixedSize(rec.width(),rec.height());
    setWindowFlags (Qt::FramelessWindowHint);



    fstream file;
    file.open("../justswing/jinglebell/gifpath.txt",ios::in);


    for(int i=0;i<jingelbellNUM;i++)
    {
        getline(file,gifname[i]);

    }
    file.close();
    file.open("../justswing/jinglebell/picpath.txt",ios::in);

    for(int i=0;i<jingelbellNUM+1;i++)
    {
        getline(file,jpgname[i]);

    }
    file.close();
    file.open("../justswing/jinglebell/Tpicpath.txt",ios::in);

    for(int i=0;i<jingelbellNUM+1;i++)
    {
        getline(file,pngname[i]);

    }
    file.close();



    temp=new QLabel(this);


    QLinearGradient linearGrad(QPointF(0,120), QPointF(500,200));
    linearGrad.setColorAt(0, Qt::red);
    linearGrad.setColorAt(0.5, Qt::yellow);
    linearGrad.setColorAt(1, Qt::green);

    QBrush brush(linearGrad);
    QPalette palette;
    palette.setBrush(QPalette::WindowText, brush);




    temp->setFont(QFont("方正苏新诗柳楷简体",50));
    temp->setGeometry(this->width()-300,this->height()/2,200,100);
    temp->setPalette(palette);
    temp->setText("CXKNB");
    temp->hide();







    flashlabel=new QLabel(this);
    flashlabel->setGeometry(this->width()/3+400,this->height()/3+400,250,100);
    QPixmap temppix;

    temppix.load("C:\\Users\\zjl\\Desktop\\24k demo resource\\flash.png");
    flashlabel->setPixmap(temppix.scaled(200,80));








    movelabel=new QLabel(this);
    QPixmap movepix;
    movelabel->setGeometry(this->width(),this->height()/3+300,120,200);
    movepix.load(QString::fromStdString(pngname[0]));
    movelabel->setPixmap(movepix.scaled(movelabel->size()));
    movelabel->raise();
    movelabel->show();
    jmoveloca=jinglebelllocation[0];





    bklabel=new QLabel(this);
    bklabel->setGeometry(this->width()/4,-50,this->width()/2,this->height()/3*2);
    movie=new QMovie(QString::fromStdString(gifname[0]));
    movie->setScaledSize(bklabel->size());
    bklabel->setMovie(movie);

    bklabel->show();
    connect(movie,SIGNAL(finished()),this,SLOT(change()));
    movie->start();



    QTimer *flashtime=new QTimer(this);
    connect(flashtime,SIGNAL(timeout()),this,SLOT(flash()));
    flashtime->start(400);
    QTimer *movetime=new QTimer(this);
    connect(movetime,SIGNAL(timeout()),this,SLOT(labelmove()));
    movetime->start(30);
    QTimer *goaltime=new QTimer(this);
    connect(goaltime,SIGNAL(timeout()),this,SLOT(goal()));
    goaltime->start(30);

}

jinglebell::~jinglebell()
{
    delete ui;
}
void jinglebell::change()
{
    if(jnum<jingelbellNUM)
    {

        jnum++;
        movie->setFileName(QString::fromStdString(gifname[jnum]));
        bklabel->setMovie(movie);

        movie->start();
        cout<<jmoveloca<<endl;

        jmoveloca=jinglebelllocation[jnum];
        QPixmap movepix;
        movepix.load(QString::fromStdString(pngname[jnum]));
        movelabel->setPixmap(movepix.scaled(movelabel->size()));
        if(jdeal1)
        {
            temp->setGeometry(this->width()-300,this->height()/2,200,100);
            temp->show();
            temp->setText("Cheer on");
            fenshu=fenshu+2;
            QPropertyAnimation *animation=new QPropertyAnimation(temp,"geometry");
            connect(animation,SIGNAL(finished()),temp,SLOT(hide()));

            double x,y,t;
            x=1300;
            y=400;
            t=0.1;
            int a=0;

            animation->setDuration(3000);

            animation->setKeyValueAt(0, QRect(1500, 500, 300, 200));
            animation->setKeyValueAt(0.05, QRect(1450,450 , 300, 200));
            animation->setKeyValueAt(0.1, QRect(1300, 400, 300, 200));
            for(;a<20;t+=0.04,a++)
            {

                {
                    if(a<10)
                    {
                        x+=40;
                        y=sqrt(40000-(x-1500)*(x-1500))+400;

                    }
                    else
                    {
                        x-=40;
                        y=-sqrt(40000-(x-1500)*(x-1500))+400;
                    }

                    animation->setKeyValueAt(t, QRect(x, y, 300, 200));
                }
            }

            animation->setKeyValueAt(0.9, QRect(1300, 450, 300, 200));
            animation->setKeyValueAt(0.95, QRect(1500, 350, 300,200));
            animation->setKeyValueAt(1, QRect(1600, 250, 300, 200));

            animation->start(QAbstractAnimation::DeleteWhenStopped);


            jscore=0;

        }
        jdeal1=0;
        jdeal2=1;
        jshuju=0;



    }
    else
    {
        this->close();
    }




}

void jinglebell::flash()
{
    if(jflashnum%2==0)
    {
        flashlabel->raise();



        flashlabel->show();
    }
    else
    {
        flashlabel->hide();
    }


    jflashnum++;


}

void jinglebell::labelmove()
{

    movelabel->setGeometry(this->width()-jmoveloca,this->height()/3+300,120,200);

    movelabel->raise();
    movelabel->show();


    if(jmoveloca>=700 &&jdeal2)
    {

        jdeal1=1;
        jdeal2=0;
        cout<<"work"<<endl;

    }






    jmoveloca+=10;

    // cout<<moveloca<<endl;


}
void jinglebell::goal()
{

    if(jdeal1)
    {
        Mat img;
        img=imread(jpgname[jnum]);
        jinglebelljudge(img);


    }



    if(ja0[2]-ja0[1]>0.4 && ja0[1]-ja0[0]<0.1 && jdeal1 &&jshuju>=4)
    {

        jscore=4;
    }
    else if(ja0[2]-ja0[1]>0.3 && ja0[1]-ja0[0]<0.1 && jdeal1 && jshuju>=4)
    {

        jscore=3;
    }
    else if(ja0[2]-ja0[1]>0.2 && ja0[1]-ja0[0]<0.1 && jdeal1 && jshuju>=4)
    {

        jscore=2;
    }
    else if(ja0[2]-ja0[1]>0.1 && ja0[1]-ja0[0]<0.1 && jdeal1 && jshuju>=4)
    {

        jscore=1;
    }
    else
    {
        jscore=0;
    }
    if(jscore==4 && jdeal1)
    {
        jshuju=0;
        jscore=-1;


        jdeal1=0;

        temp->show();
        temp->setText("Perfect");
        fenshu=fenshu+50;

        QPropertyAnimation *animation=new QPropertyAnimation(temp,"geometry");
        connect(animation,SIGNAL(finished()),temp,SLOT(hide()));

        QSoundEffect *sound=new QSoundEffect(this);
        sound->setSource(QUrl::fromLocalFile(":/perfect.wav"));
        sound->play();

        double x,y,t;
        x=1300;
        y=400;
        t=0.1;
        int a=0;


        animation->setDuration(3000);

        animation->setKeyValueAt(0, QRect(1500, 500, 300, 200));
        animation->setKeyValueAt(0.05, QRect(1450,450 , 300, 200));
        animation->setKeyValueAt(0.1, QRect(1300, 400, 300, 200));
        for(;a<20;t+=0.04,a++)
        {

            {
                if(a<10)
                {
                    x+=40;
                    y=sqrt(40000-(x-1500)*(x-1500))+400;

                }
                else
                {
                    x-=40;
                    y=-sqrt(40000-(x-1500)*(x-1500))+400;
                }

                animation->setKeyValueAt(t, QRect(x, y, 300, 200));
            }
        }

        animation->setKeyValueAt(0.9, QRect(1300, 450, 300, 200));
        animation->setKeyValueAt(0.95, QRect(1500, 350, 300,200));
        animation->setKeyValueAt(1, QRect(1600, 250, 300, 200));

        animation->start(QAbstractAnimation::DeleteWhenStopped);





    }
    else if(jscore==3 && jdeal1)
    {
        jshuju=0;
        jscore=0;

        jdeal1=0;
        temp->show();
        temp->setText("Great");
        fenshu=fenshu+20;


        QPropertyAnimation *animation=new QPropertyAnimation(temp,"geometry");
        connect(animation,SIGNAL(finished()),temp,SLOT(hide()));

        QSoundEffect *sound=new QSoundEffect(this);
        sound->setSource(QUrl::fromLocalFile(":/great.wav"));
        sound->play();

        double x,y,t;
        x=1300;
        y=400;
        t=0.1;
        int a=0;

        animation->setDuration(3000);

        animation->setKeyValueAt(0, QRect(1500, 500, 300, 200));
        animation->setKeyValueAt(0.05, QRect(1450,450 , 300, 200));
        animation->setKeyValueAt(0.1, QRect(1300, 400, 300, 200));
        for(;a<20;t+=0.04,a++)
        {

            {
                if(a<10)
                {
                    x+=40;
                    y=sqrt(40000-(x-1500)*(x-1500))+400;

                }
                else
                {
                    x-=40;
                    y=-sqrt(40000-(x-1500)*(x-1500))+400;
                }

                animation->setKeyValueAt(t, QRect(x, y, 300, 200));
            }
        }

        animation->setKeyValueAt(0.9, QRect(1300, 450, 300, 200));
        animation->setKeyValueAt(0.95, QRect(1500, 350, 300,200));
        animation->setKeyValueAt(1, QRect(1600, 250, 300, 200));

        animation->start(QAbstractAnimation::DeleteWhenStopped);




    }
    else if(jscore==2 && jdeal1)
    {
        jshuju=0;
        jscore=0;

        jdeal1=0;
        temp->show();
        temp->setText("Good");
        fenshu=fenshu+10;


        QPropertyAnimation *animation=new QPropertyAnimation(temp,"geometry");
        connect(animation,SIGNAL(finished()),temp,SLOT(hide()));

        QSoundEffect *sound=new QSoundEffect(this);
        sound->setSource(QUrl::fromLocalFile(":/good.wav"));
        sound->play();

        double x,y,t;
        x=1300;
        y=400;
        t=0.1;
        int a=0;

        animation->setDuration(3000);

        animation->setKeyValueAt(0, QRect(1500, 500, 300, 200));
        animation->setKeyValueAt(0.05, QRect(1450,450 , 300, 200));
        animation->setKeyValueAt(0.1, QRect(1300, 400, 300, 200));
        for(;a<20;t+=0.04,a++)
        {

            {
                if(a<10)
                {
                    x+=40;
                    y=sqrt(40000-(x-1500)*(x-1500))+400;

                }
                else
                {
                    x-=40;
                    y=-sqrt(40000-(x-1500)*(x-1500))+400;
                }

                animation->setKeyValueAt(t, QRect(x, y, 300, 200));
            }
        }

        animation->setKeyValueAt(0.9, QRect(1300, 450, 300, 200));
        animation->setKeyValueAt(0.95, QRect(1500, 350, 300,200));
        animation->setKeyValueAt(1, QRect(1600, 250, 300, 200));

        animation->start(QAbstractAnimation::DeleteWhenStopped);





    }
    else if(jscore==1 && jdeal1)
    {
        jshuju=0;
        jscore=0;

        jdeal1=0;
        temp->show();
        temp->setText("OK");
        fenshu=fenshu+5;



        QPropertyAnimation *animation=new QPropertyAnimation(temp,"geometry");
        connect(animation,SIGNAL(finished()),temp,SLOT(hide()));

        double x,y,t;
        x=1300;
        y=400;
        t=0.1;
        int a=0;

        animation->setDuration(3000);

        animation->setKeyValueAt(0, QRect(1500, 500, 300, 200));
        animation->setKeyValueAt(0.05, QRect(1450,450 , 300, 200));
        animation->setKeyValueAt(0.1, QRect(1300, 400, 300, 200));
        for(;a<20;t+=0.04,a++)
        {

            {
                if(a<10)
                {
                    x+=40;
                    y=sqrt(40000-(x-1500)*(x-1500))+400;

                }
                else
                {
                    x-=40;
                    y=-sqrt(40000-(x-1500)*(x-1500))+400;
                }

                animation->setKeyValueAt(t, QRect(x, y, 300, 200));
            }
        }

        animation->setKeyValueAt(0.9, QRect(1300, 450, 300, 200));
        animation->setKeyValueAt(0.95, QRect(1500, 350, 300,200));
        animation->setKeyValueAt(1, QRect(1600, 250, 300, 200));

        animation->start(QAbstractAnimation::DeleteWhenStopped);

    }

    else
    {

    }

}
