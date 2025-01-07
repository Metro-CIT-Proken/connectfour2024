import numpy as np

def is_win(field, player1, player2):
    count_dot=0
    # フィールドのサイズを取得
    rows, cols = field.shape
    for i in range(field.shape[0]):
        for j in range(field.shape[1]):
            if(field[i][j]=='.'):
                count_dot+=1
            
    
    # 勝利条件をチェックする関数
    def check_winner(symbol):
        # 横方向
        for i in range(rows):
            for j in range(cols - 3):  # 横に4つ見る
                if np.all(field[i, j:j+4] == symbol):
                    return True
        
        # 縦方向
        for i in range(rows - 3):  # 縦に4つ見る
            for j in range(cols):
                if np.all(field[i:i+4, j] == symbol):
                    return True
        
        # 右下がりの斜め方向
        for i in range(rows - 3):
            for j in range(cols - 3):
                if np.all([field[i+k, j+k] == symbol for k in range(4)]):
                    return True
        
        # 左下がりの斜め方向
        for i in range(rows - 3):
            for j in range(3, cols):
                if np.all([field[i+k, j-k] == symbol for k in range(4)]):
                    return True
        
        return False

    # 各プレイヤーの勝利判定
    if check_winner('#'):
        return player1
    elif check_winner('@'):
        return player2
    elif count_dot==0:
        return "draw"
    else:
        return None  # 勝者がいない場合


