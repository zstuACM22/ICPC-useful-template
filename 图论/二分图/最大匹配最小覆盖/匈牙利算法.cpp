// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 匈牙利算法. 时间: O(mn), 空间: O(n+m)
const int MAX = 505;

bool vis[MAX];
int match[MAX];
vector<int> edge[MAX];
vector<int> left_node;

bool dfs(int x) {
    for (int y : edge[x]) {
        if (vis[y])
            continue;
        vis[y] = true;
        if (match[y] == 0 or dfs(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

// 匈牙利算法
int hungarian(int n) {
    int res = 0;
    fill(match, match + n, 0);
    for (int x : left_node) {
        fill(vis, vis + n, false);
        if (dfs(x))
            res++;
    }
    return res;
}