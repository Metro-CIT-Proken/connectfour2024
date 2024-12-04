import sys
import numpy as np
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QTableWidget, QTableWidgetItem, QLabel
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor

# 対戦データを管理するクラス
class Matchup:
    def __init__(self, array, p1, p2):
        self.array = array
        self.p1 = p1
        self.p2 = p2

# 複数の対戦データを管理するクラス
class MatchupList:
    def __init__(self):
        self.arrays = []

    def add_matchup(self, matchup):
        self.arrays.append(matchup)

# テーブルの画面、配列を受け取る
class TableWidget(QTableWidget):
    def __init__(self, array):
        super().__init__(array.shape[0], array.shape[1])
        rows, cols = array.shape
        for row in range(rows):
            self.setRowHeight(row, 40)  # 行の高さを設定
            for col in range(cols):
                self.setColumnWidth(col, 80)  # 列の幅を設定
                item = QTableWidgetItem(str(array[row, col]))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)

                # 配列の値に基づいてセルの色を設定
                if array[row, col] == '.':
                    item.setBackground(QColor(0, 0, 0))
                elif array[row, col] == '#':
                    item.setBackground(QColor(177, 215, 250))
                elif array[row, col] == '@':
                    item.setBackground(QColor(0, 255, 0))
                self.setItem(row, col, item)

        # ヘッダーラベルの非表示設定
        self.horizontalHeader().setVisible(False)
        self.verticalHeader().setVisible(False)

# メインの画面
class ArrayVisualizer(QMainWindow):
    def __init__(self, matchup_list):
        super().__init__()
        self.setWindowTitle("Array Visualizer")
        self.setGeometry(0, 0, 800, 600)

        # メインウィジェットとレイアウトを作成
        main_widget = QWidget()
        layout = QVBoxLayout()

        # 複数の配列を表示するためにテーブルを生成してレイアウトに追加
        for matchup in matchup_list.arrays:
            p1 = matchup.p1
            p2 = matchup.p2
            title_label = QLabel(f"{p1} vs {p2}")
            title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)  # タイトルを中央揃え
            layout.addWidget(title_label)

            table = TableWidget(matchup.array)
            layout.addWidget(table)

        main_widget.setLayout(layout)
        self.setCentralWidget(main_widget)

# numpy配列を生成（例：異なる配列を用意）
array0 = np.array([
    [0, 1, 0, 1],
    [1, 0, 1, 0],
    [0, 1, 0, 1],
    [1, 0, 1, 0]
])
array1 = np.array([
    [0, 1, 0, 1],
    [1, 0, 1, 0]
])
array2 = np.array([
    [1, 1, 0, 0],
    [0, 1, 1, 0]
])

# 対戦データを作成
matchup_list = MatchupList()
matchup_list.add_matchup(Matchup(array0, "Alice", "Bob"))
matchup_list.add_matchup(Matchup(array1, "Charlie", "Dana"))
matchup_list.add_matchup(Matchup(array2, "Eve", "Frank"))

# PyQtアプリケーションを実行
app = QApplication(sys.argv)
window = ArrayVisualizer(matchup_list)  # matchup_listを渡す
window.show()
sys.exit(app.exec())
