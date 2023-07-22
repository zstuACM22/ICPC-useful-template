// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# [SCOI2010]传送带

## 题目描述

在一个 $2$ 维平面上有两条传送带，每一条传送带可以看成是一条线段。两条传送带分别为线段 $\text{AB}$ 和线段 $\text{CD}$。lxhgww 在 $\text{AB}$ 上的移动速度为 $P$，在 $\text{CD}$ 上的移动速度为 $Q$，在平面上的移动速度 $R$。现在 lxhgww 想从 $\text A$ 点走到 $\text D$ 点，他想知道最少需要走多长时间。

## 输入格式

第一行 $4$ 个整数，表示 $\text A$ 和 $\text B$ 的坐标，分别为 $A_x$，$A_y$，$B_x$，$B_y$。

第二行 $4$ 个整数，表示 $\text C$ 和 $\text D$ 的坐标，分别为 $C_x$，$C_y$，$D_x$，$D_y$。

第三行 $3$ 个整数，分别是 $P$，$Q$，$R$。

## 输出格式

输出数据为一行，表示 lxhgww 从 $\text A$ 点走到 $\text D$ 点的最短时间，保留到小数点后 $2$ 位。

## 样例 #1

### 样例输入 #1

```
0 0 0 100
100 0 100 100
2 2 1
```

### 样例输出 #1

```
136.60
```

## 提示

对于 $100\%$ 的数据，$1\le A_x,A_y,B_x,B_y,C_x,C_y,D_x,D_y\le10^3$，$1\le P,Q,R\le10$。
*/

const double EPS = 1e-9;
using pdd = pair<double, double>;
double p, q, r;

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    Point() : Point(0, 0) {}
    friend istream &operator>>(istream &cin, Point &a) { return cin >> a.x >> a.y; }
    friend Point mid(Point a, Point b, double lambda = 0.5) { return Point(lambda * a.x + (1 - lambda) * b.x, lambda * a.y + (1 - lambda) * b.y); }
    friend double dis(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }
} A, B, C, D;

double calc(double lambda, double mu) {
    Point S = mid(A, B, lambda);  // S: 离开传送带 AB 的点
    Point T = mid(C, D, mu);      // T: 离开传送带 CD 的点
    return dis(A, S) / p + dis(T, D) / q + dis(S, T) / r;
}

// 当 lambda 最优, 关于 mu, calc() 为凹函数
double triple_search_mu(double lambda) {
    double l = 0, r = 1;
    while (r - l >= EPS) {
        double m = (l + r) / 2;
        if (calc(lambda, m - EPS) > calc(lambda, m + EPS)) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

// 当 mu 最优, 关于 lambda, calc() 为凹函数
pdd triple_search() {
    double l = 0, r = 1;
    while (r - l >= EPS) {
        double m = (l + r) / 2;
        if (calc(m - EPS, triple_search_mu(m - EPS)) > calc(m + EPS, triple_search_mu(m + EPS))) {
            l = m;
        } else {
            r = m;
        }
    }
    return {l, triple_search_mu(l)};
}

void solve() {
    cin >> A >> B >> C >> D;
    cin >> p >> q >> r;
    pdd x = triple_search();
    cout << calc(x.first, x.second) << endl;
}