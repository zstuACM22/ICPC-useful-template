// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扩展欧几里得算法求逆元. 依赖: exgcd. 复杂度: O(log(modulo))
const int MOD = 1000000007;

// 扩展欧几里得算法. 求解: 二元一次方程 ax + by = c. 返回: bool-有解. 复杂度: O(lg(min(a, b))).
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

int inv(int primal, int modulo = MOD) {
    int x, y;
    bool flag = exgcd(primal, modulo, 1, x, y);
    return flag ? (x % modulo + modulo) % modulo : -1;
}