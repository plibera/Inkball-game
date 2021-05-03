#ifndef GOAL_H
#define GOAL_H

#include <QGraphicsItem>

class Goal : public QGraphicsItem
{
    qreal w;
    qreal h;
    QColor color;

public:
    Goal(qreal width, qreal height, QColor color);
    QColor getColor();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
};

#endif // GOAL_H
