//客户端连接类，继承于TCP套接字类
//负责与客户端进行交互
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QTimer>
#include "db.h"

class ClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    ClientSocket(QObject *parent = 0);
    //向客户端发送消息
    void sendMsg(QString);
    //客户端用户id
    int uid;
    //大厅位置
    int desknum;

private slots:
    //读取客户端发送的数据，根据数据类型进行处理
    void readClient();
    //删除与客户端的连接
    void deleteConnect();
    //向客户端发送当前大厅数据
    void dealHall();

public slots:
    //判断转发消息是否时本客户端，是则将消息转发过去，否则不处理
    void toMessage(int,QString);

private:
    quint16 nextBlockSize;
    //服务器数据库
    ServerDB serverDb;
    //大厅信息更新定时器
    QTimer updatetimer;
    //处理用户登陆信息
    void dealLogin(QDataStream &in);
    //处理用户进入游戏信息
    void dealPlay(QDataStream &in);
    //处理用户退出游戏信息
    void dealQuit(QDataStream &in);
    //处理用户转发消息信息
    void dealMsg(QDataStream &in);

signals:
    //用户需要转发消息时发出
    void toMsg(int,QString);
};

#endif // CLIENTSOCKET_H
