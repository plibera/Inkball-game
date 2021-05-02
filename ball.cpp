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

    qreal dist = speed/FPS;
    QPointF futurePos(x()+dist*stepX, y()+dist*stepY);
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
    futurePos.setX(x()+dist*stepX);
    futurePos.setY(y()+dist*stepY);
    for(Segment* segment : inkBallScene->segments)
    {
        if(segment->getColor() != segmentColor)
            continue;
        int direction = int(round(segment->getSegment().angle()/45))%4;
        if(direction%2 == 0)
        {
            QLineF testLine(QPointF(futurePos.x(), futurePos.y()-BALL_D/2), QPointF(futurePos.x(), futurePos.y()+BALL_D/2));
            QLineF testLine2(QPointF(futurePos.x()-BALL_D/2, futurePos.y()), QPointF(futurePos.x()+BALL_D/2, futurePos.y()));
            QLineF::IntersectionType type = testLine.intersects(segment->getSegment(), nullptr);
            QLineF::IntersectionType type2 = testLine2.intersects(segment->getSegment(), nullptr);
            if(type == QLineF::BoundedIntersection || type2 == QLineF::BoundedIntersection)
            {
                setAngle(angle+M_PI);
                inkBallScene->removeItem(segment);
                inkBallScene->segments.removeOne(segment);
                delete segment;
                inkBallScene->update();
                break;
            }
        }
        else
        {
            qreal offset = BALL_D/(2*sqrt(2));
            QLineF testLine(QPointF(futurePos.x()-offset, futurePos.y()-offset), QPointF(futurePos.x()+offset, futurePos.y()+offset));
            QLineF testLine2(QPointF(futurePos.x()-offset, futurePos.y()+offset), QPointF(futurePos.x()+offset, futurePos.y()-offset));
            QLineF::IntersectionType type = testLine.intersects(segment->getSegment(), nullptr);
            QLineF::IntersectionType type2 = testLine2.intersects(segment->getSegment(), nullptr);
            if(type == QLineF::BoundedIntersection || type2 == QLineF::BoundedIntersection)
            {
                if((direction == 1 && stepY == 0) || (direction == 3 && stepX == 0))
                    setAngle(angle-M_PI/2);
                else
                    setAngle(angle+M_PI/2);
                inkBallScene->removeItem(segment);
                inkBallScene->segments.removeOne(segment);
                delete segment;
                inkBallScene->update();
                break;
            }
        }
    }
    setPos(QPointF(x() + dist*stepX, y() + dist*stepY));
    for(Goal* goal : inkBallScene->goals)
    {
        QLineF testLine(goal->pos(), pos());
        if(testLine.length() < BALL_D)
        {
            inkBallScene->removeItem(this);
            inkBallScene->balls.removeOne(this);
            inkBallScene->update();
            delete this;
        }
    }
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
