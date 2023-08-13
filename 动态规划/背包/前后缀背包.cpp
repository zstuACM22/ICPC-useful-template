// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 前后缀背包. 复杂度: O(qm) + 预处理 O(nm)
const int MAXM = 10005;
const int MAXN = 105;

int m, n, q;             // 背包容量, 物品数量, 询问次数
int v[MAXN];             // 体积
int w[MAXN];             // 价值
int prebag[MAXN][MAXM];  // 前缀背包
int sufbag[MAXN][MAXM];  // 后缀背包

void prefix_treatment() {
    for (int i = 0; i <= m; i++)
        prebag[0][i] = 0;  // 空白优化
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < v[i]; j++)
            prebag[i][j] = prebag[i - 1][j];
        for (int j = v[i]; j <= m; j++)
            prebag[i][j] = max(prebag[i - 1][j], prebag[i - 1][j - v[i]] + w[i]);
    }
}

void suffix_treatment() {
    for (int i = 0; i <= m; i++)
        sufbag[n + 1][i] = 0;  // 空白优化
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < v[i]; j++)
            sufbag[i][j] = sufbag[i + 1][j];
        for (int j = v[i]; j <= m; j++)
            sufbag[i][j] = max(sufbag[i + 1][j], sufbag[i + 1][j - v[i]] + w[i]);
    }
}

int query(int l, int r) {
    int max_ = 0;
    for (int i = 0; i <= m; i++)
        max_ = max(max_, prebag[l - 1][i] + sufbag[r + 1][m - i]);
    return max_;
}

void solve() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    prefix_treatment();
    suffix_treatment();

    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
}