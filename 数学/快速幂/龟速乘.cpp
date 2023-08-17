// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 龟速乘 - Useless. 复杂度: O(log(multiplier))
const int MOD = 1000000007;

// 用于解决 1e18 级别取模. 通常使用浮点乘更快
// 考虑效率 __int128_t 快约 20%
int float_mul(int x, int y, int modulo) {
    int d = (long double)x / modulo * y + 0.5;
    int r = x * y - d * modulo;
    if (r < 0) r += modulo;
    return r;
}

int slow_mul(int base, int multiplier, int modulo = MOD) {
    int res = 0;
    base %= modulo;
    multiplier %= modulo;
    while (multiplier) {
        if (multiplier & 1)
            res = (res + base) % modulo;
        base = (base << 1) % modulo;
        multiplier >>= 1;
    }
    return res;
}

int slow_mul(int base, int multiplier) {
    int res = 0;
    base %= MOD;
    multiplier %= MOD;
    while (multiplier) {
        if (multiplier & 1)
            res = (res + base) % MOD;
        base = (base << 1) % MOD;
        multiplier >>= 1;
    }
    return res;
}