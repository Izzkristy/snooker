#include "connectServer.h"
#include "global.h"
#include <QHostAddress>
#include <QMessageBox>

//构造函数
connectServer::connectServer(QObject *parent)
    : QObject(parent)
{
    //套接字连接成功后调用connected函数
    this->connect(&tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    //传输过来的数据可读后调用recevData函数
    this->connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(recevData()));
    //套接字发生错误后调用error函数
    this->connect(&tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                  this,SLOT(error()));
}

//连接到服务器
//描述：连接到指定的服务器及端口
//参数：无
//返回值：无
void connectServer::connectToServer()
{
    tcpSocket.connectToHost(QHostAddress::LocalHost,7962);
    netBlockSize = 0;
}

//连接建立后发出连接成功的信号
void connectServer::connected()
{
    emit connectOK();
}

//向服务器发送请求
//描述：根据类型向调用函数向服务器发送请求
//'L' 登陆请求
//'H' 大厅信息更新请求
//'P' 进入游戏请求
//'Q' 退出游戏请求
//'M' 转发信息请求
//参数：requestType 请求类型,num 用户id，message 消息内容
//返回值：无
void connectServer::sendRequest(quint8 requestType,int num,QString message)
{
    switch(requestType)
    {
    case 'L':
        sendLogin();
        break;
    case 'H':
        sendHall();
        break;
    case 'P':
        sendPlay(num);
        break;
    case 'Q':
        sendQuit(num);
        break;
    case 'M':
        sendMsg(num,message);
        break;
    }
}
struct loginMsg
{
    int msgtype;
    int id;
    char name[20];
    char pwd[20];
};

//发送登陆信息
void connectServer::sendLogin()
{
    //QByteArray block;
    //QDataStream out(&block,QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_8);
    //out << quint16(0) << quint8('L') << G_name << G_password;
    //out.device()->seek(0);
    //out << quint16(block.size() - sizeof(quint16));
    struct loginMsg login;
    memset(&login,0x00,sizeof(login));
    login.msgtype = 0x01;
    login.id = 1;
    memcpy(login.name,"scuzz",5);
    memcpy(login.pwd,"123456",6);
    //login.name = "scuzz";
    //login.pwd = "123456";
    //out << loginMsg;
    tcpSocket.write((char *)(&login),sizeof(login));
}

//接收服务器发回的数据
void connectServer::recevData()
{
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);
    if (netBlockSize == 0)
    {
        if (tcpSocket.bytesAvailable() < sizeof(int))
            return;
        in >> netBlockSize;
    }

    if (tcpSocket.bytesAvailable() < netBlockSize)
        return;

    quint8 type;
    in >> type;
    switch(type)
    {
    case 'L':
        loginRecev(in);
        break;
    case 'H':
        hallRecev(in);
        break;
    case 'P':
        playRecev(in);
        break;
    case 'M':
        msgRecev(in);
        break;
    }
}

void connectServer::loginRecev(QDataStream &in)
{
    quint8 result;
    in >> result;
    if(result)
    {
        in >> G_id;
        in >> G_score;
    }
    netBlockSize = 0;
    emit recevLogin();
}

void connectServer::sendHall()
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << quint8('H');
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);
}

void connectServer::hallRecev(QDataStream &in)
{
    in >> G_onlineNum;
    for(int i=0;i<PLAYERNUM;i++)
    {
        in >> player[i].id;
        in >> player[i].name;
        in >> player[i].score;
    }
    netBlockSize = 0;
    emit recevHall();
}

void connectServer::sendPlay(int num)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << quint8('P') << num;
    out << G_id << G_name << G_score;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);
}

void connectServer::playRecev(QDataStream &in)
{
    quint8 result;
    in >> result;
    netBlockSize = 0;
    emit recevPlay(result);
}

void connectServer::sendQuit(int num)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << quint8('Q') << num;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);
}

void connectServer::sendMsg(int num, QString message)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << quint8('M') << num << message;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);
}

void connectServer::msgRecev(QDataStream &in)
{
    QString massage;
    in >> massage;
    netBlockSize = 0;
    emit recevMsg(massage);
}

void connectServer::error()
{
    QMessageBox::critical(NULL,tr("error"),tcpSocket.errorString(),QMessageBox::Yes);
}

void connectServer::closeConnect()
{
    tcpSocket.close();
}
