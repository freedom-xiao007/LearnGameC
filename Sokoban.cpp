#include "Sokoban.h"
#include<iostream>
#include<time.h>
#include<conio.h>

Sokoban::Sokoban() {
	initArea();
	initWalls();
	initMan();
	initBoxs();
	initTargets();
	redraw();

	while (true) {
		controller();
		if (isOver()) {
			break;
		}
	}
	
}

void Sokoban::redraw() {
	system("cls");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << area[i][j];
		}
		std::cout << std::endl;
	}
}

void Sokoban::controller() {
	int input = _getch();
	if (input == 72) {
		up();
	}
	else if (input == 80) {
		down();
	}
	else if (input == 75) {
		left();
	}
	else if (input == 77) {
		right();
	}
	redraw();
	isOver();
}

void Sokoban::initArea() {
	/*std::cout << "请输出地区的大小：宽、高\n";
	std::cin >> width;
	std::cin >> height;*/
	width = 50;
	height = 20;

	area = new char* [height];
	for (int i = 0; i < height; i++) {
		area[i] = new char[width];
		for (int j = 0; j < width; j++) {
			area[i][j] = ' ';
		}
	}
	for (int i = 0; i < width; i++) {
		area[0][i] = '#';
		area[height - 1][i] = '#';
	}
	for (int i = 0; i < height; i++) {
		area[i][0] = '#';
		area[i][width - 1] = '#';
	}
}

void Sokoban::initMan() {
	int seed = 1;
	int x, y;
	while (true) {
		srand(seed);
		++seed;
		x = (rand() % (width - 1)) + 1;

		srand(seed);
		++seed;
		y = (rand() % (height - 1)) + 1;

		if (area[y][x] == '#') {
			continue;
		}
		area[y][x] = '*';
		break;
	}
}

void Sokoban::initWalls() {
	delete walls;
	int amount = (rand() % (width * height / 10 - 1)) + 1;
	std::cout << "rand wall count: " << amount << "\n";
	amount = 5;
	int x, y;
	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < amount; j++) {
			srand(i);
			x = (rand() % (width - 1)) + 1;

			srand(i + j);
			y = (rand() % (height - 1)) + 1;

			//std::cout << "rand wall point: " << x << " " << y << "\n";
			area[y][x] = '#';
		}
	}
}

void Sokoban::initBoxs() {
	int seed = 1;
	int x, y;
	int count = 1;
	while (true) {
		srand(seed);
		++seed;
		x = (rand() % (width - 1)) + 1;

		srand(seed);
		++seed;
		y = (rand() % (height - 1)) + 1;

		if (area[y][x] == '#' || area[y][x] == '*' || area[y][x] == '$') {
			continue;
		}
		area[y][x] = '$';
		++count;

		if (count > 5) {
			break;
		}
	}
}

void Sokoban::initTargets() {
	int seed = 1;
	int x, y;
	int count = 1;
	while (true) {
		srand(seed);
		++seed;
		x = (rand() % (width - 1)) + 1;

		srand(seed);
		++seed;
		y = (rand() % (height - 1)) + 1;

		if (area[y][x] == '#' || area[y][x] == '*' || area[y][x] == '$' || area[y][x] == '@') {
			continue;
		}
		area[y][x] = '@';
		++count;

		if (count > 5) {
			break;
		}
	}
}

void Sokoban::up() {
	int* pos = findMan();
	int manCurrentPos[2] = { *pos, *(pos + 1) };
	int manNextPos[2] = { (*manCurrentPos) - 1, *(manCurrentPos + 1) };
	//std::cout << *manCurrentPos << " " << *(manCurrentPos + 1) << std::endl;
	//std::cout << *manNextPos << " " << *(manNextPos + 1) << std::endl;
	if (area[manNextPos[0]][manNextPos[1]] == '$') {
		int boxNextPos[2] = { (*manNextPos) - 1, *(manNextPos + 1) };
		move(manNextPos, boxNextPos);
	}
	move(manCurrentPos, manNextPos);
}

void Sokoban::down() {
	int* pos = findMan();
	int manCurrentPos[2] = { *pos, *(pos + 1) };
	int manNextPos[2] = { (*manCurrentPos) + 1, *(manCurrentPos + 1) };
	//std::cout << *manCurrentPos << " " << *(manCurrentPos + 1) << std::endl;
	//std::cout << *manNextPos << " " << *(manNextPos + 1) << std::endl;
	if (area[manNextPos[0]][manNextPos[1]] == '$') {
		int boxNextPos[2] = { (*manNextPos) + 1, *(manNextPos + 1) };
		move(manNextPos, boxNextPos);
	}
	move(manCurrentPos, manNextPos);
}

void Sokoban::left() {
	int* pos = findMan();
	int manCurrentPos[2] = { *pos, *(pos + 1) };
	int manNextPos[2] = { (*manCurrentPos), *(manCurrentPos + 1) - 1};
	//std::cout << *manCurrentPos << " " << *(manCurrentPos + 1) << std::endl;
	//std::cout << *manNextPos << " " << *(manNextPos + 1) << std::endl;
	if (area[manNextPos[0]][manNextPos[1]] == '$') {
		int boxNextPos[2] = { (*manNextPos), *(manNextPos + 1) - 1};
		move(manNextPos, boxNextPos);
	}
	move(manCurrentPos, manNextPos);
}

void Sokoban::right() {
	int* pos = findMan();
	int manCurrentPos[2] = { *pos, *(pos + 1) };
	int manNextPos[2] = { (*manCurrentPos), *(manCurrentPos + 1) + 1 };
	//std::cout << *manCurrentPos << " " << *(manCurrentPos + 1) << std::endl;
	//std::cout << *manNextPos << " " << *(manNextPos + 1) << std::endl;
	if (area[manNextPos[0]][manNextPos[1]] == '$') {
		int boxNextPos[2] = { (*manNextPos), *(manNextPos + 1) + 1 };
		move(manNextPos, boxNextPos);
	}
	move(manCurrentPos, manNextPos);
}

int* Sokoban::findMan() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (area[j][i] == '*') {
				int position[2];
				position[0] = j;
				position[1] = i;
				return position;
			}
		}
	}
	return NULL;
}

void Sokoban::move(int* currentPos, int* nextPos) {
	if (*nextPos < 0 || *nextPos >= height) {
		return;
	}
	if (*(nextPos + 1) < 0 || *(nextPos + 1) >= width) {
		return;
	}
	if (area[*nextPos][*(nextPos + 1)] == '#') {
		return;
	}
	//std::cout << *currentPos << " " << *(currentPos + 1) << std::endl;
	//std::cout << *nextPos << " " << *(nextPos + 1) << std::endl;
	char c = area[*currentPos][*(currentPos + 1)];
	area[*currentPos][*(currentPos + 1)] = ' ';
	area[*nextPos][*(nextPos + 1)] = c;
}

bool Sokoban::isOver() {
	return false;
}
