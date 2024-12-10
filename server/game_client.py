import requests


from game_controller import *
from game import Game

def main():
    url = 'http://127.0.0.1:8432'

    # first_player_id = input("先手のプレイヤーID")
    # response = requests.post(url, json={'player': "first", "name":first_player_id})
    # if response.status_code == 200:
    #     print("サーバーの接続に成功しました。")
    # second_player_id = input("後手のプレイヤーID")
    # response = requests.post(url, json={'player': "second", "name":second_player_id})
    # if response.status_
    player_id = input("プレイヤーIDを入力してください")
    game_controller = GameController(first_player_id, second_player_id)
    game_controller.start()

    while(True):
        player_id = input("プレイヤーIDを入力してください")
        pos = int(input("場所を入力してください"))

        game_controller.setAction(player_id, pos)



if __name__ == '__main__':
    main()
