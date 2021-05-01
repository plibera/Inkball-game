#ifndef INKBALLSCENE_H
#define INKBALLSCENE_H

#include <QGraphicsScene>

#include "ball.h"
#include "obstacle.h"
#include "constants.h"

class InkBallScene : public QGraphicsScene
{
    QList <Ball*> balls;
    QList <Obstacle*> obstacles;
    QPointF sourcePosition;

public:
    InkBallScene();

    void addBall(QColor color, qreal direction, QPointF position = QPointF(-1, -1));
    void addObstacle(QPointF position);
};

#endif // INKBALLSCENE_H
