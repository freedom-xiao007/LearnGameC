// LearnGame.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include <winnt.h>
#include <wincon.h>
#include <afxres.h>

#include <Sokoban.h>
#include <Snake.h>
#include <Tetris.h>
#include <Cool.h>

HANDLE hOutput, hOutBuf;//����̨��Ļ���������
COORD coord = {0, 0};
DWORD bytes = 0;

int main()
{
    hOutBuf = CreateConsoleScreenBuffer(
            GENERIC_WRITE,//������̿�����������д����
            FILE_SHARE_WRITE,//���建�����ɹ���дȨ��
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
    );
    hOutput = CreateConsoleScreenBuffer(
            GENERIC_WRITE,//������̿�����������д����
            FILE_SHARE_WRITE,//���建�����ɹ���дȨ��
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
    );
    //���������������Ĺ��
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = -1;
    cci.dwSize = 0;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);

    std::cout << "�������Ϸ��Ӧ�ı�ſ�ʼ��Ϸ!\n" << std::endl;
    std::cout << "1: ������\n" << std::endl;
	std::cout << "2: ������\n" << std::endl;
    std::cout << "3: ̰����\n" << std::endl;
    std::cout << "4: ����˹����\n" << std::endl;

	char input;
	std::cin >> input;
	if (input == '1') {
        Cool cool = Cool();
	}
	else if (input == '2') {
        Sokoban sokoban = Sokoban(hOutput, hOutBuf, coord, bytes);
	}
    else if (input == '3') {
        Snake snake = Snake(hOutput, hOutBuf, coord, bytes);
    }
    else if (input == '4') {
        Tetris tetris = Tetris(hOutput, hOutBuf, coord, bytes);
    }

	system("pause");
    return 0;
}


