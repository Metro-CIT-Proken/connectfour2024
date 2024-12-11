import socketio

sio = socketio.Client()

@sio.on('board')
def on_server_data(data):
    print(f"Received: {data}")

# @sio.event
# def connect():
#     print("Success connect")

# @sio.event
# def disconnect():
#     print("Success disconnect")

sio.connect('ws://localhost:8432')
sio.wait()
