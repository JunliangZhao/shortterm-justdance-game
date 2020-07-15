#include "justdance.h"
#include "ui_justdance.h"
#include "mybutton.h"
#include "scoredialog.h"
#include<QPropertyAnimation>
#include<selectdialog.h>
#include<QLabel>
#include<QDir>

#include"jinglebell.h"
#include"kk.h"

extern int fenshu;
justdance::justdance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui:: justdance)
{
    ui->setupUi(this);





    //实现渐变打开界面
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    //设置窗口全屏无边框以及背景图
    setWindowFlags (Qt::FramelessWindowHint);
    showFullScreen();
    this->setBackgroundImage(":/背景多边形3.jpg");

    //设置背景中心图片label
    dancepic=new QLabel(this);
    dancepic->setGeometry(this->width()/4,this->height()/5,this->width()/2,this->height()/5*3-100);
    QPixmap dancepix;
    dancepix.load(":/舞蹈背景");
    dancepic->setPixmap(dancepix);
    dancepic->show();
    //dancepic->raise();

    //设置各种按钮
    selectbtn=new MyButton(this);
    exitbtn=new MyButton(this);
    StartButton=new MyButton(this);
    qiegeBtn=new MyButton(this);

    selectbtn->setText("点歌");
    exitbtn->setText("退出");
    StartButton->setText("开始！");
    qiegeBtn->setText("更换歌曲");

    selectbtn->setFont(QFont("方正苏新诗柳楷简体",25));
    StartButton->setFont(QFont("方正苏新诗柳楷简体",25));
    exitbtn->setFont(QFont("方正苏新诗柳楷简体",25));

    selectbtn->setGeometry(this->width()/2-300,this->height()/4*3,200,100);
    exitbtn->setGeometry(this->width()/2+100,this->height()/4*3,200,100);
    StartButton->setGeometry(this->width()/2-100,this->height()/2,200,100);

    exitbtn->setStyleSheet("background-image: url(:/背景多边形.jpg);border-radius: 20px;");
    selectbtn->setStyleSheet("background-image: url(:/背景多边形.jpg);border-radius: 20px;");
    StartButton->setStyleSheet("background-image: url(:/背景多边形2.jpg);border-radius: 20px;");
    qiegeBtn->setStyleSheet("background-image: url(:/背景多边形.jpg);border-radius: 20px;");

    //连接信号和槽函数
    connect(qiegeBtn,SIGNAL(clicked(bool)),this,SLOT(qiege()));
    connect(selectbtn,SIGNAL(clicked(bool)),this,SLOT(on_selectbtn_clicked()));
    connect(exitbtn,SIGNAL(clicked(bool)),this,SLOT(on_exitbtn_clicked()));
    connect(StartButton,SIGNAL(clicked(bool)),this,SLOT(on_StartButton_clicked()));

    //设置音效和背景音乐
    dingdong=new QSoundEffect(this);
    dingdong->setSource(QUrl::fromLocalFile(":/叮咚.wav"));

    bgm=new QSoundEffect(this);
    bgm->setSource(QUrl::fromLocalFile(":/bgm.wav"));
    bgm->setVolume(0.5);
    bgm->play();

    //隐藏和显示按钮
    StartButton->hide();
    selectbtn->show();
    exitbtn->show();


    //设置label
    f=QFont("方正苏新诗柳楷简体",20);
    ui->lrclabel1->setFont(f);
    ui->lrclabel2->setFont(f);
    ui->lrclabel1->setGeometry(50,this->height()*3/4,800,50);
    ui->lrclabel2->setGeometry(50,this->height()*3/4,800,50);
    ui->lrclabel1->hide();
    ui->lrclabel1->hide();

}

justdance::~justdance()
{
    delete ui;
}

