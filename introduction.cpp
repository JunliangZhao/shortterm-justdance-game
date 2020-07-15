#include "introduction.h"
#include "ui_introduction.h"
#include "classicgame.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QPainter>
#include <QGridLayout>
#include <QImage>
#include <QDebug>
#include <QPushButton>
#include <QFont>
introduction::introduction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::introduction)
{

    ui->setupUi(this);

    setWindowFlags (Qt::FramelessWindowHint);
    //设置标题
    this->setWindowTitle(tr("游戏说明"));

    //设置背景颜色
    QPalette palette = this->palette();  //获取调色板
    palette.setColor(QPalette::Window, QColor(255, 255, 255));  //设置为白色
    this->setPalette(palette);  //重新设置调色板

    // 给MainWindow新建一个新的中心窗口
    QWidget* newCentralWidget = new QWidget;
    this->setCentralWidget(newCentralWidget);

    // 栅格布局
    QGridLayout* layout = new QGridLayout(this);

    //添加QLabel控件
    QLabel *label1 = new QLabel(this);  //创建QLabel控件
//    setCentralWidget(label1);  //将当前控件至于中央
//    label1->setText("sjhskj");

    //添加Qpixmap对象，载入图片
    QPixmap p;
    p.load(":/imgs/fantasy.jpg");
    label1->setPixmap(p);

    //设置客户区大小
    label1->show();
    layout->addWidget(label1, 0, 0, 1, 1);

    //layout设置到中心窗口
    label1->adjustSize();
    this->resize(500,600);

    QLabel *l1 = new QLabel(this);
    QString a = "华文行楷";
    QFont *ft=new QFont(a,22);
    l1->setText("ta要躲开陨石");
    l1->setFont(*ft);
    l1->setGeometry(100,220,300,100);

    QLabel *l2 = new QLabel(this);
    QString a2 = "华文行楷";
    QFont *ft2=new QFont(a2,22);
    l2->setText("还要收集各种元素石");
    l2->setFont(*ft2);
    l2->setGeometry(100,260,300,100);

    QLabel *l3 = new QLabel(this);
    QString a3 = "华文行楷";
    QFont *ft3=new QFont(a3,22);
    l3->setText("用手势操控人物");
    l3->setFont(*ft3);
    l3->setGeometry(100,300,500,100);

    QLabel *l6 = new QLabel(this);
    QString a6 = "华文行楷";
    QFont *ft6=new QFont(a6,22);
    l6->setText("接住更多元素石");
    l6->setFont(*ft6);
    l6->setGeometry(100,340,500,100);

    QLabel *l7 = new QLabel(this);
    QString a7 = "华文行楷";
    QFont *ft7=new QFont(a7,22);
    l7->setText("获得魔法超能力");
    l7->setFont(*ft7);
    l7->setGeometry(100,380,500,100);

    QLabel *l4 = new QLabel(this);
    QString a4 = "华文行楷";
    QFont *ft4=new QFont(a4,22);
    l4->setText("这是我们的主人公");
    l4->setFont(*ft4);
    l4->setGeometry(100,100,300,100);
    QLabel *labelpig = new QLabel(this);
    QPixmap pl;
    pl.load(":/xuemeileft.png");
    labelpig->setPixmap(pl);
    labelpig->setGeometry(350,50,100,100);
    labelpig->show();

    QLabel * l5= new QLabel(this);
    QString a5 = "华文行楷";
    QFont *ft5=new QFont(a5,22);
    l5->setText("一位魔法城堡里的公主");
    l5->setFont(*ft5);
    l5->setGeometry(100,140,300,100);

    QLabel * l11= new QLabel(this);;
    l11->setText("有一天，天上掉下各种宝石");
    l11->setFont(*ft6);
    l11->setGeometry(100,180,400,100);

    QPushButton *bt3= new QPushButton(this);
    QString pushButton_SS3 = "QPushButton{border-radius:10px;color:black;}";
    bt3->setStyleSheet(pushButton_SS3);
    bt3->setCursor(QCursor(Qt::PointingHandCursor));
    bt3->show();
    bt3->setText("返回");
    bt3->setGeometry(this->width()-150,this->height()-50,150,50);
    QString a0 = "华文行楷";
    QFont *ft0=new QFont(a0,22);
    bt3->setFont(*ft0);
    connect(bt3,SIGNAL(clicked()),this,SLOT(back()));
}

introduction::~introduction()
{
    delete ui;
}

void introduction::back()
{
    this->close();
   classicgame *p = new classicgame;
    p->show();
}
