// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Lucas 定理求排列组合
// 时间: O(log_MOD(n)) + 预处理: O(MOD)
// 要求 MOD 是质数且较小, MAX 大于 MOD
const int MAX = 1000005;
const int MOD = 999983;

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

// 初始化绑定
void init(int n) {
    load_inv(n);
    load_fac(n);
    load_ifc(n);  // 必须放在最后
}

// 询问排列数与组合数
inline int A(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[m - n] % MOD : 0; }
inline int C(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[n] % MOD * ifc[m - n] % MOD : 0; }

// Lucas 定理. 时间: O(log_MOD(n)) + 预处理: O(MOD)
// 要求模是质数
int Lucas(int m, int n) {
    if (n < 0 or n > m) 
        return 0;
    int res = 1;
    while (n) {
        res = res * C(m % MOD, n % MOD) % MOD;
        m /= MOD;
        n /= MOD;
    }
    return res;
}