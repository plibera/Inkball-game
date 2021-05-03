#include "level.h"
#include <sstream>

using namespace std;

Level::Level(int levelId, std::string levelInfo)
    :levelId(levelId)
{
    if(!levelInfo.empty())
        fromString(levelInfo);
    else
    {
        gridW = GRID_W;
        gridH = GRID_H;
    }
}

Level::Level(int levelId, int w, int h)
    :levelId(levelId), gridW(w), gridH(h)
{

}

std::string Level::toString()
{
    stringstream ss;
    ss<<gridW<<" "<<gridH<<" ";
    vector<bool> containsObstacle;
    containsObstacle.insert(containsObstacle.begin(), false, gridW*gridH);
    for(auto obs : obstacles)
    {
        containsObstacle[obs.second*gridW + obs.first] = true;
    }
    for(bool x : containsObstacle)
    {
        if(x)
            ss<<"1";
        else
            ss<<"0";
    }
    ss<<" ";
    ss<<source.first<<" "<<source.second<<" ";
    ss<<goals.size()<<" ";
    for(auto &goal : goals)
    {
        ss<<goal.x<<" "<<goal.y<<" "<<goal.color.red()<<" "<<goal.color.green()<<" "<<goal.color.blue()<<" ";
    }
    ss<<balls.size()<<" ";
    for(auto &ball : balls)
    {
        ss<<ball.x<<" "<<ball.y<<" "<<ball.angle<<" "<<ball.deployDelay<<" "<<ball.color.red()<<" "<<ball.color.green()<<" "<<ball.color.blue()<<" ";
    }
    ss<<scores.size()<<" ";
    for(auto &score : scores)
    {
        ss<<score<<" ";
    }
    return ss.str();
}

void Level::fromString(std::string levelInfo)
{
    obstacles.clear();
    goals.clear();
    balls.clear();
    scores.clear();

    stringstream ss;
    ss.str(levelInfo);
    ss>>gridW>>gridH;
    char c;
    for(int i = 0; i < gridW*gridH; ++i)
    {
        ss>>c;
        if(c == '1')
        {
            obstacles.push_back(make_pair(i%gridW, i/gridW));
        }
    }
    ss>>source.first>>source.second;
    int n;
    ss>>n;
    for(int i = 0; i < n; ++i)
    {
        GoalInfo goal;
        ss>>goal.x>>goal.y;
        int r, g, b;
        ss>>r>>g>>b;
        goal.color = QColor(r, g, b);
        goals.push_back(goal);
    }
    ss>>n;
    for(int i = 0; i < n; ++i)
    {
        BallInfo ball;
        ss>>ball.x>>ball.y>>ball.angle>>ball.deployDelay;
        int r, g, b;
        ss>>r>>g>>b;
        ball.color = QColor(r, g, b);
        balls.push_back(ball);
    }
    ss>>n;
    int score;
    for(int i = 0; i < n; ++i)
    {
        ss>>score;
        scores.push_back(score);
    }
    sort(scores.begin(), scores.end());
}

void Level::addScore(int score)
{
    scores.push_back(score);
    sort(scores.begin(), scores.end());
}
