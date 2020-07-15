#ifndef USERSQL_H
#define USERSQL_H
#include<QObject>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>


class usersql : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase db;
    explicit usersql(QObject *parent = nullptr);
    bool userconnect();
    bool userinsertion();

signals:

public slots:
};

#endif // USERSQL_H
