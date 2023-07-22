// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

void demo() {
    __builtin_clz(0x34);       // 计数前导零 (count leading zero)  681ms  per 1e9 times 均摊 40x
    __builtin_ctz(0x34);       // 计数后继零 (count trailing zero) 715ms  per 1e9 times 均摊 2.5x 最优 40x
    __builtin_popcount(0x34);  // 计数一的个数                     1865ms per 1e9 times 均摊 10x
}