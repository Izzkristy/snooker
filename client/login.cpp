#include "login.h"
#include "global.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QtNetwork>
#include <QDataStream>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //this->connect(ui->login,SIGNAL(clicked()),this,SLOT(checkLogin()));
    this->connect(ui->login,SIGNAL(clicked()),(QObject*)&serverConnect,SLOT(connectToServer()));
    this->connect((QObject*)&serverConnect,SIGNAL(connectOK()),this,SLOT(sendLogin()));
    this->connect((QObject*)&serverConnect,SIGNAL(recevLogin()),this,SLOT(checkLogin()));

}

Login::~Login()
{
    delete ui;
}

void Login::sendLogin()
{
    if((NULL == ui->user->text()) || (NULL == ui->password->text()))
    {
        QMessageBox::critical(NULL,tr("error"),tr("用户名或密码为空"),QMessageBox::Yes);
        return;
    }
    G_name = ui->user->text();
    G_password = ui->password->text();
    serverConnect.sendRequest('L');
    ui->statusLabel->setText(tr("正在连接服务器"));
}

void Login::checkLogin()
{
    if(G_id)
    {
        emit loginsuccess();
        this->close();
    }
    else
    {
        QMessageBox::critical(NULL,tr("error"),tr("用户名或密码错误！"),QMessageBox::Yes);
        serverConnect.closeConnect();
        ui->statusLabel->setText(tr(""));
    }
}

