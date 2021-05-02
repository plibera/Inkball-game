#include "inkballview.h"

InkBallView::InkBallView(InkBallScene* inkBallScene)
    :QGraphicsView(inkBallScene)
{
    setRenderHint(QPainter::Antialiasing);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "InkBall"));
    setFixedSize(scene()->sceneRect().width(), scene()->sceneRect().height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    QObject::connect(&timer, &QTimer::timeout, inkBallScene, &QGraphicsScene::advance);
    timer.start(1000/FPS);
}
