// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 逆康托展开. 计算第排名的 1..n 的排列
const int MAX = 100005;
const int MOD = 1000000007;

int n;          // 序列长度
int perm[MAX];  // 序列, 输出. 0-index

// 逆康托展开. 0-index, 时间: O(n^2)
bool vis[MAX];
bool arcCantor(int rank) {
    memset(vis, 0, sizeof(bool) * (n + 1));
    for (int i = n - 1; i >= 0; i--) {
        perm[i] = rank % (n - i);
        rank /= (n - i);
    }
    if (rank) return false;
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