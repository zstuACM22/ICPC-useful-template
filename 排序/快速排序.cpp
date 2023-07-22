// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 快速排序. 如果必要, 使用__quick_sort, 其l/r是包含的. 时间: O(nlogn) -> O(n^2), 空间: O(nlogn)
void __quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        do i++;
        while (q[i] < x);
        do j--;
        while (q[j] > x);
        if (i < j)
            swap(q[i], q[j]);
    }
    __quick_sort(q, l, j);
    __quick_sort(q, j + 1, r);
}
void quick_sort(int q[], int n) { __quick_sort(q, 0, n - 1); }