// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Useless - 枚举因数. 参数: x: 原数, res: 因数结果. 返回: 因数个数. 复杂度: O(x^0.5).
int enum_divisors(int x, int res[]) {
    int cnt = 0;
    int oth[128];  // 足够大
    int len = 0;
    for (int i = 1; i <= x / i; i++) {
        if (x % i == 0) {
            res[cnt++] = i;
            oth[len++] = x / i;
        }
    }
    if (res[cnt - 1] == oth[len - 1])
        len--;  // 如果是完全平方数
    for (int i = len - 1; i >= 0; i--)
        res[cnt++] = oth[i];
    return cnt;
}