#include "Snake.h"
#include <conio.h>
#include <winnt.h>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>

Snake::Snake(void *pVoid, void *pVoid1, _COORD coord, unsigned long bytes)
{
    HANDLE hOutBuf = static_cast<HANDLE>(pVoid);
    HANDLE hOutput = static_cast<HANDLE>(pVoid1);

    initArea();
    createSnake();
    creatFood();
    direction = 72;

    long long stamp = getCurrentStamp();
    bool buffSelect = true;
    while (true) {
        if(kbhit()) {
            direction = _getch();
            if (direction == 27) {
                break;
            }
        }
        if(getCurrentStamp() - stamp >= 500) {
            if(!move(direction)) {
                for (int i = 0; i < height; i++) {
                    coord.Y = i;
                    WriteConsoleOutputCharacterA(hOutBuf, data[i], width, coord, &bytes);
                }
                char* over = "!!!!!!GAME OVER!!!!!!";
                WriteConsoleOutputCharacterA(hOutBuf, over, 21, coord, &bytes);
                SetConsoleActiveScreenBuffer(hOutBuf);
                continue;
            }
            stamp = getCurrentStamp();
        }

        if (buffSelect) {
            for (int i = 0; i < height; i++) {
                coord.Y = i;
                WriteConsoleOutputCharacterA(hOutBuf, data[i], width, coord, &bytes);
            }

            SetConsoleActiveScreenBuffer(hOutBuf);
            buffSelect = false;
        }
        else {
            for (int i = 0; i < height; i++) {
                coord.Y = i;
                WriteConsoleOutputCharacterA(hOutput, data[i], width, coord, &bytes);
            }

            SetConsoleActiveScreenBuffer(hOutput);
            buffSelect = true;
        }
    }
}

void Snake::initArea()
{
	data = new char* [height];
	for (int i = 0; i < this->height; i++) {
		data[i] = new char[this->width];
	}

    for (int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            data[i][j] = ' ';
        }
    }

	for (int i = 0; i < this->height; i++) {
		data[i][0] = '#';
		data[i][this->width - 1] = '#';
	}

	for (int i = 0; i < this->width; i++) {
		data[0][i] = '#';
		data[this->height - 1][i] = '#';
	}
}

bool Snake::move(int action)
{
    if (action == 72) {
        return up();
    }
    else if (action == 80) {
        return down();
    }
    else if (action == 75) {
        return left();
    }
    else if (action == 77) {
        return right();
    }
    return true;
}

void Snake::creatFood() {
    int* position = createRandPosition();
    data[*position][*(position + 1)] = '*';
}

bool Snake::up() {
    int* position = findSnakeHead();
    int currentX = *position;
    int currentY = *(position + 1);
    int nextX = currentX - 1;
    int nextY = currentY;

    if(isDead(nextX, nextY)) {
        return false;
    }

    if(data[nextX][nextY] == '*') {
        eat(nextX, nextY);
    }

    moveSnake(currentX, currentY, nextX, nextY);
    return true;
}

bool Snake::down() {
    int* position = findSnakeHead();
    int currentX = *position;
    int currentY = *(position + 1);
    int nextX = currentX + 1;
    int nextY = currentY;

    if(isDead(nextX, nextY)) {
        return false;
    }

    if(data[nextX][nextY] == '*') {
        eat(nextX, nextY);
    }

    moveSnake(currentX, currentY, nextX, nextY);
    return true;
}

bool Snake::left() {
    int* position = findSnakeHead();
    int currentX = *position;
    int currentY = *(position + 1);
    int nextX = currentX;
    int nextY = currentY - 1;

    if(isDead(nextX, nextY)) {
        return false;
    }

    if(data[nextX][nextY] == '*') {
        eat(nextX, nextY);
    }

    moveSnake(currentX, currentY, nextX, nextY);
    return true;
}

bool Snake::right() {
    int* position = findSnakeHead();
    int currentX = *position;
    int currentY = *(position + 1);
    int nextX = currentX;
    int nextY = currentY + 1;

    if(isDead(nextX, nextY)) {
        return false;
    }

    if(data[nextX][nextY] == '*') {
        eat(nextX, nextY);
    }

    moveSnake(currentX, currentY, nextX, nextY);
    return true;
}

void Snake::createSnake() {
    int* position = createRandPosition();
    data[*position][*(position + 1)] = '0';
    snakeData.push_back(position);
}

int *Snake::createRandPosition() {
    int x, y;
    while (true) {
        ++seed;
        srand(seed);
        x = (rand() % (width - 1)) + 1;

        ++seed;
        srand(seed);
        y = (rand() % (height - 1)) + 1;

        if (data[y][x] == ' ' && data[y][x] != '#') {
            int* position = new int[2];
            position[0] = y;
            position[1] = x;
            return position;
        }
    }
}

int *Snake::findSnakeHead() {
    for (int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(data[i][j] == '0') {
                int* position = new int[2];
                position[0] = i;
                position[1] = j;
                return position;
            }
        }
    }
    return nullptr;
}

long long Snake::getCurrentStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void Snake::eat(int foodX, int foodY) {
    int* last = snakeData.back();
    int x = *last;
    int y = *(last + 1);
    if(data[x + 1][y] != '#' && data[x + 1][y] != 'o') {
        int* add = new int[2]{x + 1, y};
        snakeData.push_back(add);
    } else if(data[x - 1][y] != '#' && data[x - 1][y] != 'o') {
        int* add = new int[2]{x - 1, y};
        snakeData.push_back(add);
    } else if(data[x][y + 1] != '#' && data[x][y + 1] != 'o') {
        int *add = new int[2]{x, y + 1};
        snakeData.push_back(add);
    } else if(data[x][y - 1] != '#' && data[x][y - 1] != 'o') {
        int *add = new int[2]{x, y - 1};
        snakeData.push_back(add);
    }

    data[foodX][foodY] = ' ';
    creatFood();
}

void Snake::moveSnake(int currentX, int currentY, int nextX, int nextY) {
    for(int i = 0; i < snakeData.size(); i++) {
        currentX = *snakeData.at(i);
        currentY = *(snakeData.at(i) + 1);
        *snakeData.at(i) = nextX;
        *(snakeData.at(i) + 1) = nextY;
        nextX = currentX;
        nextY = currentY;
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(data[i][j] == '0' || data[i][j] == 'o') {
                data[i][j] = ' ';
            }
        }
    }

    int x, y;
    for(int i = 0; i < snakeData.size(); i++) {
        x = *snakeData.at(i);
        y = *(snakeData.at(i) + 1);
        if(i == 0) {
            data[x][y] = '0';
        } else {
            data[x][y] = 'o';
        }
    }
}

bool Snake::isDead(int x, int y) {
    return data[x][y] == '#' || data[x][y] == 'o';
}
