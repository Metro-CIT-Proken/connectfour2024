from threading import Timer
import random
import traceback
import sys

from game import *

class GameController:
    def __init__(self, first_player_id, second_player_id, match_id):
        self.game = Game()
        self.first_player_id = first_player_id
        self.second_player_id = second_player_id
        self.match_id = match_id
        self.next_position = dict[str, int]()
        self.update_timer: Timer = None
        self.update_handlers = list()

    #10秒ごとにupdate関数を実行するようにする。
    def _startUpdateTimer(self):
        self.update_timer = Timer(40.0, self.update)
        self.update_timer.daemon = True
        self.update_timer.start()

    #初期動作
    def start(self):
        self.game.print_board(sys.stderr)
        if self.update_timer and self.update_timer.is_alive:
            return
        self._startUpdateTimer()

    #駒を置く座標を指定する
    def setAction(self, player_id: str, pos: int):
        if player_id != self.first_player_id and player_id != self.second_player_id:
            raise ValueError("プレイヤーが存在しません")
        elif pos < 0 or pos >= self.game.width - 1:
            raise ValueError("座標外")

        self.next_position[player_id] = pos

    #盤面を更新（もし座標が指定されていなかったらランダムな座標にコマがおかれる）
    def update(self):
        try:
            if self.game.is_first:
                if not(self.first_player_id in self.next_position):
                    next_position = random.randint(0, self.game.width - 1)
                else:
                    next_position = self.next_position[self.first_player_id]
                    self.next_position.pop(self.first_player_id)
            else:
                if not(self.second_player_id in self.next_position):
                    next_position = random.randint(0, self.game.width - 1)
                else:
                    next_position = self.next_position[self.second_player_id]
                    self.next_position.pop(self.second_player_id)
            self.game.advance(next_position)
            self.game.print_board(sys.stderr)
            if not(self.game.is_end()):
                self._startUpdateTimer()

            for func in self.update_handlers:
                func(self)

        except Exception as E:
            print(traceback.format_exc(E))




