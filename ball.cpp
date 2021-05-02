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

    qreal distLeft = speed;
    while(distLeft > 0)
    {
        qreal minDist = 1e9;
        qreal bAngle = 1e9;
        qreal tempDist = 1e9;
        qreal tempAngle = 1e9;
        for(Obstacle* obstacle : inkBallScene->obstacles)
        {
            if(doesCollide(obstacle, tempDist, tempAngle) && tempDist < minDist)
            {
                minDist = tempDist;
                bAngle = tempAngle;
            }
        }

        if(distLeft <= minDist)
        {
            moveBy(distLeft);
            distLeft = 0;
        }
        else
        {
            moveBy(minDist);
            distLeft -= minDist;
            angle = bAngle;
        }
    }
}


bool Ball::doesCollide(Obstacle* obstacle, qreal &dist, qreal &bAngle)
{
    QRectF rect = obstacle->boundingRect();
    bool result = false;
    qreal tempDist = 1e9;
    qreal tempAngle = 1e9;
    qreal minDist = 1e9;
    qreal bestAngle = 0;
    if(doesCollide(QLineF(obstacle->mapToScene(rect.topLeft()), obstacle->mapToScene(rect.topRight())), tempDist, tempAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }
    if(doesCollide(QLineF(obstacle->mapToScene(rect.topRight()), obstacle->mapToScene(rect.bottomRight())), tempDist, tempAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }
    if(doesCollide(QLineF(obstacle->mapToScene(rect.bottomRight()), obstacle->mapToScene(rect.bottomLeft())), tempDist, tempAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }
    if(doesCollide(QLineF(obstacle->mapToScene(rect.bottomLeft()), obstacle->mapToScene(rect.topLeft())), tempDist, tempAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }
    dist = minDist;
    bAngle = bestAngle;
    return result;
}

bool Ball::doesCollide(QLineF segment, qreal &dist, qreal &bAngle)
{
    qreal tempDist = 0;
    qreal tempAngle = 0;
    QLineF longSegment(QPointF(segment.p1().x() - 1000*segment.dx(), segment.p1().y() - 1000*segment.dy()),
                       QPointF(segment.p2().x() + 1000*segment.dx(), segment.p2().y() + 1000*segment.dy()));

    if(!intersectsSegment(longSegment, tempDist, tempAngle) || tempDist < -EPSILON)
    {
        return false;
    }

    bool result = false;
    QLineF tempSegment(segment);
    qreal segmentAngle = segment.angle()*M_PI/180;
    qreal offsetAngle = segmentAngle + M_PI/2;
    QPointF offset(BALL_D/2 * cos(offsetAngle), BALL_D/2 * sin(offsetAngle));
    tempDist = 1e9;
    tempAngle = 1e9;
    qreal minDist = 1e9;
    qreal bestAngle = 0;

    tempSegment.translate(offset);
    if(intersectsSegment(tempSegment, tempDist, tempAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }

    tempSegment = segment;
    tempSegment.translate(-1*offset);
    if(intersectsSegment(tempSegment, tempDist, bestAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }

    /*if(doesCollide(segment.p1(), tempDist, bestAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }

    if(doesCollide(segment.p2(), tempDist, bestAngle) && tempDist < minDist)
    {
        result = true;
        minDist = tempDist;
        bestAngle = tempAngle;
    }*/

    dist = minDist;
    bAngle = bestAngle;
    return result;
}

bool Ball::doesCollide(QPointF point, qreal &dist, qreal &bAngle)
{
    qreal a = 1;
    qreal b = 2*(x()-point.x())*cos(angle) + 2*(y()-point.y())*sin(angle);
    qreal c = pow(x()-point.x(), 2) + pow(y()-point.y(), 2);
    qreal delta = b*b - 4*a*c;
    if(delta <= EPSILON)
        return false;
    qreal k = (-b * sqrt(delta))/2;
    if(k < -EPSILON)
        return false;
    dist = k;

    QPointF bouncePoint(x() + k*cos(angle), y() + k*sin(angle));
    QLineF bounceRadius(point, bouncePoint);
    bAngle = 2*bounceRadius.angle()*M_PI/180 - angle - M_PI;
    bAngle += 2*M_PI;
    while(bAngle >= 2*M_PI)
        bAngle -= 2*M_PI;
    return true;
}

bool Ball::intersectsSegment(QLineF segment, qreal &dist, qreal &bAngle)
{
    QPointF pv(x() + 1e6*cos(angle), y() + 1e6*sin(angle));
    QLineF ballVector(pos(), pv);
    QPointF intersection;
    QLineF::IntersectionType type = ballVector.intersects(segment, &intersection);
    if(type != QLineF::BoundedIntersection)
    {
        return false;
    }
    qreal k = 0;
    if(abs(cos(angle)) > EPSILON)
        k = (intersection.x() - x()) / cos(angle);
    else if(abs(sin(angle)) > EPSILON)
        k = (intersection.y() - y()) / sin(angle);
    else
    {
        return false;
    }

    dist = k;
    bAngle = 2*segment.angle()*M_PI/180 - angle;
    bAngle += 2*M_PI;
    while(bAngle >= 2*M_PI)
        bAngle -= 2*M_PI;
    return true;
}

void Ball::moveBy(qreal dist)
{
    setPos(x() + dist*cos(angle), y()+dist*sin(angle));
}
