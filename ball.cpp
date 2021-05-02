#include "ball.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

#include <iostream>

using namespace std;

Ball::Ball(InkBallScene* inkBallScene, QColor color, qreal direction, qreal speed)
    : inkBallScene(inkBallScene), angle(direction), speed(speed), color(color)
{
    inkBallScene->addItem(this);
    setAngle(angle);
}


QRectF Ball::boundingRect() const
{
    return QRectF(-BALL_D/2, -BALL_D/2, BALL_D, BALL_D);
}


QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawEllipse(boundingRect());
}

void Ball::advance(int step)
{
    if (!step)
        return;

    QPointF futurePos(x()+speed*stepX, y()+speed*stepY);
    for(Obstacle* obstacle : inkBallScene->obstacles)
    {
        QPointF tl = obstacle->mapToScene(obstacle->boundingRect().topLeft());
        tl.setX(tl.x()-BALL_D/2);
        tl.setY(tl.y()-BALL_D/2);
        QPointF br = obstacle->mapToScene(obstacle->boundingRect().bottomRight());
        br.setX(br.x()+BALL_D/2);
        br.setY(br.y()+BALL_D/2);
        QRectF r(tl, br);

        if(r.contains(futurePos))
        {
            setAngle(angle + M_PI);
            break;
        }
    }
    setPos(QPointF(x() + speed*stepX, y() + speed*stepY));
}

void Ball::setAngle(qreal angle)
{
    while(angle < 0)
        angle += 2*M_PI;
    while(angle >= 2*M_PI)
        angle -= 2*M_PI;
    this->angle = angle;
    if(angle < M_PI/4)
    {
        stepX = 1;
        stepY = 0;
    }
    else if(angle >= M_PI/4 && angle < 3*M_PI/4)
    {
        stepX = 0;
        stepY = 1;
    }
    else if(angle >= 3*M_PI/4 && angle < 5*M_PI/4)
    {
        stepX = -1;
        stepY = 0;
    }
    else
    {
        stepX = 0;
        stepY = -1;
    }
}
