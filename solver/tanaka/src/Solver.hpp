#pragma once

#include<iostream>
#include<vector>
#include<string>
#include "Board.hpp"

using namespace std;

class Solver{
    private:
        static const int BOARD_WIDTH_SIZE = 7;
        static const int BOARD_HEIGHT_SIZE = 6;
        static const int PLAYER = 1;
        static const int AI = 2;
        static const int EMPTY = 0;
        pair<int, int>solve_pos=make_pair(-1, -1);
        vector< vector < int > > eva_board_one = vector< vector < int > > (7, vector<int> (6, 0));
        vector< vector < int > > eva_board_two = vector< vector < int > > (7, vector<int> (6, 0));




    public:
        Solver();
        pair<int, int> search_best_pos(Board board);
        int count_align_piece(Board board, int player, int x, int y);
        void update_legal_list_pos(Board board);
        int evaluate(Board board, bool is_ai, int x, int y);
        vector< vector < int > > advance(Board board);
        int minimax(Board board, int depth, bool is_ai, int x, int y);

        void init_eva_board_one()
        {
            for(int i = 0;i<eva_board_one.size();i++)
            {
                for(int j = 0;j<eva_board_one[0].size();j++)
                {
                    eva_board_one[i][j] = BOARD_HEIGHT_SIZE-i;
                }
            }
        }

        void init_eva_board_two()
        {
            for(int i = 0;i<eva_board_two.size();i++)
            {
                for(int j = 0;j<eva_board_two[0].size();j++)
                {
                    eva_board_two[i][j] = abs((j == BOARD_WIDTH_SIZE/2) ? BOARD_WIDTH_SIZE/2 : j%BOARD_WIDTH_SIZE);
                }
            }
        }





};
