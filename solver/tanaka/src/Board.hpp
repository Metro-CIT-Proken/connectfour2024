#pragma once

#include<iostream>
#include<vector>
#include<string>

using namespace std;


class Board{
    private:
        static const int BOARD_WIDTH_SIZE = 7;
        static const int BOARD_HEIGHT_SIZE = 6;
        static const int FIRST = 1;
        static const int SECOND = 2;
        vector<vector<int> > board;
        vector<bool> legal_list;
        bool is_first;
        bool is_first_win;
        bool is_draw;
        int turn;

    public:
        Board();
        void show_align_piece();
        void display();
        void advance(int x);
        vector<int> legal_action();
        vector<int> take_four_vector(int dx, int dy, int sx , int sy);


        bool is_end();
        bool is_all(vector<int> array);
};
