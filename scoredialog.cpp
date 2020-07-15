#include "scoredialog.h"
#include "ui_scoredialog.h"
#include<QPainter>
#include<QDebug>
#include<QLabel>
#include<QString>
#include<QTime>
#include<QPixmap>
#include<QRect>
#include<QPropertyAnimation>


scoreDialog::scoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scoreDialog)
{
    ui->setupUi(this);


    //设置背景和无边框
    this->setBackgroundImage(":/奈绪星空.jpg");
    setWindowFlags (Qt::FramelessWindowHint);



    QPixmap pix;
    pix.load(QString ( ":/黄色小星星.png"));//提前加载防止卡顿

    //设置成绩label和渐变色
    QRect rec(x,y,w,h);
    score=new QLabel(this);
    score->setGeometry(rec);

    QLinearGradient linearGrad(QPointF(50,120), QPointF(751,221));
    linearGrad.setColorAt(0, QColor(1,0,1));
    linearGrad.setColorAt(0.2, Qt::yellow);
    linearGrad.setColorAt(0.6, Qt::red);

    QBrush brush(linearGrad);
    QPalette palette;
    palette.setBrush(QPalette::Background, brush);
    score->setAutoFillBackground(true);
    score->setPalette(palette);

    //设置总评label
    zongpingLabel=new QLabel(this);
    zongpingLabel->setGeometry(x,y+100,500,100);
    QPalette p1=zongpingLabel->palette();
    p1.setColor(QPalette::WindowText,Qt::white);
    zongpingLabel->setPalette(p1);
    zongpingLabel->setFont(QFont("方正苏新诗柳楷简体",25));


    QString scoreText=QString::number(w);
    textlabel=new QLabel(scoreText,this);


    //设置闪烁label
    shininglabel=new QLabel(this);
    shininglabel->setGeometry(0,0,this->width(),this->height()+50);
    QPixmap shiningpic;
    shiningpic.load(":/透明闪烁.png");
    shininglabel->setPixmap(shiningpic.scaled(shininglabel->size(),
                                              Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation));
    shininglabel->hide();

    //设置继续按钮
    nextsongBtn=new MyButton(this);
    nextsongBtn->setText(("继续"));
    nextsongBtn->setGeometry(this->width()/5*4,this->height()/5*4,200,100);
    nextsongBtn->setFont(QFont("方正苏新诗柳楷简体",20));
    nextsongBtn->setStyleSheet("background-image: url(:/背景钻石.jpg);border-radius: 15px;");
    nextsongBtn->hide();

    //连接信号
    connect(nextsongBtn,SIGNAL(clicked(bool)),this,SLOT(nextsong()));

    //设置各种计时器
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(hidelabel()));

    Timer1=new QTimer(this);
    connect(Timer1,SIGNAL(timeout()),this,SLOT(paint()));
    Timer1->start(18);

    timer_zp=new QTimer(this);
    connect(timer_zp,SIGNAL(timeout()),this,SLOT(showzp()));

    //设置各种音效
    dong=new QSoundEffect(this);
    dong->setSource(QUrl::fromLocalFile(":/重物落地.wav"));

    clap=new QSoundEffect(this);
    clap->setSource(QUrl::fromLocalFile(":/喝彩掌声.wav"));

    ding=new QSoundEffect(this);
    ding->setSource(QUrl::fromLocalFile(":/金币弹出.wav"));

    com=new QSoundEffect(this);
    com->setSource(QUrl::fromLocalFile(":/正确.wav"));

    bgm2=new QSoundEffect(this);
    bgm2->setSource(QUrl::fromLocalFile(":/点星.wav"));
    bgm2->setVolume(0.4);
    bgm2->play();

    loading=new QSoundEffect(this);
    loading->setSource(QUrl::fromLocalFile(":/加载.wav"));
    loading->play();

    jntm=new QSoundEffect(this);
    jntm->setSource(QUrl::fromLocalFile(":/鸡你太美.wav"));

}

