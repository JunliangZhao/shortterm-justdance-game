#include "selectdialog.h"
#include "ui_selectdialog.h"
#include "songs.h"

#include <QDialog>
#include <QLabel>
#include <QPropertyAnimation>

selectDialog::selectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectDialog)
{
    ui->setupUi(this);

    setWindowFlags (Qt::FramelessWindowHint);

    songs *s1=new songs(this);

    //渐变出现
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    //设置各个按钮
    leftBtn=new MyButton(this);
    leftBtn->setText("上一首");
    rightBtn=new MyButton(this);
    rightBtn->setText("下一首");

    leftBtn->setStyleSheet("background-image: url(:/背景钻石.jpg);border-radius: 20px;");
    rightBtn->setStyleSheet("background-image: url(:/背景钻石.jpg);border-radius: 20px;");


    OKBtn=new MyButton(this);
    cancelBtn=new MyButton(this);
    OKBtn->setText("确定");
    cancelBtn->setText("取消");

    OKBtn->setGeometry(this->width()/2-250,this->height()*3/4,200,100);
    cancelBtn->setGeometry(this->width()/2+50,this->height()*3/4,200,100);
    OKBtn->setFont(font2);
    cancelBtn->setFont(font2);
    OKBtn->setStyleSheet("background-image: url(:/背景钻石.jpg);border-radius: 20px;");
    cancelBtn->setStyleSheet("background-image: url(:/背景钻石.jpg);border-radius: 20px;");

    leftBtn->setFont(font2);
    rightBtn->setFont(font2);
    leftBtn->setGeometry(50,this->height()/3,100,140);
    rightBtn->setGeometry(this->width()-150,this->height()/3,100,140);

    //建立连接
    connect(OKBtn,SIGNAL(clicked(bool)),this,SLOT(emitsong()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(quxiao()));
    connect(leftBtn,SIGNAL(clicked()),s1,SLOT(leftSelect()));
    connect(rightBtn,SIGNAL(clicked()),s1,SLOT(rightSelect()));

    //设置无边框
    setWindowFlags(windowFlags()&~Qt::WindowTitleHint);
    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);

    //设置音效
    select=new QSoundEffect(this);
    select->setSource(QUrl::fromLocalFile(":/超级玛丽加命菇.wav"));
    select->setVolume(0.5);

    //设置窗口背景
    this->setBackgroundImage(":/背景多边形2.jpg");

    //传递歌曲名字

    selectedSong=new QString(s1->centersong());
    connect(s1,SIGNAL(sendcentersong(QString)),this,SLOT(reccentersong(QString)));



}

selectDialog::~selectDialog()
{
    delete ui;
}

void selectDialog::setBackgroundImage(QString path)
{
    //设置背景
    QPixmap pixmap = QPixmap(path).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

void selectDialog::reccentersong(QString s)
{
    //接收中心歌曲
    selectedSong=new QString(s);
}

void selectDialog::emitsong()
{
    //发送歌曲名称信号并渐变消失
    select->play();
    emit sendSongName(*selectedSong);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void selectDialog::quxiao()
{
    //实现取消按钮，渐变消失
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}
