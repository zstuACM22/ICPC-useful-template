// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 01 背包 - 优化 - 内存优化 & 空白优化. 复杂度: O(nm)
const int MAXM = 10005;
const int MAXN = 105;

int m, n;     // 背包容量, 物品数量
int v[MAXN];  // 体积
int w[MAXN];  // 价值
int f[MAXM];  // 背包

void _01_knapsack() {
    for (int i = 0; i < n; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
}

void solve() {
    cin >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i] >> w[i];
    for (int i = 0; i <= m; i++)
        f[i] = 0;

    _01_knapsack();

    int max_ = f[m];
    cout << max_ << endl;
}