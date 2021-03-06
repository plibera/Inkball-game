#include "inkballscene.h"
#include <iostream>

using namespace std;

InkBallScene::InkBallScene(int ballSpeed)
    :startedSegment(nullptr), ballSpeed(ballSpeed)
{}

void InkBallScene::loadLevel(Level &level)
{
    gridCellW = (qreal)SCENE_W/(qreal)(level.gridW+2);
    gridCellH = (qreal)SCENE_H/(qreal)(level.gridH+2);
    sourcePosition.setX(gridCellW*(level.source.first+1.5));
    sourcePosition.setY(gridCellH*(level.source.second+1.5));

    for(auto &goal : level.goals)
    {
        addGoal(QPointF((goal.x+1.5)*gridCellW, (goal.y+1.5)*gridCellH), goal.color);
    }

    for(BallInfo &ball : level.balls)
    {
        if(ball.deployDelay < EPSILON)
            addBall(ball.color, ball.angle, ballSpeed, QPointF((ball.x+1.5)*gridCellW, (ball.y+1.5)*gridCellH));
        else
            waitingBalls.push_back(ball);
    }

    for(int i = 0; i < level.gridW+2; ++i)
        addObstacle(QPointF(gridCellW/2 + (qreal)i*gridCellW, gridCellH/2));
    for(int i = 0; i < level.gridW+2; ++i)
        addObstacle(QPointF(gridCellW/2 + (qreal)i*gridCellW, SCENE_H - gridCellH/2));
    for(int i = 1; i < level.gridH+1; ++i)
        addObstacle(QPointF(gridCellW/2, gridCellH/2 + (qreal)i*gridCellH));
    for(int i = 1; i < level.gridH+1; ++i)
        addObstacle(QPointF(SCENE_W - gridCellW/2, gridCellH/2 + (qreal)i*gridCellH));
    for(auto &obstacle : level.obstacles)
    {
        addObstacle(QPointF((obstacle.first+1.5)*gridCellW, (obstacle.second+1.5)*gridCellH));
    }
    gameTimer.start();
}

void InkBallScene::setSpeed(int speed)
{
    ballSpeed = speed;
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
    Obstacle *obstacle = new Obstacle(gridCellW, gridCellH);
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

void InkBallScene::addGoal(QPointF position, QColor color)
{
    Goal* goal = new Goal(gridCellW, gridCellH, color);
    goal->setPos(position);
    addItem(goal);
    goals.append(goal);
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
    if(!startedSegment || event->button() != Qt::LeftButton)
        return;
    startedSegment->setColor(segmentColor);
    update();
    startedSegment = nullptr;
}

void InkBallScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(sourcePosition, BALL_D/4, BALL_D/4);
}

int InkBallScene::getGameTime()
{
    return gameTimer.elapsed();
}

void InkBallScene::checkBallRelease()
{
    if(waitingBalls.size() == 0)
        return;
    vector<BallInfo> notReleased;
    for(auto& ball : waitingBalls)
    {
        if(ball.deployDelay < gameTimer.elapsed()/1000)
        {
            addBall(ball.color, ball.angle, ballSpeed);
        }
        else
        {
            notReleased.push_back(ball);
        }
    }
    waitingBalls = notReleased;
}
