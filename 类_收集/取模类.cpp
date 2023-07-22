// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 取模类
const int MOD = 10000007;
class ModInt {
    long long val;
    long long qpow(int x, int y) {
        int res = 1;
        while (y) {
            if (y & 1)
                res = res * x % MOD;
            x = x * x % MOD;
            y >>= 1;
        }
        return res;
    }
    long long inv() { return qpow(val, MOD - 2); }

   public:
    ModInt(int val = 0) : val((val % MOD + MOD) % MOD) {}
    friend istream &operator>>(istream &cin, ModInt &x) { return cin >> x.val, x.val = (x.val % MOD + MOD) % MOD, cin; }
    friend ostream &operator<<(ostream &cout, ModInt x) { return cout << x.val; }
    operator int() { return val; }
    friend ModInt operator-(ModInt x) { return (x.val > 0 ? (x = -x.val + MOD) : x); }
    ModInt &operator++() { return (val == MOD - 1 ? (*this = 0) : (*this = val + 1)); }
    ModInt &operator--() { return (val == 0 ? (*this = MOD - 1) : (*this = val - 1)); }
    ModInt &operator+=(ModInt x) { return *this = (val + x.val) % MOD; }
    ModInt &operator-=(ModInt x) { return *this = (val - x.val + MOD) % MOD; }
    ModInt &operator*=(ModInt x) { return *this = (val * x.val) % MOD; }
    ModInt &operator/=(ModInt x) { return *this = (val * x.inv()) % MOD; }
    friend ModInt operator+(ModInt x, ModInt y) { return x += y; }
    friend ModInt operator-(ModInt x, ModInt y) { return x -= y; }
    friend ModInt operator*(ModInt x, ModInt y) { return x *= y; }
    friend ModInt operator/(ModInt x, ModInt y) { return x /= y; }
    friend bool operator==(ModInt x, ModInt y) { return x.val == y.val; }
    friend bool operator!=(ModInt x, ModInt y) { return x.val != y.val; }
    friend bool operator<(ModInt x, ModInt y) { return x.val < y.val; }
    friend bool operator>(ModInt x, ModInt y) { return x.val > y.val; }
    friend bool operator<=(ModInt x, ModInt y) { return x.val <= y.val; }
    friend bool operator>=(ModInt x, ModInt y) { return x.val >= y.val; }
};