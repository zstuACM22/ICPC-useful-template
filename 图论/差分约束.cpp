// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 差分约束 方程组求解
// 求解方程组 x_i - x_j <= k
// 即将转换为 x_j 到 x_i 边权为 k 的图, 然后连从 0 到所有点权为 0 的边, 从 0 跑单源最短路判负环, 不存在负环则 dis[i] 为 x[i] 的一个解
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

vector<pair<int, int>> edge[MAX];
int dis[MAX];
bool vis[MAX];
int cou[MAX];

// spfa 单源多点最短路径 正负边 判断负环 队列优化
// 参数: st: 起点, n: 点数. 返回: 是否不存在负环.
bool spfa(int st, int n) {
    fill(dis, dis + n + 1, INF);
    fill(vis, vis + n + 1, false);
    fill(cou, cou + n + 1, 0);
    dis[st] = 0;
    vis[st] = true;
    queue<int> que;
    que.push(st);
    while (not que.empty()) {
        int x = que.front();
        que.pop();
        vis[x] = false;
        for (pair<int, int> p : edge[x]) {
            int y = p.first, d = p.second;
            if (dis[y] > dis[x] + d) {
                dis[y] = dis[x] + d;
                cou[y] = cou[x] + 1;
                if (cou[y] >= n)
                    return false;
                if (not vis[y]) {
                    que.push(y);
                    vis[y] = true;
                }
            }
        }
    }
    return true;
}

int diff[MAX];  // 该点取值 (特解)
bool diff_limit(int n) {
    for (int i = 1; i <= n; i++)
        edge[0].push_back({0, i});
    if (spfa(0, n)) {
        for (int i = 1; i <= n; i++)
            diff[i] = dis[i];
        return true;
    } else {
        return false;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    // 差分约束方程: x_u - x_v <= w
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[v].push_back({u, w});
    }
    if (diff_limit(n)) {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++)
            cout << diff[i] << ' ';
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
}