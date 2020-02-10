#pragma once
/*推箱子游戏
简介：
	简单的推箱子游戏，将所有箱子推到目的地即可

游戏符号标记：
	障碍物：#
	任务：*
	箱子：$
	目的地：@
	箱子+目的地：!
	人物+目的地: R

游戏控制：
	上下左右键进行移动控制
*/
class Sokoban
{
public:
	Sokoban();;
	~Sokoban() {};

private:
	int width, height; // 游戏地图的宽和高
	int boxAmount = 5; // 游戏中箱子的数量和目的地的数量
	int successCount; // 用于标记多少箱子推放到目的地了，用于判断游戏是否结束
	char** area; // 字符二维数组，游戏地图
	int seed; // 随机数种子，用当前时间戳，便于生成不同的随机数
	int wallAmount; // 游戏中墙的数量

	/*绘制游戏，打印二维数组*/
	void redraw();
	/*获取用户输入，控制人物移动*/
	bool controller();
	/*初始化地图*/
	void initArea();
	/*随机生成人物*/
	void initMan();
	/*随机生成障碍物墙*/
	void initWalls();
	/*随机生成箱子*/
	void initBoxs();
	/*随机生成目的地*/
	void initTargets();
	/*生成随机位置*/
	int* createRandPosition();
	/*生成箱子随机位置，箱子不能随机挨着墙*/
	int* createRandBoxPosition();
	/*人物向上移动*/
	void up();
	/*人物向下移动*/
	void down();
	/*人物向左移动*/
	void left();
	/*人物向右移动*/
	void right();
	/*查找返回任务坐标*/
	int* findMan();
	/*箱子或者任务的移动变换*/
	void move(int* currentPos, int* nextPos);
	/*判断游戏是否结束，看successCount是否等于boxAmount*/
	bool isOver();
};

