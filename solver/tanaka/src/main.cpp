#include "Board.hpp"

int main()
{
    Board board;


   while(true)
   {
        cout << "座標を入力してください。" ;
        int  x;
        cin >> x;
        board.advance(x);


        board.show_align_piece();

        board.display();

        if(board.is_end())
        {
            return 0;
        }
   }


}