void justdance::on_exitbtn_clicked()
{
    //实现渐变退出
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void justdance::on_selectbtn_clicked()
{

    dingdong->play();  //播放音效

    //打开选择窗口并调整相关细节
    selectDialog *dlg=new selectDialog();
    exitbtn->hide();
    selectbtn->hide();
    connect(dlg,SIGNAL(sendSongName(QString)),this,SLOT(acceptSongName(QString)));
    dlg->exec();
    exitbtn->show();
    selectbtn->show();
    if(!ui->songNameLabel->text().isEmpty())
    {
        dancepic->hide();
        selectbtn->setText("重新选歌");

    }
}

void justdance::acceptSongName(QString songname)
{
    //读取中心歌曲（即选中歌曲的歌曲名）并返回到主界面。
    ui->songNameLabel->setGeometry(this->width()/2-150,50,300,60);
    ui->songNameLabel->setAlignment(Qt::AlignHCenter);
    ui->songNameLabel->setFont(QFont("方正苏新诗柳楷简体",30));

    QPalette p2=ui->songNameLabel->palette();
    p2.setColor(QPalette::WindowText,Qt::white);
    ui->songNameLabel->setPalette(p2);

    selectedSong=new QString(songname);
    ui->songNameLabel->setText(*selectedSong);


    QString pathName=forename;
    pathName.append(*selectedSong).append(".lrc");
    QString pathName2=forename;
    pathName2.append(*selectedSong).append(".wav");

    //打开歌词和歌曲文件
    StartButton->show();
    file=new QFile(pathName);
    music->setSource(QUrl::fromLocalFile(pathName2));
}



void justdance::on_StartButton_clicked()
{


    if(ui->songNameLabel->text()=="JingelBells")
    {
        jingle=new jinglebell(this);

        jingle->show();


    }
    if(ui->songNameLabel->text()=="24K")
     {
          k24=new kk(this);

        k24->show();

    }

    gifLab1=new QLabel(this);
    movie = new QMovie(":/小黄鸭.gif");
    gifLab1->setGeometry(50,this->height()/2+50,200,200);
    gifLab1->setMovie(movie);
    movie->start();
    gifLab1->show();

    gifLab2=new QLabel(this);
    movie2 = new QMovie(":/音响.gif");
    gifLab2->setGeometry(this->width()-250,this->height()/2+50,200,200);
    gifLab2->setMovie(movie);
    movie2->start();
    gifLab2->show();

    dancepic->hide();
    //设置初始时间
    currentTime=new QTime(0,0,0,0);
    t=new QTimer(this);

    ui->lrclabel1->show();
    ui->lrclabel2->show();

    //设置按钮格式
    exitbtn->setGeometry(50,50,150,50);
    qiegeBtn->setGeometry(50,120,150,50);
    qiegeBtn->setText("重新选歌");
    qiegeBtn->show();
    exitbtn->setFont(f);
    qiegeBtn->setFont(f);

    //开始计时
    bgm->stop();
    Timer=new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(settime()));
    Timer->start(100);

    //打开歌词文件并读取文本
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    str=(file->readLine(1024));
    strlist=(str.split(":"));
    lycTime=new QTime(0,QString(strlist[0]).toInt(),
            QString(strlist[1]).toInt(),
            QString(strlist[2]).toInt()*10);

    //播放音乐
    music->play();


    selectbtn->hide();
    StartButton->hide();

}


void justdance::qiege()
{


    delete gifLab1;
    delete gifLab2;

    //退出当前歌曲，返回主界面重新选歌
    this->show();
    qiegeBtn->hide();
    bgm->play();
    dancepic->show();

    music->stop();
    t->stop();
    Timer->stop();

    ui->lrclabel1->setText("");
    ui->lrclabel2->setText("");
    ui->songNameLabel->setText("");
    selectbtn->setText("选歌");

    selectbtn->show();

    exitbtn->setGeometry(this->width()/2+100,this->height()/4*3,200,100);
}

