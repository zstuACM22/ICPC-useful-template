// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 中国剩余定理. 时间: O(n log(max(modulo)))
// 求解多组同余方程组 x % m[i] == a[i], 要求 m[i] 互质
// 求解最小解 x, 通解为 x + k * M (M: modulo 求 lcm 积)
const int MAX = 100005;

// 扩欧
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

// 线性同余
inline int linear_congruence_theorem(int a, int c, int m) {
    int x, y;
    bool flag = exgcd(a, m, c, x, y);
    return flag ? x : -1;
}

// 扩欧求逆元
inline int inv(int primal, int modulo) { return linear_congruence_theorem(primal, 1, modulo); }

// 中国剩余定理. 返回: 最小正整数解
int CRT(int rest[], int modulo[], int n) {
    int M = 1;
    for (int i = 0; i < n; i++)
        M *= modulo[i];  // 这里如果爆 int64_t 考虑使用前后缀或 __int128_t
    int res = 0;
    for (int i = 0; i < n; i++) {
        int mi = modulo[i], Mi = M / mi;
        res = (res + rest[i] * Mi * inv(Mi % mi, mi)) % M;
    }
    return res;
}
