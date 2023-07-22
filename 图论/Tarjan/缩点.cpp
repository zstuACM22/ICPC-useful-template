// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// tarjan 强连通分量 & 缩点. 时间复杂度: O(n + m)
const int MAX = 1000005;

vector<int> edge[MAX];
bool in_stk[MAX] = {false};     // 访问标记
int low[MAX];                // scc 并查集的前驱
int dfn[MAX], cnt_dfn = 0;   // dfs 序号
int stk[MAX], cnt_stk = 0;   // 临时栈, 用于延迟获取 scc 成员
int root[MAX], cnt_scc = 0;  // scc 并查集的根, 以及 scc 的数量

void __tarjan(int x) {
    low[x] = dfn[x] = ++cnt_dfn;
    in_stk[x] = true;
    stk[cnt_stk++] = x;
    for (int y : edge[x])
        if (dfn[y] == 0) {
            __tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (in_stk[y])
            low[x] = min(low[x], dfn[y]);
    if (low[x] == dfn[x]) {
        do {
            cnt_stk--;
            in_stk[stk[cnt_stk]] = false;
            root[stk[cnt_stk]] = low[x];
        } while (stk[cnt_stk] != x);
        cnt_scc++;
    }
}

void tarjan(int n) {
    fill(dfn, dfn + n + 1, 0);
    cnt_dfn = 0;
    cnt_scc = 0;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            __tarjan(i);
}

int weight2[MAX];        // 合并点权
vector<int> edge2[MAX];  // 合并连边

// 缩点
void shrink(int n) {
    tarjan(n);  // 回调
    for (int x = 1; x <= n; x++)
        for (int y : edge[x])
            edge2[root[x]].push_back(root[y]);
    for (int x = 1; x <= n; x++) {
        sort(edge2[x].begin(), edge2[x].end());
        edge2[x].resize(unique(edge2[x].begin(), edge2[x].end()) - edge2[x].begin());
        vector<int>::iterator it = find(edge2[x].begin(), edge2[x].end(), x);
        if (it != edge2[x].end()) edge2[x].erase(it);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
    }

    shrink(n);

    // 方便后续操作
    swap(edge, edge2);

    // 更多操作, 如 deg-dp 等
}