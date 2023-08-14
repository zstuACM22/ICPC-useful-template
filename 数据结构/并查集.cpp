// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 基础并查集 - 路径压缩 & 按秩合并. 时间: O(Alpha(n)) (Alpha(n) == 4), 内存: O(n)
// 只有 路径压缩 或 按秩合并. 时间都是 O(logn)
// 1-index
const int MAX = 1000005;

int father[MAX];
int edges[MAX];  // 集合边数, 按需
int nodes[MAX];  // 集合点数, 用于按秩合并

// 初始化  // Attention
void init(int n) {
    iota(father, father + n + 1, 0);
    fill(edges, edges + n + 1, 0);
    fill(nodes, nodes + n + 1, 1);
}

// 状态合并方程  // Attention
void state_merge(int x, int y) {
    edges[y] += edges[x];
    edges[x] = 0;  // 可不擦除
    nodes[y] += nodes[x];
    nodes[x] = 0;  // 可不擦除
}

// 返回根节点
int root(int x) {
    if (father[x] == x)
        return x;
    return father[x] = root(father[x]);
}

// 合并集合
bool merge(int x, int y) {
    x = root(x);
    y = root(y);
    edges[x]++;  // 新增边
    if (x == y)
        return false;
    if (nodes[x] < nodes[y]) {
        state_merge(x, y);
        father[x] = y;
    } else {
        state_merge(y, x);
        father[y] = x;
    }
    return true;
}