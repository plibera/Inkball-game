/*#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>

#include <QGraphicsItem>

class Goal : public QGraphicsItem
{
    int x = 0;
    int y = 0;
    int id = 0;
};


class Level
{
    std::vector<bool> isCellFree;
    std::vector<Goal> goals;
    std::pair<int, int> source;
    std::vector<Ball> balls;
public:
    Level();
};

#endif // LEVEL_H
*/
