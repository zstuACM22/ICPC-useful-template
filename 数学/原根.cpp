// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 原根. 时间: 最小原根: O(n^0.25*log(n)), 所有原根: O(euler(n))
const int MAX = 1000005;
const int USEFUL_MIN_ROOT[][2] = {
    {998244353, 3},
    {1000000007, 5},
    {1000000009, 13},
    {1004535809, 3}
};  // 998244353 * 1004535809 > 1e18

// 快速幂
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

// 欧拉函数
int _euler(int x) {
    if (x < 2)
        return 0;
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

// 线性筛
bool vis[MAX] = {0};
int prime[MAX];  // 质数
int prime_sieve_euler(int n) {
    int cnt = 0;
    vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (not vis[i])
            prime[cnt++] = i;  // 质数
        for (int j = 0; j < cnt and prime[j] * i <= n; j++) {
            vis[prime[j] * i] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    return cnt;
}

// 分解质因数
int divisors[MAX];  // 质因数
int prime_divisors(int x) {
    int cnt = 0;
    for (int i = 0; prime[i] <= x / prime[i]; i++)
        if (x % prime[i] == 0) {
            divisors[cnt] = prime[i];
            while (x % prime[i] == 0)
                x /= prime[i];
            cnt++;
        }
    if (x > 1)
        divisors[cnt++] = x;
    return cnt;
}

// 最小原根. 时间: O(modulo^0.25*log(modulo))
int _min_root(int modulo) {
    int cnt_divisors = prime_divisors(euler(modulo));
    int res = -1, cnt = 0;
    for (int g = 1; g < modulo; g++) {
        if (__gcd(g, modulo) > 1) continue;
        bool flag = true;
        for (int i = 0; i < cnt_divisors; i++)
            if (quick_pow(g, euler(modulo) / divisors[i], modulo) == 1) {
                flag = false;
                break;
            }
        if (flag) {
            res = g;
            break;
        }
    }
    return res;
}
inline int min_root(int modulo) {
    static int old = -1, res = -1;
    if (modulo == old) return res;
    old = modulo, res = _min_root(modulo);
    return res;
}

// 原根. 返回原根个数. 时间: O(euler(modulo))
int root[MAX];  // 原根
int primitive_root(int modulo) {
    if (min_root(modulo) == -1) return 0;
    int cnt = 0;
    for (int x = 1, g = min_root(modulo); x <= euler(modulo); x++, g = g * min_root(modulo) % modulo)
        if (__gcd(x, euler(modulo)) == 1)
            root[cnt++] = g;
    sort(root, root + cnt);
    return cnt;
}