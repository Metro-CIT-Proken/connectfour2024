import numpy as np
import sys

FIRST = 1
SECOND = 2


class Game:
    def __init__(self):
        self.width = 7
        self.height = 6
        self.board = np.zeros([self.height, self.width], int)
        self.turn = 0
        self.is_first = True
        self.is_first_win = False
        self.is_draw = False
        self.legal_list = np.full(self.width, True, bool)



    def advance(self, x):

        if len(self.board) != 6 or len(self.board[0]) != 7 :
            print("ボードの幅、高さが合っていません")
            raise ValueError

        if self.legal_list[x]:
            vertical_array = self.board[:,x]
            i = 0
            while vertical_array[i] == 0 :
                i+=1
                if i == self.height:
                    break
            if self.is_first:#先手
                vertical_array[i-1] = FIRST
            else:#後手
                vertical_array[i-1] = SECOND

            self.turn+=1
            self.is_first = not(self.is_first)
            return self.board


        else:
            print("この列に駒を置けません")
            return None

    def legal_action(self):
        legal_pos = list[list]()
        for i in range(self.width):
            vertical_array = self.board[:, i]
            if not np.any(vertical_array == 0):
                legal_pos.append(i)
        return legal_pos

    def is_end(self):
        if len(self.board) != 6 or len(self.board[0]) != 7 :
            print("ボードの幅、高さが合っていません")
            raise ValueError

        for y in range(self.height):
            for x in range(self.width):
                #右方向
                beside_array = self.board[y]
                if x+4 <= self.width:
                    four_array = beside_array[x:x+4]
                    if self.is_all(four_array):
                        return True

                #左方向
                beside_array = self.board[y]
                if x-4 >= 0:

                    four_array = beside_array[x-4:x]
                    if self.is_all(four_array):
                        return True
                #下方向
                vertical_array = self.board[:, x]

                if y + 4 <= self.height:

                    four_array = vertical_array[y:y+4]
                    if self.is_all(four_array):
                        return True

                vertical_array = self.board[:, x]
                #上方向
                if y - 4 >= 0:
                    four_array = vertical_array[y-4:y]
                    if self.is_all(four_array):
                        return  True

                #右上方向
                top_right_array = np.flipud(self.board[:y+1, x:]).diagonal()
                if len(top_right_array) >= 4:

                    four_array = top_right_array[0:4]
                    if self.is_all(four_array):
                        return True

                #右下方向
                bottom_right_array = self.board[y:, x:].diagonal()
                if len(bottom_right_array) >= 4:
                    four_array = bottom_right_array[0:4]
                    if self.is_all(four_array):
                        return True

                #左上方向
                up_left_array = np.flipud(np.fliplr(self.board[:y+1, :x+1])).diagonal()
                if len(up_left_array) >= 4:
                    four_array = up_left_array[0:4]
                    if self.is_all(four_array):
                        return True


                #左下方向
                bottom_left_array = np.fliplr(self.board[y:, :x+1]).diagonal()
                if len(bottom_left_array) >= 4:
                    four_array = bottom_left_array[0:4]
                    if self.is_all(four_array):
                        return True
        if np.all(self.legal_list==False):
            return  True
        return False

    def is_all(self,array):
        if not(isinstance(array, np.ndarray)):
            print("配列はndarray型である必要があります。")
            raise TypeError

        if np.all(array == FIRST):
            self.is_first_win = True
            return True
        elif np.all(array == SECOND):
            return True
        else:
            self.is_draw = True
            return False


    def print_board(self, output=sys.stdout):
        print("================", file=output, flush=True)
        for i in self.board:
            for e in i:
                print(e, end=' ', file=output, flush=True)
            print(file=output, flush=True)
        print("================", file=output, flush=True)



    def main(self):
        while(True):
            x = int(input())
            if type(x) != int:
                print("座標は整数で入力してください")
                raise ValueError
            self.advance(x)

            self.print_board()
            if self.is_end():
                break

            self.legal_action()
        self.end()

    def end(self):
        if self.is_first_win:
            print("先手が勝利しました")
        elif self.is_draw:
            print("引き分けです")
        else:
            print("後手が勝利しました")

    def board_to_list(self):
        list_board = self.board.tolist()
        return list_board
