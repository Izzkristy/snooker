//子线程类实现
#include <QtDebug>
#include <QtGui>
#include <QSqlQuery>
#include "thread.h"
#include "clientsocket.h"

#include <QtNetwork>

Thread::Thread(int socketDescriptor,QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void Thread::run()
{
    //新建客户端连接套接字
    ClientSocket socket;
    //设置套接字描述符
    socket.setSocketDescriptor(socketDescriptor);

    //当客户端连接断开时，线程结束
    this->connect(&socket, SIGNAL(disconnected()), this, SLOT(quit()));
    //当客户端需要转发消息时线程发出转发消息信号
    this->connect(&socket,SIGNAL(toMsg(int,QString)),this,SIGNAL(toMsg(int,QString)));
    //当线程需要处理转发消息时，客户端连接处理具体转发过程
    this->connect(this,SIGNAL(dealMsg(int,QString)),&socket,SLOT(toMessage(int,QString)));
	exec();
}
