#include "Solver.hpp"
#include "Board.hpp"

using namespace std;

Solver::Solver(){
    init_eva_board_one();
    init_eva_board_two();
}

int Solver::count_align_piece(Board board, int player, int x, int y)//(x,y)を視点に8方向の中で最大の揃ったコマを数える
{

    int board_h_size = board.board.size();
    int board_w_size = board.board[0].size();
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

                if(board.board[ny][nx] == player)
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

bool is_left(Board board)//駒が置けるか
{
    for(int i = 0;i<board.legal_list.size();i++)
    {
        if(board.legal_list[i].first == true)
        {
            return true;
        }
    }

    return false;
}

int Solver::minimax(Board board , int depth, bool is_ai , int x, int y)//評価から
{
    int score = evaluate(board, is_ai, x, y);

    cout << "score: "<< score << "x: "<< x << "y: "<< y<< endl;


    if(score == 160) return score-depth*2;
    else if(score == -160) return score+depth*2;
    if(!is_left(board)) return score;
    if(depth>=5) return score;

    if(is_ai)
    {
        int best = numeric_limits<int>::min();//intの中で最小の数

        for(int j = 0;j<board.legal_list.size();j++)
        {
            if(board.legal_list[j].first)
            {
                int i = board.legal_list[j].second;
                board.board[i][j] = AI;
                board.update_legal_list();
                best = max(best, minimax(board, depth+1 , false, j, i));
                board.board[i][j] = EMPTY;
                board.update_legal_list();
            }
        }

        return best;
    }
    else{
        int best = numeric_limits<int>::max();//intの中で最大の数

        for(int j = 0;j<board.legal_list.size();j++)
        {
            if(board.legal_list[j].first)
            {
                int i = board.legal_list[j].second;
                board.board[i][j] = PLAYER;
                board.update_legal_list();
                best = min(best, minimax(board, depth+1, true, j, i));
                board.board[i][j] = EMPTY;
                board.update_legal_list();
            }
        }
        return best;
    }
}


pair<int, int> Solver::search_best_pos(Board board)
{


    int best_val = numeric_limits<int>::min();

    pair<int, int> bestPos = make_pair(-1, -1);

    for(int j = 0;j<board.legal_list.size();j++)
    {
        if(board.legal_list[j].first)
        {
            int i = board.legal_list[j].second;
            if(board.board[i][j] == EMPTY)
            {
                board.board[i][j] = AI;
                board.update_legal_list();
                int move_val = minimax(board, 0, false, j, i);
                board.board[i][j] = EMPTY;
                board.update_legal_list();

                if(move_val > best_val)
                {
                    bestPos = make_pair(i, j);
                    best_val = move_val;
                }

            }
        }
    }

    cout << "best_val: " <<best_val << endl;
    return bestPos;

}






int Solver::evaluate(Board board, bool is_ai, int x, int y)
{
    int score = 0;
    if(board.legal_list[x].first)
    {
        if(is_ai)
        {
            if(count_align_piece(board, AI,  x,  y) == 3)
            {
                return 160;
            }
            else{
                score = count_align_piece(board, AI, x, y)*10+eva_board_one[y][x]*3+eva_board_two[y][x]*3;
                //+eva_board_one[y][x]*3+eva_board_two[y][x]*3
            }

        }
        else{
            if(count_align_piece(board, PLAYER, x, y) == 3)
            {
                return -160;
            }

            else{
                score = -1*(count_align_piece(board, PLAYER, x, y)*10)-eva_board_one[y][x]*3-eva_board_two[y][x]*3;
                //-eva_board_one[y][x]*3-eva_board_two[y][x]*3
            }
        }
    }

    return score;

}





