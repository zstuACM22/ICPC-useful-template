// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Andrew 算法求凸包. 时间: O(nlogn)(排序) + O(n)
const int MAX = 100005;

class Point {
   public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    friend bool operator<(const Point &a, const Point &b) { return a.x < b.x or a.x == b.x and a.y < b.y; }
};

class Vec {
   public:
    int x, y;
    Vec(int x = 0, int y = 0) : x(x), y(y) {}
    Vec(Point a, Point b) : Vec(b.x - a.x, b.y - a.y) {}
    Vec(Point a) : Vec({0, 0}, a) {}

    friend int dot(Vec a, Vec b) { return a.x * b.x + a.y * b.y; }
    friend int cross(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }
    friend int abs2(Vec a) { return a.x * a.x + a.y * a.y; }
    friend bool arrow_equal(Vec a, Vec b) { return a.y * b.x == a.x * b.y; }
};

bool vis[MAX];
int stk[MAX];
int cnt_stk = 0;
Point cvx[MAX];

int convex(Point *a, int n) {
    cnt_stk = 0;
    fill(vis, vis + n, false);
    sort(a, a + n);
    stk[cnt_stk++] = 0;
    for (int i = 1; i < n; i++)
        if (not vis[i]) {
            while (cnt_stk > 1 and cross(Vec(a[stk[cnt_stk - 2]], a[stk[cnt_stk - 1]]), Vec(a[stk[cnt_stk - 1]], a[i])) <= 0)
                vis[stk[--cnt_stk]] = false;
            vis[i] = true;
            stk[cnt_stk++] = i;
        }
    int tmp = cnt_stk;
    for (int i = n - 2; i >= 0; i--)
        if (not vis[i]) {
            while (cnt_stk > tmp and cross(Vec(a[stk[cnt_stk - 2]], a[stk[cnt_stk - 1]]), Vec(a[stk[cnt_stk - 1]], a[i])) <= 0)
                vis[stk[--cnt_stk]] = false;
            vis[i] = true;
            stk[cnt_stk++] = i;
        }
    cnt_stk--;
    for (int i = 0; i < cnt_stk; i++) cvx[i] = a[stk[i]];
    return cnt_stk;
}
