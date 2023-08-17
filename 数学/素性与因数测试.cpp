// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 两种针对大数分解的概率算法. 其中 Miller Rabin 概率正确, Pollard Rho 期望时间.
// Miller Rabin 素性测试. 时间: O(klogn), 正确率: 1-(1/4)^k. k: 测试次数, n: 原数
// Pollard Rho 因数测试. 时间: O(n^0.25), 仅测试因数, 不保证为质数

// 浮点乘
// inline int mul(int x, int y, int modulo) {
//     int d = (long double)x / modulo * y + 0.5;
//     int r = x * y - d * modulo;
//     if (r < 0) r += modulo;
//     return r;
// }

// 快速幂
int quick_pow(__int128_t base, int exponent, int modulo) {
    __int128_t res = 1 % modulo;
    base %= modulo;
    while (exponent) {
        if (exponent & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exponent >>= 1;
    }
    return res;
}

// Miller Rabin 素性测试
// 154590409516822759, 2305843009213693951, 4384957924686954497
int test[] = {
    2,  3,  5,  7,  11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47,
    79, 83, 89, 97, 233,
};  // 测试集: 优先使用小质数
bool Miller_Rabin(int n) {
    if (n < 2 or n > 2 and n % 2 == 0)
        return false;
    int s = n - 1;
    while (not(s & 1)) s >>= 1;
    for (int p : test) {
        if (n == p)
            return true;
        __int128_t t = s, m = quick_pow(p, s, n);
        while (t != n - 1 and m != 1 and m != n - 1) {
            m = m * m % n;
            t <<= 1;
        }
        if (m != n - 1 and not(t & 1))
            return false;
    }
    return true;
}

// 随机数生成器
mt19937 rnd((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r = 0) {
    if (l > r) swap(l, r);
    return rnd() % (r - l + 1) + l;
}

// Pollard Rho 因数测试
int Pollard_Rho(int n) {
    if (n % 2 == 0)  // Pollard 不能判 4
        return 2;
    if (Miller_Rabin(n))
        return n;
    while (true) {
        int c = randint(1, n - 1);
        auto nxt = [&](__int128_t x) -> int { return (x * x + c) % n; };
        int turtle = 1, rabbit = -1;
        __int128_t mul = 1;
        while (turtle != rabbit) {
            for (int i = 0; i < 128; i++) {
                turtle = nxt(turtle);
                rabbit = nxt(nxt(rabbit));
                __int128_t tmp = mul * abs(turtle - rabbit) % n;
                // 龟兔相遇或积将为 0 退出
                if (turtle == rabbit or tmp == 0)
                    break;
                mul = tmp;
            }
            int g = __gcd((int)mul, n);
            if (g > 1)
                return g;
        }
    }
}

// 分解质因数
int divisors[128];
int prime_divisors(int x) {
    int cnt = 0, p = 0;
    divisors[cnt++] = x;
    while (p < cnt) {
        int x = divisors[p];
        int tmp = Pollard_Rho(x);
        if (tmp == x) {
            p++;
        } else {
            divisors[p] = tmp;
            divisors[cnt++] = x / tmp;
        }
    }
    sort(divisors, divisors + cnt);
    return cnt;
}