// LearnGame.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include <Sokoban.h>
#include <Snake.h>
#include <winnt.h>
#include <wincon.h>
#include <afxres.h>

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

//    Snake snake = Snake(hOutput, hOutBuf, coord, bytes);

    std::cout << "�������Ϸ��Ӧ�ı�ſ�ʼ��Ϸ!\n" << std::endl;
	std::cout << "1: ������\n" << std::endl;
    std::cout << "2: ̰����\n" << std::endl;

	char input;
	std::cin >> input;
	if (input == '1') {
		Sokoban sokoban = Sokoban();
	}
	else if (input == '2') {
        Snake snake = Snake(hOutput, hOutBuf, coord, bytes);
	}
}


