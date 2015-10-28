#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gotoplay.h"
#include "global.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QtNetwork>
#include <QDataStream>
#include <QDebug>
#include <QLabel>
struct Player player[PLAYERNUM];
int G_id = 0;
QString G_name = "";
int G_score = 0;
QString G_password = "";
int G_onlineNum = 0;
int G_playNo = -1;
connectServer serverConnect;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dlg = NULL;
    this->resetGlobal();
    this->connect(&serverConnect,SIGNAL(recevHall()),this,SLOT(setHallInfo()));
    this->connect(&serverConnect,SIGNAL(recevPlay(quint8)),this,SLOT(startPlay(quint8)));
    //this->connect(&updatetimer,SIGNAL(timeout()),this,SLOT(updateHall()));
//    QLabel* tmp = new QLabel(this);
//    tmp->setGeometry(50,50,30,30);
//    tmp->setText(tr("sdk;lasdfg"));
//    tmp->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Location1_clicked()
{
    if(-1 != G_playNo)
    {
        QMessageBox::critical(NULL,tr("error"),tr("已进入游戏！"),QMessageBox::Yes);
        return;
    }
    G_playNo = 0;
    serverConnect.sendRequest('P',G_playNo);
}

void MainWindow::on_Location2_clicked()
{
    if(-1 != G_playNo)
    {
        QMessageBox::critical(NULL,tr("error"),tr("已进入游戏！"),QMessageBox::Yes);
        return;
    }
    G_playNo = 1;
    serverConnect.sendRequest('P',G_playNo);
}

void MainWindow::on_Location3_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location4_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location5_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location6_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location7_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location8_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location9_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location10_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location11_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location12_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location13_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location14_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location15_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location16_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location17_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_Location18_clicked()
{
    Gotoplay *dlg = new Gotoplay(this);
    dlg->show();
}

void MainWindow::on_action_triggered()
{
    QString s = "<h2>Dear: "
            + G_name +
            "</h2><p>You have scored "
            + QString::number(G_score) +
            " now!</p>" +
            "<p>Congratulations!</p>";
    QByteArray ba = s.toLatin1();
    char *ch=ba.data();
    QMessageBox::about(this,tr("User Info"),
                       tr(ch));
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::about(this,tr("About Snooker"),
                       tr("<h2>Game Snooker</h2>"
                          "<p>Thank you for using our snooker!</p>"
                          "<p>This game is maded by tow man in SiChuan University, "
                          "and this is our graduation project. Have fun</p>"));
}

void MainWindow::hallshow()
{
    this->show();
    serverConnect.sendRequest('H');
    //updatetimer.start(1000);
}

void MainWindow::setHallInfo()
{
    ui->onlinenum->setText(QString::number(G_onlineNum));
    this->setDesk();
}

void MainWindow::setDesk()
{
    if(player[0].id)
    {
        ui->luser_1->setText(player[0].name);
    }
    else
    {
        ui->luser_1->setText("");
        //ui->status_1->setText(tr("空闲"));
    }
    if(player[1].id)
    {
        ui->ruser_1->setText(player[1].name);
    }
    else
    {
        ui->ruser_1->setText("");
        //ui->status_1->setText(tr("空闲"));
    }
    if(this->dlg)
    {
        this->dlg->setPlayerInfo();
    }
}

void MainWindow::resetGlobal()
{
    G_id = 0;
    G_name = "";
    G_score = 0;
    G_password = "";
    G_onlineNum = 0;
    G_playNo = -1;
    for(int i=0;i<PLAYERNUM;i++)
    {
        player[i].id = 0;
        player[i].name = "";
        player[i].score = 0;
    }
}

void MainWindow::startPlay(quint8 result)
{
    if(result)
    {
        if(this->dlg)
        {
            delete this->dlg;
            this->dlg = NULL;
        }
        this->dlg = new Gotoplay(this);
        this->connect(dlg,SIGNAL(rejected()),this,SLOT(quitPlay()));
        this->dlg->show();
    }
    else
    {
        G_playNo = -1;
        QMessageBox::critical(NULL,tr("error"),tr("被人抢先了！"),QMessageBox::Yes);
    }
    serverConnect.sendRequest('H');
}

void MainWindow::quitPlay()
{
    if(this->dlg)
    {
        delete this->dlg;
        this->dlg = NULL;
    }
    int tmp = G_playNo;
    G_playNo = -1;
    serverConnect.sendRequest('Q',tmp);
}

void MainWindow::updateHall()
{
    serverConnect.sendRequest('H');
}
