// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 卡特兰数. Whitworth 路线 & 凸包三角划分
// {1, 1, 2, 5, 14, 42, 132, 429, ...}
// $$Catalan(n) = \sum_{i=0}^{n-1} (Catalan(i)Catalan(n-1-i)) \tag{递推公式1}$$
// $$(n-3)Catalan(n) = \frac{n}{2} \sum_{i=3}{n-1} (Catalan(i)Catalan(n-1-i)) \tag{递推公式2}$$
// $$Catalan(n) = \frac{C_{2n}^{n}}{n+1} = C_{2n}^{n} - C_{2n}^{n-1} \tag{通项公式}$$
/* 解析:
1. Whitworth 路线(栈组合问题):
    考虑最后一次离开对角线的点 (i, i) $(0 \le i \le n-1)$,
    由于考虑为最后一次离开对角线, 离开 (i, i) 在 (n, n) 前不可回归,
    将问题分解为子问题: (0, 0) ~ (i, i) 的 Whitworth 路线 & (i+1, i) ~ (n, n-1) 的 Whitworth 路线.
2. 凸包三角划分:
    取一个点为基点, 剩余点标号 0 ~ n-2, 任取 i \in [0, n-3], 以基点 / i点 / (i+1)点为顶点划分三角形,
    剩余点将构成两个凸包: (i+2) 边凸包 & (n-1-i) 边凸包.
    f(n) = \sum_{i=0}^{n-3} (f(i+2)f(n-1-i)), f(x) = Catalan(x-2)
    */
// https://www.luogu.com.cn/problem/P1754
// https://www.luogu.com.cn/problem/P2532
const int MAX = 1005;
const int MOD = 1000000007;

int C[MAX][MAX];
void load_C(int n) {
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        C[i][i] = 1;
    }
}

int Catalan(int n) { return (C[2 * n][n] - C[2 * n][n - 1] + MOD) % MOD; }