// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
// #pragma GCC optimize(3, "Ofast", "inline")
using namespace std;
 
// 数论分块. 时间: O(n^0.5)
// 数论分块的两种基本思路:
// 1. 对于区间 [l, r], 有 [n / x] = y 相等, 并在此范围内 O(1) 计算贡献, 时间复杂度 O(n^0.5).
// 2. 对于方程 [n / x] = y, 当 x <= n ^ 0.5, 枚举 x 计算所有满足 x 的 y 的贡献; 对于 y <= n ^ 0.5, 枚举 y 计算所有满足 y 的 x 的贡献.
// 对于思路 2 存在重复贡献, 但不存在缺失贡献. 

// 例题 1: 商数求和: F(n) = \sum_{i = 1}{n}{[n / i]}
int math_partition_1(int n) {
    int res = 0;
    int l = 1, r;
    while (l <= n) {
        r = n / (n / l);
        res += (r - l + 1) * (n / l);
        l = r + 1;
    }
    return res;
}

// 例题 2: 余数求和: G(n) = \sum_{i = 1}{n}{k % i}
int math_partition_2(int n, int k) {
    int l = 1, r = 0, res = 0;
    while (l <= n) {
        if (k / l and k / (k / l) < n)
            r = k / (k / l);
        else
            r = n;
        res += (k % l + k % r) * (r - l + 1) / 2;
        l = r + 1;
    }
    cout << res << endl;
}