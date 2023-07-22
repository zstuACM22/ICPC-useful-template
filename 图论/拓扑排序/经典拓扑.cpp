// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 拓扑排序. 复杂度: O(n)
const int MAX = 1000005;

set<int> edge[MAX];  // 重边, 否则用 vector
int in_degree[MAX] = {0};
int top_order[MAX];

// 建图
void build(int m) {
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (u == v)  // 自环
            continue;
        pair<set<int>::iterator, bool> tmp = edge[u].insert(v);
        if (tmp.second)
            in_degree[v]++;
    }
}

// 拓扑
bool topsort(int n) {
    int cnt = 0;
    stack<int> stk;
    for (int i = 1; i <= n; i++)
        if (in_degree[i] == 0)
            stk.push(i);
    while (not stk.empty()) {
        int x = stk.top();
        stk.pop();
        top_order[cnt++] = x;
        for (int y : edge[x]) {
            in_degree[y]--;
            if (in_degree[y] == 0)
                stk.push(y);
        }
    }
    return cnt == n;
}