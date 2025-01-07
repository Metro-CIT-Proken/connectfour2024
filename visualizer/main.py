import socketio
import json
import requests
import numpy as np
from pyqt_lesson import Matchup,MatchupList,TableWidget,ArrayVisualizer
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QTableWidget, QTableWidgetItem, QLabel
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor

sio = socketio.Client() # グローバル変数の初期化

@sio.event
def connect():
    print("Success connect")

@sio.event
def disconnect(reason=None):
    print("Success disconnect")
    if reason:
        print(f"Disconnected because of: {reason}")

@sio.on('board')
def on_board(data):
    print(f"Received board data:{data}")
    board_data = json.loads(data)
    print("Parsed board data:", board_data)
    if board_data:
        app = QApplication(sys.argv)
        matchup_list = MatchupList()
        matchup_list.add_matchup(Matchup(np.array(board_data["board"]), board_data["first"], board_data["second"]))
        window = ArrayVisualizer(matchup_list)
        window.show()
        sys.exit(app.exec())



# サーバーに接続
sio.connect('http://127.0.0.1:8432')
sio.emit('test_event',{'message':'Hello ,Server!'})
sio.wait()
