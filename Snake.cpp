#include "Snake.h"
#include <thread>
#include <iostream>

Snake::Snake()
{
	std::thread drawThread(&(this->draw));
	drawThread.join();

	std::thread controllThread(&(this->controll));
	controllThread.join();
}

void Snake::initArea()
{
	this->area = new char* [height];
	for (int i = 0; i < this->height; i++) {
		this->area[i] = new char[this->width];
	}

	for (int i = 0; i < this->height; i++) {
		this->area[i][0] = '#';
		this->area[i][this->width - 1] = '#';
	}

	for (int i = 0; i < this->width; i++) {
		this->area[0][i] = '#';
		this->area[this->height - 1][i] = '#';
	}
}

void Snake::draw()
{
	for (int i = 0; i < this->height; i++) {
		std::cout << this->area[i] << std::endl;
	}
}

void Snake::controll()
{
}

void Snake::creatFood()
{
}
