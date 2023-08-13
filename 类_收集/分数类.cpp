// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 分数类
class Frac {
   public:
    int x, y;
    short sign = 1;
    bool is_nan = false, is_inf = false;
    Frac(int a = 0, int b = 1) {
        if (b >= 0)
            x = a, y = b;
        else
            x = -a, y = -b;
        if (x < 0)
            sign = -1, x = -x;
        if (x == 0 and y == 0)
            is_nan = true;
        if (y == 0)
            is_inf = true;
        *this = shrink(*this);
    }
    friend Frac shrink(Frac a) {
        int g = __gcd(a.x, a.y);
        return g > 1 ? Frac(a.x / g, a.y / g) : a;
    }
    friend Frac operator-(Frac a) {
        Frac res = a;
        res.sign = -a.sign;
        return res;
    }
    friend Frac operator+(Frac a, Frac b) { return shrink(Frac(a.sign * a.x * b.y + b.sign * b.x * a.y, a.y * b.y)); }
    friend Frac operator-(Frac a, Frac b) { return shrink(Frac(a.sign * a.x * b.y - b.sign * b.x * a.y, a.y * b.y)); }
    friend Frac operator*(Frac a, Frac b) { return shrink(Frac(a.sign * a.x * b.sign * b.x, a.y * b.y)); }
    friend Frac operator/(Frac a, Frac b) { return shrink(Frac(a.sign * a.x * b.sign * b.y, a.y * b.x)); }
    friend bool operator<(Frac a, Frac b) { return a.sign * a.x * b.y < b.sign * a.y * b.x; }
    friend bool operator>(Frac a, Frac b) { return a.sign * a.x * b.y > b.sign * a.y * b.x; }
    friend bool operator==(Frac a, Frac b) {
        if (a.is_nan or b.is_nan)
            return false;
        return a.sign * a.x * b.y == b.sign * a.y * b.x;
    }
    friend bool operator!=(Frac a, Frac b) { return a.sign * a.x * b.y != b.sign * a.y * b.x; }
    Frac len() { Frac(x, y); }
};