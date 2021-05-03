#ifndef LEVELMAPVIEW_H
#define LEVELMAPVIEW_H

#include <QGraphicsView>

#include "level.h"

class LevelMapView : public QGraphicsView
{
    Level level;
    QGraphicsScene *graphicsScene;
public:
    LevelMapView(Level level);

    void setLevel(Level level);

protected:
    virtual void drawForeground(QPainter *painter, const QRectF &rect) override;
};

#endif // LEVELMAPVIEW_H
