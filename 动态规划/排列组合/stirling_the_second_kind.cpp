// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 第二类斯特林数(斯特林子集数). Stirling2(n, m): 将 n 个不同元素分为 m 个非空集合组合的方案数
// {{1}, {0, 1}, {0, 1, 1}, {0, 1, 3, 1}, {0, 1, 7, 6, 1}, {0, 1, 15, 25, 10, 1}, ...}
// $$Stirling(n, m) = Stirling(n-1, m-1) + m~Stirling(n-1, m)$$
/* 解析:
n 人进 m 个房间. 考虑 n 号选择:
1. n 号独占 m 号房.
2. n 号可选任意 1 ~ m 号房间.
    */
// https://www.luogu.com.cn/problem/P1655
// https://www.luogu.com.cn/problem/P3904
const int MAX = 1005;
const int MOD = 1000000007;
int Stirling[MAX][MAX] = {0};
void load_Stirling(int n) {
    Stirling[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            Stirling[i][j] = (Stirling[i - 1][j - 1] + j * Stirling[i - 1][j]) % MOD;
}