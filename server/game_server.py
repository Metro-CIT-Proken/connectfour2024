from flask import Flask, request, jsonify
from flask_socketio import SocketIO, emit
import json

from game_controller import GameController

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your_secret_key'
socketio = SocketIO(app)

games = list[GameController]()
games.append(GameController("player1", "player2"))
# games.append(GameController("player3", "player4"))

#一定時間ごとに盤面(二次元配列）を一方的に送信する
def handle_update_board(game: GameController):
    list_board = game.game.board_to_list()
    first_id = game.first_player_id
    second_id = game.second_player_id
    data = {"board":list_board, "first": first_id, "second": second_id }
    data = json.dumps(data)
    socketio.emit('board', data)

#ゲームの開始とアップデートをしたときに実行される関数の追加
for game in games:
    game.start()
    game.update_handlers.append(handle_update_board)

#複数の試合の中からプレイヤ-IDで試合を取得する
def getGame(player_id: str):
    for game in games:
        if game.first_player_id == player_id or game.second_player_id == player_id:
            return game

    return None

#プレイヤーIDから先手かを取得する
def isFirst(player_id: str):
    game = getGame(player_id)

    if game.first_player_id == player_id:
        return True
    else:
        return False

#自分のコマの場合'#'相手のコマの場合'@'に変換する
def convert_board(is_first: bool, list_board: list[list[int]]):
    for col in list_board:
        for i in range(len(col)):
            if is_first:
                if col[i] == 1:
                    col[i] = '#'
                elif col[i] == 2:
                    col[i] = '@'
            else:
                if col[i] == 1:
                    col[i] = '@'
                elif col[i] == 2:
                    col[i] = '#'
            if col[i] == 0:
                col[i] = '.'

#自分の駒を置く座標を提出する
@app.route('/submit', methods=['POST'])
def submit():
    player_id = request.args.get('token')
    choice_location = request.json.get('location')
    game = getGame(player_id)

    #プレイヤーIDから試合が取得できた場合
    if game != None:
        try:
            game.setAction(player_id, choice_location)
            return "成功しました"
        except ValueError as error:
            return str(error)

    else:
        return "ゲームが見つかりませんでした"

#自分の試合の盤面(二次元配列）を取得する
@app.route('/get', methods=['GET'])
def get():
    player_id = request.args.get('token')
    game = getGame(player_id)

    #プレイヤーIDから試合が取得できた場合
    if game != None:
        list_board = game.game.board_to_list()
        is_first = isFirst(player_id)
        convert_board(is_first, list_board)
        return jsonify({'board': list_board, 'width': game.game.width, 'height': game.game.height})

    #取得できなかった場合　
    return "ゲームが見つかりませんでした"

if __name__ == '__main__':
    app.run(port=8432, debug=True)
    # socketio.run(app, host="127.0.0.1", port=8432, debug=True)


