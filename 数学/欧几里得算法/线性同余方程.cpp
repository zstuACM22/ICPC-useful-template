// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 线性同余方程
const int MOD = 1000000007;

// 扩展欧几里得算法. 求解: 二元一次方程 ax + by = c. 复杂度: O(log(min(a, b))).
// 引用参数返回 x 最小非负整数解
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

// 线性同余方程. 依赖: exgcd. 求解: 线性同余方程 ax = c (mod m). 返回: 有解: x, 无解: -1. 复杂度: O(log(min(a, m))).
inline int linear_congruence_theorem(int a, int c, int m = MOD) {
    int x, y;
    bool flag = exgcd(a, m, c, x, y);
    return flag ? x : -1;
}