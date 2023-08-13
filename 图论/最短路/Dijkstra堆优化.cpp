// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// dijkstra - 堆优化 O((n+m)logn)
// 邻接表存图
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;
vector<pair<int, int>> edge[MAX];
int dis[MAX];
bool vis[MAX];

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