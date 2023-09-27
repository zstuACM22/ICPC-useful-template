#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define int long long
const int N = 1e5 + 10;
// 线段树（只有区间加法）

struct segment_tree_add {
    struct Node {
        int l, r, v, add;
    } tr[N << 1];
    int n = 0, st[N], tot;
    inline int ls(const int &x) { return tr[x].l; }
    inline int rs(const int &x) { return tr[x].r; }
    inline void push_up(int p) { tr[p].v = tr[ls(p)].v + tr[rs(p)].v; }
    inline void push_down(int l, int r, int p, int mid) {
        tr[ls(p)].v += tr[p].add * (mid - l + 1);
        tr[ls(p)].add += tr[p].add;
        tr[rs(p)].v += tr[p].add * (r - mid);
        tr[rs(p)].add += tr[p].add;
        tr[p].add = 0;
    }
    int build(int p, int l, int r) {
        if (l == r) {
            tr[p].v = st[l];
            return p;
        }
        int mid = l + r >> 1;
        tr[p].l = build(++tot, l, mid);
        tr[p].r = build(++tot, mid + 1, r);
        push_up(p);
        return p;
    }
    inline int build() { return build(0, 1, n); }
    void add(int L, int R, int k, int p, int l, int r) {
        if (L <= l && r <= R) {
            tr[p].v += k * (r - l + 1);
            tr[p].add += k;
            return;
        }
        if (r < L || R < l) return;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        add(L, R, k, ls(p), l, mid);
        add(L, R, k, rs(p), mid + 1, r);
        push_up(p);
    }
    inline void add(int L, int R, int k) { add(L, R, k, 0, 1, n); }
    int query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].v;
        }
        if (r < L || R < l) return 0;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        return query(L, R, ls(p), l, mid) + query(L, R, rs(p), mid + 1, r);
    }
    inline int query(int L, int R) { return query(L, R, 0, 1, n); }
} tr;

signed main() {
    int n, m;
    cin >> n >> m;
    // 这几行别忘了
    tr.n = n;
    for (int i = 1; i <= n; ++i) {
        cin >> tr.st[i];
    }
    tr.build();
    //
    for (int i = 1; i <= m; ++i) {
        int p;
        cin >> p;
        // 区间加法
        if (p == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            tr.add(l, r, k);
        }
        // 查询
        else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r) << "\n";
        }
    }
    return 0;
}