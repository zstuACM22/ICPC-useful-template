// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 任意模数快速数论变换(MTT). 时间: O(3nlogn)
// 要求 min(n, m)*A^2 < 4e26 (A:值域)
const int MAX = 100005;
const int ANY_MOD = 1000000007;

#define mm_add(x) ((x) >= MOD ? (x)-MOD : (x))
#define mm_sub(x) ((x) < 0 ? (x) + MOD : (x))

// 快速幂
template <int MOD>
constexpr int quick_pow(int base, int exponent) {
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
template <int MOD>
constexpr inline int inv(int primal) { return quick_pow<MOD>(primal, MOD - 2); }

// 多模数 NTT 参数. 使用常量加速运算
constexpr int NTT_MOD_1 = +469762049, NTT_MIN_ROOT_1 = 3, NTT_INV_ROOT_1 = inv<NTT_MOD_1>(NTT_MIN_ROOT_1);
constexpr int NTT_MOD_2 = +998244353, NTT_MIN_ROOT_2 = 3, NTT_INV_ROOT_2 = inv<NTT_MOD_2>(NTT_MIN_ROOT_2);
constexpr int NTT_MOD_3 = 1004535809, NTT_MIN_ROOT_3 = 3, NTT_INV_ROOT_3 = inv<NTT_MOD_3>(NTT_MIN_ROOT_3);
constexpr __int128_t NTT_CRT_1 = (__int128_t)NTT_MOD_2 * NTT_MOD_3 * inv<NTT_MOD_1>(NTT_MOD_2 * NTT_MOD_3);
constexpr __int128_t NTT_CRT_2 = (__int128_t)NTT_MOD_1 * NTT_MOD_3 * inv<NTT_MOD_2>(NTT_MOD_1 * NTT_MOD_3);
constexpr __int128_t NTT_CRT_3 = (__int128_t)NTT_MOD_1 * NTT_MOD_2 * inv<NTT_MOD_3>(NTT_MOD_1 * NTT_MOD_2);
constexpr __int128_t NTT_CRT_MOD = (__int128_t)NTT_MOD_1 * NTT_MOD_2 * NTT_MOD_3;  // 471064322751194440790966273

// 快速数论变换. FORWARD: 正变换, 否则为逆变换
int tax[MAX << 2];  // 最好开 4 倍内存, 后同, 严格内存: O(2^ceil(log2(n+m-1)))
template <int MOD, int MIN_ROOT, int INV_ROOT, bool FORWARD>
void _NTT(int A[], int lim) {
    for (int i = 0; i < lim; i++)
        if (i < tax[i])
            swap(A[i], A[tax[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        int Wn = quick_pow<MOD>(FORWARD ? MIN_ROOT : INV_ROOT, (MOD - 1) / (mid << 1));
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
        int inv_lim = inv<MOD>(lim);
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * inv_lim % MOD;
    }
}

// 快速数论卷积(已预处理)
template <int MOD, int MIN_ROOT, int INV_ROOT>
void NTT(int a[], int n, int b[], int m, int lim, int res[]) {
    static int A[MAX << 2], B[MAX << 2];
    memcpy(A, a, sizeof(int) * n);
    memcpy(B, b, sizeof(int) * m);
    _NTT<MOD, MIN_ROOT, INV_ROOT, true>(A, lim);
    _NTT<MOD, MIN_ROOT, INV_ROOT, true>(B, lim);
    for (int i = 0; i < lim; i++)
        A[i] = A[i] * B[i] % MOD;
    _NTT<MOD, MIN_ROOT, INV_ROOT, false>(A, lim);
    memset(B, 0, sizeof(int) * lim);  // 未作逆变换的需置零, 以备下次调用
    memcpy(res, A, sizeof(int) * (n + m - 1));
}

// 任意模数快速数论卷积. 时间: O(3(n + m)log(n + m))
// 请保证 res 数组长度 >= n + m - 1
int MTT(int a[], int n, int b[], int m, int res[]) {
    static int RES1[MAX << 1];
    static int RES2[MAX << 1];
    static int RES3[MAX << 1];
    int l = 0, lim = 1;
    while (lim < n + m - 1) {
        lim <<= 1;
        l++;
    }
    for (int i = 0; i < lim; i++)
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << (l - 1);
    // 多模数 NTT
    NTT<NTT_MOD_1, NTT_MIN_ROOT_1, NTT_INV_ROOT_1>(a, n, b, m, lim, RES1);
    NTT<NTT_MOD_2, NTT_MIN_ROOT_2, NTT_INV_ROOT_2>(a, n, b, m, lim, RES2);
    NTT<NTT_MOD_3, NTT_MIN_ROOT_3, NTT_INV_ROOT_3>(a, n, b, m, lim, RES3);
    // 中国剩余定理
    for (int i = n + m - 2; i >= 0; i--) {
        __int128_t tmp = 0;
        tmp += NTT_CRT_1 * RES1[i];
        tmp += NTT_CRT_2 * RES2[i];
        tmp += NTT_CRT_3 * RES3[i];
        res[i] = tmp % NTT_CRT_MOD % ANY_MOD;
    }
    return n + m - 1;
}
