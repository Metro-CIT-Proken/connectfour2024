#include "Board.hpp"

using namespace std;



Board::Board(){
    board = vector< vector < int > > (BOARD_HEIGHT_SIZE, vector<int>(BOARD_WIDTH_SIZE, 0));
    legal_list = vector<pair<bool,int> > (BOARD_WIDTH_SIZE, make_pair(true, 0));
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







void Board::advance(int x)
{
    update_legal_list();


    if(legal_list[x].first)
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

        if(i == 0)
        {
            cout << "コマが置けません" << endl;
            return;
        }


        if(is_first)
        {

            board[i-1][x] = FIRST;
        }
        else{
            board[i-1][x] = SECOND;
        }

        cout << 999 << endl;


        update_legal_list();
        turn++;
        is_first = !is_first;



    }
    else
    {
        cout <<" この列に駒をおこません" << endl;
    }
}

void Board::update_legal_list()
{
    for(int j = 0;j<BOARD_WIDTH_SIZE;j++)
    {
        int i = 0;
        while(i < BOARD_HEIGHT_SIZE)
        {
            if(board[i][j] == 0)
            {
                i++;
            }
            else{
                break;
            }
        }

        if(i == 0)
        {
            legal_list[j] = make_pair(false, -1);
        }
        else{
            legal_list[j] = make_pair(true, i-1);
        }
    }


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
    bool ch = true;
    for(int &i : array)
    {

        if(i != FIRST)
        {
            ch = false;
        }
    }

    if(ch){
        is_first_win = true;
        return true;
    }

    ch = true;
    for(int &i : array)
    {
        if(i != SECOND)
        {
            ch = false;
        }
    }

    if(ch) {
        return true;
    }

    return false;

}
