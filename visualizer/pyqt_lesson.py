import numpy as np
from PyQt6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QTableWidget, QTableWidgetItem, QLabel
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QColor
from jadge import is_win

# 対戦データを管理するクラス
class Matchup:
    def __init__(self, match_id, array, p1, p2):
        self.match_id = match_id
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
            self.setRowHeight(row, 50)
            for col in range(cols):
                self.setColumnWidth(col, 50)
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

        self.horizontalHeader().setVisible(False)
        self.verticalHeader().setVisible(False)

# メインの画面
class ArrayVisualizer(QMainWindow):
    def __init__(self, matchup_list):
        super().__init__()
        self.setWindowTitle("Array Visualizer")
        self.setGeometry(0, 0, 800, 600)

        # メインウィジェットとレイアウトを作成
        self.main_widget = QWidget()
        self.layout = QVBoxLayout()

        # テーブルウィジェットを保存する辞書
        self.tables = {}

        # 初期表示
        for matchup in matchup_list.arrays:
            self.add_matchup_widget(matchup)

        self.main_widget.setLayout(self.layout)
        self.setCentralWidget(self.main_widget)

    def add_matchup_widget(self, matchup):
        """新しい対戦データのウィジェットを追加"""
        p1 = matchup.p1
        p2 = matchup.p2
        match_id=matchup.match_id

        # タイトルラベル
        title_label = QLabel(f"{p1} vs {p2}\nWinner: {is_win(matchup.array, p1, p2)} match_id: {match_id}")
        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(title_label)

        # テーブルウィジェット
        table = TableWidget(matchup.array)
        self.layout.addWidget(table)

        # テーブルを辞書に保存
        self.tables[matchup.match_id] = table

    def update_board(self, match_id, new_array):
        """既存のテーブルウィジェットを更新"""
        if match_id in self.tables:
            table = self.tables[match_id]
            rows, cols = new_array.shape
            for row in range(rows):
                for col in range(cols):
                    item = table.item(row, col)
                    item.setText(str(new_array[row, col]))

                    # 配列の値に基づいてセルの色を設定
                    if new_array[row, col] == '.':
                        item.setBackground(QColor(0, 0, 0))
                    elif new_array[row, col] == '#':
                        item.setBackground(QColor(177, 215, 250))
                    elif new_array[row, col] == '@':
                        item.setBackground(QColor(0, 255, 0))
