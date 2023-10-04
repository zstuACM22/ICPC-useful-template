#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX = 1e5;
const int N = MAX + 10, Q = N, MULTITEST = 0, ED = N + 4 * Q + 10;

#define DISCRETIZE              // 离散化开关
const int query_priority = -2;  // 修改/询问优先度开关

// 二维数点问题
// 离线数据结构（思想类似于扫描线）
// 时间复杂度 O(n ㏒n)
/* 用法：
0. 确定要开的空间大小：N 是点的个数，Q 是询问的矩阵个数，ED 是每个点 x 的右界（树状数组大小）
（离散化 ED 是 N + 4 * Q, 不离散化 ED 由题目给出）（ED 本身需 +10 避免由 x++ 等情况带来的错误）
1. 同一点，如果修改优先询问，query_priority = -2，询问优先修改，query_priority = 2
2. 如果 x 的范围特别大（或者有负数），需要打开离散化开关 #define DISCRETIZE，离散化 x
3. 用 join_kind 加入表示种类的数组（x, y 可以为 0），可带权
4. 用 add_rectangle 加入询问的区间
5. x 和 y 因为离散化/自增发生了改变，如果需要用坐标计算需要另外开变量记录真实值
6. 直接 out 就可以输出每个矩阵内包含的点的个数了
*/

// 应用：
// 0. 求平面中被一个矩阵框住的点的个数
// 1. 求出区间 [l,r] 内大小在 [x,y] 范围内的数的个数。
// 2. 求一棵树的深度和点的个数有关问题
// 3. 求区间种类数（把上一个同种类出现的位置记为 y）（有板子）
/* 4. 求区间点对问题，如：求区间有无两数(相加/相乘/异或等)的结果是 x 的数。
（自己位置记为 x, 另一对位置记为 y, 查询 (l, 0) 到 (r, r) 这一矩阵即可）*/

class Count_point_2D {
   public:
    void add_point(int x, int y, int val = 1) {
        a[++cnt] = {x + 1, y + 1, val, query_priority};
    }
    void add_rectangle(int x_1, int y_1, int x_2, int y_2) {
        ++x_2, ++y_2, ++qcnt;
        a[++cnt] = {x_1, y_1, qcnt, 1};
        a[++cnt] = {x_1, y_2, qcnt, -1};
        a[++cnt] = {x_2, y_1, qcnt, -1};
        a[++cnt] = {x_2, y_2, qcnt, 1};
    }
    void solve() {
        solved = 1;
#ifdef DISCRETIZE
        discretize();
#endif
        sort(a + 1, a + 1 + cnt, [](const Node &a, const Node &b) {
            return a.y < b.y || (a.y == b.y && (a.x < b.x || (a.x == b.x && a.type < b.type)));
        });
        for (int i = 1; i <= cnt; ++i) {
            if (a[i].type == query_priority) {
#ifdef DISCRETIZE
                add(a[i].x, a[i].ind, cnt);
#else
                add(a[i].x, a[i].ind, ED);
#endif
                continue;
            }
            ans[a[i].ind] += a[i].type * query(a[i].x);
        }
        if (MULTITEST) init();
    }
    void out() {
        if (!solved) solve();
        for (int i = 1; i <= qcnt; ++i) {
            cout << ans[i] << "\n";
        }
    }
    void init() {
        for (int i = 1; i <= cnt; ++i) {
            if (a[i].type == query_priority)
#ifdef DISCRETIZE
                add(a[i].x, -a[i].ind, cnt);
#else
                add(a[i].x, -a[i].ind, ED);
#endif
        }
        for (int i = 1; i <= qcnt; ++i) ans[i] = 0;
        cnt = qcnt = solved = 0;
    }

   private:
    int cnt = 0, qcnt = 0;
    bool solved = 0;
    struct Node {
        // ind 是点的 val，矩阵的 indx
        int x, y, ind, type;
    } a[N + Q * 4];
    int tr[ED + 10], ans[Q];
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, int v, int ed) {
        for (int i = x; i <= ed; i += lowbit(i)) {
            tr[i] += v;
        }
    }
    int query(int x) {
        int ans = 0;
        for (int i = x; i; i -= lowbit(i)) {
            ans += tr[i];
        }
        return ans;
    }
    void discretize() {
        static int temp[N + Q * 4 + 10];
        for (int i = 1; i <= cnt; ++i) {
            temp[i] = a[i].x;
        }
        sort(temp + 1, temp + 1 + cnt);
        int nt = unique(temp + 1, temp + 1 + cnt) - temp - 1;
        for (int i = 1; i <= cnt; ++i) {
            a[i].x = lower_bound(temp + 1, temp + 1 + nt, a[i].x) - temp;
        }
    }
} cp2d;

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        cp2d.add_point(x, y, w);
    }
    for (int i = 1; i <= m; ++i) {
        int x_1, y_1, x_2, y_2;
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        cp2d.add_rectangle(x_1, y_1, x_2, y_2);
    }
    cp2d.out();
}