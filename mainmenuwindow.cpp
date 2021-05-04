#include "mainmenuwindow.h"

using namespace std;

MainMenuWindow::MainMenuWindow(QWidget *parent) : QMainWindow(parent), ballSpeed(SPEED), idCounter(0)
{
    resize(MAIN_MENU_DEFAULT_W, MAIN_MENU_DEFAULT_H);

    if(loadLevels())
    {
        levelMapView = new LevelMapView(*activeLevel);
        qDebug()<<"Levels read"<<Qt::endl;
    }
    else
    {
        qDebug()<<"Levels not read"<<Qt::endl;
        return;
    }

    mainWidget = new QWidget;
    setCentralWidget(mainWidget);

    prevButton = new QPushButton("Previous level");
    nextButton = new QPushButton("Next level");
    playButton = new QPushButton("Play this level");

    QObject::connect(prevButton, &QPushButton::clicked, this, &MainMenuWindow::prevLevel);
    QObject::connect(nextButton, &QPushButton::clicked, this, &MainMenuWindow::nextLevel);
    QObject::connect(playButton, &QPushButton::clicked, this, &MainMenuWindow::playLevel);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->addWidget(playButton);

    topLayout = new QVBoxLayout;
    mainWidget->setLayout(topLayout);

    speedAdjustLayout = new QHBoxLayout;
    speedAdjustSlider = new QSlider;
    speedAdjustSlider->setOrientation(Qt::Horizontal);
    speedAdjustSlider->setMinimum(100);
    speedAdjustSlider->setMaximum(500);
    speedAdjustSlider->setValue(SPEED);
    speedAdjustLabel = new QLabel;
    changeSpeed(SPEED);
    speedAdjustLayout->addWidget(speedAdjustLabel);
    speedAdjustLayout->addWidget(speedAdjustSlider);
    QObject::connect(speedAdjustSlider, &QSlider::valueChanged, this, &MainMenuWindow::changeSpeed);

    mainInfoLabel = new QLabel;
    mainInfoLabel->setAlignment(Qt::AlignCenter);
    displayMessage("Level 1");


    scoreTableWidget = new QTableWidget;
    scoreTableWidget->setColumnCount(1);
    scoreTableWidget->setRowCount(BEST_SCORES_DISPLAYED);
    QStringList columnNames = {"Best Times [s]"};
    scoreTableWidget->setHorizontalHeaderLabels(columnNames);
    scoreTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scoreTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scoreTableWidget->horizontalHeader()->setStretchLastSection(true);

    levelLayout = new QHBoxLayout;
    if(levelMapView)
    {
        QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Expanding);
        spLeft.setHorizontalStretch(3);
        levelMapView->setSizePolicy(spLeft);
        levelLayout->addWidget(levelMapView);
    }
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Expanding);
    spRight.setHorizontalStretch(1);
    scoreTableWidget->setSizePolicy(spRight);
    levelLayout->addWidget(scoreTableWidget);


    topLayout->addWidget(mainInfoLabel);
    topLayout->addLayout(levelLayout);
    topLayout->addLayout(speedAdjustLayout);
    topLayout->addLayout(buttonLayout);

    updateScoreBoard();
}


bool MainMenuWindow::loadLevels()
{
    QString data;
    QString fileName(":/levels.txt");
    //QString fileName("levels.txt");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"File not opened"<<Qt::endl;
        return false;
    }
    else
    {
        qDebug()<<"File opened"<<Qt::endl;
        data = file.readAll();
    }
    file.close();
    QStringList lines = data.split('\n');
    int counter = 1;
    for(auto& line : lines)
    {
        if(line.length() < 9)
            continue;
        Level level(counter++);
        level.fromString(line.toStdString());
        levels.push_back(level);
    }
    activeLevel = levels.begin();
    if(levels.size() > 0)
        return true;
    return false;
}

void MainMenuWindow::playLevel()
{
    GameWindow *gameWindow = new GameWindow(*activeLevel, idCounter, ballSpeed, this);
    gameWindow->setAttribute( Qt::WA_DeleteOnClose );
    gameWindow->show();
    gameWindows.push_back(make_pair(idCounter, gameWindow));
    connect(gameWindow, &GameWindow::windowGameOver, this, &MainMenuWindow::finishedGameOver);
    connect(gameWindow, &GameWindow::windowGameWon, this, &MainMenuWindow::finishedGameWon);
    idCounter++;
}

void MainMenuWindow::nextLevel()
{
    if(activeLevel == levels.end()-1)
        activeLevel = levels.begin();
    else
        activeLevel++;
    showLevel();
}

void MainMenuWindow::prevLevel()
{
    if(activeLevel == levels.begin())
        activeLevel = levels.end()-1;
    else
        activeLevel--;
    showLevel();
}

void MainMenuWindow::showLevel()
{
    levelMapView->setLevel(*activeLevel);
    levelMapView->scene()->invalidate(levelMapView->scene()->sceneRect());
    displayMessage("Level " + to_string(distance(levels.begin(), activeLevel)+1));
    updateScoreBoard();
}

void MainMenuWindow::displayMessage(std::string msg)
{
    mainInfoLabel->setText(QString::fromStdString(msg));
}

void MainMenuWindow::changeSpeed(int speed)
{
    ballSpeed = speed;
    speedAdjustLabel->setText("Ball speed: "+QString::number(speed));
}

void MainMenuWindow::finishedGameOver(int windowId, int levelId)
{
    displayMessage("Level "+to_string(levelId)+": GAME OVER");
    closeGame(windowId);
}

void MainMenuWindow::finishedGameWon(int windowId, int levelId, int gameTime)
{
    displayMessage("Level "+to_string(levelId)+" won in "+to_string(gameTime)+" seconds!");
    for(auto &level : levels)
    {
        if(level.levelId == levelId)
            level.addScore(gameTime);
    }
    saveScoresToFile();
    closeGame(windowId);
}

void MainMenuWindow::closeGame(int windowId)
{
    for(auto &window : gameWindows)
    {
        if(window.first == windowId)
        {
            window.second->close();
            break;
        }
    }
    updateScoreBoard();
}


void MainMenuWindow::updateScoreBoard()
{
    scoreTableWidget->clearContents();
    int counter = 0;
    for(auto& score : activeLevel->scores)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(score));
        scoreTableWidget->setItem(counter++, 0, item);
        if(counter == scoreTableWidget->rowCount())
            break;
    }
}


bool MainMenuWindow::saveScoresToFile()
{
    QString fileName("levels.txt");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"File not opened"<<Qt::endl;
        return false;
    }
    else
    {
        qDebug()<<"File opened"<<Qt::endl;
    }
    QTextStream out(&file);
    for(auto &level : levels)
    {
        out << QString::fromStdString(level.toString()) << "\n";
    }
    file.close();
    return true;
}
