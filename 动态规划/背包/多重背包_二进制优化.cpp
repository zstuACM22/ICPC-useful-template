// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 多重背包(二进制优化). 复杂度: O(nmlogl)
// https://www.acwing.com/problem/content/submission/5/
const int MAXM = 10005;
const int MAXN = 105;
const int LOGC = 17;

int m, n;             // 背包容量, 物品数量
int v[MAXN];          // 体积
int w[MAXN];          // 价值
int c[MAXN];          // 数量
int cnt = 0;          // 转换后 数量
int vv[MAXN * LOGC];  // 转换后 体积
int ww[MAXN * LOGC];  // 转换后 价值
int f[MAXM];          // 背包

void transform() {
    // 对数转换为 01 背包
    for (int i = 0; i < n; i++) {
        int len = c[i];
        while (len) {
            vv[cnt] = (len + 1) / 2 * v[i];
            ww[cnt] = (len + 1) / 2 * w[i];
            cnt++;
            len >>= 1;
        }
    }
}

void _01_knapsack() {
    for (int i = 0; i < cnt; i++)
        for (int j = m; j >= vv[i]; j--)
            if (f[j - vv[i]] != -1 and f[j] < f[j - vv[i]] + ww[i])
                f[j] = f[j - vv[i]] + ww[i];
}

void solve() {
    cin >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i] >> w[i];
    f[0] = 0;
    for (int i = 1; i <= m; i++)
        f[i] = -1;

    transform();
    _01_knapsack();

    int max_ = 0;
    for (int i = 1; i <= m; i++)
        max_ = max(max_, f[i]);
    cout << max_ << endl;
}