#include "inkballscene.h"

InkBallScene::InkBallScene()
{
    sourcePosition = QPointF(SCENE_W/2, SCENE_H/2);

    addBall(QColor(255, 0, 0), M_PI/2, 8);

    for(int i = 0; i < GRID_W; ++i)
        addObstacle(QPointF(OBS_W/2 + i*OBS_W, OBS_H/2));
    for(int i = 0; i < GRID_W; ++i)
        addObstacle(QPointF(OBS_W/2 + i*OBS_W, SCENE_H - OBS_H/2));
    for(int i = 1; i < GRID_H-1; ++i)
        addObstacle(QPointF(OBS_W/2, OBS_H/2 + i*OBS_H));
    for(int i = 1; i < GRID_H-1; ++i)
        addObstacle(QPointF(SCENE_W - OBS_W/2, OBS_H/2 + i*OBS_H));
}

void InkBallScene::addBall(QColor color, qreal direction, qreal speed, QPointF position)
{
    Ball *ball = new Ball(this, color, direction, speed);
    if(position.x() >= 0 && position.x() < SCENE_W && position.y() >= 0 && position.y() < SCENE_H)
        ball->setPos(position);
    else
        ball->setPos(sourcePosition);
    balls.append(ball);
}

void InkBallScene::addObstacle(QPointF position)
{
    Obstacle *obstacle = new Obstacle;
    obstacle->setPos(position);
    addItem(obstacle);
    obstacles.append(obstacle);
}
