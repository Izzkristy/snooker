#include "ball.h"

Ball::Ball(QWidget *parent) :
    QLabel(parent)
{
    this->vx = 0;
    this->vy = 0;
    this->angle = 0;
    this->setballScore(0);

}

void Ball::setballScore(int i)
{
    this->ballScore = i;
}

int Ball::getballScore()
{
    return this->ballScore;
}

void Ball::setballAttribute(attribute i)
{
    this->ballAttribute = i;
}

attribute Ball::getballAttribute()
{
    return this->ballAttribute;
}

void Ball::show()
{
    this->setVisible(true);
}

void Ball::clear()
{
    this->setVisible(false);
    this->setGeometry(0,0,0,0);
    this->px = 0;
    this->py = 0;
    this->vx = 0;
    this->vy = 0;
}

void Ball::setballPos(double px, double py)
{
    this->px = px;
    this->py = py;
    this->setGeometry(this->px-13.5,this->py-13.5,27,27);
}

void Ball::setballVel(double vx, double vy)
{
    this->vx = vx;
    this->vy = vy;
}










