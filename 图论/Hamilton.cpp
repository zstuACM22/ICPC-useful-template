// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Hamilton 最短路. 时间: O(n^2 2^n). 小心 long long / 边界多开 爆内存
// Hamilton 距离: 完成打卡图上每个点恰好的距离
const int MAX = 20;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int weight[MAX][MAX];   // 邻接矩阵存图
int dp[1 << MAX][MAX];  // 0-index, {是否到访序列, 最后到访地点} : 最短距离

int hamilton(int n) {
    for (int x = 0; x < (1 << n); x++) {
        for (int i = 0; i < n; i++) {
            dp[x][i] = INF;
        }
    }
    dp[1][0] = 0;
    for (int x = 0; x < (1 << n); x++) {
        for (int i = 0; i < n; i++) {
            if (x & 1 << i) {
                int y = x & ~(1 << i);
                for (int j = 0; j < n; j++) {
                    if (y & (1 << j)) {
                        dp[x][i] = min(dp[x][i], dp[y][j] + weight[j][i]);
                    }
                }
            }
        }
    }
    return dp[(1 << n) - 1][n - 1];
}