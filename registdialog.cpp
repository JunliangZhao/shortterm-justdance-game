#include "registdialog.h"
#include "ui_registdialog.h"
#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QMovie>
#include<QWidget>
#include<QLabel>
#include<QPalette>
#include<QColorDialog>
#include<QMovie>
#include<QPushButton>
#include<mainwindow.h>
#include<QPropertyAnimation>
#include<usersql.h>
#include<QPainter>
#include<QTimer>


registDialog::registDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registDialog)
{
    ui->setupUi(this);

    this->resize(400,300);
    this->setGeometry(590,300,800,600);
    QLabel* label1 = new QLabel(this);
    QLabel* label2 = new QLabel(this);




    label1->setText("用户名");
    label1->setGeometry(200,280,200,50);
    label2->setText("密码");
    label2->setGeometry(200,350,200,50);




    QLineEdit* edit1 = new QLineEdit(this);
    QLineEdit* edit2 = new QLineEdit(this);
    edit2->setEchoMode(QLineEdit::Password);

    edit1->setGeometry(350,280,200,50);
    edit2->setGeometry(350,350,200,50);
    QFont font2 = QFont("方正苏新诗柳楷简体",16);
    label1->setFont(font2);
    label2->setFont(font2);




    QPalette p = this->palette();
    p.setColor(QPalette::Window,QColor(255,220,234));
    this->setPalette(p);




    QLabel* label3 = new QLabel(this);
    QMovie* movie2 = new QMovie(":/动图/20081102_efa2b84c9cb3a950c02bjm6yzw5MY3qh.gif");
    label3->setMovie(movie2);
    movie2->start();
    label3->setGeometry(50,0,300,100);
    QLabel* label4 = new QLabel(this);
    label4->setMovie(movie2);
    movie2->start();
    label4->setGeometry(50,220,300,100);




    QFont font = QFont("方正苏新诗柳楷简体",16);
    QPushButton* button = new QPushButton("注册",this);
    button->setAutoFillBackground(true);
    button->setFlat(true);
    QPalette p2 = button->palette();
    p2.setColor(QPalette::Button,QColor(255,244,184));
    button->setPalette(p2);
    button->setFont(font);
    button->resize(100,50);
    button->setGeometry(250,420,300,100);
    button->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'方正苏新诗柳楷简体';"
                "background-color:rgb(125,55,75);"
                "color:rgb(238,238,238);"
                );

    QPushButton* headPortrait = new QPushButton(this);
    headPortrait->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:100px;"
                );
    headPortrait->setGeometry(300,50,200,200);
    QPixmap pixmapa(":/头像资源/0f292365fc.jpg");
    QPixmap pixmap(200,200);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //void QPainter::setRenderHints(RenderHints hints, bool on = true)
    QPainterPath path;
    path.addEllipse(0,0,200,200);
    //void QPainterPath::addEllipse(const QRectF &boundingRectangle)
    painter.setClipPath(path);
    //void QPainter::setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip)
    painter.drawPixmap(0,0,200,200,pixmapa);
    //void QPainter::drawPixmap(const QRectF &target, const QPixmap &pixmap, const QRectF &source)
    headPortrait->setIcon(QIcon(pixmap));
    headPortrait->setIconSize(QSize(200,200));



    QFont font3 = QFont("方正苏新诗柳楷简体",10);
    QLabel* label5 = new QLabel(this);
    label5->setGeometry(350,330,200,20);
    label5->setFont(font3);
    QTimer* timer = new QTimer(this);
    //判断该用户名是否已经存在
    connect(timer,&QTimer::timeout,this,[=](){
    QString s = edit1->text();
    usersql userdb;
    QSqlQuery query = QSqlQuery(userdb.db);
    bool res = query.exec("select username from user");
    //bool QSqlQuery::exec(const QString &query)
    if(res)
     {
         while(query.next())
           {
                QString qs1 = query.value(0).toString();
                 if(qs1 == s)
                   {
                       flag2 = 1;
                   }
              }
         if(flag2 == 1)
         {
             label5->setText("该用户名已被注册");
         }
         else
         {
             label5->setText("");
         }
      }
   });
    timer->start(500);




//注册界面注册键的槽函数，点击建立新用户，并将信息载入数据库
    connect(button,&QPushButton::clicked,this,[=](){
        usersql userdb;
        QSqlQuery query(userdb.db);
        QString username = edit1->text();
        QString password = edit2->text();
        QString head = ":/头像资源/0f292365fc.jpg";
        query.prepare("INSERT INTO user(username,password,head) VALUES(:username, :password,:head)");
        //bool QSqlQuery::prepare(const QString &query)
        query.bindValue(":username",username);
        //void QSqlQuery::bindValue(const QString &placeholder, const QVariant &val, QSql::ParamType paramType = QSql::In)
        query.bindValue(":password",password);
        query.bindValue(":head",head);
        query.exec();
        userdb.db.close();
        this->setWindowOpacity(1);
        QPropertyAnimation* animation = new QPropertyAnimation(this,"windowOpacity");
        animation->setDuration(1500);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
                   });
}
registDialog::~registDialog()
{
    delete ui;
}
