// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAX = 1000005;

// 2-SAT 二元适定性问题
// 需要首先将其转换为 {vertex, bool} -> {vertex, bool} (如果前者成立，后者一定成立条件作为边的有向图) 的问题
// 例如: not (A and B) ==> A -> not B, B -> not A; A or B ==> not A -> B, not B --> A
vector<int> edge[MAX];

bool in_stk[MAX << 1];
int low[MAX << 1];
int dfn[MAX << 1], cnt_dfn = 0;
int stk[MAX << 1], cnt_stk = 0;
int scn[MAX << 1], cnt_scc = 0;

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
            scn[stk[cnt_stk]] = cnt_scc;
            in_stk[stk[cnt_stk]] = false;
        } while (stk[cnt_stk] != x);
        cnt_scc++;
    }
}
void tarjan(int n) {
    fill(dfn, dfn + 2 * n + 2, 0);
    cnt_dfn = 0;
    cnt_scc = 0;
    for (int i = 2; i < 2 * n + 2; i++)
        if (dfn[i] == 0)
            __tarjan(i);
}

bool sat[MAX];  // 布尔选择 (特解)
bool twoSAT(int n) {
    tarjan(n);
    for (int i = 1; i <= n; i++)
        if (low[i << 1] == low[i << 1 | 1])
            return false;
    for (int i = 1; i <= n; i++)
        sat[i] = scn[i << 1] > scn[i << 1 | 1];
    return true;
}

void solve() {
    int n, m;
    cin >> n >> m;
    // 布尔方程: (u, x) or (v, y)
    for (int i = 0; i < m; i++) {
        int u, x, v, y;
        cin >> u >> x >> v >> y;
        edge[u << 1 | 1 - x].push_back(v << 1 | y);
        edge[v << 1 | 1 - y].push_back(u << 1 | x);
    }
    if (twoSAT(n)) {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++)
            cout << sat[i] << ' ';
        cout << endl;
    } else {
        cout << "NO" << endl;
    }  
}