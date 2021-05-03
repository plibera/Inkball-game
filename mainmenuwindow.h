#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QPushButton>
#include <QLayout>

#include "level.h"
#include "inkballview.h"
#include "inkballscene.h"
#include "gamewindow.h"
#include "levelmapview.h"

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

    std::vector<Level> levels;
    std::vector<Level>::iterator activeLevel;
    std::vector<std::pair<int, GameWindow*>> gameWindows;
    int idCounter;

    bool loadLevels();

    QWidget *mainWidget;
    QVBoxLayout *topLayout;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *playButton;
    QHBoxLayout *buttonLayout;
    LevelMapView *levelMapView;
    QHBoxLayout *levelLayout;


public:
    explicit MainMenuWindow(QWidget *parent = nullptr);

    void nextLevel();
    void prevLevel();
    void showLevel();
    void playLevel();
    void displayMessage(std::string msg);

signals:

};

#endif // MAINMENUWINDOW_H
