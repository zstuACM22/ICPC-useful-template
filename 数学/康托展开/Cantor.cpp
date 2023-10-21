// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 康托展开. 计算 1..n 的排列的排名
const int MAX = 100005;
const int MOD = 1000000007;

int n;          // 序列长度
int perm[MAX];  // 序列, 输入. 0-index

// 树状数组. 1-index
int tr[MAX];
#define lowbit(x) ((x) & -(x))
void add(int idx, int x) {
    for (; idx <= n; idx += lowbit(idx))
        tr[idx] += x;
}
int query(int idx) {
    int res = 0;
    for (; idx; idx -= lowbit(idx))
        res += tr[idx];
    return res;
}

// 康托展开. 0-index, 时间: O(nlogn)
int Cantor() {
    memset(tr, 0, sizeof(int) * (n + 1));
    int fac = 1, rank = 0;
    for (int i = n - 1; i >= 0; i--) {
        rank = (rank + fac * query(perm[i])) % MOD;
        add(perm[i], 1);
        fac = fac * (n - i) % MOD;
    }
    return rank;
}