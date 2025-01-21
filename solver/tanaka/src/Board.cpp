#include "Board.hpp"
#include "Solver.hpp"

using namespace std;



Board::Board(){
    board = vector< vector < int > > (BOARD_HEIGHT_SIZE, vector<int>(BOARD_WIDTH_SIZE, 0));
    legal_list = vector<bool> (BOARD_WIDTH_SIZE, true);
    is_first = true;
    is_first_win = false;
    is_draw = false;
}

void Board::display(){
    cout << endl;
    for (int i = 0;i<BOARD_HEIGHT_SIZE;i++)
    {
        for(int j = 0;j<BOARD_WIDTH_SIZE;j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}


void Board::show_align_piece()
{
    Solver solver;

    for(int i = 0;i<BOARD_HEIGHT_SIZE;i++)
    {
        for(int j = 0;j<BOARD_WIDTH_SIZE;j++)
        {
            cout << " 先手: "<<"x座標" << j << "y座標" << i << " : " << solver.count_align_piece(board, j, i, 1) << endl;
        }
    }
    cout << "############################################" << endl;
    for(int i = 0;i<BOARD_HEIGHT_SIZE;i++)
    {
        for(int j = 0;j<BOARD_WIDTH_SIZE;j++)
        {
            cout << " 後手: " << "x座標" << j << "y座標" << i << " : " << solver.count_align_piece(board, j, i, 2) << endl;
        }
    }
}




void Board::advance(int x)
{
    if(legal_list[x])
    {


        int i = 0;

        while(i < BOARD_HEIGHT_SIZE)
        {
            if(board[i][x] == 0)
            {
                i++;
            }
            else{
                break;
            }
        }

        if(is_first)
        {
            board[i-1][x] = FIRST;
        }
        else{
            board[i-1][x] = SECOND;
        }

        turn++;
        is_first = !is_first;
    }
    else
    {
        cout <<" この列に駒をおこません" << endl;
    }
}


vector<int>  Board::legal_action()
{
    vector<int> legal_pos;

    for(int j = 0;j<board[0].size();j++)
    {
        bool ch = true;
        for(int i = 0;i<board.size();i++)
        {
            if(board[i][j] == 0)
            {
                ch = false;
            }
        }

        if(ch)
        {
            legal_pos.push_back(j);
        }
    }

    return legal_pos;
}



vector<int> Board::take_four_vector(int dx, int dy, int sx, int sy)
{
    vector<int> four_vector;

    int x = sx;
    int y = sy;

    for(int i = 0;i<4;i++)
    {
        four_vector.push_back(board[y][x]);
        x+=dx;
        y+=dy;
    }

    return four_vector;
}


bool Board::is_end()
{
    for(int y = 0;y<BOARD_HEIGHT_SIZE;y++)
    {
        for(int x = 0;x<BOARD_WIDTH_SIZE;x++)
        {



            if(x+4 < BOARD_WIDTH_SIZE)
            {
                vector<int> four_vector = take_four_vector(1, 0, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(x-4 >= 0)
            {
                vector<int> four_vector = take_four_vector(-1, 0, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(y+4 < BOARD_HEIGHT_SIZE)
            {
                vector<int> four_vector = take_four_vector(0, 1, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(y-4 >= 0)
            {
                vector<int> four_vector = take_four_vector(0, -1, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(x+4 < BOARD_WIDTH_SIZE && y+4 < BOARD_HEIGHT_SIZE)
            {
                vector<int> four_vector = take_four_vector(1, 1, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(x+4 < BOARD_HEIGHT_SIZE && y-4 >= 0)
            {
                vector<int> four_vector = take_four_vector(1, -1, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(x-4 >= 0 && y+4 < BOARD_HEIGHT_SIZE)
            {
                vector<int> four_vector = take_four_vector(-1, 1, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }

            if(x-4 >= 0 && y-4 >= 0)
            {
                vector<int> four_vector = take_four_vector(-1, -1, x, y);

                if(is_all(four_vector))
                {
                    return true;
                }
            }


        }
    }

    return false;
}

bool Board::is_all(vector<int> array)
{
    for(int &i : array)
    {
        if(i == 0)
        {
            return false;
        }
    }
    return true;
}
