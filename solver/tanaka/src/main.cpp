#include "Board.hpp"
#include "Solver.hpp"

// void show_align_piece(Board board, Solver solver)
// {

//     cout << "先手: " << solver.count_align_piece(board, 1) << endl;
//     cout << "後手: " << solver.count_align_piece(board, 2) << endl;

// }

int main()
{
    Board board;
    Solver solver;




   while(true)
   {
        cout << "座標を入力してください。" ;
        int  x;
        cin >> x;
        board.advance(x);



        pair<int, int > bestPos = solver.search_best_pos(board);

        cout << "y: " <<  bestPos.first << "x: " << bestPos.second << endl;



        board.display();

        board.advance(bestPos.second);

        board.display();

        vector<vector < int > > score_board = vector< vector < int > > (6, vector<int> (7,0));

        for(int j = 0;j<board.legal_list.size();j++)
        {
            if(board.legal_list[j].first)
            {
                int i = board.legal_list[j].second;
                score_board[i][j] = solver.count_align_piece(board, 2, j, i);
            }
        }

        cout << "後手" << endl;

        for(int i = 0;i<6;i++)
        {
            for(int j = 0;j<7;j++)
            {
                cout << score_board[i][j] << " ";
            }
            cout << endl;
        }

        score_board = vector< vector < int > > (6, vector<int> (7,0));


        cout << "先手" << endl;

        for(int j = 0;j<board.legal_list.size();j++)
        {
            if(board.legal_list[j].first)
            {
                int i = board.legal_list[j].second;
                score_board[i][j] = solver.count_align_piece(board, 1, j , i);
            }
        }

        for(int i = 0;i<6;i++)
        {
            for(int j = 0;j<7;j++)
            {
                cout << score_board[i][j] << " ";
            }
            cout << endl;
        }


        if(board.is_end())
        {
            return 0;
        }
   }


}


