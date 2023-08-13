// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 线性递推求逆元. 要求模是质数. 求 [1, range] 所有数的逆元. 复杂度: O(range).
const int MOD = 1000000007;
void inv_liner(int range, int modulo, int res[]) {
    res[1] = 1;
    for (int i = 2; i <= range; i++)
        res[i] = (modulo - modulo / i) * res[modulo % i] % modulo;
}