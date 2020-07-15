#include "mainwindow.h"
#include <QApplication>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QTextCodec>
#include<usersql.h>
#include<QString>
int signalflag = 1;
int timenumber = 1;
int flag1 = 0;
int flag2 = 0;
int fenshu=0;
QString user;


void link()
{
    signalflag = 1;
}





void link2()
{
   timenumber = 1;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    usersql userdb;
    userdb.userinsertion();
    if(userdb.db.open())
    {
        MainWindow* w = new MainWindow;
        w->show();
    }






    return a.exec();
}
