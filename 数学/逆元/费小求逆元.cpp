// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 费小求逆元. 要求模是质数. 依赖: quick_pow. 复杂度: O(log(MOD)).
const int MOD = 1000000007;

// 快速幂
int quick_pow(int base, int exponent) {
    int res = 1 % MOD;
    base %= MOD;
    while (exponent) {
        if (exponent & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return res;
}

// 费马小定理求逆元
inline int inv(int primal) { return quick_pow(primal, MOD - 2); }