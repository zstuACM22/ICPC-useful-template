// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 无限背包. 复杂度: O(nm)
const int MAXM = 10005;
const int MAXN = 105;

int m, n;     // 背包容量, 物品数量
int v[MAXN];  // 体积
int w[MAXN];  // 价值
int f[MAXM];  // 背包

void limitless_knapsack() {
    for (int i = 0; i < n; i++)
        // for (int j = m; j >= v[i]; j--)  // 01 背包
        for (int j = v[i]; j <= m; j++)
            if (f[j - v[i]] != -1 and f[j] < f[j - v[i]] + w[i])
                f[j] = f[j - v[i]] + w[i];
}

void solve() {
    cin >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i] >> w[i];
    f[0] = 0;
    for (int i = 1; i <= m; i++)
        f[i] = -1;

    limitless_knapsack();

    int max_ = 0;
    for (int i = 1; i <= m; i++)
        max_ = max(max_, f[i]);
    cout << max_ << endl;
}