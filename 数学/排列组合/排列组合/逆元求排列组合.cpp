// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 组合数的逆元解法
// 时间: O(1) + 预处理: O(n)
// 一般开两倍内存
const int MAX = 1000005;
const int MOD = 1000000007;

// 预处理逆元
int inv[MAX];
void load_inv(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

// 预处理阶乘
int fac[MAX];
void load_fac(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % MOD;
}

// 预处理阶乘的逆元
int ifc[MAX];
void load_ifc(int n) {
    ifc[0] = 1;
    for (int i = 1; i <= n; i++)
        ifc[i] = ifc[i - 1] * inv[i] % MOD;
}

// 询问排列数与组合数
int A(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[m - n] % MOD : 0; }
int C(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[n] % MOD * ifc[m - n] % MOD : 0; }

void init() {
    load_inv(MAX - 1);
    load_fac(MAX - 1);
    load_ifc(MAX - 1);  // 必须放在最后
}