// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 高阶子集和动态规划. 时间: O(2^n)
// 优化前: O(3^n) O(n 2^n)
const int MAX = 20;

int a[1ull << MAX];
int sosdp[1ull << MAX];

void SumOfSubset(int n) {
    const int MASK = 1ull << MAX;
    for (int x = 0; x <= MASK; x++)
        sosdp[x] = a[x];
    for (int i = 0, w = 1; i < n; i++, w <<= 1)
        for (int x = 0; x <= MASK; x++)
            if (x & w)
                sosdp[x] += sosdp[x ^ w];
}

void SumOfSuperset(int n) {
    const int MASK = 1ull << MAX;
    for (int x = 0; x <= MASK; x++)
        sosdp[x] = a[x];
    for (int i = 0, w = 1; i < n; i++, w <<= 1)
        for (int x = MASK; x >= 0; x--)
            if (~x & w)
                sosdp[x] += sosdp[x ^ w];
}