// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 欧几里得算法. 复杂度: O(lg(min(x, y))).
int __gcd(int x, int y) { return x % y ? __gcd(y, x % y) : y; }
int gcd(int x, int y) { return x > y ? __gcd(x, y) : __gcd(y, x); }