//
// Created by Administrator on 2020/2/12.
//

#ifndef GAME_SHOT_H
#define GAME_SHOT_H


#include <vector>

class Shot {
public:
    Shot(HANDLE hOutBuf, HANDLE hOutput, COORD coord, DWORD bytes);
private:
    void initData();
    long long int getCurrentStamp();
    void controller(int action);
    void creatEnemy();
    void draw();
    void flush(HANDLE pVoid, HANDLE pVoid1, COORD coord, DWORD bytes, bool buffSelect);
    void move();
    void clearData();
    void fire();
    void down();
    void left();
    void right();
    void up();
    bool isDead(int x, int y);

    char** data;
    int width, height;
    std::vector<int*> allEnemy;
    std::vector<int*> liveEnemy;
    std::vector<int*> allBullet;
    std::vector<int*> liveBullet;
    int hero[2];
    bool isLive = true;
    int creatEnemyNumber = 1;

    void collosionDetect();

};


#endif //GAME_SHOT_H
