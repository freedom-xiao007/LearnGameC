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
    // 初始化数据
    void initData();
    // 将变化的数据写入,更新数据
    void draw();
    // 使用双缓冲显示
    void flush(HANDLE hOutBuf, HANDLE hOutput, COORD coord, DWORD bytes, bool buffSelect);
    // 从上方生成方块
    int createSquare();
    void createI();
    void createJ();
    void createL();
    void createO();
    void createS();
    void createZ();
    void createT();
    // 方块的移动处理
    void move(int action);
    // 碰撞检测
    bool collisionDetect(int x, int y);
    // 旋转
    void rotate();
    // 下降,不能下降时进行生成方块的重置和消除检测
    void down();
    // 左移
    void left();
    // 右移
    void right();
    // 获取系统当前时间戳
    long long getCurrentStamp();
    // 是否能进行消除检测
    void removeDetect();
    // 消除排满的方块
    void remove(int y);
    // 判断当前行是否能进行消除
    bool canRemove(int y);

    char baseSquare = '*';
    char wall = '#';
    char* squareTypes = "IJLOSZT";
    char** data;
    std::vector<int*> currentSquare;
    int center[2];
    int seed = 0;
    // 游戏地图的高和宽
    int height = 15;
    int width = 30;
};


#endif //GAME_TETRIS_H
