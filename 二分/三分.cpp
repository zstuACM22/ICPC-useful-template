// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 函数三分. 两种三分充要条件:
// 1. 函数二阶导数恒大于等于或小于等于 0
// 2. 函数有唯一极值点
const double EPS = 1e-9;

double calc(double x) {
    ;  // 表达式必须为凸函数
}

double triple_search(double l, double r) {
    while (r - l >= EPS) {
        double m = (l + r) / 2;
        // 表达式若为凹函数, 此处 < 改 >
        if (calc(m - EPS) < calc(m + EPS)) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}