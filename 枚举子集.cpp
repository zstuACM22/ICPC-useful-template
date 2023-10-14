// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAX = 10000005;

int ele[MAX];

// 枚举 x 的子集, order 为全集元素个数
int enum_subset(int x, int order) {
    int cnt = 0;
    for (int i = x; i; i = (i - 1) & x)
        ele[cnt++] = i;
    ele[cnt++] = 0;
    return cnt;
}

// 枚举 x 的超集, order 为全集元素个数
int enum_superset(int x, int order) {
    int cnt = 0, full = (1ull << order) - 1;
    for (int i = x; i <= full; i = (i + 1) | x)
        ele[cnt++] = i;
    return cnt;
}

// 枚举全集的子集, order 为全集元素个数
int enum_subset_of_fullset(int order) {
    int cnt = 0;
    for (int i = (1ull << order) - 1; i >= 0; i--)
        ele[cnt++] = i;
    return cnt;
}

// 枚举全集的有 k 个元素的子集, order 为全集元素个数
int enum_k_order_subset_of_fullset(int k, int order) {
    int cnt = 0, full = (1ull << order) - 1;
    for (int i = (1ull << k) - 1, _1, _2; i <= full; _1 = i & -i, _2 = i + _1, i = ((i & ~_2) / _1 >> 1) | _2)
        ele[cnt++] = i;
    return cnt;
}