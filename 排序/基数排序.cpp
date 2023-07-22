// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 基数排序. 时间: O(长度log_{基数}{值域}). 空间: O(长度+基数)
// 参数: q: 待排序序列, n: 序列长度, low_bound: 值域下界(含), up_bound: 值域上界(不含), radix_bit: 排序基数位数
// radix_bit: 8 或 16
void radix_sort(int q[], int n, int low_bound, int up_bound, int radix_bit) {
    int radix = 1ull << radix_bit, mask = (1ull << radix_bit) - 1;
    int *tmp = new int[n], *p = tmp;
    int *buk = new int[radix];
    if (low_bound > up_bound) swap(low_bound, up_bound);
    for (int i = 0; i < n; i++) q[i] -= low_bound;
    up_bound -= low_bound;
    for (int offset = 0; up_bound; offset += radix_bit, up_bound >>= radix_bit) {
        for (int i = 0; i < radix; i++) buk[i] = 0;
        for (int i = 0; i < n; i++) buk[q[i] >> offset & mask]++;
        for (int i = 1; i < radix; i++) buk[i] += buk[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--buk[q[i] >> offset & mask]] = q[i];
        swap(p, q);
    }
    if (q == tmp) {
        swap(p, q);
        for (int i = 0; i < n; i++) q[i] = p[i];
    }
    for (int i = 0; i < n; i++) q[i] += low_bound;
    delete[] tmp;
}