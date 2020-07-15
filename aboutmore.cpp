#include "aboutmore.h"
#include "ui_aboutmore.h"
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
aboutmore::aboutmore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::aboutmore)
{

    ui->setupUi(this);
    this->setWindowTitle(tr("更多"));
    setWindowFlags (Qt::FramelessWindowHint);


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

    QLabel *l4 = new QLabel(this);
    QString a4 = "华文行楷";
    QFont *ft4=new QFont(a4,22);
    l4->setText("异想天开小小组版权所有");
    l4->setFont(*ft4);
    l4->setGeometry(50,100,400,100);

    QLabel *l1 = new QLabel(this);
    QString a = "华文行楷";
    QFont *ft=new QFont(a,22);
    l1->setText("侵权必究");
    l1->setFont(*ft);
    l1->setGeometry(320,150,300,100);

    QLabel *l2 = new QLabel(this);
    QString a2 = "华文行楷";
    QFont *ft2=new QFont(a2,22);
    l2->setText("工作室电话：");
    l2->setFont(*ft2);
    l2->setGeometry(300,350,300,100);

    QLabel *l3 = new QLabel(this);
    QString a3 = "华文行楷";
    QFont *ft3=new QFont(a3,22);
    l3->setText("188 9345 2847");
    l3->setFont(*ft3);
    l3->setGeometry(320,400,500,100);
}

aboutmore::~aboutmore()
{
    delete ui;
}

void aboutmore::back()
{
    this->close();
    classicgame *p = new classicgame;
    p->show();
}
