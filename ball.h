#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>

#include "constants.h"
#include "inkballscene.h"

class InkBallScene;
class Obstacle;

class Ball : public QGraphicsItem
{
    InkBallScene* inkBallScene;
public:
    Ball(InkBallScene* scene, QColor color, qreal direction, qreal speed = 1);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

    bool doesCollide(Obstacle* obstacle, qreal &dist, qreal &bAngle);
    bool doesCollide(QLineF segment, qreal &dist, qreal &bAngle);
    bool doesCollide(QPointF point, qreal &dist, qreal &bAngle);
    bool intersectsSegment(QLineF segment, qreal &dist, qreal &bAngle);

protected:
    void advance(int step) override;

    void moveBy(qreal dist);

    qreal angle = 0;
    qreal speed = 0;
    QColor color;
};

#endif // BALL_H
