//子线程类

#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(int socketDescriptor,  QObject *parent);
    void run();

private:
    quint16 nextBlockSize;
    int socketDescriptor;

private slots:
    //void setUid(int);

signals:
    //转发消息信号，当有客户端需要转发消息时发出
    void toMsg(int,QString);
    //处理转发消息信号，当收到主线程的处理转发消息信号时发出
    void dealMsg(int,QString);
};

#endif // THREAD_H
