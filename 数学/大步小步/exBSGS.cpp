// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 大步小步
// 求解 base ^ x = rest (mod modulo)的最小正整数解, 不要求 modulo 为质数
// 时间: O(modulo^0.5 log(modulo))

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

// 扩展欧几里得
int __exgcd(int a, int b, int &x, int &y) {
    int d = a;
    if (b != 0) {
        d = __exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}
bool exgcd(int a, int b, int c, int &x, int &y) {
    int _x, _y, g;
    g = __exgcd(a, b, _x, _y);
    if (c % g == 0) {
        x = c / g * _x;
        y = c / g * _y;
        return true;
    } else
        return false;
}

// 逆元
int inv(int primal, int modulo) {
    int x, y;
    bool flag = exgcd(primal, modulo, 1, x, y);
    return flag ? (x % modulo + modulo) % modulo : -1;
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

// 扩展大步小步
int exBSGS(int base, int rest, int modulo) {
    if (rest == 1 || modulo == 1)
        return 0;  // 特殊情况, x = 0 时最小解
    int g = __gcd(base, modulo), k = 0, na = 1;
    while (g > 1) {
        if (rest % g != 0)
            return -1;  // 无法整除则无解
        k++;
        rest /= g;
        modulo /= g;
        na = na * (base / g) % modulo;
        if (na == rest)
            return k;  // na = rest 说明前面的a的次数为 0, 只需要返回 k
        g = __gcd(base, modulo);
    }
    int f = BSGS(base, rest * inv(na, modulo) % modulo, modulo);
    if (f == -1)
        return -1;
    return f + k;
}