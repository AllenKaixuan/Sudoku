
#ifndef _BOOARD_
#define _BOOARD_

#include<vector>
#include<time.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
using namespace std;
typedef vector<vector<char>> Board;
vector<int> get_randOrder();
void write_to_file(vector<Board> boards, string sign_statement);
vector<Board> read_from_file(string file_path);
void print_board(Board& board);

#endif

