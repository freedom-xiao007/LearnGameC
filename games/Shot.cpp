//
// Created by Administrator on 2020/2/12.
//

#include <winnt.h>
#include <wincon.h>
#include <conio.h>
#include <iostream>
#include <sys/time.h>
#include "Shot.h"

Shot::Shot(HANDLE hOutBuf, HANDLE hOutput, COORD coord, DWORD bytes) {
    SMALL_RECT rc = {0, 0, 50, 20};
    SetConsoleWindowInfo(hOutBuf, true, &rc);
    SetConsoleWindowInfo(hOutput, true, &rc);

    height = 20;
    width = 50;

    initData();

    bool buffSelect = true;
    int action = 0;
    long long stamp = getCurrentStamp();
    while(true) {
        // 检测按键,遇到ESC则退出游戏
        action = 0;
        if(kbhit()) {
            action = _getch();
            std::cout << action << std::endl;
            if(action == 27) {
                break;
            }
            else {
                controller(action);
            }
        }

        if(getCurrentStamp() - stamp >= 500) {
            creatEnemy();
            move();
            stamp = getCurrentStamp();
        }
        collosionDetect();
//        if(!isLive) {
//            char* over = "!!!!!!GAME OVER!!!!!!";
//            WriteConsoleOutputCharacterA(hOutBuf, over, 21, coord, &bytes);
//            SetConsoleActiveScreenBuffer(hOutBuf);
//            break;
//        }
        draw();

        flush(hOutBuf, hOutput, coord, bytes, buffSelect);
        buffSelect = !buffSelect;
    }
}

long long int Shot::getCurrentStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void Shot::controller(int action) {
    if(action == 32) {
        fire();
    }
    else if (action == 72) {
        up();
    }
    else if (action == 80) {
        down();
    }
    else if (action == 75) {
        left();
    }
    else if (action == 77) {
        right();
    }
}

void Shot::initData() {
    clearData();
    int center = width / 2;
    hero[0] = height - 2;
    hero[1] = center;
}

void Shot::creatEnemy() {
    int x;
    for(int i = 0; i < creatEnemyNumber; i++) {
        x = (rand() % (width - 1) + 1);
        allEnemy.push_back(new int[2]{0, x});
    }
}

void Shot::draw() {
    clearData();

    int hy = hero[0];
    int hx = hero[1];
    data[hy][hx] = 'A';

    int x, y;
    for(int i = 0; i < allBullet.size(); i++) {
        y = *allBullet[i];
        x = *(allBullet[i] + 1);
        data[y][x] = 'I';
    }

    for(int i = 0; i < allEnemy.size(); i++) {
        y = *allEnemy[i];
        x = *(allEnemy[i] + 1);
        data[y][x] = 'V';
    }
}

void Shot::flush(HANDLE hOutBuf, HANDLE hOutput, COORD coord, DWORD bytes, bool buffSelect) {
    // 双缓冲切换绘制显示,避免闪屏
    if (buffSelect) {
        for (int i = 0; i < height; i++) {
            coord.Y = i;
            WriteConsoleOutputCharacterA(hOutBuf, data[i], width, coord, &bytes);
        }

        SetConsoleActiveScreenBuffer(hOutBuf);
    }
    else {
        for (int i = 0; i < height; i++) {
            coord.Y = i;
            WriteConsoleOutputCharacterA(hOutput, data[i], width, coord, &bytes);
        }

        SetConsoleActiveScreenBuffer(hOutput);
    }
}

void Shot::move() {
    for(int i = 0; i < allBullet.size(); i++) {
        *allBullet[i] = *allBullet[i] - 1;
    }

    for(int i = 0; i < allEnemy.size(); i++) {
        *allEnemy[i] = *allEnemy[i] + 1;
    }
}

void Shot::clearData() {
    data = new char*[height];
    for(int i = 0; i < height - 1; i++) {
        data[i] = new char[width];
        data[i][0] = '|';
        for(int j = 1; j < width - 1; j++) {
            data[i][j] = ' ';
        }
        data[i][width - 1] = '|';
    }
    data[height - 1] = new char[width];
    for(int i = 0; i < width; i++) {
        data[height - 1][i] = '-';
    }
}

void Shot::fire() {
    int y = hero[0] - 1;
    int x = hero[1];
    allBullet.push_back(new int[2]{y, x});
}

void Shot::up() {
    if(hero[0] - 1 > 0) {
        hero[0] = hero[0] - 1;
    }
}

void Shot::down() {
    if(hero[0] + 1 < height - 1) {
        hero[0] = hero[0] + 1;
    }
}

void Shot::left() {
    if(hero[1] - 1 > 0) {
        hero[1] = hero[1] - 1;
    }
}

void Shot::right() {
    if(hero[1] + 1 < width - 1) {
        hero[1] = hero[1] + 1;
    }
}

void Shot::collosionDetect() {
    int x, y;
    liveBullet.clear();
    for(int i = 0; i < allBullet.size(); i++) {
        y = *allBullet[i];
        x = *(allBullet[i] + 1);
        if(data[y-1][x] == 'V' || y - 1 == 0) {
            std::cout << "dead" << std::endl;
        }
        else {
            liveBullet.push_back(new int[2]{y, x});
        }
    }
    allBullet.clear();
    allBullet = liveBullet;

    liveEnemy.clear();
    for(int i = 0; i < allEnemy.size(); i++) {
        y = *allEnemy[i];
        x = *(allEnemy[i] + 1);
        if(data[y+1][x] == 'I' || data[y+1][x] == '-') {
            std::cout << "dead" << std::endl;
        }
        else {
            liveEnemy.push_back(new int[2]{y, x});
        }

        isLive = isDead(x, y+1);
    }
    allEnemy.clear();
    allEnemy = liveEnemy;
}

bool Shot::isDead(int x, int y) {
    return data[y][x] == 'A';
}

