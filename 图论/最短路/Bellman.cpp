// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// bellman - 判断负环 & 跳出优化 O(mn)
// 边目录存图
const int MAXN = 105;
const int MAXM = 10005;
struct EDGE {
    int u, v, w;
} edge[MAXM];
int dis[MAXN];

// bellman 单源多点最短路径 正负边 判断负环 跳出优化
// 参数: st: 起点, n: 点数, m: 边数. 返回: 是否不存在负环.
bool bellman(int st, int n, int m) {
    for (int __ = 0; __ < n; __++) {
        bool flag = true;
        for (int i = 1; i <= m; i++)
            if (dis[edge[i].v] > dis[edge[i].u] + edge[i].w) {
                dis[edge[i].v] = dis[edge[i].u] + edge[i].w;
                flag = false;
            }
        if (flag)
            return true;
    }
    return false;
}