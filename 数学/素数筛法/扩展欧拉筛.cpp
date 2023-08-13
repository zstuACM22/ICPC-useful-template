// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扩展欧拉筛(线性筛) 求最小质因数 / 莫比乌斯函数
const int MAX = 1000005;
bool vis[MAX] = {0};
int minfac[MAX] = {0};     // 最小质因数
int8_t mobius[MAX] = {0};  // 莫比乌斯函数
int prime[MAX];

int prime_sieve_euler(int n) {
    int cnt = 0;
    vis[1] = true;
    minfac[1] = 0;  // 特殊标记
    mobius[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (not vis[i]) {
            prime[cnt++] = i;
            minfac[i] = i;
            mobius[i] = -1;
        }
        for (int j = 0; j < cnt and prime[j] * i <= n; j++) {
            vis[prime[j] * i] = true;
            minfac[prime[j] * i] = prime[j];
            if (i % prime[j] == 0) {
                mobius[prime[j] * i] = 0;
                break;
            }
            mobius[prime[j] * i] = -mobius[i];
        }
    }
    return cnt;
}