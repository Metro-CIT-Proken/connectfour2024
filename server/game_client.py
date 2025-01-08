import socketio
import requests
import json

sio = socketio.Client()



stop_post = False

@sio.on('board')
def on_server_data(data):
    print(f"Received: {data}")

@sio.on('result')
def recieve_result(data):
    message = data["message"]
    print(message)

@sio.event
def connect():
    print("Success connect")

@sio.event
def disconnect():
    stop_post=True
    print("Success disconnect")

sio.connect('http://127.0.0.1:8432')



while(True):
    if stop_post:
        break

    player_id = input("プレイヤーIDを決めてください: ")#プレイヤー名

    try:
        x = int(input("座標を入力してください: "))#置く座標
        if(x < 0 and x > 6):
            raise ValueError

    except ValueError as error:
        print("座標は正の整数にしてください" + str(error))

    json_data = {"location": str(x), "player": player_id}
    # json_data = json.dumps(json_data)

    response = requests.post(f'http://127.0.0.1:8432/submit',json=json_data)#サーバーにPOSTする
    if response.status_code == 200:
        print("POSTに成功しました")
    else:
        print(f"エラーが発生しました {response.status_code}")

sio.wait()
