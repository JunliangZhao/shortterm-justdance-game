#include "classicgame.h"
#include"ui_classicgame.h"
  #include "maininterface.h"
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QPainter>
#include <QGridLayout>
#include <QImage>
#include <QDebug>
#include <QPushButton>
#include <QFont>
#include "playinterface2.h"
#include <QRect>
#include <QDesktopWidget>
#include "introduction.h"
#include "aboutmore.h"
classicgame::classicgame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::classicgame)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags (Qt::FramelessWindowHint);
    this->styleSheet();

    //设置标题
    this->setWindowTitle(tr("游戏模式开始"));

    //设置客户区大小
    this->resize(500,400);

    //设置背景颜色
    QPalette palette = this->palette();  //获取调色板
    palette.setColor(QPalette::Window, QColor(255, 255, 255));  //设置为白色
    this->setPalette(palette);  //重新设置调色板

    // 给MainWindow新建一个新的中心窗口
    QWidget* newCentralWidget = new QWidget;
    newCentralWidget->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setCentralWidget(newCentralWidget);

    // 栅格布局
    QGridLayout* layout = new QGridLayout(this);


    //添加QLabel控件
    QLabel *label1 = new QLabel(this);
    label1->setAttribute(Qt::WA_DeleteOnClose,true);//创建QLabel控件
//    setCentralWidget(label1);  //将当前控件至于中央
//    label1->setText("sjhskj");

    //添加Qpixmap对象，载入图片
    QPixmap p;
    p.load(":/imgs/fantasy.jpg");
    label1->setPixmap(p);

    //设置客户区大小
    label1->show();
    layout->addWidget(label1, 0, 0, 1, 1);

    // layout设置到中心窗口
    label1->adjustSize();
    this->resize(500,600);

    //设置按钮内容与字体
    QPushButton *bt= new QPushButton(this);
    bt->setAttribute(Qt::WA_DeleteOnClose,true);

    QString pushButton_SS = "QPushButton{border-radius:10px;color:black;}";
    bt->setStyleSheet(pushButton_SS);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    bt->show();
    bt->setText("开始游戏");
    bt->setGeometry(175,250,150,50);
    QFont *ft=new QFont(ui->label->font());
    bt->setFont(*ft);
    connect(bt, SIGNAL(clicked()), this, SLOT(ClickButton()));


    QPushButton *bt2= new QPushButton(this);
    QString pushButton_SS2 = "QPushButton{border-radius:10px;color:black;}";
    bt2->setStyleSheet(pushButton_SS2);
    bt2->setAttribute(Qt::WA_DeleteOnClose,true);
    bt2->setCursor(QCursor(Qt::PointingHandCursor));
    bt2->show();
    bt2->setText("游戏说明");
    bt2->setGeometry(175,300,150,50);
    QFont *ft2=new QFont(ui->label->font());
    bt2->setFont(*ft2);
    connect(bt2, SIGNAL(clicked()), this, SLOT(ClickButton2()));

    QPushButton *bt3= new QPushButton(this);
    bt3->setAttribute(Qt::WA_DeleteOnClose,true);
    QString pushButton_SS3 = "QPushButton{border-radius:10px;color:black;}";
    bt3->setStyleSheet(pushButton_SS3);
    bt3->setCursor(QCursor(Qt::PointingHandCursor));
    bt3->show();
    bt3->setText("返回");
    bt3->setGeometry(175,350,150,50);
    QFont *ft3=new QFont(ui->label->font());
    bt3->setFont(*ft3);

    QPushButton *bt4= new QPushButton(this);
    bt4->setAttribute(Qt::WA_DeleteOnClose,true);
    bt4->setStyleSheet(pushButton_SS2);
    bt4->setCursor(QCursor(Qt::PointingHandCursor));
    bt4->show();
    bt4->setText("更多");
    bt4->setGeometry(175,400,150,50);
    QFont *ft4=new QFont(ui->label->font());
    bt4->setFont(*ft4);
    connect(bt4, SIGNAL(clicked()), this, SLOT(ClickButton4()));
     connect(bt3, SIGNAL(clicked()), this, SLOT(ClickButton3()));
}

classicgame::~classicgame()
{
    delete ui;
}

void classicgame::ClickButton()
{
    this->close();
    playinterface2 *p=new playinterface2;
    p->show();
}

void classicgame::ClickButton2()
{
    this->close();
    introduction *p=new introduction;
    p->show();
}

void classicgame::ClickButton4()
{
    this->close();
    aboutmore *p=new aboutmore;
    p->show();
}

void classicgame::ClickButton3()
{
    mainInterface *temp;
    temp=new mainInterface;
    temp->show();
    this->close();





}
