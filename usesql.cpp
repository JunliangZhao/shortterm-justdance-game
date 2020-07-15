#include "usersql.h"
#include<QObject>
#include<QDebug>
#include<QTextCodec>

usersql::usersql(QObject *parent) : QObject(parent)
{
    if(!db.open())
    {
        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
        db = QSqlDatabase::addDatabase("QSQLITE","connection");
        db.setDatabaseName("usersdata.db");
        db.setUserName("root");
        db.setPassword("123");
        db.open();
    }
    else
    {
        userconnect();
    }
}




bool usersql::userconnect()
{
    db = QSqlDatabase::database("connection");
    if(db.open())
    {
         return true;
    }
    else
    {
         return false;
    }

}



bool usersql::userinsertion()
{
    QSqlQuery query(db);
    if(query.exec("create table user(id integer primary key,username varchar,password varchar,head varchar)")
        && query.exec("insert into user values(null,'赵君亮',123,':/头像资源/0f292365fc.jpg')")
        && query.exec("insert into user values(null,'陈嘉博',123,':/头像资源/0f292365fc.jpg')")
        && query.exec("insert into user values(null,'项桂巳雨',123,':/头像资源/0f292365fc.jpg')")
        && query.exec("insert into user values(null,'李勃帆',123,':/头像资源/0f292365fc.jpg')"))
    {
        return true;
    }
    else
    {
        return false;
    }
}





