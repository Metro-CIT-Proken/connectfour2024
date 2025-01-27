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
        static const int EMPTY = 0;
        bool is_first;
        bool is_first_win;
        bool is_draw;
        int turn;

    public:
        Board();
        vector< pair<bool, int> > legal_list;
        vector<vector<int> > board;
        void display();
        void advance(int x);
        vector<int> take_four_vector(int dx, int dy, int sx , int sy);
        void update_legal_list();


        bool is_end();
        bool is_all(vector<int> array);
};
