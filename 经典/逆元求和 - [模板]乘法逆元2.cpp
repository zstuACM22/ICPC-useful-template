// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# 【模板】乘法逆元 2

## 题目描述

给定 $n$ 个正整数 $a_i$ ，求它们在模 $p$ 意义下的乘法逆元。

由于输出太多不好，所以将会给定常数 $k$，你要输出的答案为：  
$$\sum\limits_{i=1}^n\frac{k^i}{a_i}$$

答案对 $p$ 取模。

## 输入格式

第一行三个正整数 $n,p,k$，意义如题目描述。  
第二行 $n$ 个正整数 $a_i$，是你要求逆元的数。

## 输出格式

输出一行一个整数，表示答案。

## 样例 #1

### 样例输入 #1

```
6 233 42
1 4 2 8 5 7
```

### 样例输出 #1

```
91
```

## 提示

对于 $30\%$ 的数据，$1\le n \le 10^5$。

对于 $100\%$ 数据，$1\le n \le 5\times 10^6$，$2\le k < p \le 10^9$，$1\le a_i < p$，保证 $p$ 为质数。
*/

const int MAX = 5000005;

int a[MAX];
int pre[MAX];
int suf[MAX];

inline int quick_pow(int base, int exponent, int modulo) {
    int res = 1 % modulo;
    base %= modulo;
    while (exponent) {
        if (exponent & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exponent >>= 1;
    }
    return res;
}

inline int inv(int primal, int modulo) { return quick_pow(primal, modulo - 2, modulo); }

void solve() {
    int n, p, k;
    cin >> n >> p >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    pre[0] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * a[i] % p;
    }
    suf[n + 1] = 1;
    for (int i = n ;i >= 1; i--) {
        suf[i] = suf[i + 1] * a[i] % p;
    }
    int inv_s = inv(pre[n], p);
    int res = 0, kk = 1;
    for (int i = 1; i <= n; i++) {
        kk = kk * k % p;
        res = (res + kk * pre[i - 1] % p * suf[i + 1]) % p;
    }
    res = res * inv_s % p;
    cout << res << endl;
}