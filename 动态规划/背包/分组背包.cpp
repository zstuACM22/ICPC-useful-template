// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 分组背包. 复杂度: O(sum(n)m)
const int MAXM = 10005;
const int MAXN = 105;

int m, n;                            // 背包容量, 分组数量
vector<pair<int, int>> group[MAXN];  // {{体积, 价值}}
int f[MAXM];                         // 背包

void grouped_knapsack() {
    for (int i = 0; i < n; i++)
        for (int j = m; j >= 0; j--)
            for (pair<int, int> p : group[i])
                if (j >= p.second and f[j - p.first] != -1)
                    f[j] = max(f[j], f[j - p.first] + p.second);
}

void solve() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        while (t--) {
            int v, w;
            cin >> v >> w;
            group[i].push_back({v, w});
        }
    }
    f[0] = 0;
    for (int i = 1; i <= m; i++)
        f[i] = -1;

    grouped_knapsack();

    int max_ = 0;
    for (int i = 1; i <= m; i++)
        max_ = max(max_, f[i]);
    cout << max_ << endl;
}