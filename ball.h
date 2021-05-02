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
    Ball(InkBallScene* scene, QColor color, qreal direction, qreal speed = 100);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
    void setAngle(qreal angle);


protected:
    void advance(int step) override;

    qreal angle = 0;
    qreal speed = 0;
    QColor color;
    int stepX;
    int stepY;
};

#endif // BALL_H
