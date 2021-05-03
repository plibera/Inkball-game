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

public:
    explicit GameWindow(Level &level, int id, int speed, QWidget *parent = nullptr);
    ~GameWindow();

signals:

};

#endif // GAMEWINDOW_H
