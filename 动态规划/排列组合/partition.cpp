// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 划分数. Part(n, m): 将 n 个相同元素分为不多于 m 个非空集合组合的方案数
// $$Part(n, m) = Part(n, m-1) + Part(n-m, m)$$
/* 解析:
n 枚石子分为 m 堆, 考虑放入 n 号石子:
1. n 号创建了第 m 堆石子.
2. n 号放入已有 1 ~ m 堆石子,
    考虑 1 ~ n-1 号已放好,当前放入会与之后放入重复计算.
    考虑 每堆各取回 1 枚石子, 再将 m 枚石子分别放入每个堆.
    */
const int MAX = 1005;
const int MOD = 10000007;
int Part[MAX][MAX];
void load_Partition(int n) {
    Part[0][0] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i >= j)
                Part[i][j] = (Part[i][j - 1] + Part[i - j][j]) % MOD;
            else
                Part[i][j] = Part[i][j - 1];
}