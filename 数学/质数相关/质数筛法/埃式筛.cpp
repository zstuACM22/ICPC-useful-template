// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Useless - 埃氏筛
const int MAX = 1000005;
bool vis[MAX] = {0};
int prime[MAX];

// 参数: 筛上界. 返回: 质数个数. 复杂度: O(nloglogn).
int prime_sieve_eratosthenes(int n) {
    int cnt = 0;
    vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (not vis[i]) {
            prime[cnt++] = i;
            for (int j = i * i; j <= n; j += i) {
                vis[j] = true;
            }
        }
    }
    return cnt;
}