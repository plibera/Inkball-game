#ifndef INKBALLSCENE_H
#define INKBALLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTime>
#include <QElapsedTimer>

#include "ball.h"
#include "obstacle.h"
#include "constants.h"
#include "segment.h"
#include "level.h"
#include "goal.h"

class Ball;

class InkBallScene : public QGraphicsScene
{
    Q_OBJECT

    QPointF sourcePosition;
    Segment* startedSegment;
    qreal gridCellW;
    qreal gridCellH;
    int ballSpeed;
    QElapsedTimer gameTimer;

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
    int getGameTime();

signals:
    void gameOver();
    void gameWon(int seconds);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // INKBALLSCENE_H
