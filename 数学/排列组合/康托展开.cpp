// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 康托展开
const int MOD = 1000000007;
const int MAX = 100005;

int n;          // 序列长度
int perm[MAX];  // 序列

// 树状数组
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
int cantor() {
    int fac = 1, sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum = (sum + fac * query(perm[i])) % MOD;
        add(perm[i], 1);
        fac = fac * (n - i) % MOD;
    }
    return sum;
}

// 逆康托展开. 0-index, 时间: O(n^2)
bool vis[MAX];
bool arc_cantor(int x) {
    fill(vis, vis + n + 1, false);
    for (int i = n - 1; i >= 0; i--) {
        perm[i] = x % (n - i);
        x /= (n - i);
    }
    if (x) return false;
    for (int i = 0; i < n; i++) {
        int k = 0;
        for (int j = 0; j <= perm[i]; j++) {
            k++;
            while (vis[k]) 
                k++;
        }
        perm[i] = k;
        vis[k] = true;
    }
    return true;
}