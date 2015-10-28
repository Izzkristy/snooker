#ifndef BALL_H
#define BALL_H

#include <QLabel>
#include <QPoint>
#include "Typedefine.h"

/********************************************
  define the class of Ball.
  and some function about the ball.
  *******************************************/
class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = 0);
    double px;//ball's x pos
    double py;//ball's y pos
    double vx;//ball's x v
    double vy;//ball's y v
    float angle;//ball's running angle when the ball is running.

    void setballPos(double px,double py);//set ball's pos.
    void setballVel(double vx,double vy);//set ball's velocity.

    void setballScore(int i);
    int getballScore();

    void setballAttribute(attribute i);
    attribute getballAttribute();

    void clear();//make the ball disappear.
    void show();//show the ball on the desk.

private:
    int ballScore;//the ball's scores
    attribute ballAttribute;// RED means it's a red ball,WHITE represents white ball,OTHER means colorful ball


signals:
    
public slots:
    
};

#endif // BALL_H
