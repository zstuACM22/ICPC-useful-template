// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 原根
const int MAX = 1000005;

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

// 欧拉函数
int euler(int x) {
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

// 原根. 返回原根个数
int root[MAX];  // 原根
int primitive_root(int modulo) {
    int phi = euler(modulo);
    int cnt_divisors = prime_divisors(phi);
    int min_root = -1, cnt = 0;
    for (int g = 1; g < modulo; g++) {
        if (__gcd(g, modulo) > 1) continue;
        bool flag = true;
        for (int i = 0; i < cnt_divisors; i++)
            if (quick_pow(g, phi / divisors[i], modulo) == 1) {
                flag = false;
                break;
            }
        if (flag) {
            min_root = g;  // 最小原根
            break;
        }
    }
    if (min_root == -1) return 0;
    for (int x = 1, g = min_root; x <= phi; x++, g = g * min_root % modulo) {
        if (__gcd(x, phi) == 1) {
            root[cnt++] = g;
        }
    }
    sort(root, root + cnt);
    return cnt;
}