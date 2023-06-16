
#include <string.h>
#include "sudo_solver.h"
#include "command.h"

extern ofstream f;
  void SudoSolver::solve_sudo_games(const Command& command){
    vector<Board> boards = read_from_file(command.board_path);
    int count = 1;
    for(Board board : boards){
        solve_sudo_game(board);
        f.open("../answer.txt",ios::out|ios::app);
        f<<"-----------"<<count++<<"th Answers-----------"<<endl;
        write_to_file(results,"th Answer-----------");
    }

}



void SudoSolver::solve_sudo_game(Board board){
     clearState();
     for (int i = 0; i < 9; i++)
     {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '$')
            {
                spaces.push_back(pair<int, int>(i, j));
            }
            else
            {
                int digit = board[i][j] - '1';
                set_mark(i, j, digit);
            }
        }
     }
     dfs_search(board, 0);
    
}

void SudoSolver::set_mark(int i, int j, int digit)
{
    row_use_status[i] ^= (1 << digit);
    column_use_status[j] ^= (1 << digit);
    block_use_status[(i / 3) * 3 + j / 3] ^= (1 << digit);
}

void SudoSolver::clearState(){
     memset(row_use_status, 0, sizeof(row_use_status));
     memset(column_use_status, 0, sizeof(column_use_status));
     memset(block_use_status, 0, sizeof(block_use_status));
     spaces.clear();
     results.clear();
}

void SudoSolver::dfs_search(Board &board, int pos){
     if (pos == spaces.size())
        {
            results.push_back(board);
            return;
        }
        int i = spaces[pos].first;
        int j = spaces[pos].second;
        int unused_nums = ~(row_use_status[i] | column_use_status[j] | block_use_status[(i / 3) * 3 + j / 3]) & 0x1ff;
        int digit = 0;
        while (unused_nums)
        {
            if (unused_nums & 1)
            {
                set_mark(i, j, digit);
                board[i][j] = '1' + digit;
                dfs_search(board, pos + 1);
            }
            unused_nums = unused_nums >> 1;
            digit++;
        }
}

 bool SudoSolver::isAnswerUnique(){
    return results.size() ==1;
 }