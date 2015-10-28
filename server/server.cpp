//服务器主线程类实现
//说明：当主线程接收到线程的转发消息信号后会发送处理转发消息信号，该信号绑定到各个线程的处理转发消息信号
//那么转发消息的具体处理由各个线程处理，主线程只是作为信号的中继，使各个线程都能收到该信号以便做出响应。
#include <QtDebug>
#include "server.h"
//#include <stdlib.h>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

//当有客户端连接时调用该函数
//描述：增加在线人数，创建新线程处理该客户端的请求，启动线程
//参数：客户端连接的套接字描述符
//返回值：无
void Server::incomingConnection(int socketDescriptor)
{
    onlineNum++;
    Thread *thread = new Thread(socketDescriptor, this);
    //连接线程的转发消息信号与主线程的处理转发消息信号
    connect(thread,SIGNAL(toMsg(int,QString)),this,SIGNAL(dealMessage(int,QString)));
    //连接主线程的处理转发信息信号与线程的处理转发消息信号
    connect(this,SIGNAL(dealMessage(int,QString)),thread,SIGNAL(dealMsg(int,QString)));
    //连接线程结束信号与结束处理函数
    connect((thread), SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), this, SLOT(discon()));
    //启动线程
    thread->start();
}

//当线程结束时调用该函数
//描述：减少在线人数
//参数：无
//返回值：无
void Server::discon()
{
    onlineNum--;
	qDebug() << "disconnect";
}
