#include <bits/stdc++.h>
//#include <atcoder/all>
#define all(x) x.begin(), x.end()
#define rep1(i, n) for(ll i = 0; i < (ll)(n); i++)
#define rep2(i, s, n) for(ll i = (s); i < (ll)(n); i++)
#define rep3(i, s, n, c) for(ll i = (s); i < (ll)(n); i += (c))
#define repOverload(a, b, c, d, e, ...) e
#define rep(...) repOverload(__VA_ARGS__, rep3, rep2, rep1)(__VA_ARGS__)
#define fore(x, a) for(auto &x : a)
#define arr_sort(array, elm) sort(array.begin(), array.end(), [&](auto &l, auto &r) { return l[elm] < r[elm]; })
template <typename T> inline bool chmin(T& a, const T& b) {bool compare = a > b; if (a > b) a = b; return compare;}
template <typename T> inline bool chmax(T& a, const T& b) {bool compare = a < b; if (a < b) a = b; return compare;}
using namespace std;
typedef long long int ll;
//using mint = atcoder::modint998244353;
bool is_win(vector<vector<int> >field){
    //勝利判定のプログラム
}
int calculateSegmentScore(int playerCount, int opponentCount) {
    if (playerCount > 0 && opponentCount > 0) return 0; // 両者の石が混在している場合は無効
    if (playerCount > 0) {
        // 自分の石に対してスコアを計算
        return pow(10, playerCount - 1); // 例: 1個=1点、2個=10点、3個=100点、4個=勝利
    }
    if (opponentCount > 0) {
        // 相手の石に対してスコアを計算
        return -pow(10, opponentCount - 1); // 負の値で危険度を反映
    }
    return 0;
}

//いしの連続性でスコアを計算
int evaluateBoard(vector<vector<int> > &field, int player) {
    int score = 0;
    // 横方向の探索
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) { // 横に4つ並ぶ余地があるのは列0-3のみ
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 4; k++) { // 4つ分の石をチェック
                if (field[i][j + k] == player) playerCount++;
                if (field[i][j + k] == 3 - player) opponentCount++;
            }
            // スコア加算: 自分の石が多いほど高評価、相手の石が多いほど低評価
            score += calculateSegmentScore(playerCount, opponentCount);
        }
    }

    // 縦方向の探索
    for (int i = 0; i < 3; i++) { // 縦に4つ並ぶ余地があるのは行0-2のみ
        for (int j = 0; j < 7; j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 4; k++) {
                if (field[i + k][j] == player) playerCount++;
                if (field[i + k][j] == 3 - player) opponentCount++;
            }
            score += calculateSegmentScore(playerCount, opponentCount);
        }
    }

    // 斜め方向の探索（左上から右下）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 4; k++) {
                if (field[i + k][j + k] == player) playerCount++;
                if (field[i + k][j + k] == 3 - player) opponentCount++;
            }
            score += calculateSegmentScore(playerCount, opponentCount);
        }
    }

    // 斜め方向の探索（右上から左下）
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 7; j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 4; k++) {
                if (field[i + k][j - k] == player) playerCount++;
                if (field[i + k][j - k] == 3 - player) opponentCount++;
            }
            score += calculateSegmentScore(playerCount, opponentCount);
        }
    }

    return score;
}

// スコア計算の補助関数
int evaluateCenter(vector<vector<int> > &field,int player){
    int score=0;
    //列の中央に近いと点数が高い
    for(int row=0;row<6;row++){
        for(int col=2;col<5;col++){
            int playerCount=0;
            int opponentCount=0;
            if(field[row][col]==player){
                playerCount+=2;
            }
            else if (field[row][col]==3-player){
                opponentCount+=2;
            }
            score+=calculateSegmentScore(playerCount,opponentCount);
        }
    }
    //行の中央に近いと点数が高い
    for(int row =2;row<4;row++){
        for(int col=0;col<7;col++){
            int playerCount=0;
            int opponentCount=0;
            if(field[row][col]==player){
                playerCount+=2;
            }
            else if(field[row][col]==3-player){
                opponentCount+=2;
            }
            score+=calculateSegmentScore(playerCount,opponentCount);
        }
    }
    return score;
}
//
int findCanput(vector<vector<int> > &field, int col) {
    for (int i = 5; i >= 0; i--) { // 下から順に空きマスを探す
        if (field[i][col] == 0) return i; // 空いている行を返す
    }
    return -1; // その列が満杯の場合
}


pair<int, int> findBestpos(vector<vector<int> > &field, int player, int depth) {
    int bestScore = INT_MIN; // 最小値で初期化
    int bestCol = -1;

    for (int col = 0; col < 7; col++) { // 7列分試す
        int row = findCanput(field, col); // 石を置ける行を探す
        if (row == -1) continue; // その列に石を置けない場合はスキップ

        // 石を仮置き
        field[row][col] = player;

        // ミニマックス法を使って次の状態を評価（深さ1の場合は単純な評価関数）
        // 三項演算子
        int score = (depth == 1) ? evaluateBoard(field,player)*2
                                 : findBestpos(field, 3 - player, depth - 1).first;

        // 石を元に戻す
        field[row][col] = 0;

        // 最良のスコアと列を更新
        if (score > bestScore) {
            bestScore = score;
            bestCol = col;
        }
    }
    return make_pair(bestScore,bestCol);
    // return {bestScore, bestCol};
}

int main(){

    
    vector<vector<int> > field(6,vector<int>(7,0));//縦6x横7のフィールドを作成する
    pair<int,int>answer;
    //フィールドを受けとる
    // #######
    //プレイヤー引数を持ってくる
    // answer=findBestpos(field,playerID,4);
    answer=findBestpos(field,1,10);
    cout<<"Best Score :"<<answer.first<<endl;
    cout<<"Best Column :"<<answer.second<<endl;

    //field[5][6]=1;
    //cout<<evaluateCenter(field,1)<<endl;
}
