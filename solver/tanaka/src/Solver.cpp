#include "Solver.hpp"

using namespace std;

void Solver::update_legal_list_pos(vector< vector < int > > board)//置けるコマの座標
{

    for(int i = 0;i<BOARD_WIDTH_SIZE;i++)
    {
        int y = -1;
        for(int j = 0;j<BOARD_HEIGHT_SIZE;j++)
        {
            if(board[j][i] != 0)
            {
                y = j-1;
                break;
            }

        }
        legal_list_pos[i] = y;
    }
}

int Solver::count_align_piece(vector< vector < int > > board,int x, int y, int player)//(x,y)を視点に8方向の中で最大の揃ったコマを数える
{
    int board_h_size = board.size();
    int board_w_size = board[0].size();
    int max_count = 0;

    for(int dy=-1;dy<=1;dy++)
    {
        for(int dx=-1;dx<=1;dx++)
        {
            if(dx == 0 && dy == 0)
            {
                continue;
            }
            int count = 0;
            int nx = x;
            int ny = y;

            nx+=dx;
            ny+=dy;
            while(nx >= 0 && nx < board_w_size && ny >= 0 && ny < board_h_size )
            {

                if(board[ny][nx] == player)
                {
                    count++;
                }

                else{
                    break;
                }
                nx+=dx;
                ny+=dy;
            }

            max_count = max(max_count, count);
        }

    }

    return max_count;
}

pair<int, int> solve(vector< vector < int > > board)
{
    
}
