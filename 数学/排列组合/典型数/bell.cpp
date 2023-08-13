// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 贝尔数. Bell(n): 将 n 个不同元素分为任意个非空集合组合的方案数
// {1, 1, 2, 5, 15, 52, 203, 877, ...}
// $$Bell(n) = \sum_{k=0}^{n-1} (C_{n-1}^kBell(k)) \tag{递推公式}$$
// $$Bell(n) = \sum_{k=1}^{n}Stirling2(n,k) \tag{第二类Stirling数}$$
// $$Bell(n) = \frac{1}{e} \sum_{k=0}^{\infty} \frac{k^n}{k!} \tag{Dobinski公式}$$
// $$Bell(n+p) \equiv Bell ( n ) + Bell(n+1)~(mod~p)~(p~is~prime) \tag{Touchard同余}$$
// $$Bell(n+p^m) \equiv m~Bell(n) + Bell(n+1)~(mod~p)~(p~is~prime) \tag{Touchard同余}$$
// $$T(p) = \frac{p^p-1}{p-1}~(p~is~prime) \tag{Bell函数模周期}$$
const int MAX = 1005;
const int MOD = 10000007;

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

int Bell[MAX];
void load_Bell(int n) {
    fill(Bell, Bell + n + 1, 0);
    Bell[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            Bell[i] = (Bell[i] + C[i - 1][j] * Bell[j]) % MOD;
}