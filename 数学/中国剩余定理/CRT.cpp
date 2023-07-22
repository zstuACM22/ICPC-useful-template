// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 中国剩余定理
// 求解多组同余方程组 x % m[i] == a[i], 要求 m[i] 互质
const int MAX = 100005;

int __exgcd(int a, int b, int &x, int &y) {
    int d = a;
    if (b != 0) {
        d = __exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}
bool exgcd(int a, int b, int c, int &x, int &y) {
    int _x, _y, g;
    g = __exgcd(a, b, _x, _y);
    if (c % g == 0) {
        x = c / g * _x;
        y = c / g * _y;
        return true;
    } else
        return false;
}

int inv(int primal, int modulo) {
    int x, y;
    bool flag = exgcd(primal, modulo, 1, x, y);
    return flag ? (x % modulo + modulo) % modulo : -1;
}

int modulo[MAX];
int rest[MAX];

// 中国剩余定理. 返回: 最小正整数解, 通解为 res + k * M (M: modulo 求积)
int CRT(int n) {
    int M = 1;
    for (int i = 0; i < n; i++) {
        M *= modulo[i];
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        int mi = modulo[i], Mi = M / mi;
        res += rest[i] * Mi * inv(Mi % mi, mi);
    }
    return res % M;
}
