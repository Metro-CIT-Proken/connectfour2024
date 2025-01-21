#pragma once

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Solver{
    private:
        static const int BOARD_WIDTH_SIZE = 7;
        static const int BOARD_HEIGHT_SIZE = 6;
        vector<int> legal_list_pos= vector<int>(7, -1);
        pair<int, int>solve_pos=make_pair(-1, -1);

    public:
        pair<int, int> solve(vector< vector < int > > board);
        int count_align_piece(vector< vector < int > > board, int x, int y,int player);
        void update_legal_list_pos(vector< vector < int > >);

};
