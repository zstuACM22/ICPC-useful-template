// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# 齿轮

## 题目描述

Daniel13265 从不知哪里找来了 $n$ 个齿轮，第 $i$ 个齿轮的齿数为不超过 $m$ 的正整数 $a_i$。他现在想把其中 $k$ 个齿轮按照一定的方式拼接在一起。

当齿轮使用一段时间后，就会产生损耗。一个齿轮组的损耗速率是由这个齿轮组的所有齿轮齿数的最大公约数决定的：最大公约数越大，相同的齿之间啮合的频率就会增高，从而损耗的速率就会变快。这个最大公约数又被称为损耗因子。

算出一个齿轮组的损耗因子是很容易的。可是现在 Daniel13265 想要知道，对于可能拼接出的所有齿轮组的损耗因子。

Daniel13265 知道拼接出损耗因子大于 $m$ 的齿轮组是不可能的，而且由于可能拼出的齿轮组的个数很多，你只需要反过来告诉他对于所有的 $t\in[1, m]$，能够拼接出的损耗因子为 $t$ 的齿轮组的个数对 $10^9+7$ 取模后的结果即可。

## 输入格式

输入共 $2$ 行。
  
第一行包含三个正整数 $n,m,k$，分别表示 Daniel13265 拥有的齿轮个数，齿轮齿数的最大可能值与 Daniel13265 期望的齿轮组的齿轮个数。  
第二行共 $n$ 个用单个空格隔开的正整数，第 $i$ 个数 $a_i$ 表示第 $i$ 个齿轮的齿数。

## 输出格式

输出一行 $m$ 个整数，第 $t$ 个数表示能够拼接出的损耗因子为 $t$ 的齿轮组的个数对 $10^9+7$ 取模后的结果。

## 样例 #1

### 样例输入 #1

```
5 6 2
1 2 3 4 6
```

### 样例输出 #1

```
6 3 1 0 0 0
```

## 提示

### 样例解释

损耗因子为 $1$ 的齿轮组有 $(1,2),(1,3),(1,4),(1,6),(2,3),(3,4)$ 共 $6$ 个；  
损耗因子为 $2$ 的齿轮组有 $(2,4),(2,6),(4,6)$ 共 $3$ 个；  
损耗因子为 $3$ 的齿轮组有 $(3,6)$ 共 $1$ 个。

对于 $100\%$ 的数据，满足 $1\le k\le n\le10^6$，$1\le a_i\le m\le10^6$。
*/

const int MAX = 1000006;
const int MOD = 1000000007;

// 预处理逆元
int inv[MAX];
void load_inv(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

// 预处理阶乘
int fac[MAX];
void load_fac(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % MOD;
}

// 预处理阶乘的逆元
int ifc[MAX];
void load_ifc(int n) {
    ifc[0] = 1;
    for (int i = 1; i <= n; i++)
        ifc[i] = ifc[i - 1] * inv[i] % MOD;
}

// 询问排列数与组合数
int A(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[n] % MOD : 0; }
int C(int m, int n) { return 0 <= n and n <= m ? fac[m] * ifc[n] % MOD * ifc[m - n] % MOD : 0; }

int buk[MAX];
int cnt_mul[MAX];
int dp[MAX];

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    load_inv(n);
    load_fac(n);
    load_ifc(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        buk[x]++;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j += i) {
            cnt_mul[i] += buk[j];
        }
    }
    for (int i = m; i >= 1; i--) {
        dp[i] = C(cnt_mul[i], k);
        for (int j = i * 2; j <= m; j += i) {
            dp[i] = (dp[i] - dp[j] + MOD) % MOD;
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << dp[i] << ' ';
    }
    cout << endl;
}