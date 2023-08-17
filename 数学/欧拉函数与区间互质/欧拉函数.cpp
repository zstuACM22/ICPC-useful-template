// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 欧拉函数. 求区间 [1, x] 中与 x 互质的数的个数. 时间: O(logx) -> O(x^0.5).
int _euler(int x) {
    if (x < 2)
        return 0;
    int res = x;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0)
                x /= i;
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