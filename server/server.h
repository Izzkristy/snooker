//服务器主线程类
#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include "thread.h"
#include "desk.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    //创建新线程,设置套接字描述符(有客户端连接时调用)
    void incomingConnection(int socketDescriptor);

protected slots:
    //减少在线人数(客户端连接断开时调用)
	void discon();

signals:
    //需要转发消息是发出
    void dealMessage(int,QString);

private:
    //Thread *thread[MAXTHREADNUM];
};

#endif // SERVER_H
