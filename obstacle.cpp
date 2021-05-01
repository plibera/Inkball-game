#include "obstacle.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>


Obstacle::Obstacle()
{

}

QRectF Obstacle::boundingRect() const
{
    return QRectF(-OBS_W/2, -OBS_H/2, OBS_W, OBS_H);
}


QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(obstacleOutlineColor);
    painter->drawRect(boundingRect());
    painter->setBrush(obstacleColor);
    painter->drawRect(QRectF(-OBS_W*0.4, -OBS_H*0.4, 0.8*OBS_W, 0.8*OBS_H));
}
