// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 三维数点. 时间: O(nlognlogn), 空间: O(n)
// 离线询问三维空间 {(i, j, k) | 0 <= i <= x and 0 <= j <= y and 0 <= k <= z} 中点的个数
// 如果要将询问由前缀改区间, 别忘改空间大小
const int MAXN = 100005;
const int MAXD = 10000005;

#define DIS_Z  // 离散化开关

// 空间点集, 0-index
struct Point {
    int x, y, z;  // 坐标
    bool query;   // 是否为查询点, 1 / -1 表示查询点, 0 表示计数点
    int idx;      // 答案索引, 0-index
    friend bool operator<(const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        if (a.z != b.z) return a.z < b.z;
        return not a.query and b.query;
    }
} P[MAXN * 2];  // } P[MAXN * 9];
int cntP = 0;

// 依次存储每次询问的答案, 0-index
int resQ[MAXN];
int cntQ = 0;

// 离散化, 0-index
#ifdef DIS_Z
int Z[MAXN * 2];  // int Z[MAXN * 3];
int cntZ = 0;
#define arcZ(x) (lower_bound(Z, Z + cntZ, (x)) - Z)
#else
int cntZ = 0;
#define arcZ(x) ((x) + 1)  // 因为可能得到 -1
#endif

// 树状数组, 1-index
namespace TA {
#ifdef DIS_Z
int tr[MAXN * 2];  // int tr[MAXN * 3];
#else
int tr[MAXD];
#endif
#define lowbit(x) ((x) & -(x))
inline void add(int idx, int val) {
    for (; idx <= cntZ; idx += lowbit(idx))
        tr[idx] += val;
}
inline int query(int idx) {
    int res = 0;
    for (; idx; idx -= lowbit(idx))
        res += tr[idx];
    return res;
}
}  // namespace TA

// 归并排序, 0-index
namespace MS {
int idx[MAXN * 2];  // int idx[MAXN * 9];
int tmp[MAXN * 2];  // int tmp[MAXN * 9];
void _merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    _merge_sort(l, mid);
    _merge_sort(mid + 1, r);
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++)
        if (j > r or i <= mid and P[idx[i]].y <= P[idx[j]].y) {
            tmp[k] = idx[i++];
            if (not P[tmp[k]].query)
                TA::add(arcZ(P[tmp[k]].z) + 1, 1);
        } else {
            tmp[k] = idx[j++];
            if (P[tmp[k]].query)
                resQ[P[tmp[k]].idx] += TA::query(arcZ(P[tmp[k]].z) + 1);
        }
    for (int i = l; i <= mid; i++)
        if (not P[idx[i]].query)
            TA::add(arcZ(P[idx[i]].z) + 1, -1);
    memcpy(idx + l, tmp + l, sizeof(int) * (r - l + 1));
}
inline void merge_sort() {
    iota(idx, idx + cntP, 0);
    _merge_sort(0, cntP - 1);
}
}  // namespace MS

// 在三维空间加入计数点 (x, y, z)
inline void add_point(int x, int y, int z) {
    P[cntP++] = {x, y, z, false, 0};
#ifdef DIS_Z
    Z[cntZ++] = z;
#else
    cntZ = max(cntZ, arcZ(z) + 1);
#endif
}

// 在三维空间加入询问 {(i, j, k) | 0 <= i <= x and 0 <= j <= y and 0 <= k <= z}
inline void add_query(int x, int y, int z) {
    P[cntP++] = {x, y, z, true, cntQ++};
#ifdef DIS_Z
    Z[cntZ++] = z;
#else
    cntZ = max(cntZ, arcZ(z) + 1);
#endif
}

// 解决所有询问
inline void count_all() {
    sort(P, P + cntP);
#ifdef DIS_Z
    sort(Z, Z + cntZ);
    cntZ = unique(Z, Z + cntZ) - Z;
#endif
    MS::merge_sort();
}

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add_point(x, y, z);
        add_query(x, y, z);
    }
    count_all();
    for (int i = 0; i < n; i++) {
        cout << resQ[i] << endl;
    }
}