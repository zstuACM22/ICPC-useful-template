// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 第一类斯特林数(斯特林轮转数). Stirling1(n, m): 将 n 个不同元素分为 m 个非空轮换组合的方案数
// {{1}, {0, 1}, {0, 1, 1}, {0, 2, 3, 1}, {0, 6, 11, 6, 1}, {0, 24, 50, 35, 10, 1}, ...}
// $$stirling(n, m) = stirling(n-1, m-1) + (n-1)~stirling(n-1, m)$$
/* 解析:
n 人坐 m 张圆桌. 考虑 n 号入座:
1. n 号独坐 m 号桌.
2. n 号可坐任意 1 ~ n-1 号左边.
    */
// https://leetcode.cn/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/
// https://www.luogu.com.cn/problem/P4609
const int MAX = 1005;
const int MOD = 1000000007;
int stirling[MAX][MAX] = {0};
void load_stirling(int n) {
    stirling[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            stirling[i][j] = (stirling[i - 1][j - 1] + (i - 1) * stirling[i - 1][j]) % MOD;
}