// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MOD = 1000000007;
const int SQR = 65536;  // 严格大小 sqrt(euler(MOD) * 2)

int euler_modulo, gcd_base_modulo, size_block;
int size_pow[SQR];
int base_pow[SQR];

// 欧拉函数. 复杂度: O(logx) -> O(sqrt(x)).
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

// 光速幂预处理. 基于分块, 时间复杂度: O(sqrt(euler(base)))
void load_supper_pow(int base) {
    base %= MOD;
    ::euler_modulo = euler(MOD);
    ::gcd_base_modulo = __gcd(base, MOD);
    ::size_block = sqrt(euler_modulo * 2);
    base_pow[0] = 1;
    for (int i = 1; i <= size_block; i++)
        base_pow[i] = base_pow[i - 1] * base % MOD;
    size_pow[0] = 1;
    for (int i = 1, lim = euler_modulo * 2 / size_block; i <= lim; i++)
        size_pow[i] = size_pow[i - 1] * base_pow[size_block] % MOD;
}

// 光速幂 + 扩展欧拉定理. 时间复杂度: O(1)
int supper_pow(int exponent) {
    if (exponent < euler_modulo)
        ;
    else if (gcd_base_modulo == 1)
        exponent = exponent % euler_modulo;
    else
        exponent = exponent % euler_modulo + euler_modulo;
    return size_pow[exponent / size_block] * base_pow[exponent % size_block] % MOD;
}