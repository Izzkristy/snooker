//数据库定义文件

#ifndef DB_H
#define DB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtCore>

//数据库类
class ServerDB
{
    public:
        ServerDB(QString dbname = "server.db");
        ~ServerDB();

    public:
        //检查用户是否存在
        int checkUser(QString name,QString pwd,int &score);
        //QVector<QVector<QString> > find(QString type, QString key);

    private:
        //数据库连接
        QSqlDatabase db;
        //数据库操作执行对象
        QSqlQuery *query;
};

//extern BesDB besdb;

#endif // DB_H
