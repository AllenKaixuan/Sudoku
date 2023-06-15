#include<iostream>
#include "command.h"

void Command::show(){
    if(is_create){
        cout<<"创建"<<endboard_number<<"个终局游戏"<<endl;
    }
    else if(is_solve){
        cout<<"解决"<<board_path<<"路径下的棋盘的游戏"<<endl;
    }
    else {
        if(game_number!=0){
            cout<<"需要的游戏数量为"<<game_number<<endl;
        }
        if(game_hard_level!=0){
            cout<<"游戏难度为"<<game_hard_level<<endl;
        }
        if(hole_number!=0){
            cout<<"游戏中挖空的数量"<<hole_number<<endl;
        }
        if(is_unique){
            cout<<"生成的游戏的解唯一"<<endl;
        }
    }
}