scoreDialog::~scoreDialog()
{
    delete ui;
}
void scoreDialog::setBackgroundImage(QString path)
{
    //设置窗口背景
    QPixmap pixmap = QPixmap(path).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

void scoreDialog::paintEvent(QPaintEvent *event)
{

    qDebug()<<0;
    Q_UNUSED(event);
    if(t!=0)
    {

        //绘制黄色小星星
        QString pathName = ":/黄色小星星.png";
        QImage sourceImage;
        sourceImage.load(pathName);
        QPainter *p=new QPainter(this);
        p->setRenderHint( QPainter::Antialiasing );
        QColor quadColor( 0, 0, 255 );

        //使小星星绕自己中心旋转
        p->setBrush( quadColor );
        QTime time = QTime::currentTime();

        p->translate( 400, 100 );
        p->rotate( ( time.second() + ( time.msec() / 1000.0 ) ) * 12.0 );

        p->drawImage(QRect(-50, -50, sourceImage.width(), sourceImage.height()), sourceImage);
        delete p;   //删除画笔

        //绘制一个可旋转的小星星
        if(w>=200)
        {
            QPainter *p1=new QPainter(this);
            p1->translate(500, 100);
            p1->rotate(12.0+ ( time.second() + ( time.msec() / 1000.0 ) ) * 12.0 );

            p1->drawImage(QRect(-50, -50, sourceImage.width(), sourceImage.height()), sourceImage);
            delete p1;


        }
        //绘制一个可旋转的小星星
        if(w>=300)
        {
            QPainter *p2=new QPainter(this);
            p2->translate(600, 100);
            p2->rotate(24.0+ ( time.second() + ( time.msec() / 1000.0 ) ) * 12.0 );


            p2->drawImage(QRect(-50, -50, sourceImage.width(), sourceImage.height()), sourceImage);
            delete p2;
        }
        //绘制一个可旋转的小星星
        if(w>=400)
        {
            QPainter *p3=new QPainter(this);
            p3->translate(700, 100);
            p3->rotate(36.0+ ( time.second() + ( time.msec() / 1000.0 ) ) * 12.0 );


            p3->drawImage(QRect(-50, -50, sourceImage.width(), sourceImage.height()), sourceImage);
            delete p3;
        }
    }


}

void scoreDialog::paint()
{
    //绘制分数条
    w++;
    QRect rec(x,y,w,h);

    //绘制渐变色
    score->setGeometry(rec);
    QLinearGradient linearGrad(QPointF(50,120), QPointF(500,221));
    linearGrad.setColorAt(0, Qt::magenta);
    linearGrad.setColorAt(0.3, Qt::blue);
    linearGrad.setColorAt(0.6, Qt::yellow);
    linearGrad.setColorAt(0.9, Qt::red);

    QBrush brush(linearGrad);
    QPalette palette;
    palette.setBrush(QPalette::Background, brush);
    score->setAutoFillBackground(true);
    score->setPalette(palette);


    //设置label
    QString scoreText=QString::number(w);
    QPalette p=textlabel->palette();
    p.setColor(QPalette::WindowText,Qt::white);
    textlabel->setPalette(p);
    textlabel->setFont(QFont("方正苏新诗柳楷简体",25));
    textlabel->setText(scoreText);
    textlabel->setGeometry(QRect(x+w+10,y,500,50));

    //达到100分时触发计时器
    if(w>=100)
    {
        Timer2=new QTimer(this);
        connect(Timer2,SIGNAL(timeout()),this,SLOT(update()));
        Timer2->start(30);
        t=1;
    }
    //判断是否达到最终成绩
    if(w==finalScore)
    {

        //播放和关闭音效
        loading->stop();
        com->play();

        Timer1->stop();
        delete Timer1;

        //判断评价
        if(finalScore<=100)
        {
            pj=QString("东大蔡徐坤！");
            zongping.append(pj);
        }
        if(finalScore>100&&finalScore<=200)
        {
            pj=QString("舞房萌新！");
            zongping.append(pj);
        }
        if(finalScore>200&&finalScore<=300)
        {
            pj=QString("广场领舞者！");
            zongping.append(pj);
        }
        if(finalScore>300&&finalScore<=400)
        {
            pj= QString("东大舞王！");
            zongping.append(pj);
        }
        if(finalScore>400)
        {
            pj= QString("舞王再世！");
            zongping.append(pj);
        }

        //触发计时器实现音效调用
        timer_zp->start(600);

    }

    //星星出来时闪烁
    if(w==100||w==200||w==300||w==400||w==500)
    {

        shininglabel->show();
        timer->start(250);

        ding->play();

    }


}


void scoreDialog::hidelabel()
{
    //使闪烁label消失
    shininglabel->hide();
    timer->stop();

}

void scoreDialog::showzp()
{
    //绘制出评价并播放音效
    QString str=pj.mid(0,s);
    zongping=QString("评价：").append(str);
    zongpingLabel->setText(zongping);
    s++;
    if(s>1&&s<=pj.length())
        dong->play();
    if(s==(pj.length()+1))
    {
        if(finalScore>100)
            clap->play();
        else
        {
            bgm2->stop();
            jntm->play();
            this->onShakeWindow();
        }

    }

    nextsongBtn->show();

}

void scoreDialog::nextsong()
{

    //触发继续按钮使结算界面消失，返回主界面
    bgm2->stop();
    clap->stop();


    //渐变消失
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));


}

void scoreDialog::recscore(QString name, QString songname, int score)
{
    //接收歌名用户名和最终得分的槽函数
    songName=songname;
    finalScore=score;

    //将基础资料显示在label中
    userName=QString("用户名：");
    userName.append(name);
    usernameLabel=new QLabel(this);
    userName.append("   歌曲名: ");
    userName.append(songName);
    usernameLabel->setGeometry(x,y-50,800,h);
    usernameLabel->setFont(QFont("方正苏新诗柳楷简体",25));
    usernameLabel->setText(userName);
    usernameLabel->show();
    QPalette p=usernameLabel->palette();
    p.setColor(QPalette::WindowText,Qt::white);
    usernameLabel->setPalette(p);

}


void scoreDialog::onShakeWindow()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
