// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 二维数点. 时间: O(nlogn), 空间: O(n)
// 离线询问二维平面 {(i, j) | x <= i <= xx and y <= j <= yy} 中点的个数
const int MAXN = 100005;
const int MAXD = 10000005;

#define DIS_Y  // 离散化开关

// 平面点集, 0-index
struct Point {
    int x, y;   // 坐标
    int query;  // 是否为查询点, 1 / -1 表示查询点, 0 表示计数点
    int wi;     // 如果为计数点, 表示其点权; 如果为查询点, 表示其答案索引, 0-index
    friend bool operator<(const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return not a.query and b.query;
    }
} P[MAXN * 5];
int cntP = 0;

// 离散化, 0-index
#ifdef DIS_Y
int Y[MAXN * 3];
int cntY = 0;
#define arcY(x) (lower_bound(Y, Y + cntY, (x)) - Y)
#else
int cntY = 0;
#define arcY(x) ((x) + 1)  // 因为可能得到 -1
#endif

// 树状数组, 1-index
#ifdef DIS_Y
int tr[MAXN * 3];
#else
int tr[MAXD];
#endif
#define lowbit(x) ((x) & -(x))
inline void add(int idx, int val) {
    for (; idx <= cntY; idx += lowbit(idx))
        tr[idx] += val;
}
inline int query(int idx) {
    int res = 0;
    for (; idx; idx -= lowbit(idx))
        res += tr[idx];
    return res;
}

// 依次存储每次询问的答案, 0-index
int resQ[MAXN];
int cntQ = 0;

// 重置
inline void clear() {
    for (int i = 0; i < cntP; i++)
        if (not P[i].query)
            add(arcY(P[i].y) + 1, -P[i].wi);
    memset(resQ, 0, sizeof(int) * cntQ);
    cntP = 0;
    cntQ = 0;
    cntY = 0;
}

// 在二维平面加入计数点 (x, y)
inline void add_point(int x, int y, int w = 1) {
    P[cntP++] = {x, y, false, w};
#ifdef DIS_Y
    Y[cntY++] = y;
#else
    cntY = max(cntY, arcY(y) + 1);
#endif
}

// 在二维平面加入询问 {(i, j) | x <= i <= xx and y <= j <= yy}
inline void add_query(int x, int y, int xx, int yy) {
    x--, y--;
    P[cntP++] = {x, y, 1, cntQ};
    P[cntP++] = {x, yy, -1, cntQ};
    P[cntP++] = {xx, y, -1, cntQ};
    P[cntP++] = {xx, yy, 1, cntQ};
#ifdef DIS_Y
    Y[cntY++] = y;
    Y[cntY++] = yy;
#else
    cntY = max(cntY, arcY(yy) + 1);
#endif
    cntQ++;
}

// 解决所有询问
inline void count_all() {
    sort(P, P + cntP);
#ifdef DIS_Y
    sort(Y, Y + cntY);
    cntY = unique(Y, Y + cntY) - Y;
#endif
    for (int i = 0; i < cntP; i++) {
        int idx = arcY(P[i].y) + 1;  // arcY 是 0-index, tr 是 1-index
        if (P[i].query)
            resQ[P[i].wi] += query(idx) * P[i].query;
        else
            add(idx, P[i].wi);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add_point(x, y);
    }
    for (int i = 0; i < m; i++) {
        int x, y, xx, yy;
        cin >> x >> y >> xx >> yy;
        add_query(x, y, xx, yy);
    }
    count_all();
    for (int i = 0; i < cntQ; i++) {
        cout << resQ[i] << endl;
    }
}