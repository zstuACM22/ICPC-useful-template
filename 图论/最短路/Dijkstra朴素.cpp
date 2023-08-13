// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// dijkstra - O(n^2)
// 邻接表存图
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;
vector<pair<int, int>> edge[MAX];
int dis[MAX];
bool vis[MAX];

// dijkstra 单源多点最短路径 正边 O(n^2)
// 参数: st: 起点.
void dijkstra(int st, int n) {
    fill(dis, dis + n + 1, INF);
    fill(vis, vis + n + 1, false);
    int x = st;
    dis[x] = 0;
    while (x != -1) {
        vis[x] = true;
        for (pair<int, int> p : edge[x]) {
            int y = p.first, w = p.second;
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
            }
        }
        x = -1;
        for (int i = 1; i <= n; i++) {
            if (not vis[i] and (x == -1 or dis[x] > dis[i])) {
                x = i;
            }
        }
    }
}
