// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 几何类
// 凸包请见下链接
// Source: https://zhuanlan.zhihu.com/p/540420439
const double EPS = -1e12;
const double PI = acos(-1.0);
// 角度用弧度制
struct Vec {
    double x, y;
    Vec() { x = 0, y = 0; }
    Vec(double a, double b) { x = a, y = b; }
    friend istream &operator>>(istream &cin, Vec &a) { return cin >> a.x >> a.y; }
    friend ostream &operator<<(ostream &cout, Vec a) { return cout << a.x << ' ' << a.y; }
    Vec operator-() { return Vec(-x, -y); }
    Vec operator+(Vec a) { return Vec(x + a.x, y + a.y); }
    Vec operator-(Vec a) { return Vec(x - a.x, y - a.y); }
    Vec operator*(double a) { return Vec(x * a, y * a); }
    Vec operator/(double a) { return Vec(x / a, y / a); }
    friend Vec operator*(double a, Vec b) { return Vec(b.x * a, b.y * a); }
    friend Vec operator/(double a, Vec b) { return Vec(b.x / a, b.y / a); }
    Vec operator+=(Vec a) { return Vec(x += a.x, y += a.y); }
    Vec operator-=(Vec a) { return Vec(x -= a.x, y -= a.y); }
    Vec operator*=(double a) { return Vec(x *= a, y *= a); }
    Vec operator/=(double a) { return Vec(x /= a, y /= a); }
    double operator*(Vec a) { return x * a.x + y * a.y; }  // 点积
    double operator^(Vec a) { return x * a.y - y * a.x; }  // 叉积
    bool operator<(Vec a) {
        if (y == 0 and a.y == 0)
            if (x * a.x >= 0)
                return fabs(x) < fabs(a.x);
            else
                return x > 0;
        if (y >= 0 and a.y < 0)
            return true;
        if (y < 0 and a.y >= 0)
            return false;
        if ((*this ^ a) > 0)
            return true;
        else if ((*this ^ a) == 0)
            return fabs(x) < fabs(a.x);
        else
            return false;
    }
    bool operator>(Vec a) {
        if (y == 0 and a.y == 0)
            if (x * a.x >= 0)
                return fabs(x) > fabs(a.x);
            else
                return x < 0;
        if (y < 0 and a.y >= 0)
            return true;
        if (y >= 0 and a.y < 0)
            return false;
        if ((*this ^ a) < 0)
            return true;
        else if ((*this ^ a) == 0)
            return fabs(x) > fabs(a.x);
        else
            return false;
    }
    bool operator==(Vec a) { return x == a.x and y == a.y; }
};

bool is_nan(Vec a) { return isnan(a.x) or isnan(a.y); }
double abs2(Vec a) { return a.x * a.x + a.y * a.y; }
double abs(Vec a) { return sqrt(a.x * a.x + a.y * a.y); }
Vec unit(Vec a) { return a / abs(a); }
Vec turn90(Vec a) { return Vec(-a.y, a.x); }                                                                   // 逆时针旋转 90 度
Vec turn(Vec a, double rad) { return Vec(a.x * cos(rad) - a.y * sin(rad), a.y * cos(rad) + a.x * sin(rad)); }  // 逆时针旋转
double height(Vec a, Vec b1, Vec b2) { return fabs((b1 - a) ^ (b2 - a)) / abs(b1 - b2); }                      // 点线距离

// cos 夹角
double angle_cos(Vec a, Vec b) {
    return a * b / abs(a) / abs(b);
}

// tan 夹角
double angle_tan(Vec a, Vec b) {
    double f = fabs((a.x * b.y - b.x * a.y) / (a.x * b.x + a.y * b.y));
    return angle_cos(a, b) >= 0 ? f : -f;
}

// 直线交点
Vec line_cross(Vec a1, Vec a2, Vec b1, Vec b2) {
    a2 -= a1;
    b2 -= b1;
    return b2 ^ a2 ? a1 + (b2 ^ (b1 - a1)) / (b2 ^ a2) * a2 : Vec(NAN, NAN);
}

// 线段交点
Vec segment_cross(Vec a1, Vec a2, Vec b1, Vec b2) {
    Vec c = line_cross(a1, a2, b1, b2);
    return (a1 - c) * (a2 - c) > 0 or (b1 - c) * (b2 - c) > 0 ? Vec(NAN, NAN) : c;
}