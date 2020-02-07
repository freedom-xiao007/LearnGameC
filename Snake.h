#pragma once
class Snake
{
public:
	Snake();
	~Snake() {};

private:
	void initArea();
	void draw();
	void controll();
	void creatFood();

	int height = 30;
	int width = 15;
	char** area;
};

