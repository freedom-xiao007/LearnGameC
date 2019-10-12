#pragma once
class Sokoban
{
public:
	Sokoban();;
	~Sokoban() {};
	
private:
	int width, height;
	char** area;
	int man[2];
	int** walls;
	int boxs[10];
	int targets[10];
	char action;

	void redraw();
	void controller();
	void initArea();
	void initMan();
	void initWalls();
	void initBoxs();
	void initTargets();
	void up();
	void down();
	void left();
	void right();
	int* findMan();
	void move(int* currentPos, int* nextPos);
	bool isOver();
};

