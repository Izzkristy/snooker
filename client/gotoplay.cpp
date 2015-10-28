#include "gotoplay.h"
#include "ui_gotoplay.h"
#include "ball.h"
#include "Typedefine.h"
#include "mainwindow.h"
#include <QWidget>
#include <QMouseEvent>
#include "qmath.h"
#include <QTimer>
#include <QCursor>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QMessageBox>
#include <QDateTime>
#include <QTime>
#include <global.h>
#include <QStringList>
Gotoplay::Gotoplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gotoplay)
{
    ui->setupUi(this);
    ui->powerSetted->setRange(0,10);
    this->setPlayerInfo();
    ui->startPutton->setEnabled(false);
    ui->powerSetted->setEnabled(false);
    this->isOnPlay = false;
    power = 0;
    this->myTurn = false;
    this->ballToHit = 0;
    timer = new QTimer();
    colock = new QTimer();
    colock->start(1000);
    time.start(); //开始计时，以ms为单位
    this->connect(timer,SIGNAL(timeout()),this,SLOT(ballMovingTillStay()));
    this->connect(colock,SIGNAL(timeout()),this,SLOT(updateTime()));
    this->connect(ui->Restart,SIGNAL(clicked()),this,SLOT(on_Restart_clicked()));
    this->connect(ui->Send,SIGNAL(clicked()),this,SLOT(sendMessage()));
    this->connect(&serverConnect,SIGNAL(recevMsg(QString)),this,SLOT(recevMessage(QString)));
    this->connect(ui->startPutton,SIGNAL(clicked()),this,SLOT(startPlay()));
    initializeball();
    initializeballPosition();
}

Gotoplay::~Gotoplay()
{
    delete ui;
}

//initialize the ball.
void Gotoplay::initializeball()
{
    for(int i=0;i<22;i++)
    {
        ball[i] = new Ball(this);
        ball[i]->show();
    }

    for(int i=1;i<16;i++)
    {
        ball[i]->setballAttribute(RED);
    }

    for(int i=16;i<22;i++)
    {
        ball[i]->setballAttribute(OTHER);
    }

    //set the ball's name.
    ball[0]->setObjectName("white");
    //set the ball's background pic.
    ball[0]->setStyleSheet("border-image: url(:/Images/Images/0.png);");
    //set the ball's score.
    ball[0]->setballScore(0);
    //set the white's attribute.
    ball[0]->setballAttribute(WHITE);

    ball[1]->setObjectName("red_1");
    ball[1]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[1]->setballScore(1);

    ball[2]->setObjectName("red_2");
    ball[2]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[2]->setballScore(1);

    ball[3]->setObjectName("red_3");
    ball[3]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[3]->setballScore(1);

    ball[4]->setObjectName("red_4");
    ball[4]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[4]->setballScore(1);

    ball[5]->setObjectName("red_5");
    ball[5]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[5]->setballScore(1);

    ball[6]->setObjectName("red_6");
    ball[6]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[6]->setballScore(1);

    ball[7]->setObjectName("red_7");
    ball[7]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[7]->setballScore(1);

    ball[8]->setObjectName("red_8");
    ball[8]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[8]->setballScore(1);

    ball[9]->setObjectName("red_9");
    ball[9]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[9]->setballScore(1);

    ball[10]->setObjectName("red_10");
    ball[10]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[10]->setballScore(1);

    ball[11]->setObjectName("red_11");
    ball[11]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[11]->setballScore(1);

    ball[12]->setObjectName("red_12");
    ball[12]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[12]->setballScore(1);

    ball[13]->setObjectName("red_13");
    ball[13]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[13]->setballScore(1);

    ball[14]->setObjectName("red_14");
    ball[14]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[14]->setballScore(1);

    ball[15]->setObjectName("red_15");
    ball[15]->setStyleSheet("border-image: url(:/Images/Images/1.png);");
    ball[15]->setballScore(1);

    ball[16]->setObjectName("yellow");
    ball[16]->setStyleSheet("border-image: url(:/Images/Images/2.png);");
    ball[16]->setballScore(2);

    ball[17]->setObjectName("green");
    ball[17]->setStyleSheet("border-image: url(:/Images/Images/3.png);");
    ball[17]->setballScore(3);

    ball[18]->setObjectName("brown");
    ball[18]->setStyleSheet("border-image: url(:/Images/Images/4.png);");
    ball[18]->setballScore(4);

    ball[19]->setObjectName("blue");
    ball[19]->setStyleSheet("border-image: url(:/Images/Images/5.png);");
    ball[19]->setballScore(5);

    ball[20]->setObjectName("pink");
    ball[20]->setStyleSheet("border-image: url(:/Images/Images/6.png);");
    ball[20]->setballScore(6);

    ball[21]->setObjectName("black");
    ball[21]->setStyleSheet("border-image: url(:/Images/Images/7.png);");
    ball[21]->setballScore(7);
}

