#include "goal.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>


Goal::Goal(qreal width, qreal height, QColor color)
    :w(width), h(height), color(color)
{}


QRectF Goal::boundingRect() const
{
    return QRectF(-w/2, -h/2, w, h);
}


QPainterPath Goal::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Goal::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(boundingRect());
    painter->setBrush(QColor(0, 0, 0));
    painter->drawEllipse(QPointF(0,0), 0.4*w, 0.4*h);
}
