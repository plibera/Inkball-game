#include "inkballview.h"

InkBallView::InkBallView(InkBallScene* inkBallScene)
    :QGraphicsView(inkBallScene)
{
    setRenderHint(QPainter::Antialiasing);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "InkBall"));
    setFixedSize(scene()->sceneRect().width(), scene()->sceneRect().height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    connect(&timer, &QTimer::timeout, inkBallScene, &QGraphicsScene::advance);
    connect(&timer, &QTimer::timeout, inkBallScene, &InkBallScene::checkBallRelease);
    timer.start(1000/FPS);
}
