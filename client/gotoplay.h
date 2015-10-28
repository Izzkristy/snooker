#ifndef GOTOPLAY_H
#define GOTOPLAY_H

#include <QDialog>
#include "ball.h"
#include <QTimer>
#include <QTime>
#include <QVector>
/************************************************************
  the main play area.
  contains ball initialize,ball collision and so on
  ***********************************************************/

namespace Ui {
class Gotoplay;
}

class Gotoplay : public QDialog
{
    Q_OBJECT
    
public:
    explicit Gotoplay(QWidget *parent = 0);
    ~Gotoplay();
    Ball *ball[22];
    QVector<int> ballInHoleNums;
    int indexFirstCollisionBall;
    int stickPower;//the power stick giving the white ball.
    double power;//all the power,to confirm that all the ball are not moving.
    QTimer *timer;
    QTimer *colock;
    QTime time;
    void initializeball();
    void initializeballPosition();//initialize the balls' position.
    void play();//time slice the ball's move, including ball-in-hole,ball collision.
    void ballCollide();//Every time click on the desk,the function run,about the collision.
    void lineCollision(Ball *a);
    void Rebound(Ball *a,Ball *b);
    void ballInhole();//judge if the ball is in hole or not.
    void balldecay();//decay the ball's speed.
    void ballGo();

    int score();//do not hit red in.
    int scoreOther();// do hit red in.
    int scoreRedOver();
    int max(int i,int j);

    void rival_do(double x,double y,int strength);//the rival's play.
    void setPlayerInfo();



protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);


private:
    Ui::Gotoplay *ui;
    int fightPlayer;//对手编号
    bool isOnPlay;//是否已开始游戏
    bool myTurn;
    int ballToHit;
    //发送击球信息
    void sendHitBallInfo(double x,double y,int strength);
    //计算积分
    void computeScore();


protected slots:
        void ballMovingTillStay();
        void on_Restart_clicked();
        void updateTime();
        void sendMessage();
        void recevMessage(QString);
        void startPlay();
};

#endif // GOTOPLAY_H
