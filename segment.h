#ifndef SEGMENT_H
#define SEGMENT_H

#include <QGraphicsItem>
#include "constants.h"

class Segment : public QGraphicsItem
{
    QLineF segment;
    QColor color;

public:
    Segment(QLineF line, QColor color = segmentShadowColor);
    Segment(QPointF p1, QPointF p2, QColor color = segmentShadowColor);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
    QLineF getSegment();
    QColor getColor();
    void setColor(QColor color);
    void setP1(QPointF p1);
    void setP2(QPointF p2);
};

#endif // SEGMENT_H