//initialize the ball's position.
void Gotoplay::initializeballPosition()
{

    ball[0]->setGeometry(250,200,27,27);
    ball[1]->setGeometry(720,270,27,27);
    ball[2]->setGeometry(742,258,27,27);
    ball[3]->setGeometry(742,282,27,27);
    ball[4]->setGeometry(765,248,27,27);
    ball[5]->setGeometry(765,272,27,27);
    ball[6]->setGeometry(765,296,27,27);
    ball[7]->setGeometry(786,235,27,27);
    ball[8]->setGeometry(786,260,27,27);
    ball[9]->setGeometry(786,285,27,27);
    ball[10]->setGeometry(786,310,27,27);
    ball[11]->setGeometry(808,221,27,27);
    ball[12]->setGeometry(808,248,27,27);
    ball[13]->setGeometry(808,273,27,27);
    ball[14]->setGeometry(808,298,27,27);
    ball[15]->setGeometry(808,322,27,27);
    //依次为 2、3、4、5、6、7分球。
    ball[16]->setGeometry(210,200,27,27);
    //ball[16]->show();
    ball[17]->setGeometry(210,340,27,27);
    ball[18]->setGeometry(210,270,27,27);
    ball[19]->setGeometry(470,270,27,27);
    ball[20]->setGeometry(690,270,27,27);
    ball[21]->setGeometry(860,270,27,27);
    //设置球心坐标
    for(int i = 0;i<22;i++)
    {
        ball[i]->px = ball[i]->x()+13.5;
        ball[i]->py = ball[i]->y()+13.5;
    }
}

void Gotoplay::mousePressEvent(QMouseEvent *event)
{
    ballInHoleNums.clear();
    indexFirstCollisionBall = 0;
    if(event->button() == Qt::LeftButton)
    {
        if(this->myTurn)
        {
            if(power<=0)
            {
                int cur_x = event->x();
                int cur_y = event->y();
                float tmp1 = cur_y-ball[0]->py;
                float tmp2 = sqrt((cur_y-ball[0]->py)*(cur_y-ball[0]->py)+
                                   (cur_x-ball[0]->px)*(cur_x-ball[0]->px));
                float tmp3 = tmp1/tmp2;
                ball[0]->angle = qAsin(tmp3);

                stickPower = ui->powerSetted->value();
                if(cur_x<ball[0]->px)
                    ball[0]->vx = -stickPower*cos(ball[0]->angle);
                else
                    ball[0]->vx = stickPower*cos(ball[0]->angle);
                ball[0]->vy = stickPower*sin(ball[0]->angle);
                //发送击球信息
                this->sendHitBallInfo(cur_x,cur_y,stickPower);

                this->play();
                timer->start(10);
            }
            else
            {
                QCursor *myCursor=new QCursor(QPixmap(":/Images/Images/cursor.png"),-1,-1);
                setCursor(*myCursor);
            }
        }
        else
        {
            QCursor *myCursor=new QCursor(QPixmap(":/Images/Images/cursor.png"),-1,-1);
            setCursor(*myCursor);
        }

    }
}


void Gotoplay::mouseMoveEvent(QMouseEvent *)
{
;
}

void Gotoplay::play()
{
    ball[0]->px = ball[0]->px + ball[0]->vx;
    ball[0]->py = ball[0]->py + ball[0]->vy;
    power = ball[0]->vx * ball[0]->vx + ball[0]->vy * ball[0]->vy;
}

void Gotoplay::ballMovingTillStay()
{
    //if the whole power is zero,which means all the balls stop moving,
    //then stop the timer.
    if(power<=0)
    {
        timer->stop();
        this->computeScore();
    }
    ballGo();
    ballInhole();
    ballCollide();
    balldecay();

}

