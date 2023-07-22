// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 树上启发式合并. 以 树上颜色合并 为例
const int MAX = 100005;

int n;
vector<int> edge[MAX];
int color[MAX];
int sons[MAX];
int heavy[MAX];
int cnt[MAX], max_ = 0, cc = 0;
int res[MAX];

// 标记重链
int dfs(int x, int pre) {
    int cnt = 1;
    int ymax = 0, max_ = 0;
    for (int y : edge[x]) {
        if (y == pre)
            continue;
        int tmp = dfs(y, x);
        if (max_ < tmp) {
            max_ = tmp;
            ymax = y;
        }
        cnt += tmp;
    }
    heavy[x] = ymax;
    return cnt;
}

// 计算贡献  // Attention
void calc(int x, int pre, int heavy_son, int val) {
    for (int y : edge[x]) {
        if (y == pre or y == heavy_son)
            continue;
        calc(y, x, heavy_son, val);
    }
    cnt[color[x]] += val;
    if (cnt[color[x]] == max_)
        cc += color[x];
    else if (cnt[color[x]] > max_) {
        max_ = cnt[color[x]];
        cc = color[x];
    }
}

// 树上启发式合并
void dsu(int x, int pre, bool keep) {
    for (int y : edge[x]) {
        if (y == pre or y == heavy[x])
            continue;
        dsu(y, x, false);
    }
    if (heavy[x])
        dsu(heavy[x], x, true);
    calc(x, pre, heavy[x], 1);
    res[x] = cc;
    if (not keep) {
        calc(x, pre, 0, -1);
        max_ = 0;
        cc = 0;
    }
}