// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
给定一个长度为 n (n <= 1e5) 的序列, 对于 q (q <= 1e5) 询问区间 [l, r], 求 [l, r] 的幂塔。
*/


const int MAX = 100005;

// 欧拉函数
int _euler(int x) {
    if (x < 2) 
        return 0;
    int res = x;
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) 
        res = res / x * (x - 1);
    return res;
}
inline int euler(int x) {
    static int old = -1, res = -1;
    if (x == old) return res;
    old = x, res = _euler(x);
    return res;
}

#define mm_ex(x, modulo) ((x) < (modulo) ? (x) : (x) % (modulo) + (modulo))

// 快速幂
int quick_pow(int base, int exponent, int modulo) {
    int res = mm_ex(1, modulo);
    base = mm_ex(base, modulo);
    while (exponent) {
        if (exponent & 1) {
            res = mm_ex(res * base, modulo);
        }
        base = mm_ex(base * base, modulo);
        exponent >>= 1;
    }
    return res;
}

// 预处理欧拉函数迭代
int euler_iter[MAX];
void load_euler_ex(int x) {
    int cnt = 0;
    while (x) {
        euler_iter[cnt++] = x;
        x = euler(x);
    }
}

// 递归解幂塔
int a[MAX];
int calc(int l, int r, int i) {
    if (l == r or euler_iter[i] == 1) return mm_ex(a[l], euler_iter[i]);
    return quick_pow(a[l], calc(l + 1, r, i + 1), euler_iter[i]);
}

void solve() {
    int n, m;
    cin >> n >> m;
    load_euler_ex(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << calc(l - 1, r - 1, 0) % m << endl;
    }
}