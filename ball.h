#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>

#include "constants.h"
#include "inkballscene.h"

class InkBallScene;

class Ball : public QGraphicsItem
{
    InkBallScene* inkBallScene;
public:
    Ball(InkBallScene* scene, QColor color, qreal direction);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    QColor color;
};

#endif // BALL_H
