// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扩展中国剩余定理
// 求解多组同余方程组 x % m[i] == a[i], 不要求 m[i] 互质, 小心爆 int64_t
// 求解最小解 x, 通解为 x + k * M (M: modulo 求 lcm 积)
const int MAX = 100005;
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

inline int linear_congruence_theorem(int a, int c, int m) {
    int x, y;
    bool flag = exgcd(a, m, c, x, y);
    return flag ? (x % m + m) % m : -1;
}

// 扩展中国剩余定理. 返回: 最小正整数解, 通解为 res + k * M (M: modulo 求 lcm 积)
int exCRT(int rest[], int modulo[], int n) {
    int M = 1, res = 1;
    for (int i = 0; i < n; i++) {
        int r = rest[i], m = modulo[i];
        int t = linear_congruence_theorem(M, ((r - res) % m + m) % m, m);
        if (t == -1) return -1;
        res = res + t * M;
        M = M / __gcd(m, M) * m;
        res = res % M;
    }
    return res;
}