// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

const int MAX = 1000006;
std::bitset<MAX> bits;
void demo() {
    // bitset 支持一切位运算, 但有移或左移负数位会变为移动 0
    bool flag = bits.all();                 // ~bits == 0
    bool flag = bits.any();                 // bits != 0
    bool flag = bits.none();                // bits == 0
    std::bitset<MAX> bits2 = bits.flip();   // ~bits
    unsigned long long siz = bits.count();  // 计数 1
}