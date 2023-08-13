// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 扫描线. 以 平面面积并 为例.时间: O(nlogn)
const int MAX = 100005;

int M[MAX << 1];  // Attention: 二倍内存
int cntM = 0;
int arcM(int x) { return lower_bound(M + 1, M + cntM + 1, x) - M; }

struct Line {
    int x1, x2, y, val;
} line[MAX << 1];  // Attention: 二倍内存
int cntL = 0;

struct ST {
    int len = 0;
    int cnt = 0;
} tr[MAX << 3];  // Attention: 八倍内存

#define ls(idx) ((idx) << 1)
#define rs(idx) ((idx) << 1 | 1)

void push_up(int idx, int left, int right) {
    if (tr[idx].cnt)
        tr[idx].len = M[right + 1] - M[left];
    else if (left < right)
        tr[idx].len = tr[ls(idx)].len + tr[rs(idx)].len;
    else
        tr[idx].len = 0;
}

void build(int idx, int left, int right) {
    if (left == right) {
        tr[idx].len = 0;
        tr[idx].cnt = 0;
        return;
    }
    int mid = left + right >> 1;
    build(ls(idx), left, mid);
    build(rs(idx), mid + 1, right);
    push_up(idx, left, right);
}
void build(int n) { build(1, 1, n - 1); }

void modify(int l, int r, int val, int idx, int left, int right) {
    if (l <= left and right <= r) {
        tr[idx].cnt += val;
        push_up(idx, left, right);
        return;
    }
    int mid = left + right >> 1;
    if (l <= mid) modify(l, r, val, ls(idx), left, mid);
    if (mid < r) modify(l, r, val, rs(idx), mid + 1, right);
    push_up(idx, left, right);
}
void modify(int n, int l, int r, int val) { modify(arcM(l), arcM(r) - 1, val, 1, 1, n - 1); }

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, xx, yy;
        cin >> x >> y >> xx >> yy;
        line[cntL++] = {x, xx, y, 1};
        line[cntL++] = {x, xx, yy, -1};
        M[++cntM] = x;
        M[++cntM] = xx;
    }
    sort(line, line + cntL, [](Line x, Line y) -> bool { return x.y < y.y; });
    sort(M + 1, M + cntM + 1);
    cntM = unique(M + 1, M + cntM + 1) - M - 1;
    build(cntM);
    int pre = 0, res = 0;
    for (int i = 0; i < cntL; i++) {
        res += tr[1].len * (line[i].y - pre);
        modify(cntM, line[i].x1, line[i].x2, line[i].val);
        pre = line[i].y;
    }
    cout << res << endl;
}