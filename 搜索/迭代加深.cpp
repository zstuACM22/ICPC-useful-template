// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 迭代加深. 常数时间 换 指数空间 的 最少步数问题 的 深搜解法
// 最小步数问题 通常使用 广度优先搜索 解决, 但在 状态转移复杂/状态指数增长 的场景会出现内存爆炸, 可以使用 迭代加深 解决
const int MAX = 105;

int path[MAX];

// 核心代码, 因题而异
bool dfs(int x, int n, int depth) {
    if (path[x - 1] == n) return true;
    if (x >= depth) return false;
    for (int i = 0; i < x; i++) {
        for (int j = i; j < x; j++) {
            path[x] = path[i] + path[j];
            if (path[x] <= path[x - 1] or path[x] > n) continue;
            bool tmp = dfs(x + 1, n, depth);
            if (tmp) return true;
        }
    }
    return false;
}

void solve(int n) {
    // 迭代加深框架
    int depth = 1;
    while (true) {
        path[0] = 1;
        bool tmp = dfs(1, n, depth);
        if (tmp) break;
        depth++;
    }
    for (int i = 0; i < depth; i++) {
        cout << path[i];
    }
    cout << endl;
}