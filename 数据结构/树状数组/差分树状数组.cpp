// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 树状数组. 时间: O(logn), 内存: O(n)
const int MAX = 100005;
 
int n;
int a[MAX];         // 1-index
int tr[MAX] = {0};  // 1-index

#define lowbit(x) ((x) & -(x))

// 建树. 时间: O(n)
void build() {
    for (int i = 1; i <= n; i++)
        tr[i] = a[i] - a[i - lowbit(i)];
}

// 单点修改. 时间: O(logn)
void add(int l, int r, int x) {
    for (; l <= n; l += lowbit(l))
        tr[l] += x;
    for (r++; r <= n; r += lowbit(r))
        tr[r] -= x;
}

// 区间查询. 时间: O(logn)
int query(int idx) {
    int x = 0;
    for (; idx; idx -= lowbit(idx))
        x += tr[idx];
    return x;
}
