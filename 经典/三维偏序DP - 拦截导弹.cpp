// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# [SDOI2011] 拦截导弹

## 题目描述

某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度、并且能够拦截任意速度的导弹，但是以后每一发炮弹都不能高于前一发的高度，其拦截的导弹的飞行速度也不能大于前一发。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。

在不能拦截所有的导弹的情况下，我们当然要选择使国家损失最小、也就是拦截导弹的数量最多的方案。但是拦截导弹数量的最多的方案有可能有多个，如果有多个最优方案，那么我们会随机选取一个作为最终的拦截导弹行动蓝图。

我方间谍已经获取了所有敌军导弹的高度和速度，你的任务是计算出在执行上述决策时，每枚导弹被拦截掉的概率。
*/

const int MAX = 50005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

#define DIS_Z  // 离散化开关

// 空间点集, 0-index
struct Point {
    int x, y, z;  // 坐标
    int idx;      // 答案索引, 0-index
    friend bool operator<(const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
} P[MAX];
pair<int, double> resP[2][MAX];  // 依次存储每次询问的答案, 0-index
int cntP = 0;

// 离散化, 0-index
int Z[MAX];
int cntZ = 0;
#define arcZ(x) (lower_bound(Z, Z + cntZ, (x)) - Z)

// 树状数组, 1-index
namespace TA {
pair<int, double> tr[MAX];
#define lowbit(x) ((x) & -(x))
inline void reset(int idx) {
    for (; idx <= cntZ; idx += lowbit(idx))
        tr[idx] = {0, 0};
}
inline void setmax(int idx, pair<int, double> val) {
    for (; idx <= cntZ; idx += lowbit(idx))
        if (tr[idx].first == val.first)
            tr[idx].second += val.second;
        else if (tr[idx].first < val.first)
            tr[idx] = val;
}
inline pair<int, double> premax(int idx) {
    pair<int, double> res = {0, 0};
    for (; idx; idx -= lowbit(idx))
        if (res.first == tr[idx].first)
            res.second += tr[idx].second;
        else if (res.first < tr[idx].first)
            res = tr[idx];
    return res;
}
}  // namespace TA

// 归并排序, 0-index
namespace MS {
int w;
int idx[MAX];
int tmp[MAX];
void _merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    _merge_sort(l, mid);
    memcpy(tmp + mid + 1, idx + mid + 1, sizeof(int) * (r - mid));
    stable_sort(tmp + mid + 1, tmp + r + 1, [&](int i, int j) -> bool { return P[i].y < P[j].y; });
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r or i <= mid and P[idx[i]].y <= P[tmp[j]].y) {
            int x = idx[i++];
            TA::setmax(arcZ(P[x].z) + 1, resP[w][P[x].idx]);
        } else {
            int x = tmp[j++];
            pair<int, double> p = TA::premax(arcZ(P[x].z) + 1);
            p.first++;
            if (resP[w][P[x].idx].first == p.first)
                resP[w][P[x].idx].second += p.second;
            else if (resP[w][P[x].idx].first < p.first)
                resP[w][P[x].idx] = p;
        }
    }
    for (int i = l; i <= mid; i++)
        TA::reset(arcZ(P[idx[i]].z) + 1);
    _merge_sort(mid + 1, r);
    stable_sort(idx + l, idx + r + 1, [&](int i, int j) -> bool { return P[i].y < P[j].y; });
}
inline void merge_sort(int w) {
    MS::w = w;
    iota(idx, idx + cntP, 0);
    _merge_sort(0, cntP - 1);
}
}  // namespace MS

// 重置
// inline void clear() {
//     for (int i = 0; i < cntP; i++)
//         resP[i] = {0, 0};
//     cntP = 0;
//     cntZ = 0;
// }

// 在三维空间加入计数点 (x, y, z)
inline void add_point(int x, int y, int z) {
    P[cntP] = {x, y, z, cntP};
    cntP++;
    Z[cntZ++] = z;
}

// 解决所有询问
inline void count_all() {
    sort(P, P + cntP);
    sort(Z, Z + cntZ);
    cntZ = unique(Z, Z + cntZ) - Z;
    fill(resP[0], resP[0] + cntP, pair<int, double>{1, 1});
    MS::merge_sort(0);

    for (int i = 0; i < cntP; i++) {
        P[i].x = -P[i].x;
        P[i].y = -P[i].y;
        P[i].z = -P[i].z;
    }
    reverse(P, P + cntP);
    for (int i = 0; i < cntZ; i++) {
        Z[i] = -Z[i];
    }
    reverse(Z, Z + cntZ);
    fill(resP[1], resP[1] + cntP, pair<int, double>{1, 1});
    MS::merge_sort(1);
}

void solve() {
    int n, k;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add_point(i, -x, -y);
    }
    add_point(-INF, -INF, -INF);
    add_point(INF, INF, INF);
    count_all();
    cout << resP[0][cntP - 1].first - 2 << endl;
    double tot = resP[0][cntP - 1].second;
    for (int i = 0; i < n; i++) {
        if (resP[0][i].first + resP[1][i].first == resP[0][cntP - 1].first + 1)
            cout << resP[0][i].second * resP[1][i].second / tot << ' ';
        else
            cout << 0.0 << endl;
    }
    cout << endl;
}

int32_t main() {
#ifdef TEST
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
#endif
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    clock_t start_time = clock();
#endif
    cout << fixed << setprecision(18);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

#ifdef LOCAL
    cout << "Used " << call_count << " Function Calls." << endl;
    cout << "Used " << (int)(clock() - start_time) << " Microseconds of Time." << endl;
#endif
    return 0;
}
