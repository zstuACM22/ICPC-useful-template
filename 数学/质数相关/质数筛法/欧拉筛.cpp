// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 欧拉筛(线性筛)
const int MAX = 1000005;
bool vis[MAX] = {0};
int prime[MAX];

// 参数: 筛上界. 返回: 质数个数. 复杂度: O(n)
int prime_sieve_euler(int n) {
    int cnt = 0;
    vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (not vis[i])  // 质数
            prime[cnt++] = i;
        for (int j = 0; j < cnt and prime[j] * i <= n; j++) {
            vis[prime[j] * i] = true;  // 标记i的质数倍为合数
            // 该语句在 prime[j] * i 访问共其 不重复质因子数 次.
            if (i % prime[j] == 0)  // 该语句在 prime[j] * i 访问共其 (总质因子数 - 不重复质因子数) 次.
                break;
            /*  解析:
                如果 i 的质因集包含 prime[j],
                则对于任意 prime[jj] (j < jj < cnt, 即 prime[jj] > prime[j]),
                必有 ii = prime[jj] * i / prime[j] 为整数 且 ii > i,
                这个值 ii (如果 ii <= n) 将在将来被同样的操作,
                因此该做法不会遗漏任何值.

                这个操作保证了所有质数标记操作 vis[prime[j] * i] = true 中,
                prime[j] 是 prime[j] * i 的最小质因数,
                然而每个数 (非1正整数) 有且仅有一个最小质因数,
                因此每个 vis 元素仅被访问一次,
                复杂度为 O(n).  */
        }
    }
    return cnt;
}