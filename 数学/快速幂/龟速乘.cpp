// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 龟速乘. 复杂度: O(log(multiplier))
const int MOD = 1000000007;

int slow_mul(int base, int multiplier) {
    int res = 0;
    while (multiplier) {
        if (multiplier & 1)
            res += base;
        base += base;
        multiplier >>= 1;
    }
    return res;
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