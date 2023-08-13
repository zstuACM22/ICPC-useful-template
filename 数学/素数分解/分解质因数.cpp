// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 分解质因数 - 线性筛优化. 时间：O(log(x)) -> O(x^0.5/ln(x))
// 不用线性筛优化版本时间: O(log(x)) -> O(x^0.5)
const int MAX = 100005;

bool vis[MAX] = {0};
int prime[MAX];                // 质数
pair<int, int> divisors[MAX];  // {质因数, 个数}

// 参数: 筛上界. 返回: 质数个数. 复杂度: O(n)
int prime_sieve_euler(int n) {
    int cnt = 0;
    vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (not vis[i])
            prime[cnt++] = i;  // 质数
        for (int j = 0; j < cnt and prime[j] * i <= n; j++) {
            vis[prime[j] * i] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    return cnt;
}

// 分解质因数. 参数: x: 原数. 返回: 互异质因数个数.
int prime_divisors(int x) {
    int cnt = 0;
    for (int i = 0; prime[i] <= x / prime[i]; i++)
        if (x % prime[i] == 0) {
            divisors[cnt] = {prime[i], 0};
            while (x % prime[i] == 0) {
                x /= prime[i];
                divisors[cnt].second++;
            }
            cnt++;
        }
    if (x > 1)
        divisors[cnt++] = {x, 1};
    return cnt;
}