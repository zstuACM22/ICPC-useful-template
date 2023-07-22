// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 米勒罗宾素性测试. 时间: O(klogn), 正确率: 1-(1/4)^k. k: 测试次数, n: 原数

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

int test[] = {2, 3, 5, 7, 233};  // 测试集: 优先使用小质数

// 米勒罗宾素性测试
bool Miller_Rabin(int n) {
    if (n < 2 or n > 2 and n % 2 == 0) return false;
    int s = n - 1;
    while (not(s & 1)) s >>= 1;
    for (int p : test) {
        if (n == p) return true;
        int t = s, m = quick_pow(p, s, n);
        while (t != n - 1 and m != 1 and m != n - 1) {
            m = (__int128_t)m * m % n;
            t <<= 1;
        }
        if (m != n - 1 and not(t & 1)) return false;
    }
    return true;
}