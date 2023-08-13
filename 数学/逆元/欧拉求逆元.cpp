// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Useless - 欧拉求逆元. 不要求模是质数. 时间: O(log(MOD)) + 预处理 O(log(MOD)) -> O(MOD^0.5)
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

// 欧拉函数
int _euler(int x) {
    int res = x;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}
inline int euler(int x) {
    static int old = -1, res = -1;
    if (x == old) return res;
    old = x, res = _euler(x);
    return res;
}

// 欧拉函数求逆元
inline int inv(int primal) {
    int res = quick_pow(primal, euler(MOD) - 1);
    return primal * res % MOD == 1 ? res : -1;
}