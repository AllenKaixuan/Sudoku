#ifndef SUDO_SOLVER_H
#define SUDO_SOLVER_H
#include "command.h"
#include "board.h"

class SudoSolver{
    private:
        int row_use_status[9];
        int column_use_status[9];
        int block_use_status[9];
        vector<Board> results;
        vector<pair<int, int>> spaces;
    public:
        void solve_sudo_games(const Command& command);
        void solve_sudo_game(Board board);
        void dfs_search(Board &board, int pos);
        void set_mark(int i, int j, int digit);
        void clearState();
        bool isAnswerUnique();
};

#endif