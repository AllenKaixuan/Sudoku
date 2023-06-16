#include<cstring>
#include "board.h"

ofstream f;

void print_board(Board& board){

    for(int i = 0 ; i < board.size();i++){
        for(int j=0; j<board[i].size();j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    cout<<"-----------------"<<endl;
}

vector<int> get_randOrder()
{   
    vector<int> order;
    bool sign[9];
    for(int i = 0; i < 9; i++){
        sign[i] = false;
    }
    while (order.size() != 9)
    {
        int num = rand() % 9;
        if (sign[num])
        {
            continue;
        }
        else
        {
            order.push_back(num);
            sign[num] = true;
        }
    }

    return order;
}

void write_to_file(vector<Board> boards, string sign_statement){
   
    for(int k = 0; k < boards.size(); k++){
        f<<"-----------the "<<k+1<<sign_statement<<endl;
        for(int i = 0; i < boards[k].size(); i++){
            for(int j = 0; j<boards[k][i].size(); j++){
                f << boards[k][i][j];
            }
            f << endl;
        }
    }
    f.close();

}

vector<Board> read_from_file(string file_path){
    ifstream infile;
    vector<Board> boards;
    infile.open(file_path);
    char data[100];
    Board board;
    vector<char> row;
    while (!infile.eof())
    {
        infile.getline(data, 100);
        if (data[0] == '-')
        {   
            if(board.size() > 0)
            boards.push_back(board);
            board.clear();
            continue;
        }
        for (int i = 0; i < strlen(data); i++)
        {
            if (('1' <= data[i] && data[i] <= '9') || data[i] == '$')
            {
                row.push_back(data[i]);
            }
        }
        board.push_back(row);
        row.clear();
    }
    boards.push_back(Board(board));
    infile.close();
    return boards;
}