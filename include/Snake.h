#pragma once

#include <wincon.h>
#include <vector>

class Snake
{
public:
	Snake(void *pVoid, void *pVoid1, _COORD coord, unsigned long i);
	~Snake() {};

private:
	void initArea();
	bool move(int action);
	bool up();
	bool down();
	bool left();
	bool right();
	void createSnake();
	void creatFood();
	int* createRandPosition();
	int* findSnakeHead();
	long long getCurrentStamp();
	void eat(int foodX, int foodY);
	void moveSnake(int currentX, int currentY, int nextX, int nextY);
	bool isDead(int x, int y);

	int height = 15;
	int width = 30;
	char** data;
    int seed; // 随机数种子，用当前时间戳，便于生成不同的随机数
    int direction; // up:72, down:80, left:75, right:77
    std::vector<int*> snakeData;
};

