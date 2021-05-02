#include "segment.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <iostream>

using namespace std;

Segment::Segment(QLineF line, QColor color)
    :segment(line), color(color)
{

}

Segment::Segment(QPointF p1, QPointF p2, QColor color)
    :segment(p1, p2), color(color)
{

}

QRectF Segment::boundingRect() const
{
    return QRectF(segment.p1(), segment.p2());
}


QPainterPath Segment::shape() const
{
    QPainterPath path;
    path.moveTo(segment.p1());
    path.lineTo(segment.p2());
    return path;
}

void Segment::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(color, 3));
    painter->drawLine(segment);
}

QLineF Segment::getSegment()
{
    return segment;
}

void Segment::setColor(QColor color)
{
    this->color = color;
}

void Segment::setP1(QPointF p1)
{
    segment.setP1(p1);
}

void Segment::setP2(QPointF p2)
{
    segment.setP2(p2);
}

QColor Segment::getColor()
{
    return color;
}
