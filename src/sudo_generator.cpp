#include "sudo_generator.h"
#include "sudo_solver.h"
// #include "board.h"

extern ofstream f;

SudoGenerator::SudoGenerator(/* args */)
{
    
}

SudoGenerator::~SudoGenerator()
{
}


void row_or_col_change(Board &board, int src_x, int src_y, bool is_row_change)
{
        int rand_tmp = rand() % 2 + 1;
        int first_order[3] = {1, 2, 0};
        int second_order[3] = {2, 0, 1};
        if (rand_tmp == 2)
        {
            first_order[0] = 2;
            first_order[1] = 0;
            first_order[2] = 1;
            second_order[0] = 1;
            second_order[1] = 2;
            second_order[2] = 0;
        }
        for (int i = 0; i < 3; i++)
        {
            if (is_row_change)
            {
                board[src_x][i] = board[src_x + first_order[0]][src_y + i];
                board[src_x + 1][i] = board[src_x + first_order[1]][src_y + i];
                board[src_x + 2][i] = board[src_x + first_order[2]][src_y + i];
                board[src_x][i + 6] = board[src_x + second_order[0]][src_y + i];
                board[src_x + 1][i + 6] = board[src_x + second_order[1]][src_y + i];
                board[src_x + 2][i + 6] = board[src_x + second_order[2]][src_y + i];
            }
            else
            {
                board[i][src_y] = board[src_x + i][src_y + first_order[0]];
                board[i][src_y + 1] = board[src_x + i][src_y + first_order[1]];
                board[i][src_y + 2] = board[src_x + i][src_y + first_order[2]];
                board[i + 6][src_y] = board[src_x + i][src_y + second_order[0]];
                board[i + 6][src_y + 1] = board[src_x + i][src_y + second_order[1]];
                board[i + 6][src_y + 2] = board[src_x + i][src_y + second_order[2]];
            }
        }
 }

void SudoGenerator::generate_end_map(const Command& command){
    vector<Board> boards;
    for(int i = 0;i < command.endboard_number;i++){
        vector<vector<char> > board(9, vector<char>(9, '$'));
        vector<int> row = get_randOrder();
        for (int i = 0; i < 3; i++)
        {
            board[3][i + 3] = row[i] + '1';
            board[4][i + 3] = row[i + 3] + '1';
            board[5][i + 3] = row[i + 6] + '1';
        }
        row_or_col_change(board, 3, 3, true);
        row_or_col_change(board, 3, 3, false);
        row_or_col_change(board, 3, 0, false);
        row_or_col_change(board, 3, 6, false);
        boards.push_back(board);
    }
    f.open("../endmap.txt");
    write_to_file(boards,"th EndMap-----------");


}

int get_different_hard_level_dig_holes(int game_hard_level){
    int digHoles;
    switch (game_hard_level)
    {
    case 1:
        //25-34
        digHoles = rand()% 10 + 25;
        break;
    case 2:
        //35-44
        digHoles = rand()% 10 + 35;
        break;
    case 3:
        // 45-55
        digHoles = rand()% 11 + 45;
        break;
    default:
        //20-24
        digHoles = rand()% 5 + 20;
        break;
    }
    return digHoles;
}

void SudoGenerator::generate_sudo_game(const Command& command){
    int digHoles;
    SudoSolver solver = SudoSolver();
    vector<Board> boards;
    for(int i = 0; i < command.game_number;){
        if(command.hole_number!=0)
            digHoles = command.hole_number;
        else
            digHoles = get_different_hard_level_dig_holes(command.game_hard_level);
    
        vector<vector<char> > board(9, vector<char>(9, '$'));
        vector<int> row = get_randOrder();
        for (int i = 0; i < 3; i++)
        {
            board[3][i + 3] = row[i] + '1';
            board[4][i + 3] = row[i + 3] + '1';
            board[5][i + 3] = row[i + 6] + '1';
        }
        row_or_col_change(board, 3, 3, true);
        row_or_col_change(board, 3, 3, false);
        row_or_col_change(board, 3, 0, false);
        row_or_col_change(board, 3, 6, false);
        
        int digCount = digHoles;
        while (digHoles)
        {
            int x = rand() % 9;
            int y = rand() % 9;
            if (board[x][y] == '$')
                continue;
            char tmp = board[x][y];
            board[x][y] = '$';
            digHoles--;
        }
    if(command.is_unique){
        solver.solve_sudo_game(board); 
        if(solver.isAnswerUnique()){
             i++;
             boards.push_back(board);
        }
    }
    else{
        i++;
        boards.push_back(board);
    }
    }
  
    f.open("../sudogame.txt");
    write_to_file(boards,"th SudoGame-----------");
}