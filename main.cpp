#include <QtMath>
#include <QtWidgets>
#include <iostream>

#include "ball.h"
#include "constants.h"
#include "obstacle.h"
#include "inkballscene.h"
#include "inkballview.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    InkBallScene inkBallScene;
    InkBallView view(&inkBallScene);
    view.show();

    return app.exec();
}
