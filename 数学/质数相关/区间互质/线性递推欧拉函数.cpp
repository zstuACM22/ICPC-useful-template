// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 线性筛法欧拉函数. 求区间[1, x]中与x互质的数的个数, x 遍历 [1, n]. 复杂度: O(n).
const int MAX = 1000005;

bool vis[MAX] = {0};
int prime[MAX];
int euler[MAX];
void euler_linear(int n) {
    int cnt = 0;
    euler[1] = 1;
    vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (not vis[i]) {
            prime[cnt++] = i;
            euler[i] = i - 1;  // 质数
        }
        for (int j = 0; j < cnt and prime[j] * i <= n; j++) {
            vis[prime[j] * i] = true;
            if (i % prime[j] == 0) {
                // 该语句在 prime[j] * i 访问共其 (总质因子数 - 不重复质因子数) 次.
                euler[prime[j] * i] = euler[i] * prime[j];
                break;
            }
            // 该语句在 prime[j] * i 访问共其 不重复质因子数 次.
            euler[prime[j] * i] = euler[i] * (prime[j] - 1);
        }
    }
}