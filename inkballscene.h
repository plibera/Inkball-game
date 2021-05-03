#ifndef INKBALLSCENE_H
#define INKBALLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "ball.h"
#include "obstacle.h"
#include "constants.h"
#include "segment.h"
#include "level.h"
#include "goal.h"

class Ball;

class InkBallScene : public QGraphicsScene
{
    QPointF sourcePosition;
    Segment* startedSegment;
    qreal gridCellW;
    qreal gridCellH;
    int ballSpeed;

public:
    QList <Ball*> balls;
    QList <Obstacle*> obstacles;
    QList <Segment*> segments;
    QList <Goal*> goals;

    InkBallScene(int ballSpeed = SPEED);

    void addBall(QColor color, qreal direction, qreal speed, QPointF position = QPointF(-1, -1));
    void addObstacle(QPointF position);
    Segment* addSegment(QLineF line);
    void addGoal(QPointF position, QColor color);

    void loadLevel(Level &level);
    void setSpeed(int speed);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // INKBALLSCENE_H
