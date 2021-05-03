#include "mainmenuwindow.h"

using namespace std;

MainMenuWindow::MainMenuWindow(QWidget *parent) : QMainWindow(parent), ballSpeed(SPEED), idCounter(0)
{
    if(loadLevels())
    {
        levelMapView = new LevelMapView(*activeLevel);
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

    levelLayout = new QHBoxLayout;
    if(levelMapView)
        levelLayout->addWidget(levelMapView);

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

    topLayout->addLayout(levelLayout);
    topLayout->addLayout(speedAdjustLayout);
    topLayout->addLayout(buttonLayout);
}


bool MainMenuWindow::loadLevels()
{
    QString data;
    QString fileName(":/levels.txt");
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
    GameWindow *gameWindow = new GameWindow(*activeLevel, idCounter, ballSpeed);
    gameWindow->show();
    gameWindows.push_back(make_pair(idCounter, gameWindow));
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
}

void MainMenuWindow::displayMessage(std::string msg)
{

}

void MainMenuWindow::changeSpeed(int speed)
{
    ballSpeed = speed;
    speedAdjustLabel->setText("Ball speed: "+QString::number(speed));
}
