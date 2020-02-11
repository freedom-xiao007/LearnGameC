//
// Created by Administrator on 2020/2/11.
//

#ifndef GAME_TETRIS_H
#define GAME_TETRIS_H


#include <string>
#include <deque>
#include <vector>

class Tetris {
public:
    Tetris(HANDLE pVoid, HANDLE pVoid1, COORD coord, DWORD bytes);

private:
    // ��ʼ������
    void initData();
    // ���仯������д��,��������
    void draw();
    // ʹ��˫������ʾ
    void flush(HANDLE hOutBuf, HANDLE hOutput, COORD coord, DWORD bytes, bool buffSelect);
    // ���Ϸ����ɷ���
    int createSquare();
    void createI();
    void createJ();
    void createL();
    void createO();
    void createS();
    void createZ();
    void createT();
    // ������ƶ�����
    void move(int action);
    // ��ײ���
    bool collisionDetect(int x, int y);
    // ��ת
    void rotate();
    // �½�,�����½�ʱ�������ɷ�������ú��������
    void down();
    // ����
    void left();
    // ����
    void right();
    // ��ȡϵͳ��ǰʱ���
    long long getCurrentStamp();
    // �Ƿ��ܽ����������
    void removeDetect();
    // ���������ķ���
    void remove(int y);
    // �жϵ�ǰ���Ƿ��ܽ�������
    bool canRemove(int y);

    char baseSquare = '*';
    char wall = '#';
    char* squareTypes = "IJLOSZT";
    char** data;
    std::vector<int*> currentSquare;
    int center[2];
    int seed = 0;
    // ��Ϸ��ͼ�ĸߺͿ�
    int height = 15;
    int width = 30;
};


#endif //GAME_TETRIS_H
