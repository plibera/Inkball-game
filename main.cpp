#include <QtMath>
#include <QtWidgets>
#include <iostream>

#include "ball.h"
#include "constants.h"
#include "obstacle.h"
#include "inkballscene.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    InkBallScene scene;

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "InkBall"));
    view.setFixedSize(view.scene()->sceneRect().width(), view.scene()->sceneRect().height());
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view.show();


    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}
