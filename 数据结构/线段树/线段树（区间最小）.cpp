#include <bits/stdc++.h>
#define int long long
using namespace std;
#define psi pair<string, int>
const int N = 1e5 + 10, MULTITEST = 0, inf = 1e18;
// 线段树（区间取 max，求区间最大）

class segment_tree_min {
   public: 
    int n;
    inline int build(int n, int st[]) {
        this->n = n;
        return build(0, 1, n, st);
    }
    inline void Min(int L, int R, int k) { Min(L, R, k, 0, 1, n); }
    inline int query(int L, int R) { return query(L, R, 0, 1, n); }

   private:
    int tot;
    struct Node {
        int l, r, v, lazy;
    } tr[N * 2];
    inline int ls(const int &x) { return tr[x].l; }
    inline int rs(const int &x) { return tr[x].r; }
    inline void push_up(int p) { 
        tr[p].v = min(tr[ls(p)].v, tr[rs(p)].v);
        tr[p].lazy = max(tr[ls(p)].lazy, tr[rs(p)].lazy);
    }
    inline void push_down(int l, int r, int p, int mid) {
        tr[ls(p)].v = min(tr[ls(p)].v, tr[p].lazy);
        tr[ls(p)].lazy = min(tr[ls(p)].lazy, tr[p].lazy);
        tr[rs(p)].v = min(tr[rs(p)].v, tr[p].lazy);
        tr[rs(p)].lazy = min(tr[rs(p)].lazy, tr[p].lazy);
        tr[p].lazy = inf;
    }
    int build(int p, int l, int r, int st[]) {
        if (l == r) {
            tr[p].v = tr[p].lazy = st[l];
            return p;
        }
        int mid = l + r >> 1;
        tr[p].l = build(++tot, l, mid, st);
        tr[p].r = build(++tot, mid + 1, r, st);
        push_up(p);
        return p;
    }
    void Min(int L, int R, int k, int p, int l, int r) {
        if (L <= l && r <= R) {
            tr[p].v = min(tr[p].v, k);
            tr[p].lazy = min(tr[p].lazy, k);
            return;
        }
        if (r < L || R < l || tr[p].lazy <= k) return;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        Min(L, R, k, ls(p), l, mid);
        Min(L, R, k, rs(p), mid + 1, r);
        push_up(p);
    }
    int query(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].v;
        }
        if (r < L || R < l) return inf;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        return min(query(L, R, ls(p), l, mid), query(L, R, rs(p), mid + 1, r));
    }
} tr;