void Gotoplay::ballGo()
{
    for(int i=0;i<22;i++)
    {
        double multx = 0.6;//速度系数
        double x = ball[i]->vx+ball[i]->px-13.5;
        double y = ball[i]->vy+ball[i]->py-13.5;
        ball[i]->px = multx*ball[i]->vx+ball[i]->px;
        ball[i]->py = multx*ball[i]->vy+ball[i]->py;
        ball[i]->setGeometry(x,y,27,27);
    }
}

/*******************************************
hide the ball.
the hole's location:
(40,60)(484.5,40)(929,60)
(40,500)(484.5,520)(929,500)
*******************************************/
void Gotoplay::ballInhole()
{
    double r1 = 28;//the hole's r plus the ball's r.
    for(int i = 0;i<22;i++)
    {
        int x = ball[i]->px;
        int y = ball[i]->py;
        if((x-40)*(x-40)+(y-60)*(y-60)<=r1*r1
        ||(473<=x&&x<=494&&y<=73.5)
        ||(x-929)*(x-929)+(y-60)*(y-60)<=r1*r1
        ||(x-40)*(x-40)+(y-500)*(y-500)<=r1*r1
        ||(473<=x&&x<=494&&y>=486.5)
        ||(x-929)*(x-929)+(y-500)*(y-500)<=r1*r1)
        {
            ballInHoleNums.append(i);
            ball[i]->clear();
            if(i == 0)
            {
                ball[0]->setGeometry(200,290,27,27);
                ball[0]->show();
                ball[0]->px = ball[0]->x()+13.5;
                ball[0]->py = ball[0]->y()+13.5;
                ball[0]->vx = 0;
                ball[0]->vy = 0;
                ball[0]->show();
                break;
            }

        }
    }
}

/****************************************************
detect the ball's collide.ball&edge , ball&ball
****************************************************/
void Gotoplay::ballCollide()
{
    for (int i=0; i<22;i++)
    {
        lineCollision(ball[i]);//detect the collision between the ball and the edge.
    }

    //detect the collision between two balls.
    for (int i=0; i<22; i++)
    {
        for (int j=i+1; j<22; j++)
        {
            if((ball[i]->px - ball[j]->px)*(ball[i]->px - ball[j]->px)
               + (ball[i]->py - ball[j]->py)*(ball[i]->py - ball[j]->py) <= 25.0*25.0)
            {
                if(indexFirstCollisionBall == 0)
                {
                    if(i != 0)
                    {
                        ballInHoleNums.append(i);
                        indexFirstCollisionBall++;
                    }
                    if(j != 0)
                    {
                        ballInHoleNums.append(j);
                        indexFirstCollisionBall++;
                    }
                }

                Rebound(ball[i], ball[j]);
            }
        }
    }
}

void Gotoplay::lineCollision(Ball *a)
{
    if(a->px-13.5<40||a->px+13.5>929)
        a->vx = -a->vx;
    else if(a->py-13.5<60||a->py+13.5>500)
        a->vy = -a->vy;


}

void Gotoplay::Rebound(Ball *a, Ball *b)
{
    double cx = b->px - a->px;
    double cy = b->py - a->py;
    double tmpvx;
    double tmpvy;
    double tmppx;
    double tmppy;
    if ((a->vx - b->vx)*cx + (a->vy - b->vy)*cy>0)
    {
        tmppx = a->px - b->px;
        tmppy = a->py - b->py;
        tmpvx = ((a->vx-b->vx)*tmppx*tmppx+(a->vy-b->vy)*tmppx*tmppy)
                /(tmppx*tmppx+tmppy*tmppy);
        tmpvy = ((a->vy-b->vy)*tmppy*tmppy+(a->vx-b->vx)*tmppx*tmppy)
                /(tmppx*tmppx+tmppy*tmppy);

        a->vx = a->vx - tmpvx;
        a->vy = a->vy - tmpvy;
        b->vx = b->vx + tmpvx;
        b->vy = b->vy + tmpvy;
    }

}

