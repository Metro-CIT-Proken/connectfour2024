import socketio

sio = socketio.Client()

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
    print("Success disconnect")

sio.connect('http://127.0.0.1:8432')
sio.wait()
