// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 费马小定理求逆元. 依赖: quick_pow. 复杂度: O(log(modulo)).
const int MOD = 1000000007;

int quick_pow(int base, int exponent, int modulo = MOD) {
    int res = 1;
    while (exponent) {
        if (exponent & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exponent >>= 1;
    }
    return res;
}

int inv(int primal, int modulo = MOD) { return quick_pow(primal, modulo - 2, modulo); }