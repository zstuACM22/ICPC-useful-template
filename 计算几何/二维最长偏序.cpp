// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAXN = 100005;
const int MAXD = 10000005;

#define DIS_Y  // 离散化开关

// 平面点集, 0-index
struct Point {
    int x, y;  // 坐标
    int idx;   // 答案索引, 0-index
    friend bool operator<(const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }
} P[MAXN];
int cntP = 0;

// 离散化, 0-index
#ifdef DIS_Y
int Y[MAXN];
int cntY = 0;
#define arcY(x) (lower_bound(Y, Y + cntY, x) - Y)
#else
int cntY = 0;
#define arcY(x) (x)
#endif

// 树状数组, 1-index
#ifdef DIS_Y
int tr[MAXN];
#else
int tr[MAXD];
#endif
#define lowbit(x) ((x) & -(x))
void add(int idx, int x) {
    for (; idx <= cntY; idx += lowbit(idx))
        tr[idx] = max(tr[idx], x);
}
int query(int idx) {
    int res = 0;
    for (; idx; idx -= lowbit(idx))
        res = max(res, tr[idx]);
    return res;
}

// 在二维平面加入点 (x, y)
void add_point(int x, int y) {
    P[cntP] = {x, y, cntP};
    cntP++;
#ifdef DIS_Y
    Y[cntY++] = y;
#else
    cntY = max(cntY, arcY(y) + 1);
#endif
}

// 解决所有询问, 对于每个点求从原点到该点的最长偏序 (不含原点)
int resP[MAXN];  // 依次存储每次询问的答案, 0-index
void count_all() {
    sort(P, P + cntP);
#ifdef DIS_Y
    sort(Y, Y + cntY);
    cntY = unique(Y, Y + cntY) - Y;
#endif
    for (int i = 0; i < cntP; i++) {
        int idx = arcY(P[i].y) + 1, x = query(idx) + 1;
        add(idx, x);
        resP[P[i].idx] = x;
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add_point(x, y);
    }
    count_all();
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, resP[i]);
    }
    cout << res << endl;
}