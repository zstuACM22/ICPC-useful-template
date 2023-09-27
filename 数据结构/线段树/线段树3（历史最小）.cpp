#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10, inf = 1e18;
// 线段树（区间加法，区间取最大值，
// 维护区间和，区间当前最小值，区间历史最小值）

int n, m;
struct segment_tree {
    struct Node {
        // mina:当前最小  minb:历史最小  se:当前第二小
        int l, r, sum, se, cnt;
        int mina, minb;
        int add1, add2, add1_min, add2_min;
    } tr[N << 1];
    int n = 0, st[N], tot;
    int ls(const int &x) { return tr[x].l; }
    int rs(const int &x) { return tr[x].r; }
    void push_up(int p) {
        tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
        tr[p].minb = min(tr[ls(p)].minb, tr[rs(p)].minb);
        if (tr[ls(p)].mina < tr[rs(p)].mina) {
            tr[p].se = min(tr[rs(p)].mina, tr[ls(p)].se);
            tr[p].mina = tr[ls(p)].mina;
            tr[p].cnt = tr[ls(p)].cnt;
        } else if (tr[ls(p)].mina > tr[rs(p)].mina) {
            tr[p].se = min(tr[ls(p)].mina, tr[rs(p)].se);
            tr[p].mina = tr[rs(p)].mina;
            tr[p].cnt = tr[rs(p)].cnt;
        } else {
            tr[p].se = min(tr[ls(p)].se, tr[rs(p)].se);
            tr[p].mina = tr[ls(p)].mina;
            tr[p].cnt = tr[ls(p)].cnt + tr[rs(p)].cnt;
        }
    }
    void change(int l, int r, int p, int add1, int add2, int add1_min, int add2_min) {
        tr[p].sum += add1 * tr[p].cnt + add2 * (r - l + 1 - tr[p].cnt);
        tr[p].add1_min = min(tr[p].add1_min, tr[p].add1 + add1_min);
        tr[p].add2_min = min(tr[p].add2_min, tr[p].add2 + add2_min);
        tr[p].minb = min(tr[p].minb, tr[p].mina + add1_min);
        tr[p].mina += add1;

        tr[p].add1 += add1;
        tr[p].add2 += add2;
        if (tr[p].se != inf) tr[p].se += add2;
    }
    void push_down(int l, int r, int p, int mid) {
        int minw = min(tr[ls(p)].mina, tr[rs(p)].mina);
        if (minw == tr[ls(p)].mina)
            change(l, mid, ls(p), tr[p].add1, tr[p].add2, tr[p].add1_min, tr[p].add2_min);
        else
            change(l, mid, ls(p), tr[p].add2, tr[p].add2, tr[p].add2_min, tr[p].add2_min);
        if (minw == tr[rs(p)].mina)
            change(mid + 1, r, rs(p), tr[p].add1, tr[p].add2, tr[p].add1_min, tr[p].add2_min);
        else
            change(mid + 1, r, rs(p), tr[p].add2, tr[p].add2, tr[p].add2_min, tr[p].add2_min);
    
        tr[p].add1 = tr[p].add2 = tr[p].add1_min = tr[p].add2_min = 0;
    }
    int build(int p, int l, int r, int st[]) {
        tr[p].add1 = tr[p].add2 = tr[p].add1_min = tr[p].add2_min = 0;
        if (l == r) {
            tr[p].sum = tr[p].mina = tr[p].minb = st[l];
            tr[p].cnt = 1;
            tr[p].se = inf;
            return p;
        }
        int mid = (l + r) >> 1;
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
            tr[p].add1_min = min(tr[p].add1_min, tr[p].add1);
            tr[p].add2_min = min(tr[p].add2_min, tr[p].add2);
            tr[p].mina += k;
            tr[p].minb = min(tr[p].minb, tr[p].mina);
            if (tr[p].se != inf) tr[p].se += k;
            return;
        }
        if (r < L || R < l) return;
        int mid = (l + r) >> 1;
        push_down(l, r, p, mid);
        add(L, R, k, ls(p), l, mid);
        add(L, R, k, rs(p), mid + 1, r);
        push_up(p);                  
    }
    void add(int L, int R, int k) { add(L, R, k, 0, 1, n); }
    // void modify(int L, int R, int k, int p, int l, int r) {
    //     // 会使 min 乱掉
    //     add(L, R, -1e9);
    //     Max(L, R, k);
    // }
    // void modify(int L, int R, int k) { modify(L, R, k, 0, 1, n); }
    void Max(int L, int R, int k, int p, int l, int r) {
        if (r < L || R < l || k <= tr[p].mina) {
            return;
        }
        if (L <= l && r <= R && k < tr[p].se) {
            int dif = tr[p].mina - k;
            tr[p].sum -= tr[p].cnt * dif;
            tr[p].mina = k;
            tr[p].add1 -= dif;
            return;
        }
        int mid = (l + r) >> 1;
        push_down(l, r, p, mid);
        Max(L, R, k, ls(p), l, mid);
        Max(L, R, k, rs(p), mid + 1, r);
        push_up(p);
    }
    void Max(int L, int R, int k) { Max(L, R, k, 0, 1, n); }
    int query_sum(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].sum;
        }
        if (r < L || R < l) return 0;
        int mid = (l + r) >> 1;
        push_down(l, r, p, mid);
        return query_sum(L, R, ls(p), l, mid) + query_sum(L, R, rs(p), mid + 1, r);
    }
    int query_sum(int L, int R) { return query_sum(L, R, 0, 1, n); }
    int query_mina(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].mina;
        }
        if (r < L || R < l) return inf;
        int mid = (l + r) >> 1;
        push_down(l, r, p, mid);
        return min(query_mina(L, R, ls(p), l, mid), query_mina(L, R, rs(p), mid + 1, r));
    }
    int query_mina(int L, int R) { return query_mina(L, R, 0, 1, n); }
    int query_minb(int L, int R, int p, int l, int r) {
        if (L <= l && r <= R) {
            return tr[p].minb;
        }
        if (r < L || R < l) return inf;
        int mid = (l + r) >> 1;
        push_down(l, r, p, mid);
        return min(query_minb(L, R, ls(p), l, mid), query_minb(L, R, rs(p), mid + 1, r));
    }
    int query_minb(int L, int R) { return query_minb(L, R, 0, 1, n); }
} tr;