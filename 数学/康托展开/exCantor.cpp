// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扩展康托展开. 求任意排列的排名, 排列可以包含重复元素
const int MAX = 100005;
const int MOD = 1000000007;

int n;          // 序列长度
int perm[MAX];  // 序列, 输入. 0-index

// 费马小定理求逆元
int quick_pow(int base, int exponent) {
    int res = 1 % MOD;
    base %= MOD;
    while (exponent) {
        if (exponent & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return res;
}
inline int inv(int primal) { return quick_pow(primal, MOD - 2); }

// 树状数组. 1-index
int tr[MAX];
#define lowbit(x) ((x) & -(x))
void inc(int idx) {
    for (; idx <= n; idx += lowbit(idx))
        tr[idx]++;
}
int query(int idx) {
    int res = 0;
    for (; idx; idx -= lowbit(idx))
        res += tr[idx];
    return res;
}

// 离散化. 0-index
int M[MAX];
int cntM = 0;
#define arcM(x) (lower_bound(M, M + cntM, (x)) - M)

// 扩展康托展开. 0-index, 时间: O(nlogn)
int cnt[MAX];  // 每个元素出现次数
void exCantor() {
    memset(cnt, 0, sizeof(int) * (n + 1));
    memset(tr, 0, sizeof(int) * (n + 1));
    cntM = n;
    memcpy(M, perm, sizeof(int) * n);
    sort(M, M + cntM);
    cntM = unique(M, M + cntM) - M;
    int fac = 1, rank = 0;
    for (int i = n - 1; i >= 0; i--) {
        int idx = arcM(perm[i]) + 1;
        cnt[idx]++;
        inc(idx);
        fac = fac * inv(cnt[idx]) % MOD;
        rank = (rank + fac * query(idx - 1)) % MOD;
        fac = fac * (n - i) % MOD;
    }
    cout << rank << endl;
}