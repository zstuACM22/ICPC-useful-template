// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 大步小步
// 求解 base ^ x = rest (mod modulo)的最小正整数解, 要求 modulo 为质数
// 时间: O(modulo^0.5 log(modulo))
// 求解 x ^ a = b (mod p) 即转换为 g ^ a ^ c = b (mod p), x = g ^ c (mod p), g 是 p 的原根

// 快速幂
int quick_pow(int base, int exponent, int modulo) {
    int res = 1;
    while (exponent) {
        if (exponent & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exponent >>= 1;
    }
    return res;
}

// 大步小步
int BSGS(int base, int rest, int modulo) {
    base %= modulo, rest %= modulo;
    int m = ceil(sqrt(modulo));
    // 如果 0 可以是解:
    // if (base and rest == 1)
    //     return 0;
    if (base == rest)
        return 1;
    if (base == 0 and rest)
        return -1;
    map<int, int> M;
    int now = rest % modulo, f = quick_pow(base, m, modulo);
    M[now] = 0;
    for (int i = 1; i <= m; ++i) {
        now = (now * base) % modulo;
        M[now] = i;
    }
    now = 1;
    for (int i = 1; i <= m; ++i) {
        now = (now * f) % modulo;
        if (M[now]) {
            int ans = (i * m - M[now]) % modulo;
            return (ans + modulo) % modulo;
        }
    }
    return -1;
}