// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 判断二分图
// 1-index
const int MAX = 3005;
int color[MAX] = {0};  // 0: 未染色, 1: 红色, -1: 蓝色
vector<int> edge[MAX];

bool dfs(int x) {
    for (int y : edge[x])
        if (color[y]) {
            if (color[x] + color[y])
                return false;
        } else {
            color[y] = -color[x];
            if (not dfs(y))
                return false;
        }
    return true;
}
bool is_bpg(int n) {
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            color[i] = 1;
            if (not dfs(i))
                return false;
        }
    }
    return true;
}