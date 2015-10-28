//与服务器通信类定义
#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QTcpSocket>

class connectServer : public QObject
{
    Q_OBJECT

public:
    //构造函数
    connectServer(QObject *parent = 0);
    //向服务器发送数据请求
    void sendRequest(quint8 requestType,int num = -1,QString message = "");

public slots:
    //连接服务器
    void connectToServer();
    //关闭连接
    void closeConnect();

signals:
    //连接服务器成功信号
    void connectOK();
    void recevLogin();
    //接收到登陆返回信息信号
    void recevHall();
    //接收到游戏返回信息信号
    void recevPlay(quint8);
    //接收到转发消息信号
    void recevMsg(QString);

private slots:
    //连接错误处理
    void error();
    //建立连接处理
    void connected();
    //接收到数据处理
    void recevData();

private:
    //套接字
    QTcpSocket tcpSocket;
    int netBlockSize;
    //发送登陆信息
    void sendLogin();
    //处理登陆返回信息
    void loginRecev(QDataStream &in);
    //发送更新大厅信息请求
    void sendHall();
    //处理大厅更新请求返回信息
    void hallRecev(QDataStream &in);
    //发送进入游戏信息
    void sendPlay(int num);
    //处理进入游戏请求返回信息
    void playRecev(QDataStream &in);
    //发送退出游戏信息
    void sendQuit(int num);
    //发送消息转发信息
    void sendMsg(int num,QString message);
    //处理转发过来的消息
    void msgRecev(QDataStream &in);
};

#endif // CONNECTSERVER_H
