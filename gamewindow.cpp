#include "gamewindow.h"

GameWindow::GameWindow(Level &level, int id, int speed, QWidget *parent) : QMainWindow(parent), id(id)
{
    inkBallScene = new InkBallScene(speed);
    inkBallScene->loadLevel(level);
    view = new InkBallView(inkBallScene);
    setCentralWidget(view);
    QString windowTitle = "InkBall Level "+QString::number(level.levelId);
    setWindowTitle(windowTitle);
    setFixedSize(view->size());
}

GameWindow::~GameWindow()
{
    delete view;
    delete inkBallScene;
}
