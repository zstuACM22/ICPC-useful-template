// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 快速幂. 复杂度: O(log(exponent))
const int MOD = 1000000007;

int quick_pow(int base, int exponent) {
    int res = 1;
    while (exponent) {
        if (exponent & 1)
            res *= base;
        base *= base;
        exponent >>= 1;
    }
    return res;
}

int quick_pow(int base, int exponent, int modulo = MOD) {
    int res = 1 % modulo;
    base %= modulo;
    while (exponent) {
        if (exponent & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exponent >>= 1;
    }
    return res;
}

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