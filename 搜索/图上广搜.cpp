// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 图上广搜. 时间复杂度: O(m)
// 邻接表存图
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;
vector<int> edge[MAX];
int dis[MAX];
bool vis[MAX];

void bfs(int st, int ed, int n) {
    fill(dis, dis + n + 1, INF);
    fill(vis, vis + n + 1, false);
    queue<pair<int, int>> que;
    dis[st] = 0;
    que.push({0, st});
    while (not que.empty() and not vis[ed]) {
        pair<int, int> p = que.front();
        int x = p.second, distance = p.first;
        que.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int y : edge[x]) {
            if (dis[y] > distance + 1) {
                dis[y] = distance + 1;
                que.push({dis[y], y});
            }
        }
    }
}