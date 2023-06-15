#ifndef COMMAND
#define COMMAND

#include<string>
using namespace std;
class Command{
public:
    //创建数独终盘
    bool is_create;
    int endboard_number;

    //解棋盘
    bool is_solve;
    string board_path;

    //需要的游戏数量(数独盘面的个数)
    int game_number;

    //生成游戏的难度(反映在数独挖洞个数)
    int game_hard_level;

    //生成游戏中挖空的数量
    int hole_number;

    //生成游戏的解是否唯一
    bool is_unique;

    void show();

};

#endif