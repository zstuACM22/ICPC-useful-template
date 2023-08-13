// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 分层图 + dijkstra. 带免权次数的最短路问题. 时间: O(kmlog(kn))
const int MAXN = 10005;
const int MAXK = 11;
const int INF = 0x3f3f3f3f3f3f3f3fll;

vector<pair<int, int>> edge[MAXN * (MAXK + 1)];
int dis[MAXN * (MAXK + 1)];
bool vis[MAXN * (MAXK + 1)];

// dijkstra 单源多点最短路径 正边 堆优化 O((n+m)log(n))
// 参数: st: 起点. n: 点数
void dijkstra(int st, int n) {
    fill(dis, dis + n + 1, INF);
    fill(vis, vis + n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    dis[st] = 0;
    heap.push({0, st});
    while (not heap.empty()) {
        pair<int, int> p = heap.top();
        int x = p.second, distance = p.first;
        heap.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (pair<int, int> p : edge[x]) {
            int y = p.first, weight = p.second;
            if (dis[y] > distance + weight) {
                dis[y] = distance + weight;
                heap.push({dis[y], y});
            }
        }
    }
}

// 0-index nodes
int layered(int st, int ed, int n, int k) {
    for (int i = k; i > 0; i--) {
        for (int j = 0; j < n; j++) {
            edge[j + i * n - n].reserve(2 * edge[j].size());  // Attention: 不能去掉, 否则地址重置发生错误
            for (pair<int, int> p : edge[j]) {
                // Attention: 不能颠倒顺序
                edge[j + i * n].push_back({p.first + i * n, p.second});
                edge[j + i * n - n].push_back({p.first + i * n, 0});
            }
        }
    }
    dijkstra(st, (k + 1) * n);
    int res = INF;
    for (int i = 0; i <= k; i++) {
        res = min(res, dis[ed + i * n]);
    }
    return res;
}

void solve() {
    int n, m, k, st, ed;
    cin >> n >> m >> k >> st >> ed;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    }
    cout << layered(st, ed, n, k) << endl;
}