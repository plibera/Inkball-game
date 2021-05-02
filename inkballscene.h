#ifndef INKBALLSCENE_H
#define INKBALLSCENE_H

#include <QGraphicsScene>

#include "ball.h"
#include "obstacle.h"
#include "constants.h"

class Ball;

class InkBallScene : public QGraphicsScene
{
    QPointF sourcePosition;

public:
    QList <Ball*> balls;
    QList <Obstacle*> obstacles;

    InkBallScene();

    void addBall(QColor color, qreal direction = 0, qreal speed = 1, QPointF position = QPointF(-1, -1));
    void addObstacle(QPointF position);
};

#endif // INKBALLSCENE_H
