#include <QtDebug>
#include <QtNetwork>
#include <QSqlQuery>
#include <QMap>
#include "clientsocket.h"
#include "desk.h"

//构造函数
ClientSocket::ClientSocket(QObject *parent)
    : QTcpSocket(parent)
{
    //有客户端发送过来的数据时调用readClient函数处理消息
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    //客户端连接断开时调用deleteConnect函数
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteConnect()));
    //隔一段时间向客户端发送大厅信息
    this->connect(&updatetimer,SIGNAL(timeout()),this,SLOT(dealHall()));
//    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    uid = 0;
    desknum = -1;
    nextBlockSize = 0;
}

//读取客户端发送的数据，根据数据类型进行处理
//'L' login 登陆信息
//'H' hall大厅信息
//'P' play进入游戏信息
//'Q' quit退出游戏信息
//'M' message消息信息
void ClientSocket::readClient()
{
    //停止发送大厅数据
    updatetimer.stop();
    //读取发送过来的数据
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_8);

    if (nextBlockSize == 0)
    {
        if (bytesAvailable() < sizeof(quint16))
            return;
        in >> nextBlockSize;
    }

    if (bytesAvailable() < nextBlockSize)
        return;

    quint8 requestType;
    //读取消息类型标识，根据标识调用对应的处理函数
    in >> requestType;
	switch(requestType)
    {
    case 'L':
        this->dealLogin(in);
        break;
    case 'H':
        this->dealHall();;
        break;
    case 'P':
        this->dealPlay(in);
        break;
    case 'Q':
        this->dealQuit(in);
        break;
    case 'M':
        this->dealMsg(in);
        break;
	}
}

//登陆信息处理函数
//描述：读取发送过来的用户名和密码，检查用户名和密码是否合法
//      合法则将用户名和分数发送给客户端，不合法则发送对应标识
//参数：套接字读取接口(引用)
//返回值：无
void ClientSocket::dealLogin(QDataStream &in)
{
    //读取用户名和密码
    QString name;
    QString password;
    in >> name;
    in >> password;
    int score;
    //检查用户名和密码的合法性
    int s = serverDb.checkUser(name,password,score);
    qDebug() << s;
    //发送数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    if (s)
    {
        nextBlockSize = 0;
        this->uid = s;
        out << quint16(0) << quint8('L') << quint8(1) << s << score;
    }
    else
    {
        nextBlockSize = 0;
        out << quint16(0) << quint8('L') << quint8(0);
    }
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
    out << quint16(0xFFFF);
}

//大厅信息处理函数
//描述：将大厅信息发送给客户端
//参数：无
//返回值：无
void ClientSocket::dealHall()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    nextBlockSize = 0;
    out << quint16(0) << quint8('H');
    //发送在线人数
    out << onlineNum;
    //发送大厅信息
    for(int i=0;i<PLAYERNUM;i++)
    {
        out << player[i].id;
        out << player[i].name;
        out << player[i].score;
    }
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
    out << quint16(0xFFFF);
    //启动大厅数据更新定时器
    updatetimer.start(UPDATETIME);
}

//用户进入游戏信息处理
//描述：用户进入游戏，更新对应的大厅信息
//参数：套接字读取接口(引用)
//返回值：无
void ClientSocket::dealPlay(QDataStream &in)
{
    int id;
    in >> id;
    this->desknum = id;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    nextBlockSize = 0;
    out << quint16(0) << quint8('P');
    if(player[id].id)
    {
        out << quint8(0);
    }
    else
    {
        out << quint8(1);
        in >> player[id].id;
        in >> player[id].name;
        in >> player[id].score;
    }
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
    out << quint16(0xFFFF);
    //启动大厅信息更新定时器
    updatetimer.start(UPDATETIME);
}

//用户退出游戏信息处理
//描述：用户退出游戏，更新对应的大厅信息
//参数：套接字读取接口(引用)
//返回值：无
void ClientSocket::dealQuit(QDataStream &in)
{
    int num;
    in >> num;
    player[num].id = 0;
    player[num].name = "";
    player[num].score = 0;
    this->dealHall();
}

//用户发送消息信息处理
//描述：读取用户发送消息的接收者以及消息内容，发出转发信息信号
//参数：套接字读取接口(引用)
//返回值：无
void ClientSocket::dealMsg(QDataStream &in)
{
    int id;
    QString message;
    in >> id;
    in >> message;
    emit toMsg(id,message);
    updatetimer.start(UPDATETIME);
}

//向客户端发送消息
//描述：向客户端发送对应消息
//参数：消息字符串
//返回值：无
void ClientSocket::sendMsg(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    nextBlockSize = 0;
    out << quint16(0) << quint8('M');
    out << msg;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
    out << quint16(0xFFFF);
}

//删除连接
//描述：客户端连接断开，更新大厅信息，同时发送大厅更新数据
//参数：无
//返回值：无
void ClientSocket::deleteConnect()
{
    if(-1 != desknum)
    {
        player[desknum].id = 0;
        player[desknum].name = "";
        player[desknum].score = 0;
        this->dealHall();
    }
}
    

//转发消息处理
//描述：检查转发消息是否是给当前客户端，是则发送给客户端，否则不做处理
//参数：用户id，消息字符串
//返回值：无
void ClientSocket::toMessage(int id, QString msg)
{
    if(id == this->uid)
    {
        this->sendMsg(msg);
    }
}
