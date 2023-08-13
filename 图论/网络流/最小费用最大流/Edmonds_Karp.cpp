// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// EK + SPFA 算法. 注意: 本算法不处理反边, 重边. 时间复杂度: 很快 -> O(nm^3)
const int MAX = 1005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int n, m, st, ed;
int max_flow = 0, min_cost = 0;
int dis[MAX];
int vis[MAX];
int flow[MAX];
int pre[MAX];
int weight[MAX][MAX] = {0};
int cost[MAX][MAX] = {0};
vector<int> edge[MAX];

// 最短路径搜索(存在负边, 不处理负环)
bool spfa() {
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        vis[i] = false;
    }
    dis[st] = 0;
    queue<int> que;
    que.push(st);
    vis[st] = true;
    flow[st] = INF;
    pre[st] = st;
    while (not que.empty()) {
        int x = que.front();
        que.pop();
        vis[x] = false;
        for (int y : edge[x]) {
            if (weight[x][y] == 0)
                continue;
            if (dis[y] > dis[x] + cost[x][y]) {
                dis[y] = dis[x] + cost[x][y];
                flow[y] = min(flow[x], weight[x][y]);
                pre[y] = x;
                if (not vis[y]) {
                    que.push(y);
                    vis[y] = true;
                }
            }
        }
    }
    return dis[ed] < INF;
}

// 修改流
void modify(int w) {
    int y = ed;
    max_flow += w;
    while (pre[y] != y) {
        int x = pre[y];
        weight[x][y] -= w;
        weight[y][x] += w;
        min_cost += w * cost[x][y];
        y = x;
    }
}

// EK 主调用
void edmonds_karp() {
    max_flow = 0, min_cost = 0;
    while (spfa())
        modify(flow[ed]);
}

void solve() {
    cin >> n >> m >> st >> ed;
    for (int i = 0; i < m; i++) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        if (u == v or w == 0)  // 自环, 空边
            continue;
        edge[u].push_back(v);
        edge[v].push_back(u);
        weight[u][v] = w;
        cost[u][v] = c;
        cost[v][u] = -c;
    }
    edmonds_karp();
    cout << max_flow << ' ' << min_cost << endl;
}