/*******************************************
decay the ball's v
*******************************************/
void Gotoplay::balldecay()
{
    power = 0;
    for (int i=0; i<22; i++)
    {
        if (ball[i]->vx * ball[i]->vx + ball[i]->vy * ball[i]->vy <= 0.01)
        {

            ball[i]->vx = 0;
            ball[i]->vy = 0;
        }
        else
        {
            if(ball[i]->vx * ball[i]->vx + ball[i]->vy * ball[i]->vy <= 0.5)
            {
                ball[i]->vx = 0.99 * ball[i]->vx ;
                ball[i]->vy = 0.99 * ball[i]->vy ;
            }
            else
            {
                ball[i]->vx = 0.996 * ball[i]->vx ;
                ball[i]->vy = 0.996 * ball[i]->vy ;
            }
        }
    }

    for (int i=0; i<22; i++)
    {
        power =power + ball[i]->vx * ball[i]->vx + ball[i]->vy * ball[i]->vy ;
    }

    if(power<=0)
    {
        //this->computeScore();//调用计分函数score()/scoreOther;
        setCursor(Qt::ArrowCursor);
    }
}

void Gotoplay::on_Restart_clicked()
{
    if(power<=0)
    {
        initializeballPosition();
        for(int i=0;i<22;i++)
        {
            ball[i]->show();
        }
    }
    else
        QMessageBox::about(this,tr("Remind"),tr("Please wait until all the balls are stopped!"));

}
//Be to hit the red balls.
int Gotoplay::score()
{
    int firstBall = 0;
    int redBalls = 0;
    int other = 0;

    if(ballInHoleNums.size() == 0)//if no ball is moving
        return -4;

    if(ballInHoleNums[0] == 0)//if only the white ball in hole
        return -4;

    if(ballInHoleNums[0]>=1&&ballInHoleNums[0]<=15)
        firstBall = 1;
    else
        firstBall = -1;

    for(int i=1;i<ballInHoleNums.size();i++)
    {
        int j = ballInHoleNums[i];
        if(ball[j]->getballAttribute() == RED)
            redBalls++;
        else
            other = max(other,j);
    }

    if(firstBall == 1&& redBalls>=0 && other == 0)
        return redBalls;
    else
        return -ball[other]->getballScore();

}

int Gotoplay::scoreOther()
{
    int firstBall = 0;
    int other = 0;
    bool isTheSameOtherBall = false;

    if(ballInHoleNums.size() == 0)//if no ball is moving except the white one.
        return -4;

    if(ballInHoleNums[0] == 0)//if only the white ball in hole
        return -4;

    if(ballInHoleNums[0]>=16&&ballInHoleNums[0]<=21)
        firstBall = 1;
    else
        firstBall = -1;

    for(int i=1;i<ballInHoleNums.size();i++)
    {
        int j = ballInHoleNums[i];
        if(j == ballInHoleNums[0])//the first moving ball except the white one == the ball in hole
            isTheSameOtherBall = true;
        else
            other = max(other,j);
    }

    if(firstBall == 1 && isTheSameOtherBall && other == 0)
        return ball[ballInHoleNums[0]]->getballScore();
    else
        return -max(ball[ballInHoleNums[0]]->getballScore(),
                    ball[other]->getballScore());

}
//only Other balls on the desk.
int Gotoplay::scoreRedOver()
{
    ;
}

int Gotoplay::max(int i, int j)
{
    if(i>=j)
        return i;
    else
        return j;
}


//server passes the parameters.(x,y)->the cursor's location. strength->the stickPower.
void Gotoplay::rival_do(double x, double y, int strength)
{
    float tmp1 = y-ball[0]->py;
    float tmp2 = sqrt((y-ball[0]->py)*(y-ball[0]->py)+
                       (x-ball[0]->px)*(x-ball[0]->px));
    float tmp3 = tmp1/tmp2;
    ball[0]->angle = qAsin(tmp3);

    stickPower = strength;
    if(x<ball[0]->px)
        ball[0]->vx = -stickPower*cos(ball[0]->angle);
    else
        ball[0]->vx = stickPower*cos(ball[0]->angle);
    ball[0]->vy = stickPower*sin(ball[0]->angle);
    play();
    timer->start(10);
}

void Gotoplay::updateTime()
{
    QDateTime time = QDateTime::currentDateTime();//get the system's time.
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");//set the formation of the time.
    ui->time->setText("Time:  "+strTime);


    int time_Diff = this->time.elapsed();
    int tmpsec = time_Diff/1000;
    int tmpmin = tmpsec/60;
    int tmphour = tmpmin/60;
    int hour = tmphour%60;
    int min = tmpmin%60;
    int sec = tmpsec%60;

    QString strSec = QString("%1").arg(sec);
    QString strMin = QString("%1").arg(min);
    QString strHour = QString("%1").arg(hour);

    ui->lastTime->setText("You have played:  "+strHour+" : "+strMin+" : "+strSec);
}

