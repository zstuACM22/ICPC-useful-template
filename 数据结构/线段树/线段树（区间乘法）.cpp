#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define int long long
const int N = 1e5 + 10;
// 线段树（支持区间加减乘，区间查询）

int mod;
struct segment_tree_muti {
    struct Node {
        int l, r, v, add, mul = 1;
    } tr[N << 1];
    int n, st[N], tot;
    inline int ls(const int &x) { return tr[x].l; }
    inline int rs(const int &x) { return tr[x].r; }
    inline void push_up(int p) { tr[p].v = (tr[ls(p)].v + tr[rs(p)].v) % mod; }
    inline void push_down(int l, int r, int p, int mid) {
        tr[ls(p)].v = tr[ls(p)].v * tr[p].mul % mod;
        tr[ls(p)].v = (tr[ls(p)].v + tr[p].add * (mid - l + 1) % mod) % mod;
        tr[ls(p)].mul = tr[ls(p)].mul * tr[p].mul % mod;
        tr[ls(p)].add = (tr[ls(p)].add * tr[p].mul) % mod;
        tr[ls(p)].add = (tr[ls(p)].add + tr[p].add) % mod;
        tr[rs(p)].v = tr[rs(p)].v * tr[p].mul % mod;
        tr[rs(p)].v = (tr[rs(p)].v + tr[p].add * (r - mid) % mod) % mod;
        tr[rs(p)].mul = tr[rs(p)].mul * tr[p].mul % mod;
        tr[rs(p)].add = (tr[rs(p)].add * tr[p].mul) % mod;
        tr[rs(p)].add = (tr[rs(p)].add + tr[p].add) % mod;
        tr[p].add = 0;
        tr[p].mul = 1;
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
            tr[p].v = (tr[p].v + k * (r - l + 1) % mod) % mod;
            tr[p].add = (tr[p].add + k) % mod;
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
    void mul(int L, int R, int k, int p, int l, int r) {
        if (L <= l && r <= R) {
            tr[p].v = tr[p].v * k % mod;
            tr[p].add = tr[p].add * k % mod;
            tr[p].mul = tr[p].mul * k % mod;
            return;
        }
        if (r < L || R < l) return;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        mul(L, R, k, ls(p), l, mid);
        mul(L, R, k, rs(p), mid + 1, r);
        push_up(p);
    }
    inline void mul(int L, int R, int k) { mul(L, R, k, 0, 1, n); }
    int query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) return tr[p].v;
        if (r < L || R < l) return 0;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        return (query(L, R, ls(p), l, mid) + query(L, R, rs(p), mid + 1, r)) % mod;
    }
    inline int query(int L, int R) { return query(L, R, 0, 1, n); }
} tr;

signed main() {
    int n, m;
    cin >> n >> m >> mod;
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
        // 区间乘除
        if (p == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            tr.mul(l, r, k);
        }
        // 区间加减
        else if (p == 2) {
            int l, r, k;
            cin >> l >> r >> k;
            tr.add(l, r, k);
        }
        // 区间查询
        else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r) << "\n";
        }
    }
    return 0;
}