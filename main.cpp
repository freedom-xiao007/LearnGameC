// LearnGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <Sokoban.h>
#include <Snake.h>
#include <winnt.h>
#include <wincon.h>
#include <afxres.h>

HANDLE hOutput, hOutBuf;//控制台屏幕缓冲区句柄
COORD coord = {0, 0};
DWORD bytes = 0;

int main()
{
    hOutBuf = CreateConsoleScreenBuffer(
            GENERIC_WRITE,//定义进程可以往缓冲区写数据
            FILE_SHARE_WRITE,//定义缓冲区可共享写权限
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
    );
    hOutput = CreateConsoleScreenBuffer(
            GENERIC_WRITE,//定义进程可以往缓冲区写数据
            FILE_SHARE_WRITE,//定义缓冲区可共享写权限
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
    );
    //隐藏两个缓冲区的光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = -1;
    cci.dwSize = 0;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);

//    Snake snake = Snake(hOutput, hOutBuf, coord, bytes);

    std::cout << "请输出游戏对应的编号开始游戏!\n" << std::endl;
	std::cout << "1: 推箱子\n" << std::endl;
    std::cout << "2: 贪吃蛇\n" << std::endl;

	char input;
	std::cin >> input;
	if (input == '1') {
		Sokoban sokoban = Sokoban();
	}
	else if (input == '2') {
        Snake snake = Snake(hOutput, hOutBuf, coord, bytes);
	}
}


