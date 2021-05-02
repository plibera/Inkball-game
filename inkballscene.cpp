#include "inkballscene.h"
#include <iostream>

using namespace std;

InkBallScene::InkBallScene()
    :startedSegment(nullptr)
{
    sourcePosition = QPointF(SCENE_W/2, SCENE_H/2);

    addBall(QColor(255, 0, 0), M_PI/2, 300);
    addBall(QColor(0, 0, 255), 0, 50, QPointF(100, 100));
    addBall(QColor(0, 255, 255), 0, 200, QPointF(600, 100));


    for(int i = 0; i < GRID_W; ++i)
        addObstacle(QPointF(OBS_W/2 + i*OBS_W, OBS_H/2));
    for(int i = 0; i < GRID_W; ++i)
        addObstacle(QPointF(OBS_W/2 + i*OBS_W, SCENE_H - OBS_H/2));
    for(int i = 1; i < GRID_H-1; ++i)
        addObstacle(QPointF(OBS_W/2, OBS_H/2 + i*OBS_H));
    for(int i = 1; i < GRID_H-1; ++i)
        addObstacle(QPointF(SCENE_W - OBS_W/2, OBS_H/2 + i*OBS_H));
    addObstacle(QPointF(400, 100));

    //addSegment(QLineF(QPointF(0, 0), QPointF(500, 500)));
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

Segment* InkBallScene::addSegment(QLineF line)
{
    Segment *segment = new Segment(line, segmentShadowColor);
    addItem(segment);
    segments.append(segment);
    return segment;
}


void InkBallScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    startedSegment = addSegment(QLineF(event->scenePos(), event->scenePos()));
}

void InkBallScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!startedSegment)
        return;
    QRectF oldRect = startedSegment->boundingRect();

    QLineF line(startedSegment->getSegment().p1(), event->scenePos());
    qreal angle = line.angle();
    angle = 45*round(angle/45);
    if(angle >= 360)
        angle -= 360;
    angle *= M_PI/180;
    qreal length = line.length();
    QPointF point(length*cos(angle), -1*length*sin(angle));
    startedSegment->setP2(startedSegment->getSegment().p1() + point);
    update();
}

void InkBallScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!startedSegment)
        return;
    startedSegment->setColor(segmentColor);
    update();
    startedSegment = nullptr;
}
