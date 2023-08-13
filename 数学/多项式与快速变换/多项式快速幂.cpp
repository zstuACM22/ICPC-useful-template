// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 多项式快速幂. 时间: O(nlog(n)log(exponent))
const int MAX = 100005;
const int MOD = 998244353;
const int EULER_MOD = MOD - 1;              // 模的欧拉函数, 用于欧拉降幂
const int EULER_MOD_MOD = EULER_MOD * MOD;  // 欧拉函数与模的乘积, 用于取多项式降幂的有效余数
const int MIN_ROOT = 3;                     // 模的最小原根, 用于快速数论变换
const int INV_ROOT = 332748118;             // 最小原根的逆元, 用于逆快速数论变换

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

// 欧拉降幂
inline int exeuler(int base, int exponent) {
    if (exponent < MOD)
        return quick_pow(base, exponent);
    else if (__gcd(base, MOD) == 1)
        return quick_pow(base, exponent % EULER_MOD);
    else
        return quick_pow(base, exponent % EULER_MOD + EULER_MOD);
}

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

// 多项式带模(x^n)自乘(已预处理)
void NTT_self_mul_mod(int A[], int b[], int n, int lim) {
    static int B[MAX << 2];
    _NTT<true>(A, lim);
    if (A == b) {
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * A[i] % MOD;
    } else {
        memcpy(B, b, sizeof(int) * n);
        _NTT<true>(B, lim);
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * B[i] % MOD;
        memset(B, 0, sizeof(int) * lim);
    }
    _NTT<false>(A, lim);
    memset(A + n, 0, sizeof(int) * (lim - n));
}

// 多项式快速幂(带预处理). 时间: O(nlog(n)log(exponent))
void NTT_quick_pow(int base[], int n, int exponent, int res[]) {
    static int RES[MAX << 2], BASE[MAX << 2];
    memset(RES, 0, sizeof(int) * n);
    RES[0] = 1;
    memcpy(BASE, base, sizeof(int) * n);
    int l = 0, lim = 1;
    while (lim < n + n - 1) {
        lim <<= 1;
        l++;
    }
    for (int i = 0; i < lim; i++)
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << (l - 1);
    while (exponent) {
        if (exponent & 1) {
            NTT_self_mul_mod(RES, BASE, n, lim);
        }
        NTT_self_mul_mod(BASE, BASE, n, lim);
        exponent >>= 1;
    }
    memcpy(res, RES, sizeof(int) * n);
}

// 多项式自乘常数
inline void poly_self_mul(int a[], int n, int x) {
    for (int i = 0; i < n; i++)
        a[i] = a[i] * x % MOD;
}

// 多项式降幂. 降幂后时间: O(nlog(n)log(exponent % MOD))
// 要求 n <= MOD, 否则也可以降幂但相对复杂, 该函数不适用
void NTT_desc_pow(int base[], int n, const char exponent[], int m, int res[]) {
    uint64_t e = 0;
    bool flag = false;
    for (int i = 0; i < m; i++) {
        e = (e * 10 + (exponent[i] - '0'));
        if (e >= EULER_MOD_MOD) {
            flag = true;
            e %= EULER_MOD_MOD;
        }
    }
    int e1 = e / MOD, e2 = e % MOD;
    if (flag) e1 += EULER_MOD;
    NTT_quick_pow(base, n, e2, res);
    int x = exeuler(base[0], e1);
    poly_self_mul(res, n, x);
}
