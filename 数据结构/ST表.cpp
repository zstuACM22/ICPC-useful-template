// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// ST表 - 以 区间最大值 为例. 时间: O(1) + 预处理: O(nlogn), 内存: O(nlogn)
// 1-index
const int MAX = 100005;
const int LOG = 17;

int lg2[MAX];
int a[MAX];
int st[MAX][LOG];

inline void load_lg2(int n) {
    lg2[0] = -1;
    for (int i = 1; i <= n; i++)
        lg2[i] = lg2[i >> 1] + 1;
}

inline void build(int n) {
    for (int i = 1; i <= n; i++)
        st[i][0] = a[i];
    for (int j = 1, v = 1; v < n; j++, v <<= 1)
        for (int i = 1; i <= n; i++)
            st[i][j] = max(st[i][j - 1], st[min(i + v, n)][j - 1]);  // Attention
}

inline int query(int l, int r) {
    int u = lg2[r - l + 1];
    return max(st[l][u], st[r - (1 << u) + 1][u]);  // Attention
}