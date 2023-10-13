// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 三维最长偏序. 时间: O(nlognlogn), 空间: O(n)
// 计算三维空间中以每点结束的最长偏序, 要求不存在重合点
const int MAXN = 100005;
const int MAXD = 10000005;

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
} P[MAXN];
int resP[MAXN];  // 依次存储每次询问的答案, 0-index
int dp[2][MAXN];
int cntP = 0;

// 离散化, 0-index
#ifdef DIS_Z
int Z[MAXN];
int cntZ = 0;
#define arcZ(x) (lower_bound(Z, Z + cntZ, (x)) - Z)
#else
int cntZ = 0;
#define arcZ(x) (x)
#endif

// 树状数组, 1-index
namespace TA {
#ifdef DIS_Z
int tr[MAXN];
#else
int tr[MAXD];
#endif
#define lowbit(x) ((x) & -(x))
inline void reset(int idx) {
    for (; idx <= cntZ; idx += lowbit(idx))
        tr[idx] = 0;
}
inline void setmax(int idx, int val) {
    for (; idx <= cntZ; idx += lowbit(idx))
        tr[idx] = max(tr[idx], val);
}
inline int premax(int idx) {
    int res = 0;
    for (; idx; idx -= lowbit(idx))
        res = max(res, tr[idx]);
    return res;
}
}  // namespace TA

// 归并排序, 0-index
namespace MS {
int idx[MAXN];
int tmp[MAXN];
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
            TA::setmax(arcZ(P[x].z) + 1, resP[P[x].idx]);
        } else {
            int x = tmp[j++];
            resP[P[x].idx] = max(resP[P[x].idx], TA::premax(arcZ(P[x].z) + 1) + 1);
        }
    }
    for (int i = l; i <= mid; i++)
        TA::reset(arcZ(P[idx[i]].z) + 1);
    _merge_sort(mid + 1, r);
    stable_sort(idx + l, idx + r + 1, [&](int i, int j) -> bool { return P[i].y < P[j].y; });
}
inline void merge_sort() {
    iota(idx, idx + cntP, 0);
    _merge_sort(0, cntP - 1);
}
}  // namespace MS

// 重置
inline void clear() {
    for (int i = 0; i < cntP; i++)
        resP[i] = 0;
    cntP = 0;
    cntZ = 0;
}

// 在三维空间加入计数点 (x, y, z)
inline void add_point(int x, int y, int z) {
    P[cntP] = {x, y, z, cntP};
    cntP++;
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
    fill(resP, resP + cntP, 1);
    MS::merge_sort();
}

void solve() {
    int n, k;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add_point(i, -x, -y);
    }
    count_all();
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, resP[i]);
    }
    cout << res << endl;
    for (int i = 0; i < n; i++) {
        cout << 0 << ' ';
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
