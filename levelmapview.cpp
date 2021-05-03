#include "levelmapview.h"
#include <iostream>

using namespace std;

LevelMapView::LevelMapView(Level level)
    :level(level)
{
    graphicsScene = new QGraphicsScene;
    setScene(graphicsScene);
    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
}


void LevelMapView::setLevel(Level level)
{
    this->level = level;
}


void LevelMapView::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(backgroundColor);
    painter->drawRect(rect);
    qreal gridCellW = rect.width()/level.gridW;
    qreal gridCellH = rect.height()/level.gridH;
    painter->setBrush(obstacleColor);
    for(auto &obstacle : level.obstacles)
    {
        QPointF tl(rect.x() + obstacle.first*gridCellW, rect.y() + obstacle.second*gridCellH);
        QPointF br(rect.x() + (obstacle.first+1)*gridCellW, rect.y() + (obstacle.second+1)*gridCellH);
        QRectF r(tl, br);
        painter->drawRect(r);
    }
    for(auto &goal : level.goals)
    {
        painter->setBrush(goal.color);
        QPointF tl(rect.x() + goal.x*gridCellW, rect.y() + goal.y*gridCellH);
        QPointF br(rect.x() + (goal.x+1)*gridCellW, rect.y() + (goal.y+1)*gridCellH);
        QRectF r(tl, br);
        painter->drawRect(r);
    }
}
