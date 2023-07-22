// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 组合数的动态规划解法
// 时间: O(n^2)
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

int A[MAX][MAX];
void load_A(int n) {
    for (int i = 0; i <= n; i++) {
        A[i][0] = 1;
        for (int j = 1; j <= i; j++)
            A[i][j] = A[i][j - 1] * (i + 1 - j) % MOD;
    }
}