// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扩展欧几里得算法. 求解: 二元一次方程 ax + by = c. 复杂度: O(log(min(a, b))).
// 引用返回 x 最小非负整数解
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
        int p = b / g;
        x = (c / g * _x % p + p) % p;
        y = (c - a * x) / b;
        return true;
    } else
        return false;
}