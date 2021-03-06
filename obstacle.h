#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>

#include "constants.h"

class Obstacle : public QGraphicsItem
{
    qreal w;
    qreal h;
public:
    Obstacle(qreal width, qreal height);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
};

#endif // OBSTACLE_H
