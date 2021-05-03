#include "gamewindow.h"

GameWindow::GameWindow(Level &level, int id, QWidget *parent) : QMainWindow(parent), id(id)
{
    inkBallScene = new InkBallScene;
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
