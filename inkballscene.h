#ifndef INKBALLSCENE_H
#define INKBALLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "ball.h"
#include "obstacle.h"
#include "constants.h"
#include "segment.h"
#include "level.h"

class Ball;

class InkBallScene : public QGraphicsScene
{
    QPointF sourcePosition;
    Segment* startedSegment;

public:
    QList <Ball*> balls;
    QList <Obstacle*> obstacles;
    QList <Segment*> segments;

    InkBallScene();

    void addBall(QColor color, qreal direction = 0, qreal speed = 100, QPointF position = QPointF(-1, -1));
    void addObstacle(QPointF position);
    Segment* addSegment(QLineF line);

    void loadLevel(Level &level);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // INKBALLSCENE_H
