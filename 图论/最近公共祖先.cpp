// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 最近公共祖先. 时间复杂度: O(logn) + 预处理: O(nlogn), 空间复杂度: O(nlogn)
// 1-index
const int MAX = 100005;
const int LOG = 17;

int lg2[MAX];
vector<int> edge[MAX];
int depth[MAX];  // 根深为 0
int st[MAX][LOG];

// 预处理对数
void load_lg2(int n) {
    lg2[0] = -1;
    for (int i = 1; i <= n; i++)
        lg2[i] = lg2[i >> 1] + 1;
}

// 建表
void build(int x, int pre, int level) {
    depth[x] = level;
    st[x][0] = pre;
    for (int i = 1; i <= lg2[depth[x]]; i++)
        st[x][i] = st[st[x][i - 1]][i - 1];
    for (int y : edge[x])
        if (y != pre)
            build(y, x, level + 1);
}

// 查询多级祖先, 不存在返回 -1
int ancestor(int x, int p) {
    if (p > depth[x])
        return -1;
    while (p) {
        int step = lg2[p];
        x = st[x][step];
        p -= 1 << step;
    }
    return x;
}

// 查询最近公共祖先, 不存在返回 -1
int lca(int x, int y) {
    if (depth[x] < depth[y])
        swap(x, y);
    while (depth[x] > depth[y])
        x = st[x][lg2[depth[x] - depth[y]]];
    if (x == y)
        return x;
    for (int k = lg2[depth[x]]; k >= 0; k--)
        if (st[x][k] != st[y][k]) {
            x = st[x][k];
            y = st[y][k];
        }
    if (st[x][0] == st[y][0])
        return st[x][0];
    return -1;
}