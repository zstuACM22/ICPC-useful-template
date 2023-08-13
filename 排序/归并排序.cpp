// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 归并排序. 如果必要, 使用_merge_sort, 其l/r是包含的. 时间: O(nlogn), 空间: O(n)
void _merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    _merge_sort(q, l, mid);
    _merge_sort(q, mid + 1, r);
    int *tmp = new int[r - l + 1] - l;
    int k = l, i = l, j = mid + 1;
    while (i <= mid and j <= r)
        if (q[i] <= q[j])
            tmp[k++] = q[i++];
        else
            tmp[k++] = q[j++];
    while (i <= mid)
        tmp[k++] = q[i++];
    while (j <= r)
        tmp[k++] = q[j++];
    for (i = l; i <= r; i++)
        q[i] = tmp[i];
    delete [](tmp + l);
}
void merge_sort(int q[], int n) { _merge_sort(q, 0, n - 1); }