#pragma once

#include <wincon.h>
#include <vector>

class Snake
{
public:
	Snake(void *pVoid, void *pVoid1, _COORD coord, unsigned long i);
	~Snake() {};

private:
    // 初始化数据(墙,豆子,蛇)
	void initArea();
    // 移动处理,如果不能移动,返回false
	bool move(int action);
	// 向上移动,不能移动返回false
	bool up();
	// 向下移动,不能移动返回false
	bool down();
	// 向左移动,不能移动返回false
	bool left();
	// 向右移动,不能移动返回false
	bool right();
	// 生成蛇数据
	void createSnake();
	// 生成豆子
	void creatFood();
	// 随机生成位置,返回x,y坐标
	int* createRandPosition();
	// 寻找蛇头坐标位置,返回x,y坐标
	int* findSnakeHead();
	// 获取当前系统时间戳
	long long getCurrentStamp();
	// 处理吃到豆子后的数据变化:豆子消失,蛇边长,并再生成豆子
	void eat(int foodX, int foodY);
	// 处理蛇的移动:蛇头向前移动,其他位置移动都向前移动一位
	void moveSnake(int currentX, int currentY, int nextX, int nextY);
	// 判断是否碰撞到墙或蛇身,是既死亡
	bool isDead(int x, int y);

	int height = 15;
	int width = 30;
	char** data;
    int seed; // 随机数种子，用当前时间戳，便于生成不同的随机数
    int direction; // up:72, down:80, left:75, right:77
    std::vector<int*> snakeData; // 蛇头和蛇身数据,蛇头是第一个
};

