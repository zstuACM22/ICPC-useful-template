// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 欧几里得算法. 复杂度: O(lg(min(x, y))).
int _gcd(int x, int y) { return x % y ? _gcd(y, x % y) : y; }
int gcd(int x, int y) { return x > y ? _gcd(x, y) : _gcd(y, x); }

// 二进制欧几里得算法. 卡常
#define ctz __builtin_ctzll
int binary_gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    int az = ctz(a);
    int bz = ctz(b);
    int z = min(az, bz);
    b >>= bz;
    while (a) {
        a >>= az;
        int diff = a - b;
        az = ctz(diff);
        b = min(a, b), a = abs(diff);
    }
    return b << z;
}