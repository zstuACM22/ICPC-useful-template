// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 矩阵上广搜. 时间复杂度: O(sn^2) (s 为 next_ 数组大小)
const int MAX = 1005;

int n, m;
char map_[MAX][MAX];
int track[MAX][MAX];
struct XY {
    int x;
    int y;
    XY operator+(XY xy) { return {x + xy.x, y + xy.y}; }
    XY operator*(int v) { return {x * v, y * v}; }
    bool operator<(XY xy) const { return track[x][y] < track[xy.x][xy.y]; }
    bool operator>(XY xy) const { return track[x][y] > track[xy.x][xy.y]; }
    // Attention: map_[x][y] != 'x'， track[x][y] > track[xy.x][xy.y] 在面积搜索中需去掉
    bool is_valid(XY xy) { return 0 <= x and x < n and 0 <= y and y < m and map_[x][y] != 'x' and (track[x][y] == -1 or track[x][y] > track[xy.x][xy.y]); }
};
vector<XY> next_{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
queue<XY> que;

void bfs(XY st, XY ed) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            track[i][j] = -1;
    que.push(st);
    track[st.x][st.y] = 0;
    while (not que.empty() and track[ed.x][ed.y] == -1) {
        XY pos = que.front();
        que.pop();
        for (XY nxt : next_)
            for (int i = 1; i < n; i++) {
                XY nw = pos + nxt * i;
                if (nw.is_valid(pos)) {
                    track[nw.x][nw.y] = track[pos.x][pos.y] + 1;
                    que.push(nw);
                } else
                    break;
            }
    }
}

void solve() {
    XY st, ed;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> map_[i];
        for (int j = 0; j < m; j++)
            if (map_[i][j] == 'A')
                st = {i, j};
            else if (map_[i][j] == 'B')
                ed = {i, j};
    }
    bfs(st, ed);
    cout << track[ed.x][ed.y] << endl;
}