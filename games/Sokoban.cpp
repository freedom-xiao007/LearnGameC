#include "../include/Sokoban.h"
#include<iostream>
#include<time.h>
#include<conio.h>
#include <winnt.h>

Sokoban::Sokoban(void *pVoid, void *pVoid1, _COORD coord, unsigned long bytes) {
    HANDLE hOutBuf = static_cast<HANDLE>(pVoid);
    HANDLE hOutput = static_cast<HANDLE>(pVoid1);
    SMALL_RECT rc = {0, 0, 30, 15};
    SetConsoleWindowInfo(hOutBuf, true, &rc);
    SetConsoleWindowInfo(hOutput, true, &rc);

	successCount = 0;
	seed = time(NULL);
	width = 30;
	height = 15;
	wallAmount = 10;

	initArea();
	initWalls();
	initMan();
	initBoxs();
	initTargets();
	redraw();

    bool buffSelect = true;
	while (true) {
		if(!controller()) {
            break;
		}
		if (isOver()) {
            for (int i = 0; i < height; i++) {
                coord.Y = i;
                WriteConsoleOutputCharacterA(hOutBuf, area[i], width, coord, &bytes);
            }
            char* over = "!!!!!!GOOD!!!!!!";
            WriteConsoleOutputCharacterA(hOutBuf, over, 21, coord, &bytes);
            SetConsoleActiveScreenBuffer(hOutBuf);
            continue;
		}

        if (buffSelect) {
            for (int i = 0; i < height; i++) {
                coord.Y = i;
                WriteConsoleOutputCharacterA(hOutBuf, area[i], width, coord, &bytes);
            }

            SetConsoleActiveScreenBuffer(hOutBuf);
            buffSelect = false;
        }
        else {
            for (int i = 0; i < height; i++) {
                coord.Y = i;
                WriteConsoleOutputCharacterA(hOutput, area[i], width, coord, &bytes);
            }

            SetConsoleActiveScreenBuffer(hOutput);
            buffSelect = true;
        }
	}

}

void Sokoban::redraw() {
	system("cls");
	std:: cout << "障碍物：# 主角：* 箱子：$ 目的地：@ 箱子+目的地：! 人物+目的地: R" << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << area[i][j];
		}
		std::cout << std::endl;
	}
}

bool Sokoban::controller() {
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
	else if (input == 27) {
        return false;
	}
//	redraw();
    return true;
}

void Sokoban::initArea() {
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
	std::cout << "Initing man!\n";
	int* position = createRandPosition();
	area[*position][*(position + 1)] = '*';
}

void Sokoban::initWalls() {
	std::cout << "Initing wall!\n";
	int* position = NULL;
	for (int i = 0; i < wallAmount; i++) {
		position = createRandPosition();
		area[*position][*(position + 1)] = '#';
	}
}

void Sokoban::initBoxs() {
	std::cout << "Initing box!\n";
	int* position = NULL;
	for (int i = 0; i < boxAmount; i++) {
		position = createRandBoxPosition();
		area[*position][*(position + 1)] = '$';
	}
}

void Sokoban::initTargets() {
	std::cout << "Initing target!\n";
	int* position = NULL;
	for (int i = 0; i < boxAmount; i++) {
		position = createRandPosition();
		area[*position][*(position + 1)] = '@';
	}
}

int* Sokoban::createRandPosition() {
	int x, y;
	while (true) {
		++seed;
		srand(seed);
		x = (rand() % (width - 1)) + 1;

		++seed;
		srand(seed);
		y = (rand() % (height - 1)) + 1;

		if (area[y][x] == ' ') {
			int* position = new int[2];
			position[0] = y;
			position[1] = x;
			return position;
		}
	}
}

int* Sokoban::createRandBoxPosition() {
	int x, y;
	while (true) {
		++seed;
		srand(seed);
		x = (rand() % (width - 4)) + 2;

		++seed;
		srand(seed);
		y = (rand() % (height - 4)) + 2;

		if (area[y][x] == ' ') {
            int* position = new int[2];
            position[0] = y;
            position[1] = x;
            return position;
		}
	}
}

void Sokoban::up() {
	int* pos = findMan();
	int manCurrentPos[2] = { *pos, *(pos + 1) };
	int manNextPos[2] = { (*manCurrentPos) - 1, *(manCurrentPos + 1) };
	//std::cout << *manCurrentPos << " " << *(manCurrentPos + 1) << std::endl;
	//std::cout << *manNextPos << " " << *(manNextPos + 1) << std::endl;
	if (area[manNextPos[0]][manNextPos[1]] == '$' || area[manNextPos[0]][manNextPos[1]] == '!') {
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
	if (area[manNextPos[0]][manNextPos[1]] == '$' || area[manNextPos[0]][manNextPos[1]] == '!') {
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
	if (area[manNextPos[0]][manNextPos[1]] == '$' || area[manNextPos[0]][manNextPos[1]] == '!') {
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
	if (area[manNextPos[0]][manNextPos[1]] == '$' || area[manNextPos[0]][manNextPos[1]] == '!') {
		int boxNextPos[2] = { (*manNextPos), *(manNextPos + 1) + 1 };
		move(manNextPos, boxNextPos);
	}
	move(manCurrentPos, manNextPos);
}

int* Sokoban::findMan() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (area[j][i] == '*' || area[j][i] == 'R') {
				int* position = new int[2];
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
	if (area[*nextPos][*(nextPos + 1)] == '#' || area[*nextPos][*(nextPos + 1)] == '$') {
		return;
	}
	//std::cout << *currentPos << " " << *(currentPos + 1) << std::endl;
	//std::cout << *nextPos << " " << *(nextPos + 1) << std::endl;
	char current = area[*currentPos][*(currentPos + 1)];
	char next = area[*nextPos][*(nextPos + 1)];
	if (current == '$' && next == '@') {
		area[*currentPos][*(currentPos + 1)] = ' ';
		area[*nextPos][*(nextPos + 1)] = '!';
		++successCount;
	}
	else if (current == '*' && next == '!') {
		area[*currentPos][*(currentPos + 1)] = ' ';
		area[*nextPos][*(nextPos + 1)] = 'R';
	}
	else if (current == '!' && next == ' ') {
		area[*currentPos][*(currentPos + 1)] = '@';
		area[*nextPos][*(nextPos + 1)] = '$';
		--successCount;
	}
	else if (current == 'R' && next == ' ') {
		area[*currentPos][*(currentPos + 1)] = '@';
		area[*nextPos][*(nextPos + 1)] = '*';
	}
	else if (current == '*' && next == '@') {
		area[*currentPos][*(currentPos + 1)] = ' ';
		area[*nextPos][*(nextPos + 1)] = 'R';
	}
	else {
		area[*currentPos][*(currentPos + 1)] = ' ';
		area[*nextPos][*(nextPos + 1)] = current;
	}
}

bool Sokoban::isOver() {
	if (successCount >= boxAmount) {
		return true;
	}
	return false;
}
