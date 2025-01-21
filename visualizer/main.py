import socketio
import json
import numpy as np
from pyqt_lesson import Matchup, MatchupList, ArrayVisualizer  # 分割したクラスをインポート
import sys
from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QTimer, QObject, pyqtSignal, pyqtSlot
import threading

# Socket.IOクライアントの準備
sio = socketio.Client()
matchDict = {}

# PyQt 用の Signal/Slot クラス
class GuiUpdater(QObject):
    update_signal = pyqtSignal(dict)

    def __init__(self):
        super().__init__()

    @pyqtSlot(dict)
    def update_gui(self, board_data):
        try:
            match_id = board_data["match_id"]
            new_array=np.array(board_data["board"])
            first_player_id=board_data["first"]
            second_player_id=board_data["second"]
            if match_id in matchDict:
                # 既存の試合ウィジェットを更新
                matchDict[match_id].array=new_array
                visualizer.update_board(match_id,new_array)
            else:
                # 新しい試合ウィジェットを追加
                matchup = Matchup(
                    match_id,
                    new_array,
                    first_player_id,
                    second_player_id
                )
                matchup_list.add_matchup(matchup)
                matchDict[match_id]=matchup
                visualizer.add_matchup_widget(matchup)
        except Exception as e:
            print(f"Error updating GUI: {e}")

# サーバー接続用のスレッド関数
def sio_thread_function():
    sio.connect('http://127.0.0.1:8432')
    sio.wait()  # Socket.IO イベントループ

# グローバル変数のセットアップ
app = QApplication(sys.argv)
matchup_list = MatchupList()
visualizer = ArrayVisualizer(matchup_list)
gui_updater = GuiUpdater()

# Signal/Slotの接続
gui_updater.update_signal.connect(gui_updater.update_gui)

# サーバーからボードデータを受け取ったとき
@sio.on('board')
def on_server_data(data):
    try:
        print(f"Received board data: {data}")
        board_data = json.loads(data)
        gui_updater.update_signal.emit(board_data)  # GUI更新をメインスレッドに移動
    except Exception as e:
        print(f"Error processing server data: {e}")

# Socket.IO接続イベント
@sio.event
def connect():
    print("Connected to server")

@sio.event
def disconnect(reason=None):
    print("Disconnected from server")
    if reason:
        print(f"Disconnected because of: {reason}")

# Socket.IOのスレッドを開始
socket_thread = threading.Thread(target=sio_thread_function)
socket_thread.daemon = True
socket_thread.start()

# PyQt アプリケーションの初期化
visualizer.show()

# PyQt のタイマーを使用して非同期イベントを処理
timer = QTimer()
timer.timeout.connect(lambda: None)  # 空の関数（非同期処理を続けるため）
timer.start(100)  # 100ms 毎にタイマーを発火

# PyQt アプリケーションを開始
sys.exit(app.exec())  # アプリケーションのイベントループ開始
