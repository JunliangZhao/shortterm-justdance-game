#include "logindialog.h"
#include "ui_logindialog.h"
#include <maininterface.h>
#include<changeheaddialog.h>
#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPalette>
#include<QColorDialog>
#include<QMovie>
#include<QPushButton>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include<mainwindow.h>
#include<QDebug>
#include<QPropertyAnimation>
#include<usersql.h>
#include<QTimer>
#include<QPixmap>
#include<QPainter>
#include <QVariant>
#include<QDebug>
#include<QSqlError>
#include<QString>
extern QString user;
int headflag = 0;
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);


    this->setGeometry(590,300,800,600);
    QLabel* label1 = new QLabel(this);
    QLabel* label2 = new QLabel(this);
    label1->setText("用户名");
    label1->setGeometry(200,280,200,50);
    label2->setText("密码");
    label2->setGeometry(200,350,200,50);



    QFont font = QFont("方正苏新诗柳楷简体",16);
    label1->setFont(font);
    label2->setFont(font);
    QFont font2 = QFont("方正苏新诗柳楷简体",10);
    QFont font3 = QFont("方正苏新诗柳楷简体",26);


    QLineEdit* edit1 = new QLineEdit(this);
    QLineEdit* edit2 = new QLineEdit(this);
    edit2->setEchoMode(QLineEdit::Password);
    edit1->setGeometry(350,280,200,50);
    edit2->setGeometry(350,350,200,50);
    edit1->setFont(font);







     QPalette p = this->palette();
     p.setColor(QPalette::Window,QColor(255,220,234));
     //void QPalette::setColor(ColorGroup group, ColorRole role, const QColor &color)
     this->setPalette(p);




     QLabel* label4 = new QLabel(this);
     label4->setGeometry(350,330,200,20);
     label4->setFont(font2);

     QTimer* timer = new QTimer(this);
     connect(timer,&QTimer::timeout,this,[=](){
     QString s = edit1->text();
     usersql userdb;
     QSqlQuery query = QSqlQuery(userdb.db);
     //用户名的提取，匹配，得到匹配的用户名后，调出该用户的头像并显示，并将该用户不存在这句话消去
     bool res = query.exec("select username,head from user");
     if(res)
      {
          while(query.next())
            {
                 QString qs1 = query.value(0).toString();
                 //QVariant QSqlQuery::value(int index) const
                  if(qs1 == s)
                    {
                        user=qs1;
                        label4->setText("");
                        QPixmap pixmapa(query.value(1).toString());
                        QPixmap pixmap(200,200);
                        pixmap.fill(Qt::transparent);
                        //void QPixmap::fill(const QPaintDevice *device, const QPoint &p)
                        QPainter painter(&pixmap);
                        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
                        QPainterPath path;
                        path.addEllipse(0,0,200,200);
                        painter.setClipPath(path);
                        painter.drawPixmap(0,0,200,200,pixmapa);
                        headPortrait->setIcon(QIcon(pixmap));
                        headPortrait->setIconSize(QSize(200,200));
                        flag2 = 1;
                    }
               }
          if(flag2 == 0)
          {
              label4->setText("该用户名不存在");
          }
       }
    });
     timer->start(500);





     button = new QPushButton("登录",this);
     button->setAutoFillBackground(true);
     button->setFlat(true);
     QPalette p2 = button->palette();
     p2.setColor(QPalette::Button,QColor(255,244,184));
     button->setPalette(p2);
     button->setFont(font3);
     button->setGeometry(250,420,300,100);
     button->setStyleSheet(
                 "border: 2px solid #8f8f91;"
                 "border-radius:10px;"
                 "font-family:'方正苏新诗柳楷简体';"
                 "background-color:rgb(125,55,75);"
                 "color:rgb(238,238,238);"
                 );



//头像按钮的创建，默认头像为第一张
     headPortrait = new QPushButton(this);
     headPortrait->setStyleSheet(
                 "border: 2px solid #8f8f91;"
                 "border-radius:100px;"
                 );

    // void
     //setStyleSheet(const QString &styleSheet)

     headPortrait->setGeometry(300,50,200,200);
     QString s[20];
     s[0] = ":/头像资源/0f292365fc.jpg";
     s[1] = ":/头像资源/102e183982.jpg";
     s[2] = ":/头像资源/2aaa52d36c.jpg";
     s[3] = ":/头像资源/370cbd1446.jpg";
     s[4] = ":/头像资源/3a5df6885e.jpg";
     s[5] = ":/头像资源/4414189b4c.jpg";
     s[6] = ":/头像资源/687b2c1605.jpg";
     s[7] = ":/头像资源/7d60054b1a.jpg";
     s[8] = ":/头像资源/7fc2a93100.jpg";
     s[9] = ":/头像资源/80ac99618c.jpg";
     s[10] = ":/头像资源/bPwFQ336.jpg";
     s[11] = ":/头像资源/c41dc29112.jpg";
     s[12] = ":/头像资源/eabc1d6f85.jpg";
     s[13] = ":/头像资源/eac3cb1170.jpg";
     s[14] = ":/头像资源/edf7945f57.jpg";
     s[15] = ":/头像资源/ffbd1deaae.jpg";
     s[16] = ":/头像资源/QQ图片20190904110529.jpg";
     s[17] = ":/头像资源/TIKpu55j.jpg";
     s[18] = ":/头像资源/VaHWQ008.jpg";
     s[19] = ":/头像资源/ZVp1588B.jpg";
     QPixmap pixmapa(s[0]);
     QPixmap pixmap(200,200);
     pixmap.fill(Qt::transparent);
     QPainter painter(&pixmap);
     painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
     QPainterPath path;
     path.addEllipse(0,0,200,200);
     painter.setClipPath(path);
     painter.drawPixmap(0,0,200,200,pixmapa);
     headPortrait->setIcon(QIcon(pixmap));
     headPortrait->setIconSize(QSize(200,200));



