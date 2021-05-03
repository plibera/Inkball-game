#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>

#include <QGraphicsItem>

#include "constants.h"

struct BallInfo
{
    qreal x;
    qreal y;
    qreal angle;
    qreal deployDelay;
    QColor color;
};

struct GoalInfo
{
    int x;
    int y;
    QColor color;
};

struct Level
{
    int levelId;
    int gridW;
    int gridH;
    std::vector<int> scores;
    std::vector<std::pair<int, int>> obstacles;
    std::pair<int, int> source;
    std::vector<GoalInfo> goals;
    std::vector<BallInfo> balls;

    Level(int levelId, std::string levelInfo);
    Level(int levelId, int w = GRID_W, int h = GRID_H);
    std::string toString();
    void fromString(std::string levelInfo);
    void addScore(int score);
};

#endif // LEVEL_H
