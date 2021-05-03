#include <QtMath>
#include <QtWidgets>
#include <iostream>
#include <fstream>

#include "ball.h"
#include "constants.h"
#include "obstacle.h"
#include "inkballscene.h"
#include "inkballview.h"

using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Level level;
    QString data;
    QString fileName(":/levels.txt");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"File not opened"<<endl;
    }
    else
    {
        qDebug()<<"File opened"<<endl;
        data = file.readAll();
    }
    file.close();
    QStringList lines = data.split('\n');
    level.fromString(lines[2].toStdString());

    InkBallScene inkBallScene;
    inkBallScene.loadLevel(level);
    InkBallView view(&inkBallScene);
    view.show();

    return app.exec();
}
