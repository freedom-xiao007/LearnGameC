//
// Created by Administrator on 2020/2/10.
//

#include <afxres.h>
#include <conio.h>
#include <deque>
#include "Cool.h"

Cool::Cool() {
    system("mode con cols=100 lines=30"); //cols为控制台的宽度，lines则代表控制台的高度。
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    int height = 30;
    int width = 100;

    std::deque<char*> deque;

    HANDLE handle;
    COORD pos;
    int key;
    char* str = "    1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM                                   ";
    while(true) {
        if(kbhit()) {
            key = _getch();
            if (key == 27) {
                break;
            }
        }

        deque.push_front(creatString(width, str));
        if(deque.size() > height) {
            deque.pop_back();
        }

        for (int i = 0; i < deque.size(); i++) {
            for(int j = 0; j < width; j++) {
                handle = GetStdHandle(STD_OUTPUT_HANDLE);
                pos.X = j;
                pos.Y = i;
                SetConsoleCursorPosition(handle, pos);
                putchar(deque[i][j]);
            }
        }
    }
}

char *Cool::creatString(int width, char* str) {
    char* s = new char[width];
    int amount = strlen(str);
    for(int i = 0; i < width; i++) {
        srand(seed);
        s[i] = str[(rand() % (amount - 1)) + 1];
        ++seed;
        if(i % 2 == 0) {
            s[i] = ' ';
        }
        if(i % 3 == 0) {
            s[i] = ' ';
        }
        if(i % 5 == 0) {
            s[i] = ' ';
        }
    }
    return s;
}
