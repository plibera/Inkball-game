#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QPushButton>
#include <QLayout>
#include <QSlider>
#include <QLabel>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>

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
    int ballSpeed;
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
    QHBoxLayout *speedAdjustLayout;
    QSlider *speedAdjustSlider;
    QLabel *speedAdjustLabel;
    QLabel *mainInfoLabel;
    QTableWidget *scoreTableWidget;



public:
    explicit MainMenuWindow(QWidget *parent = nullptr);

    void nextLevel();
    void prevLevel();
    void showLevel();
    void playLevel();
    void displayMessage(std::string msg);
    void changeSpeed(int speed);
    void finishedGameOver(int windowId, int levelId);
    void finishedGameWon(int windowId, int levelId, int gameTime);
    void closeGame(int windowId);
    void updateScoreBoard();
    bool saveScoresToFile();


};

#endif // MAINMENUWINDOW_H
