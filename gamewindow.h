#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "inkballscene.h"
#include "inkballview.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
    InkBallScene* inkBallScene;
    InkBallView* view;
    int id;
    int levelId;

public:
    explicit GameWindow(Level &level, int id, int speed, QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void gameOver();
    void gameWon(int gameTime);

signals:
    void windowGameOver(int id, int levelId);
    void windowGameWon(int id, int levelId, int gameTime);

};

#endif // GAMEWINDOW_H
