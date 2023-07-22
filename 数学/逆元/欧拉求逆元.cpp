// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Useless - 欧拉定理求逆元. 复杂度: O(log(modulo)) + 预处理: O(log(modulo)) -> O(modulo^0.5)
const int MOD = 1000000007;

// 欧拉函数. 求区间 [1, x] 中与 x 互质的数的个数. 复杂度: O(logx) -> O(x^0.5).
int euler(int x) {
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

int inv(int primal, int modulo = MOD) {
    static int eu = -1, last = -1;
    if (modulo != last)  // 预处理: modulo 变化的时候执行. 如果 modulo 反复变化这里会 TLE.
    {
        eu = euler(modulo) - 1;
        last = modulo;
    }
    int _eu = eu, _primal = primal, res = 1;
    while (_eu > 0) {
        if (_eu & 1)
            res = res * _primal % modulo;
        _eu >>= 1;
        _primal = _primal * _primal % modulo;
    }
    return primal * res % modulo == 1 ? res : 0;
}