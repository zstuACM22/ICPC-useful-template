// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 快速数论变换(NTT). 时间: O(nlogn)
const int MAX = 100005;
const int MOD = 998244353;
const int MIN_ROOT = 3;
const int INV_ROOT = 332748118;

// 要求模数必须为 NTT 模数, 下面为常用的 MOD / MIN_ROOT / INV_ROOT
// 对于质数 P=2^A*X+1, 可用作长度 2^A 的 NTT. A 越大越适合作为 NTT 模数
const int NTT_MOD[][3] = {
    {469762049, 3, 156587350},  // 2 ^ 26 * 7   + 1
    {998244353, 3, 332748118},  // 2 ^ 23 * 119 + 1
    {1004535809, 3, 334845270}  // 2 ^ 21 * 479 + 1
};

#define mm_add(x) ((x) >= MOD ? (x)-MOD : (x))
#define mm_sub(x) ((x) < 0 ? (x) + MOD : (x))

// 快速幂
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

// 逆元
inline int inv(int primal) { return quick_pow(primal, MOD - 2); }

// 快速数论变换. FORWARD: 正变换, 否则为逆变换
int tax[MAX << 2];  // 最好开 4 倍内存, 后同, 严格内存: O(2^ceil(log2(n+m-1)))
template <bool FORWARD>
void _NTT(int A[], int lim) {
    for (int i = 0; i < lim; i++)
        if (i < tax[i])
            swap(A[i], A[tax[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        int Wn = quick_pow(FORWARD ? MIN_ROOT : INV_ROOT, (MOD - 1) / (mid << 1));
        for (int j = 0, R = mid << 1; j < lim; j += R) {
            int w = 1;
            for (int k = 0; k < mid; k++, w = w * Wn % MOD) {
                int x = A[j + k], y = w * A[j + mid + k] % MOD;
                A[j + k] = mm_add(x + y);
                A[j + mid + k] = mm_sub(x - y);
            }
        }
    }
    if (not FORWARD) {
        int inv_lim = inv(lim);
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * inv_lim % MOD;
    }
}

// 快速数论卷积. 时间: O((n + m)log(n + m))
// 请保证 res 数组长度 >= n + m - 1
int NTT(int a[], int n, int b[], int m, int res[]) {
    static int A[MAX << 2], B[MAX << 2];
    memcpy(A, a, sizeof(int) * n);
    memcpy(B, b, sizeof(int) * m);
    int l = 0, lim = 1;
    while (lim < n + m - 1) {
        lim <<= 1;
        l++;
    }
    for (int i = 0; i < lim; i++)
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << (l - 1);
    _NTT<true>(A, lim);
    _NTT<true>(B, lim);
    for (int i = 0; i < lim; i++)
        A[i] = A[i] * B[i] % MOD;
    _NTT<false>(A, lim);
    memset(B, 0, sizeof(int) * lim);  // 未作逆变换的需置零, 以备下次调用
    memcpy(res, A, sizeof(int) * (n + m - 1));
    return n + m - 1;
}