//设置玩家即对手个人信息
void Gotoplay::setPlayerInfo()
{
    //玩家在右边
    if(G_playNo%2)
    {
        fightPlayer = G_playNo - 1;
        ui->rightPlayer->setText(G_name);
        ui->rplayer->setText(G_name + ": ");
        ui->leftPlayer->setText(player[fightPlayer].name);
        if(player[fightPlayer].id)
        {
            ui->lplayer->setText(player[fightPlayer].name + ": ");
            ui->Send->setEnabled(true);
            ui->startPutton->setEnabled(true);
            //ui->powerSetted->setEnabled(true);
        }
        else
        {
            ui->lplayer->setText(player[fightPlayer].name);
            ui->Send->setEnabled(false);
            ui->startPutton->setEnabled(false);
        }
    }
    //玩家在左边
    else
    {
        fightPlayer = G_playNo + 1;
        ui->leftPlayer->setText(G_name);
        ui->lplayer->setText(G_name + ": ");
        ui->rightPlayer->setText(player[fightPlayer].name);
        if(player[fightPlayer].id)
        {
            ui->rplayer->setText(player[fightPlayer].name + ": ");
            ui->Send->setEnabled(true);
            if(false == isOnPlay)
            {
                ui->startPutton->setText(tr("等待开始"));
            }
            //ui->startPutton->setEnabled(true);
            //ui->powerSetted->setEnabled(true);
        }
        else
        {
            ui->rplayer->setText(player[fightPlayer].name);
            ui->startPutton->setText(tr("等待对手"));
            ui->Send->setEnabled(false);
        }
    }
}

//发送聊天信息
void Gotoplay::sendMessage()
{
    QDateTime time = QDateTime::currentDateTime();//get the system's time.
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss");
    QString message = ui->msglineEdit->text();
    QString msg;
    if(!message.isEmpty())
    {
        msg =  "<font color='blue'>" + G_name + " " + strTime + "</font><br> " + message;
        message = " " + message;
        ui->textBrowser->append(msg);
        ui->msglineEdit->clear();
        serverConnect.sendRequest('M',player[fightPlayer].id,message);
    }
}

//接收消息
void Gotoplay::recevMessage(QString message)
{
    //开始信息
    if(message.startsWith('s'))
    {
        isOnPlay = true;
        ui->startPutton->setText(tr("playing"));
        ui->powerSetted->setEnabled(true);
    }
    //聊天消息
    else if(message.startsWith(' '))
    {
        QDateTime time = QDateTime::currentDateTime();//get the system's time.
        QString strTime = time.toString("yyyy-MM-dd hh:mm:ss");
        QString msg =  "<font color='green'>" + player[fightPlayer].name + " " + strTime + "</font><br>" + message;
        ui->textBrowser->append(msg);
    }
    else
    {
        double x;
        double y;
        int strength;
        QStringList msgList = message.split(',');
        x = msgList.at(0).toDouble();
        y = msgList.at(1).toDouble();
        strength = msgList.at(2).toInt();
        this->rival_do(x,y,strength);
    }
}

//开始游戏
void Gotoplay::startPlay()
{
    isOnPlay = true;
    ui->startPutton->setText(tr("playing"));
    ui->startPutton->setEnabled(false);
    ui->powerSetted->setEnabled(true);
    QString message = "s";
    serverConnect.sendRequest('M',player[fightPlayer].id,message);
    this->myTurn = true;
}

void Gotoplay::sendHitBallInfo(double x, double y, int strength)
{
    QString message;
    message = QString::number(x) + "," + QString::number(y) + "," + QString::number(strength);
    serverConnect.sendRequest('M',player[fightPlayer].id,message);
}

void Gotoplay::computeScore()
{
    int score = 0;
    qDebug() << myTurn;
    if(0 == ballToHit)
    {
        score = -1;//this->score();
        if(score <= 0)
        {
            this->myTurn = !(this->myTurn);
        }
        else
        {
            ballToHit = 1;
        }
    }
    else if(1 == ballToHit)
    {
        score = this->scoreOther();
        if(score <= 0)
        {
            this->myTurn = !(this->myTurn);
        }
        else
        {
            ballToHit = 0;
        }
    }
    qDebug() << myTurn;
    qDebug() << score;
}









