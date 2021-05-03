#include "gamewindow.h"
#include <iostream>

using namespace std;

GameWindow::GameWindow(Level &level, int id, int speed, QWidget *parent) : QMainWindow(parent), id(id)
{
    inkBallScene = new InkBallScene(speed);
    inkBallScene->loadLevel(level);
    levelId = level.levelId;
    view = new InkBallView(inkBallScene);
    setCentralWidget(view);
    QString windowTitle = "InkBall Level "+QString::number(level.levelId);
    setWindowTitle(windowTitle);
    setFixedSize(view->size());

    connect(inkBallScene, &InkBallScene::gameOver, this, &GameWindow::gameOver);
    connect(inkBallScene, &InkBallScene::gameWon, this, &GameWindow::gameWon);
}

GameWindow::~GameWindow()
{
    delete view;
    delete inkBallScene;
}


void GameWindow::gameOver()
{
    emit windowGameOver(id, levelId);
}

void GameWindow::gameWon(int gameTime)
{
    emit windowGameWon(id, levelId, gameTime);
}
