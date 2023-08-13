// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// exLucas 求排列组合
// 时间: O(log(MOD)log(m)) + 预处理: O(MOD)
// 要求 MOD 较小, MAX 大于 MOD
const int MAX = 1000005;
const int MOD = 999983;

// 分解质因数(无筛优化)
pair<int, int> divisors[128];
int prime_divisors(int x) {
    int cnt = 0;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0) {
            divisors[cnt] = {i, 0};
            while (x % i == 0) {
                x /= i;
                divisors[cnt].second++;
            }
            cnt++;
        }
    if (x > 1)
        divisors[cnt++] = {x, 1};
    return cnt;
}

// 预处理阶乘 及 分解质因数
int fac[MAX];
int cnt_divisors;
void init_exLucas() {
    fac[0] = 1;
    for (int i = 1; i <= MOD; i++)
        fac[i] = fac[i - 1] * i % MOD;
    cnt_divisors = prime_divisors(MOD);
}

// 快速幂
int quick_pow(int base, int exponent) {
    __int128_t res = 1;
    while (exponent) {
        if (exponent & 1)
            res *= base;
        base *= base;
        exponent >>= 1;
    }
    return res;
}
int quick_pow(int base, int exponent, int modulo) {
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

// 扩展欧几里得
int _exgcd(int a, int b, int &x, int &y) {
    int d = a;
    if (b != 0) {
        d = _exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}
inline bool exgcd(int a, int b, int c, int &x, int &y) {
    int _x, _y, g;
    g = _exgcd(a, b, _x, _y);
    if (c % g) return false;
    int p = b / g;
    x = (c / g * _x % p + p) % p;
    y = (c - a * x) / b;
    return true;
}

// 线性同余方程
inline int linear_congruence_theorem(int a, int c, int m) {
    int x, y;
    bool flag = exgcd(a, m, c, x, y);
    return flag ? x : -1;
}

// 扩欧求逆元
inline int inv(int primal, int modulo) { return linear_congruence_theorem(primal, 1, modulo); }

// 中国剩余定理(改)
int CRT(int rest[], int modulo[], int n) {
    int res = 0, M = MOD;  // 本例中 M 直接取 MOD 即可
    for (int i = 0; i < n; i++) {
        int mi = modulo[i], Mi = M / mi;
        res = (res + rest[i] * Mi * inv(Mi % mi, mi)) % M;
    }
    return res;
}

// 扩展 Lucas 定理. 时间: O(log(MOD)log(m)) + 预处理: O(MOD)
int exLucas(int m, int n) {
    if (n < 0 or n > m)
        return 0;
    static int rest[128], modulo[128];
    for (int i = 0; i < cnt_divisors; i++) {
        int p = divisors[i].first, M = quick_pow(p, divisors[i].second);
        int cnt = 0, R = 1;
        for (int i = m; i; i /= p) {
            cnt += i / p;
            R = R * fac[i % p] % M;
        }
        for (int i = n; i; i /= p) {
            cnt -= i / p;
            R = R * inv(fac[i % p], M) % M;
        }
        for (int i = m - n; i; i /= p) {
            cnt -= i / p;
            R = R * inv(fac[i % p], M) % M;
        }
        R = R * quick_pow(fac[p], cnt, M) % M;
        rest[i] = R;
        modulo[i] = M;
    }
    return CRT(rest, modulo, cnt_divisors);  // 时间: O(log(MOD))
}
