#include "ball.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

Ball::Ball(QColor color, qreal direction)
    : angle(direction), color(color)
{}


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
    setPos(x()+1, y());
}
