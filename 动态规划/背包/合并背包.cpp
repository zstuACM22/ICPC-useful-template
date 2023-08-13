// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 合并背包. 复杂度: O(m^2)
const int MAXN = 1005;
const int MAXM = 1005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int n, m;
int dp[MAXN][MAXM];  // 默认值 -INF-1

// 将背包 y 合并到背包 x. 可以用分组背包
void merge_knapsack(int x, int y) {
    for (int i = m; i >= 0; i--)
        for (int j = i; j >= 0; j--) {
            if (dp[x][i - j] < 0 or dp[y][j] < 0)
                continue;
            dp[x][i] = max(dp[x][i], dp[x][i - j] + dp[y][j]);
        }
}