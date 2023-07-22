// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// tarjan 割边. 时间复杂度: O(n + m)
const int MAX = 1000005;

vector<int> edge[MAX];
int low[MAX];
int dfn[MAX], cnt_dfn = 0;
pair<int, int> cut[MAX];
int cnt_cut = 0;

void __tarjan(int x, int pre) {
    bool flag = false;
    low[x] = dfn[x] = ++cnt_dfn;
    for (int y : edge[x])
        if (dfn[y] == 0) {
            __tarjan(y, x);
            // 除去树边, 该点无法连到其前驱
            if (low[y] > dfn[x]) cut[cnt_cut++] = {x, y};
            low[y] = min(low[y], low[x]);
        } else if (flag or y != pre)
            low[y] = min(low[y], dfn[x]);
        else
            flag = true;  // 处理重边
}

void tarjan(int n) {
    fill(dfn, dfn + n + 1, 0);
    cnt_dfn = 0;
    cnt_cut = 0;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            __tarjan(i, i);
}