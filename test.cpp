// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
// #pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

inline int test___builtin_clz(int x) {
    return __builtin_clz(x);
}

inline int test_clz(int x) {
    int cnt = 0;
    while (x) {
        x >>= 1;
        cnt++;
    }
    return sizeof(x) * 8 - cnt;
}

inline int test___builtin_ctz(int x) {
    return __builtin_ctz(x);
}

inline int test_ctz(int x) {
    int cnt = 0;
    while (!(x & 1)) {
        x >>= 1;
        cnt++;
    }
    return cnt;
}

inline int test_ctz_log2(int x) {
    x &= -x;
    return __builtin_log2(x);
}

inline int test___builtin_popcount(int x) {
    return __builtin_popcount(x);
}

inline int test_popcount(int x) {
    int cnt = 0;
    while (x) {
        x ^= x & -x;
        cnt++;
    }
    return cnt;
}

signed main() {
    const int N = 1e9;
    clock_t start_time;

    start_time = clock();
    for (int i = 1; i <= N; i++) {
        sqrt(i);
    }
    cout << (double)(clock() - start_time) << endl;

    start_time = clock();
    for (int i = 1; i <= N; i++) {
        __builtin_sqrt(i);
    }
    cout << (double)(clock() - start_time) << endl;

    return 0;
}