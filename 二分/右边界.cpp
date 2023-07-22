// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 二分查找, 返回首个大于索引.
int binary_search_upper(int q[], int n, int value) {
    int i = 0, j = n - 1;
    while (i <= j) {
        int m = (i + j) / 2;
        if (q[m] <= value)
            i = m + 1;
        else
            j = m - 1;
    }
    return i;
}