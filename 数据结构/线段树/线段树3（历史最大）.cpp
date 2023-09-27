#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10, inf = 1e18;
// 线段树（区间加法，区间取最小值，
// 维护区间和，区间当前最大值，区间历史最大值）

struct segment_tree {
    struct Node {
        int l, r, sum, maxa, maxb, se, cnt;
        int add1, add2, add3, add4;
    } tr[N << 1];
    int n = 0, st[N], tot;
    int ls(const int &x) { return tr[x].l; }
    int rs(const int &x) { return tr[x].r; }
    void push_up(int p) {
        tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
        tr[p].maxb = max(tr[ls(p)].maxb, tr[rs(p)].maxb);
        if (tr[ls(p)].maxa > tr[rs(p)].maxa) {
            tr[p].se = max(tr[rs(p)].maxa, tr[ls(p)].se);
            tr[p].maxa = tr[ls(p)].maxa;
            tr[p].cnt = tr[ls(p)].cnt;
        } else if (tr[ls(p)].maxa < tr[rs(p)].maxa) {
            tr[p].se = max(tr[ls(p)].maxa, tr[rs(p)].se);
            tr[p].maxa = tr[rs(p)].maxa;
            tr[p].cnt = tr[rs(p)].cnt;
        } else {
            tr[p].se = max(tr[ls(p)].se, tr[rs(p)].se);
            tr[p].maxa = tr[ls(p)].maxa;
            tr[p].cnt = tr[ls(p)].cnt + tr[rs(p)].cnt;
        }
    }
    void change(int l, int r, int p, int add1, int add2, int add3, int add4) {
        tr[p].sum += add1 * tr[p].cnt + add2 * (r - l + 1 - tr[p].cnt);
        tr[p].add3 = max(tr[p].add3, tr[p].add1 + add3);
        tr[p].add1 += add1;
        tr[p].add4 = max(tr[p].add4, tr[p].add2 + add4);
        tr[p].add2 += add2;
        tr[p].maxb = max(tr[p].maxb, tr[p].maxa + add3);
        tr[p].maxa += add1;
        if (tr[p].se != -inf) tr[p].se += add2;
    }
    void push_down(int l, int r, int p, int mid) {
        int maxw = max(tr[ls(p)].maxa, tr[rs(p)].maxa);
        if (maxw == tr[ls(p)].maxa)
            change(l, mid, ls(p), tr[p].add1, tr[p].add2, tr[p].add3, tr[p].add4);
        else
            change(l, mid, ls(p), tr[p].add2, tr[p].add2, tr[p].add4, tr[p].add4);
        if (maxw == tr[rs(p)].maxa)
            change(mid + 1, r, rs(p), tr[p].add1, tr[p].add2, tr[p].add3, tr[p].add4);
        else
            change(mid + 1, r, rs(p), tr[p].add2, tr[p].add2, tr[p].add4, tr[p].add4);
        tr[p].add1 = tr[p].add2 = tr[p].add3 = tr[p].add4 = 0;
    }
    int build(int p, int l, int r, int st[]) {
        tr[p].add1 = tr[p].add2 = tr[p].add3 = tr[p].add4 = 0;
        if (l == r) {
            tr[p].sum = tr[p].maxa = tr[p].maxb = st[l];
            tr[p].add1 = tr[p].add2 = tr[p].add3 = tr[p].add4 = 0;
            tr[p].cnt = 1;
            tr[p].se = -inf;
            return p;
        }
        int mid = l + r >> 1;
        tr[p].l = build(++tot, l, mid, st);
        tr[p].r = build(++tot, mid + 1, r, st);
        push_up(p);
        return p;
    }
    int build(int n, int st[]) {
        this->n = n;
        return build(0, 1, n, st);
    }
    void add(int L, int R, int k, int p, int l, int r) {
        if (L <= l && r <= R) {
            tr[p].sum += k * (r - l + 1);
            tr[p].add1 += k, tr[p].add2 += k;
            tr[p].add3 = max(tr[p].add3, tr[p].add1);
            tr[p].add4 = max(tr[p].add4, tr[p].add2);
            tr[p].maxa += k;
            tr[p].maxb = max(tr[p].maxb, tr[p].maxa);
            if (tr[p].se != -inf) tr[p].se += k;
            return;
        }
        if (r < L || R < l) return;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        add(L, R, k, ls(p), l, mid);
        add(L, R, k, rs(p), mid + 1, r);
        push_up(p);
    }
    void add(int L, int R, int k) { add(L, R, k, 0, 1, n); }
    void Min(int L, int R, int k, int p, int l, int r) {
        if (r < L || R < l || k >= tr[p].maxa) {
            return;
        }
        if (L <= l && r <= R && k > tr[p].se) {
            int dif = tr[p].maxa - k;
            tr[p].sum -= tr[p].cnt * dif;
            tr[p].maxa = k;
            tr[p].add1 -= dif;
            return;
        }
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        Min(L, R, k, ls(p), l, mid);
        Min(L, R, k, rs(p), mid + 1, r);
        push_up(p);
    }
    void Min(int L, int R, int k) { Min(L, R, k, 0, 1, n); }
    int query_sum(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].sum;
        }
        if (r < L || R < l) return 0;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        return query_sum(L, R, ls(p), l, mid) + query_sum(L, R, rs(p), mid + 1, r);
    }
    int query_sum(int L, int R) { return query_sum(L, R, 0, 1, n); }
    int query_maxa(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].maxa;
        }
        if (r < L || R < l) return -inf;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        return max(query_maxa(L, R, ls(p), l, mid), query_maxa(L, R, rs(p), mid + 1, r));
    }
    int query_maxa(int L, int R) { return query_maxa(L, R, 0, 1, n); }
    int query_maxb(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].maxb;
        }
        if (r < L || R < l) return -inf;
        int mid = l + r >> 1;
        push_down(l, r, p, mid);
        return max(query_maxb(L, R, ls(p), l, mid), query_maxb(L, R, rs(p), mid + 1, r));
    }
    int query_maxb(int L, int R) { return query_maxb(L, R, 0, 1, n); }
} tr;
int a[N];

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    tr.build(n, a);
    for (int i = 1; i <= m; ++i) {
        int p;
        cin >> p;
        // 区间加法
        if (p == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            tr.add(l, r, k);
        }
        // 取 min
        else if (p == 2) {
            int l, r, k;
            cin >> l >> r >> k;
            tr.Min(l, r, k);
        }
        // 查询 sum(l, r)
        else if (p == 3) {
            int l, r;
            cin >> l >> r;
            cout << tr.query_sum(l, r) << "\n";
        }
        // 查询 Ai （当前最大值）
        else if (p == 4) {
            int l, r;
            cin >> l >> r;
            cout << tr.query_maxa(l, r) << "\n";
        }
        // 查询 Bi （历史最大值）
        else {
            int l, r;
            cin >> l >> r;
            cout << tr.query_maxb(l, r) << "\n";
        }
    }
    return 0;
}