//头像按钮的槽函数，可以更换头像并载入数据库
     connect(headPortrait,&QPushButton::clicked,this,[=](){
          changeHeadDialog* changehead = new changeHeadDialog;
          QLabel* label = new QLabel(changehead);
          label->setGeometry(150,0,900,750);
          QPixmap map(s[0]);
          QPixmap map2 = map.scaled(label->size().width() - 300,label->size().height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
          label->setPixmap(map2);
          label->setAlignment(Qt::AlignHCenter);
          //void
          //setAlignment(Qt::Alignment)

          label->show();



          connect(changehead->leftbutton,&QPushButton::clicked,changehead,[=](){
                  headflag--;
                  if(headflag == -1)
                  {
                      headflag = 19;
                  }
                  QPixmap map(s[headflag]);
                  QPixmap map2 = map.scaled(label->size().width() - 300,label->size().height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                  label->setPixmap(map2);
         });




          connect(changehead->rightbutton,&QPushButton::clicked,changehead,[=](){
                  headflag++;
                  if(headflag == 20)
                  {
                      headflag = 0;
                  }
                  QPixmap map(s[headflag]);
                  QPixmap map2 = map.scaled(label->size().width() - 300,label->size().height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                  label->setPixmap(map2);
                  //void
                 // setPixmap(const QPixmap &)

          });



//更换头像界面中确定键，载入对应的用户数据库，并将头像改为确定后的头像
          connect(changehead->bottombutton,&QPushButton::clicked,changehead,[=](){
              QString s1 = edit1->text();
              QString s2 = edit2->text();
              usersql userdb;
              QSqlQuery query = QSqlQuery(userdb.db);
              bool res = query.exec("select username, password from user");
              if(res)
              {
                  QString qs1;
                  QString qs2;
                  int i = 0;
                  while(query.next())
                  {
                      i++;
                      qs1 = query.value(0).toString();
                      qs2 = query.value(1).toString();
                      qDebug()<<qs1<<endl;
                      qDebug()<<endl;
                      qDebug()<<endl;
                      qDebug()<<endl;
                      qDebug()<<endl;
                      if(qs1 == s1 && qs2 == s2)
                      {
                          flag = 1;
                          usersql userdb;
                          QSqlQuery query = QSqlQuery(userdb.db);
                          query.clear();
                          query.prepare(QString("update user set username = ?,password = ?,head = ? where id = %1").arg(i));
                          query.bindValue(0,s1);
                          query.bindValue(1,s2);
                          query.bindValue(2,s[headflag]);
                          if(!query.exec())
                          {
                              qDebug()<< query.lastError().text();
                          }
                      }
                  }
               }
              userdb.db.close();
              QPixmap pixmapa(s[headflag]);
              QPixmap pixmap(200,200);
              pixmap.fill(Qt::transparent);
              QPainter painter(&pixmap);
              painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
              QPainterPath path;
              path.addEllipse(0,0,200,200);
              painter.setClipPath(path);
              painter.drawPixmap(0,0,200,200,pixmapa);
              headPortrait->setIcon(QIcon(pixmap));
              headPortrait->setIconSize(QSize(200,200));
              changehead->close();
          });
     });

//登录界面登录键的槽函数，将用户信息与数据库匹配
     connect(button,&QPushButton::clicked,this,[=](){
            QString s1 = edit1->text();
            QString s2 = edit2->text();
            usersql userdb;
            QSqlQuery query = QSqlQuery(userdb.db);
            bool res = query.exec("select username, password from user");
            if(res)
            {
                QString qs1;
                QString qs2;
                int i = 0;
                while(query.next())
                {
                    i++;
                    qs1 = query.value(0).toString();
                    qs2 = query.value(1).toString();
                    qDebug()<<qs1<<endl;
                    qDebug()<<endl;
                    qDebug()<<endl;
                    qDebug()<<endl;
                    qDebug()<<endl;
                    if(qs1 == s1 && qs2 == s2)
                    {
                        flag = 1;
                        usersql userdb;
                        QSqlQuery query = QSqlQuery(userdb.db);
                        query.clear();
                        //void QSqlQuery::clear()
                        query.prepare(QString("update user set username = ?,password = ?,head = ? where id = %1").arg(i));
                        query.bindValue(0,s1);
                        query.bindValue(1,s2);
                        query.bindValue(2,s[headflag]);
                        if(!query.exec())
                        {
                            qDebug()<< query.lastError().text();
                            //QSqlError QSqlQuery::lastError() const
                        }
                    }
                }
             }
            userdb.db.close();
     });
}




loginDialog::~loginDialog()
{
    delete ui;
}
