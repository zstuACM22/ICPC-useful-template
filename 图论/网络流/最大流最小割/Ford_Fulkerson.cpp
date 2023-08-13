// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Useless - FF 算法. 时间复杂度: 小概率很快 -> O(fm) (f: 所求-最大流) / O(wm^2) (w: 边权)
const int MAX = 1005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int n, m, st, ed;
int flow[MAX];
int pre[MAX];  // 前驱与标记双重作用
int weight[MAX][MAX] = {0};
vector<int> edge[MAX];

// 快速路径搜索
bool dfs(int x) {
    if (x == ed)
        return true;
    for (int y : edge[x])
        if (weight[x][y] > 0 and pre[y] == -1) {
            flow[y] = min(flow[x], weight[x][y]);
            pre[y] = x;
            if (dfs(y))
                return true;
            pre[y] = -1;
        }
    return false;
}
bool dfs() {
    for (int i = 1; i <= n; i++)
        pre[i] = -1;
    flow[st] = INF;
    pre[st] = st;
    return dfs(st);
}

// 修改流
void modify(int w) {
    int y = ed;
    while (pre[y] != y) {
        int x = pre[y];
        weight[x][y] -= w;
        weight[y][x] += w;
        y = x;
    }
}

// FF 主调用
int ford_fulkerson() {
    int res = 0;
    for (int y : edge[st])
        res -= weight[y][st];
    while (dfs())
        modify(flow[ed]);
    for (int y : edge[st])
        res += weight[y][st];
    return res;
}

void solve() {
    cin >> n >> m >> st >> ed;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == v or w == 0)  // 自环, 空边
            continue;
        if (weight[u][v] or weight[v][u])  // 重边
            weight[u][v] += w;
        else {
            edge[u].push_back(v);
            edge[v].push_back(u);
            weight[u][v] = w;
        }
    }
    cout << ford_fulkerson() << endl;
}