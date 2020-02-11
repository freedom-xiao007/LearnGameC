//
// Created by Administrator on 2020/2/11.
//

#include <conio.h>
#include <winnt.h>
#include <cstdlib>
#include <afxres.h>
#include <sys/time.h>
#include "Tetris.h"

Tetris::Tetris(HANDLE pVoid, HANDLE pVoid1, COORD coord, DWORD bytes) {
    HANDLE hOutBuf = static_cast<HANDLE>(pVoid);
    HANDLE hOutput = static_cast<HANDLE>(pVoid1);
    SMALL_RECT rc = {0, 0, 30, 15};
    SetConsoleWindowInfo(hOutBuf, true, &rc);
    SetConsoleWindowInfo(hOutput, true, &rc);

    initData();

    bool buffSelect = true;
    int action = 0;
    long long stamp = getCurrentStamp();
    while(true) {
        // ¼ì²â°´¼ü,Óöµ½ESCÔòÍË³öÓÎÏ·
        action = 0;
        if(kbhit()) {
            action = _getch();
            if(action == 27) {
                break;
            } else {
                move(action);
            }
        }

        if(getCurrentStamp() - stamp >= 1000) {
            move(80);
            stamp = getCurrentStamp();
        }

        if(currentSquare.empty()) {
            createSquare();
        }
        draw();

        flush(hOutBuf, hOutput, coord, bytes, buffSelect);
        buffSelect = !buffSelect;
    }
}

void Tetris::initData() {
    data = new char*[height];
    for(int i = 0; i < height - 1; i++) {
        data[i] = new char[width];
        data[i][0] = wall;
        for(int j = 1; j < width - 1; j++) {
            data[i][j] = ' ';
        }
        data[i][width - 1] = '#';
    }
    data[height - 1] = new char[width];
    for(int i = 0; i < width; i++) {
        data[height - 1][i] = '#';
    }
}

void Tetris::flush(HANDLE hOutBuf, HANDLE hOutput, COORD coord, DWORD bytes, bool buffSelect) {
    // Ë«»º³åÇÐ»»»æÖÆÏÔÊ¾,±ÜÃâÉÁÆÁ
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

int Tetris::createSquare() {
    int amount = strlen(squareTypes);
    ++seed;
    srand(seed);
    int type = rand() % (amount- 1);
    if(squareTypes[type] == 'I') {
        createI();
    } else if(squareTypes[type] == 'J') {
        createJ();
    } else if(squareTypes[type] == 'L') {
        createL();
    } else if(squareTypes[type] == 'O') {
        createO();
    } else if(squareTypes[type] == 'S') {
        createS();
    } else if(squareTypes[type] == 'Z') {
        createZ();
    } else if(squareTypes[type] == 'T') {
        createT();
    }

    return (rand() % (width - 1)) + 1;
}

void Tetris::createI() {
    int x = (rand() % (width - 1) + 1);
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x, 2});
    currentSquare.push_back(new int[2]{x, 3});
    center[0] = x;
    center[1] = 2;
}

void Tetris::createJ() {
    int x = (rand() % (width - 1) + 2);
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x, 2});
    currentSquare.push_back(new int[2]{x-1, 2});
    center[0] = x;
    center[1] = 2;
}

void Tetris::createL() {
    int x = (rand() % (width - 1) + 1);
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x, 2});
    currentSquare.push_back(new int[2]{x+1, 2});
    center[0] = x;
    center[1] = 2;
}

void Tetris::createO() {
    int x = (rand() % (width - 1) + 1);
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x+1, 0});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x+1, 1});
    center[0] = x;
    center[1] = 1;
}

void Tetris::createS() {
    int x = (rand() % (width - 1) + 2);
    currentSquare.push_back(new int[2]{x+1, 0});
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x-1, 1});
    center[0] = x;
    center[1] = 1;
}

void Tetris::createZ() {
    int x = (rand() % (width - 1) + 2);
    currentSquare.push_back(new int[2]{x-1, 0});
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x+1, 1});
    center[0] = x;
    center[1] = 1;
}

void Tetris::createT() {
    int x = (rand() % (width - 1) + 2);
    currentSquare.push_back(new int[2]{x, 0});
    currentSquare.push_back(new int[2]{x-1, 1});
    currentSquare.push_back(new int[2]{x, 1});
    currentSquare.push_back(new int[2]{x+1, 1});
    center[0] = x;
    center[1] = 1;
}

void Tetris::draw() {
    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        data[y][x] = baseSquare;
    }
}

void Tetris::move(int action) {
    if(action == 32) {
        rotate();
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

bool Tetris::collisionDetect(int x, int y) {
    int ox, oy;
    for(int i = 0; i < currentSquare.size(); i++) {
        ox = currentSquare.at(i)[0];
        oy = currentSquare.at(i)[1];
        if(ox == x && oy == y) {
            return false;
        }
    }

    return data[y][x] == '*' || data[y][x] == '#';
}

void Tetris::rotate() {
    int cos90 = 0;
    int sin90 = 1;
    int dx = center[0];
    int dy = center[1];
    int nx, ny;
    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        nx = (x - dx) * cos90 - (y - dy) * sin90 + dx;
        ny = (x - dx) * sin90 + (y - dy) * cos90 + dy;
        if(collisionDetect(nx, ny)) {
            return;
        }
    }

    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        nx = (x - dx) * cos90 - (y - dy) * sin90 + dx;
        ny = (x - dx) * sin90 + (y - dy) * cos90 + dy;
        *(currentSquare.at(i)) = nx;
        *(currentSquare.at(i) + 1) = ny;
        data[y][x] = ' ';
    }
}

void Tetris::down() {
    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        if(collisionDetect(x, y + 1)) {
            currentSquare.clear();
            removeDetect();
            return;
        }
    }

    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        *(currentSquare.at(i) + 1) = y + 1;
        data[y][x] = ' ';
    }
    center[1] = center[1] + 1;
}

void Tetris::left() {
    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        if(collisionDetect(x - 1, y)) {
            return;
        }
    }

    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        *(currentSquare.at(i)) = x - 1;
        data[y][x] = ' ';
    }
    center[0] = center[0] - 1;
}

void Tetris::right() {
    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        if(collisionDetect(x + 1, y)) {
            return;
        }
    }

    for(int i = 0; i < currentSquare.size(); i++) {
        int x = currentSquare.at(i)[0];
        int y = currentSquare.at(i)[1];
        *(currentSquare.at(i)) = x + 1;
        data[y][x] = ' ';
    }
    center[0] = center[0] + 1;
}

long long Tetris::getCurrentStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void Tetris::removeDetect() {
    for(int i = height - 1; i >= 0; i--) {
        if(canRemove(i)) {
            remove(i);
        }
    }
}

bool Tetris::canRemove(int y) {
    for(int i = 1; i < width - 1; i++) {
        if(data[y][i] != '*') {
            return false;
        }
    }
    return true;
}

void Tetris::remove(int y) {
    for(int i = y; i > 0; i--) {
        for(int j = 1; j < width - 1; j++) {
            data[i][j] = data[i - 1][j];
        }
    }
}