void justdance::settime()
{
    //设置时间
    int ms=currentTime->msec();
    int s=currentTime->second();
    int m=currentTime->minute();
    int h=currentTime->hour();
    ms+=100;
    if(ms==1000)
    {
        ms=0;
        s++;
    }
    if(s==60)
    {
        s=0;
        m++;
    }
    if(m==60)
    {
        m=0;
        h++;
    }
    currentTime->setHMS(h,m,s,ms);
    //qDebug()<<*currentTime;

    //判断当前时间是否和歌词时间对应
    if(*currentTime>=*lycTime)
    {

        if(!k24->isVisible())
        //if(strlist[3]=="end")
        {
            //打开结算界面
            Timer->stop();
            delete Timer;
            music->stop();
            t->stop();
            delete t;
            this->hide();
            extern QString user;
            scoreDialog *sdlg=new scoreDialog();
            connect(this,SIGNAL(sendscore(QString,QString,int)),sdlg,SLOT(recscore(QString,QString,int)));
            connect(sdlg->nextsongBtn,SIGNAL(clicked(bool)),this,SLOT(show()));
            emit sendscore(user,*selectedSong,fenshu);

            qiegeBtn->setGeometry(this->width()/2-100,this->height()/3,200,100);
            qiegeBtn->setText("继续下一首");
            exitbtn->setGeometry(this->width()/2-100,this->height()/3*2,200,100);

            sdlg->show();

            t=new QTimer(this);
            Timer=new QTimer(this);
            music=new  QSoundEffect(this);
        }
       else
        {
            //播放歌词，计算歌词间隔，并开始歌词计时器
            count=0;
            t->stop();
            delete t;
            t=new QTimer(this);
            //ui->lrclabel1->setText(strlist[3]);
            ui->lrclabel2->setText("");
            str2=(file->readLine(1024));
            strlist2=(str2.split(":"));
            int dm=(QString(strlist2[0]).toInt()-QString(strlist[0]).toInt());
            int ds=(QString(strlist2[1]).toInt()-QString(strlist[1]).toInt());
            int dms=(QString(strlist2[2]).toInt()-QString(strlist[2]).toInt())*10;
            int dt=dm*60*1000+ds*1000+dms;
            //qDebug()<<ds;
            int num=QString(strlist[3]).length();
            int tt=dt/(num);


            connect(t,SIGNAL(timeout()),this,SLOT(paint()));
            if(tt>500)
                tt-=500;
            t->start(tt);

            str=str2;
            strlist3=strlist;
            strlist=strlist2;

            qDebug()<<strlist;

            lycTime=new QTime(0,QString(strlist[0]).toInt(),
                    QString(strlist[1]).toInt(),
                    QString(strlist[2]).toInt()*10);
        }

    }

}

void justdance::paint()
{
    //绘制歌词label实现卡拉ok效果
    count++;
    if(count!=0)
    {
        QPalette p2=ui->lrclabel1->palette();
        p2.setColor(QPalette::WindowText,Qt::white);
        ui->lrclabel1->setPalette(p2);

        //设置渐变色
        QLinearGradient linearGrad(QPointF(0,120), QPointF(800,200));
        linearGrad.setColorAt(0, Qt::red);
        linearGrad.setColorAt(0.5, Qt::yellow);
        linearGrad.setColorAt(1, Qt::green);
        QBrush brush(linearGrad);
        QPalette palette;
        palette.setBrush(QPalette::WindowText, brush);

        int length = QString(strlist3[3]).length();

        if(count >= length)
        {
            count=length-1;
            t->stop();
            delete t;
            t=new QTimer(this);

        }
        ui->lrclabel2->setPalette(palette);
        //label->setText("");
        QString s = QString(strlist3[3]).mid(0, count);
        QString s2= QString(strlist3[3]).mid(0, length-1);

        ui->lrclabel2->setText(s);
        if(count!=length-1)
        {
            ui->lrclabel1->setText(s2);
        }
        else
        {
            ui->lrclabel1->setText("");
        }

    }

}

void justdance::setBackgroundImage(QString path)
{
    //设置主界面背景
    QPixmap pixmap = QPixmap(path).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

