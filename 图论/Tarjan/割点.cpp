// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// tarjan 割点. 时间复杂度: O(n + m)
const int MAX = 1000005;

vector<int> edge[MAX];
int low[MAX];
int dfn[MAX], cnt_dfn = 0;
bool cut[MAX];

// 主函数
void __tarjan(int x, int pre) {
    low[x] = dfn[x] = ++cnt_dfn;
    for (int y : edge[x])
        if (dfn[y] == 0) {
            __tarjan(y, x);
            // 后继无法连到前驱之前
            if (low[y] >= dfn[x]) cut[x] = true;
            low[x] = min(low[x], low[y]);
        } else if (y != pre)
            low[x] = min(low[x], dfn[y]);
}

// 起点特殊处理
void _tarjan(int x) {
    int sons = 0;
    low[x] = dfn[x] = ++cnt_dfn;
    for (int y : edge[x])
        if (dfn[y] == 0) {
            sons++;
            __tarjan(y, x);  // 主调用
            low[x] = min(low[x], low[y]);
        }
    // 因为无向图 tarjan 没有横叉边, 孩子数大于 2 即为割点
    if (sons >= 2) cut[x] = true;
}

// 处理非连通问题
void tarjan(int n) {
    fill(cut, cut + n + 1, false);
    fill(dfn, dfn + n + 1, 0);
    cnt_dfn = 0;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            _tarjan(i);
}