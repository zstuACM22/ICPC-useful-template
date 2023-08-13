// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// kruskal - O(mlogm)
const int MAXN = 10005;
const int MAXM = 100005;
int n, m;
struct Edge {
    int u;
    int v;
    int w;
} edge[MAXM];
int father[MAXN];

int root(int x) { return father[x] == x ? x : father[x] = root(father[x]); }

void merge(int x, int y) { father[root(x)] = root(y); }

int kruskal() {
    iota(father + 1, father + n + 1, 1);
    sort(edge, edge + m, [](const Edge &x, const Edge &y) { return x.w < y.w; });
    int cnt = 0, i = 0, dis = 0;
    while (cnt < n - 1 and i < m) {
        if (root(edge[i].u) != root(edge[i].v)) {
            merge(edge[i].u, edge[i].v);
            cnt++;
            dis += edge[i].w;
        }
        i++;
    }
    if (cnt < n - 1)
        return -1;
    return dis;
}