#include "db.h"

//ServerDB serverDb;
//数据库类构造函数，初始化数据库连接，建立数据库操作执行对象
ServerDB::ServerDB(QString dbname)
{
    if(QSqlDatabase::contains("server"))
    {
        //数据库连接已存在，使用已建立的数据库连接
        db = QSqlDatabase::database("server");
    }
    else
    {
        //数据库连接不存在，新建数据库连接
        db = QSqlDatabase::addDatabase("QSQLITE","server");
    }
    //db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库连接名
    db.setDatabaseName(dbname);
    //打开数据库
    if (!db.open()) {
        qDebug()<<"can't open db"<<dbname;
        exit(1);
    }
    //新建数据库操作执行对象
    query = new QSqlQuery(db);
    query->setForwardOnly(true);
}

//数据库类析构函数，关闭数据库连接，删除数据库操作执行对象
ServerDB::~ServerDB()
{
    delete query;
    if (db.isOpen()) {
        db.close();
    }
}
//检查指定的用户是否存在
//参数：name 用户名，pwd 用户密码，score(引用) 保存用户分数
//返回值：用户存在返回用户id，同时设置score为用户分数;用户不存在返回0
int ServerDB::checkUser(QString name,QString pwd,int &score)
{
    //int i = 0;
    QString sql;
    sql = "select id,score from user where name = '" + name + "' AND pwd = '" + pwd + "'";
    qDebug() << sql;
    query->exec(sql);
    //int cols = query->record().count();
    //qDebug() << cols;
    if(query->next())
    {
        //db.close();
        int id = query->value(0).toInt();
        score = query->value(1).toInt();
        db.close();
        return id;
    }
    else
    {
        //int idNo = query->record().indexOf("id");
        db.close();
        return 0;
    }
}
