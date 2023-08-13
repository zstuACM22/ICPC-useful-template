// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扩欧求逆元. 不要求模是质数. 复杂度: O(log(modulo))
const int MOD = 1000000007;

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

// 扩展欧几里得求逆元
inline int inv(int primal) { return linear_congruence_theorem(primal, 1, MOD); }