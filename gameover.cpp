#include "gameover.h"
#include "ui_gameover.h"
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QPainter>
#include <QGridLayout>
#include <QImage>
#include <QDebug>
#include <QPushButton>
#include <QFont>
#include <QRect>
#include <QDesktopWidget>
#include "classicgame.h"
#include"ui_classicgame.h"

gameover::gameover(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    setWindowFlags (Qt::FramelessWindowHint);


    //设置标题
    this->setWindowTitle(tr("gameover"));
    QLabel *label1 = new QLabel(this);  //创建QLabel控件

    //添加Qpixmap对象，载入图片,将图片最大化
    QPixmap p;
    p.load(":/imgs/fantasticbackground.jpg");
    label1->setFixedSize(this->width(),this->height());
    label1->setPixmap(p.scaled(label1->size(),Qt::KeepAspectRatio,
                               Qt::SmoothTransformation));
    label1->show();
    label1->setGeometry(0,0,1350,700);

    //设置按钮内容与字体
    QPushButton *bt= new QPushButton(this);
    QString pushButton_SS = "QPushButton{border-radius:10px;color:black;}";
    bt->setStyleSheet(pushButton_SS);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    bt->show();
    bt->setText("返回");
    bt->setGeometry(this->width()/2-75,this->height()/2-25,150,50);
    QString a = "华文中宋";
    QFont *ft=new QFont(a,25);
    //QFont *ft=new QFont(ui->label->font());
    bt->setFont(*ft);
    connect(bt, SIGNAL(clicked()), this, SLOT(ClickButton()));
    QLabel *temp=new QLabel(this);
    temp->setGeometry(this->width()/2-75,this->height()/2-100,150,50);
    extern QString user;
    temp->setFont(*ft);
    temp->setText(user);
    QLinearGradient linearGrad(QPointF(50,120), QPointF(300,221));
    linearGrad.setColorAt(0, Qt::red);
    linearGrad.setColorAt(0.5, Qt::yellow);
    linearGrad.setColorAt(1, Qt::green);
    QBrush brush(linearGrad);
    QPalette palette2;
    palette2.setBrush(QPalette::WindowText, brush);
    temp->setAutoFillBackground(true);
    temp->setPalette(palette2);
    temp->show();

}

gameover::~gameover()
{
    delete ui;
}

void gameover::ClickButton()
{

     classicgame *temp= new classicgame;
     this->close();
     temp->show();

}
